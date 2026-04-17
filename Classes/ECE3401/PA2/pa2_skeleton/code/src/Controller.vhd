library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.itype_pkg.all;

entity Controller is
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
end entity Controller;

architecture Behavioral of Controller is
    signal Inst_Type : instruction_type;
begin

-- Decode instruction into types
process(opcode, funct3, funct7)
begin
    Inst_Type <= INVALID;

    case opcode is
        when R_type =>
            case funct3 is
                when "000" =>
                    if funct7 = "0000000" then
                        Inst_Type <= ADD_R;
                    elsif funct7 = "0100000" then
                        Inst_Type <= SUB_R;
                    end if;

                when "001" =>
                    if funct7 = "0000000" then
                        Inst_Type <= SLL_R;
                    end if;

                when "101" =>
                    if funct7 = "0000000" then
                        Inst_Type <= SRL_R;
                    end if;

                when others =>
                    Inst_Type <= INVALID;
            end case;

        when I_type =>
            case funct3 is
                when "000" =>
                    Inst_Type <= ADD_I;

                when "001" =>
                    if funct7 = "0000000" then
                        Inst_Type <= SLL_I;
                    end if;

                when "101" =>
                    if funct7 = "0000000" then
                        Inst_Type <= SRL_I;
                    end if;

                when others =>
                    Inst_Type <= INVALID;
            end case;

        when Load_type =>
            if funct3 = "010" then
                Inst_Type <= LW;
            end if;

        when St_type =>
            if funct3 = "010" then
                Inst_Type <= SW;
            end if;

        when B_type =>
            if funct3 = "001" then
                Inst_Type <= BNE_B;
            end if;

        when others =>
            Inst_Type <= INVALID;
    end case;
end process;

-- generate control signals based on instruction type and BNE outcome
process(Inst_Type, BNE)
begin
    -- DEFAULT VALUES FOR ALL CONTROL SIGNALS
    PCSrc    <= '0';
    ALUSrcB  <= '0';
    RegWrite <= '0';
    MemWrite <= '0';
    MemRead  <= '0';
    WBSrc    <= '0';
    ALUCtl   <= "000";

    case Inst_Type is
        when ADD_R =>
            RegWrite <= '1';
            ALUCtl   <= "000";

        when SUB_R =>
            RegWrite <= '1';
            ALUCtl   <= "001";

        when SLL_R =>
            RegWrite <= '1';
            ALUCtl   <= "010";

        when SRL_R =>
            RegWrite <= '1';
            ALUCtl   <= "011";

        when ADD_I =>
            ALUSrcB  <= '1';
            RegWrite <= '1';
            ALUCtl   <= "000";

        when SLL_I =>
            ALUSrcB  <= '1';
            RegWrite <= '1';
            ALUCtl   <= "010";

        when SRL_I =>
            ALUSrcB  <= '1';
            RegWrite <= '1';
            ALUCtl   <= "011";

        when LW =>
            ALUSrcB  <= '1';
            RegWrite <= '1';
            MemRead  <= '1';
            WBSrc    <= '1';
            ALUCtl   <= "000";

        when SW =>
            ALUSrcB  <= '1';
            MemWrite <= '1';
            ALUCtl   <= "000";

        when BNE_B =>
            ALUCtl   <= "001";
            PCSrc    <= BNE;

        when others =>
            null;
    end case;
end process;

end architecture Behavioral;