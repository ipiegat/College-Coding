library ieee;
use ieee.std_logic_1164.all;

entity pass_through is
    port (
        a : in  std_logic;
        y : out std_logic
    );
end entity;

architecture rtl of pass_through is
begin
    y <= a;
end architecture;
