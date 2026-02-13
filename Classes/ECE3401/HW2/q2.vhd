library ieee;
use ieee.std_logic_1164.all;

entity q2 is
    Port (
        clk  : in std_logic;
        rst  : in std_logic;
        ld   : in std_logic;
        W    : in std_logic;
        X    : in std_logic;
        Y    : in std_logic;
        Z    : in std_logic;
        Q_1  : out std_logic;
        Q_2  : out std_logic;
        Q_3  : out std_logic;
        Q_4  : out std_logic
    );
end q2;

architecture rtl of q2 is

    signal q1, q2_i, q3_i, q4_i : std_logic;

begin

    process(clk, rst)
    begin
        if rst = '1' then
            q1   <= '0';
            q2_i <= '0';
            q3_i <= '0';
            q4_i <= '0';
        elsif rising_edge(clk) then
            if ld = '1' then
                q1   <= W;
                q2_i <= X;
                q3_i <= Y;
                q4_i <= Z;
            else
                q1   <= q4_i xor q1;
                q2_i <= q1;
                q3_i <= q2_i;
                q4_i <= q3_i;
            end if;
        end if;
    end process;

    Q_1 <= q1;
    Q_2 <= q2_i;
    Q_3 <= q3_i;
    Q_4 <= q4_i;

end rtl;
