library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Datapath is
    Port (
        clk_in          : in  std_logic;
        rst_in          : in  std_logic;
        pc_en           : in  std_logic;

        ALUSrcB         : in  std_logic;
        PCSrc           : in  std_logic;
        WBSrc           : in  std_logic;
        alu_contrl      : in  std_logic_vector(2 downto 0);

        data_mem_out    : in  std_logic_vector(31 downto 0);
        immediate       : in  std_logic_vector(31 downto 0);
        read_data1      : in  std_logic_vector(31 downto 0);
        read_data2      : in  std_logic_vector(31 downto 0);

        inst_addr       : out std_logic_vector(31 downto 0);
        dmem_addr       : out std_logic_vector(31 downto 0);
        regf_wd         : out std_logic_vector(31 downto 0);
        bne             : out std_logic
    );
end Datapath;

architecture Behavioral of Datapath is
    signal pc_reg      : std_logic_vector(31 downto 0) := (others => '0');
    signal pc_plus_4   : std_logic_vector(31 downto 0);
    signal pc_branch   : std_logic_vector(31 downto 0);
    signal pc_next     : std_logic_vector(31 downto 0);

    signal alu_in2     : std_logic_vector(31 downto 0);
    signal alu_out     : std_logic_vector(31 downto 0);

    signal add_res     : signed(32 downto 0);
    signal sub_res     : signed(32 downto 0);
    signal pc4_res     : unsigned(32 downto 0);
    signal pcb_res     : signed(32 downto 0);
begin

    alu_in2 <= read_data2 when ALUSrcB = '0' else immediate;

    add_res <= resize(signed(read_data1), 33) + resize(signed(alu_in2), 33);
    sub_res <= resize(signed(read_data1), 33) - resize(signed(alu_in2), 33);

    pc4_res <= resize(unsigned(pc_reg), 33) + to_unsigned(4, 33);
    pcb_res <= resize(signed(pc_reg), 33) + resize(signed(immediate), 33);

    process(read_data1, alu_in2, alu_contrl, add_res, sub_res)
    begin
        case alu_contrl is
            when "000" =>
                alu_out <= std_logic_vector(add_res(31 downto 0));

            when "001" =>
                alu_out <= std_logic_vector(sub_res(31 downto 0));

            when "010" =>
                alu_out <= std_logic_vector(
                    shift_left(unsigned(read_data1), to_integer(unsigned(alu_in2(4 downto 0))))
                );

            when "011" =>
                alu_out <= std_logic_vector(
                    shift_right(unsigned(read_data1), to_integer(unsigned(alu_in2(4 downto 0))))
                );

            when others =>
                alu_out <= (others => '0');
        end case;
    end process;

    bne <= '1' when read_data1 /= read_data2 else '0';

    regf_wd  <= data_mem_out when WBSrc = '1' else alu_out;
    dmem_addr <= '0' & alu_out(30 downto 0);

    pc_plus_4 <= std_logic_vector(pc4_res(31 downto 0));
    pc_branch <= std_logic_vector(pcb_res(31 downto 0));
    pc_next   <= pc_branch when PCSrc = '1' else pc_plus_4;

    process(clk_in, rst_in)
    begin
        if rst_in = '1' then
            pc_reg <= (others => '0');
        elsif rising_edge(clk_in) then
            if pc_en = '1' then
                pc_reg <= pc_next;
            end if;
        end if;
    end process;

    inst_addr <= pc_reg;

end Behavioral;