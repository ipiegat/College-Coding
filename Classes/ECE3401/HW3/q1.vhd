library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity q1 is
    Port (Din, gnd, A : in bit; Dout : out bit);
end q1;

architecture Behavioral of q1 is:
    signal W1, W2, W3: bit;
begin
    W1 <= not gnd after 3ns;
    W2 <= Din and W1 after 5ns;
    W3 <= reject 9ns inertial (A or W2) after 10ns;
    Dout <= reject 14ns inertial (W3 xor gnd) after 15ns;
end Behavioral;
