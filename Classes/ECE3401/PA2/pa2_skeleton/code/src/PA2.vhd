library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.itype_pkg.all;

entity PA2 is
    generic (
        MEM_INIT_FILE : string := "RType_ADD.out"
    );
    port (
        clk_in : in  std_logic;
        rst_in : in  std_logic;
        terminate : out std_logic
    );
end entity PA2;

architecture Behavioral of PA2 is

    -- =====================================================
    -- Internal Signals
    -- =====================================================
    signal instruction   : std_logic_vector(31 downto 0);
    signal regf_rd1      : std_logic_vector(31 downto 0);
    signal regf_rd2      : std_logic_vector(31 downto 0);
    signal immediate_out : std_logic_vector(31 downto 0);
    signal regf_wd       : std_logic_vector(31 downto 0);

    signal ALUSrcB       : std_logic;
    signal PCSrc         : std_logic;
    signal RegWrite      : std_logic;
    signal MemWrite      : std_logic;
    signal MemRead       : std_logic;
    signal WBSrc         : std_logic;
    signal alu_contrl    : std_logic_vector(2 downto 0);

    signal dmem_addr     : std_logic_vector(31 downto 0);
    signal data_mem_out  : std_logic_vector(31 downto 0);

    signal bne           : std_logic;
    signal pc_en         : std_logic;
    signal inst_addr     : std_logic_vector(31 downto 0);
    signal inst_addr_shifted    : std_logic_vector(31 downto 0);

    signal inst_type : instruction_type := INVALID;

    -- =====================================================
    -- Component Declarations
    -- =====================================================

    component Imem_Dmem
        generic (
            MEM_INIT_FILE : string := "RType_ADD.out"
        );
        port (
            clk          : in  std_logic;
            inst_address : in  std_logic_vector(31 downto 0);
            data_address : in  std_logic_vector(31 downto 0);
            write_data   : in  std_logic_vector(31 downto 0);
            MemWrite     : in  std_logic;
            MemRead      : in  std_logic;
            terminate    : in  std_logic;
            inst_mem_out : out std_logic_vector(31 downto 0);
            data_mem_out : out std_logic_vector(31 downto 0)
        );
    end component;

    component register_file
        generic (
            DATA_WIDTH    : integer := 32;
            ADDR_WIDTH    : integer := 5;
            MEM_INIT_FILE : string  := "RType_ADD.out"
        );
        port (
            write_data : in  std_logic_vector(31 downto 0);
            rs1        : in  std_logic_vector(4 downto 0);
            rs2        : in  std_logic_vector(4 downto 0);
            rd         : in  std_logic_vector(4 downto 0);
            we         : in  std_logic;
            clk        : in  std_logic;
            rst        : in  std_logic;
            terminate  : in  std_logic;
            read_data1 : out std_logic_vector(31 downto 0);
            read_data2 : out std_logic_vector(31 downto 0)
        );
    end component;

    component Immediate
        port (
            Inst_In : in  std_logic_vector(31 downto 0);
            Imm_Out : out std_logic_vector(31 downto 0)
        );
    end component;

    component Controller
        port (
            opcode   : in  std_logic_vector(6 downto 0);
            funct3   : in  std_logic_vector(2 downto 0);
            funct7   : in  std_logic_vector(6 downto 0);
            BNE      : in  std_logic;
            PCSrc    : out std_logic;
            ALUSrcB  : out std_logic;
            RegWrite : out std_logic;
            MemWrite : out std_logic;
            MemRead  : out std_logic;
            WBSrc    : out std_logic;
            ALUCtl   : out std_logic_vector(2 downto 0)
        );
    end component;

    component Datapath
        port (
            clk_in       : in  std_logic;
            rst_in       : in  std_logic;
            pc_en        : in  std_logic;
            ALUSrcB      : in  std_logic;
            PCSrc        : in  std_logic;
            WBSrc        : in  std_logic;
            alu_contrl   : in  std_logic_vector(2 downto 0);
            data_mem_out : in  std_logic_vector(31 downto 0);
            immediate    : in  std_logic_vector(31 downto 0);
            read_data1   : in  std_logic_vector(31 downto 0);
            read_data2   : in  std_logic_vector(31 downto 0);
            inst_addr    : out std_logic_vector(31 downto 0);
            dmem_addr    : out std_logic_vector(31 downto 0);
            regf_wd      : out std_logic_vector(31 downto 0);
            bne          : out std_logic
        );
    end component;

begin

    -- =====================================================
    -- Address shifting (equivalent to >>2) and Halt Logic
    -- =====================================================
    inst_addr_shifted  <= std_logic_vector(shift_right(unsigned(inst_addr), 2));

    terminate <= '1' when instruction = x"00100013" else '0';

    -- =====================================================
    -- Unified Instruction + Data Memory
    -- =====================================================
    inst_data_mem : Imem_Dmem
        generic map (
            MEM_INIT_FILE => MEM_INIT_FILE
        )
        port map (
            clk          => clk_in,
            inst_address => inst_addr_shifted,
            data_address => dmem_addr,
            write_data   => regf_rd2,
            MemWrite     => MemWrite,
            MemRead      => MemRead,
            terminate    => terminate,
            inst_mem_out => instruction,
            data_mem_out => data_mem_out
        );

    -- =====================================================
    -- Register File
    -- =====================================================
    reg_file_inst : register_file
        generic map (
            DATA_WIDTH    => 32,
            ADDR_WIDTH    => 5,
            MEM_INIT_FILE => MEM_INIT_FILE
        )
        port map (
            write_data => regf_wd,
            rs1        => instruction(19 downto 15),
            rs2        => instruction(24 downto 20),
            rd         => instruction(11 downto 7),
            we         => RegWrite,
            clk        => clk_in,
            rst        => rst_in,
            terminate  => terminate,
            read_data1 => regf_rd1,
            read_data2 => regf_rd2
        );

    -- =====================================================
    -- IMM GEN
    -- =====================================================
    immediate_unit : Immediate
        port map (
            Inst_In => instruction,
            Imm_Out => immediate_out
        );

    -- =====================================================
    -- Control Unit
    -- =====================================================
    control_unit : Controller
        port map (
            opcode   => instruction(6 downto 0),
            funct3   => instruction(14 downto 12),
            funct7   => instruction(31 downto 25),
            BNE      => bne,
            PCSrc    => PCSrc,
            ALUSrcB  => ALUSrcB,
            RegWrite => RegWrite,
            MemWrite => MemWrite,
            MemRead  => MemRead,
            WBSrc    => WBSrc,
            ALUCtl   => alu_contrl
        );

    -- =====================================================
    -- DATAPATH
    -- =====================================================
    datapath_inst : Datapath
        port map (
            clk_in       => clk_in,
            rst_in       => rst_in,
            pc_en        => '1',
            ALUSrcB      => ALUSrcB,
            PCSrc        => PCSrc,
            WBSrc        => WBSrc,
            alu_contrl   => alu_contrl,
            data_mem_out => data_mem_out,
            immediate    => immediate_out,
            read_data1   => regf_rd1,
            read_data2   => regf_rd2,
            inst_addr    => inst_addr,
            dmem_addr    => dmem_addr,
            regf_wd      => regf_wd,
            bne          => bne
        );    

end architecture Behavioral;
