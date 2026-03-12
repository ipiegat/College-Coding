library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity q1 is
    Port (
        A : in std_logic;
        B : in std_logic;
        C : in std_logic;
        D : in std_logic;
        S1 : in std_logic;
        S2 : in std_logic;
        S3 : in std_logic;
        S4 : in std_logic;
        X : out std_logic
    );
end q1;

X <= (A and not B) when S4 = '0' else
   '1'             when S3 = '0' else
    (A xnor B)     when S2 = '0' else
    B              when S1 = '0' else
    (C or D);

process (S1, S2, S3, S4, A, B, C, D)
begin
    if (S4 = '0') then
        X <= (A and not B);
    elsif (S3 = '0') then
        X <= 1;
    elsif (S2 = '0') then
        X <= (A xnor B);
    elsif (S1 = '0') then
        X <= B;
    else
        X <= (C or D);
    end if;
end process;