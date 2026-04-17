library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity GEMM_RV5 is
    Port (
        -- GEMM-RiscV Interface related inputs and outputs
        -- from RiscV
        riscv_rs1       : in  std_logic_vector(4 downto 0);
        riscv_rs2       : in  std_logic_vector(4 downto 0);
        riscv_rd        : in  std_logic_vector(4 downto 0);
        MemWrite        : in  std_logic;
        RegWrite        : in  std_logic;
        riscv_regf_wd   : in std_logic_vector(31 downto 0);

        -- from GEMM
        gemm_active     : in  std_logic;
        gemm_output     : in  std_logic_vector(31 downto 0);
        A_addr_gemm     : in  std_logic_vector(4 downto 0);
        B_addr_gemm     : in  std_logic_vector(4 downto 0);
        C_addr_gemm     : in  std_logic_vector(4 downto 0);

        -- to PC logic
        pc_en           : out std_logic;

        -- to DMem 
        dmem_we         : out std_logic;

        -- to Register File
        regf_we         : out std_logic;
        regf_wd         : out std_logic_vector(31 downto 0);
        rs1_addr        : out std_logic_vector(4 downto 0); 
        rs2_addr        : out std_logic_vector(4 downto 0); 
        rd_addr         : out std_logic_vector(4 downto 0)
    );
end GEMM_RV5;

architecture Behavioral of GEMM_RV5 is
begin

    --enter your VHDL codes here

end Behavioral;
