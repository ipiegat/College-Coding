library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity GEMM_RV5 is
    Port (
        riscv_rs1       : in  std_logic_vector(4 downto 0);
        riscv_rs2       : in  std_logic_vector(4 downto 0);
        riscv_rd        : in  std_logic_vector(4 downto 0);
        MemWrite        : in  std_logic;
        RegWrite        : in  std_logic;
        riscv_regf_wd   : in  std_logic_vector(31 downto 0);

        gemm_active     : in  std_logic;
        gemm_output     : in  std_logic_vector(31 downto 0);
        A_addr_gemm     : in  std_logic_vector(4 downto 0);
        B_addr_gemm     : in  std_logic_vector(4 downto 0);
        C_addr_gemm     : in  std_logic_vector(4 downto 0);

        pc_en           : out std_logic;
        dmem_we         : out std_logic;
        regf_we         : out std_logic;
        regf_wd         : out std_logic_vector(31 downto 0);
        rs1_addr        : out std_logic_vector(4 downto 0);
        rs2_addr        : out std_logic_vector(4 downto 0);
        rd_addr         : out std_logic_vector(4 downto 0)
    );
end GEMM_RV5;

architecture Behavioral of GEMM_RV5 is
begin
    process(all)
    begin
        if gemm_active = '1' then
            pc_en    <= '0';
            dmem_we  <= '0';

            regf_we  <= gemm_active;
            regf_wd  <= gemm_output;

            rs1_addr <= A_addr_gemm;
            rs2_addr <= B_addr_gemm;
            rd_addr  <= C_addr_gemm;
        else
            pc_en    <= '1';
            dmem_we  <= MemWrite;

            regf_we  <= RegWrite;
            regf_wd  <= riscv_regf_wd;

            rs1_addr <= riscv_rs1;
            rs2_addr <= riscv_rs2;
            rd_addr  <= riscv_rd;
        end if;
    end process;
end Behavioral;