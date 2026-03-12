library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity q2 is
    Port (
        clk : in std_logic;
        rst : in std_logic;
        ld : in std_logic;
        W : in std_logic;
        X : in std_logic;
        Y : in std_logic;
        Z : in std_logic;
        Q_1 : out std_logic;
        Q_2 : out std_logic;
        Q_3 : out std_logic;
        Q_4 : out std_logic
    );
end q2;

architecture Behavioral of q2 is

    signal d1, d2, d3, d4 : std_logic;

begin

    process(clk, rst)
    begin
        if rst = '1' then
            d1 <= '0';
            d2 <= '0';
            d3 <= '0';
            d4 <= '0';
        
        elsif rising_edge(clk) then
            if ld = '1' then
                d1 <= W;
                d2 <= X;
                d3 <= Y;
                d4 <= Z;
            else
                d1 <= d4;
                d2 <= d1;
                d3 <= d2;
                d4 <= d3;
            end if;
        end if;
    end process;

    Q_1 <= d1;
    Q_2 <= d2;
    Q_3 <= d3;
    Q_4 <= d4;

end Behavioral;