library ieee;
use ieee.std_logic_1164.all;
use std.textio.all;
use ieee.std_logic_textio.all;

entity tb_and_gate is
end;

architecture sim of tb_and_gate is
    signal a : std_logic := '0';
    signal b : std_logic := '0';
    signal y : std_logic;
begin
    uut: entity work.and_gate
        port map (a => a, b => b, y => y);

    process
        variable L : line;
    begin
        a <= '0'; b <= '0'; wait for 1 ns;
        write(L, string'("a=0 b=0 y=")); write(L, y); writeline(output, L);

        a <= '0'; b <= '1'; wait for 1 ns;
        write(L, string'("a=0 b=1 y=")); write(L, y); writeline(output, L);

        a <= '1'; b <= '0'; wait for 1 ns;
        write(L, string'("a=1 b=0 y=")); write(L, y); writeline(output, L);

        a <= '1'; b <= '1'; wait for 1 ns;
        write(L, string'("a=1 b=1 y=")); write(L, y); writeline(output, L);

        wait;
    end process;
end architecture;
