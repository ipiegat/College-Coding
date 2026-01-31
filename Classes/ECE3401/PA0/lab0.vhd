-- Simulation Tutorial
-- 1-bit Adder

-- This is just to make a reference to some common things needed.
LIBRARY IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- We declare the 1-bit adder with the inputs and outputs
-- shown inside the port().
-- This will add two bits together(x,y), with a carry in(cin) and 
-- output the sum(sum) and a carry out(cout).
entity BIT_ADDER is
        port( a, b, cin         : in  unsigned(0 downto 0);
              sum, cout         : out STD_LOGIC );
end BIT_ADDER;

-- This describes the functionality of the 1-BIT adder.
architecture BHV of BIT_ADDER is
signal temp : unsigned(1 downto 0); -- 'signal' refers to an internal bus
begin
        -- Calculate the complete sum.
		temp <= ('0' & a) + ('0' & b) + ('0' & cin); -- '&' concatenates 2 values.
		
		-- Sum of the 1-BIT adder.
        sum <=  temp(0);

        -- Carry out of the 1-BIT adder.
        cout <= temp(1);
end BHV;
