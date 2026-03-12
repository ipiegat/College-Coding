library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- serial adder
entity SerialAdder_FSM is
    port(
        clk : in std_logic;
        async_reset : in std_logic;
        start : in std_logic;
        acc_in : in std_logic_vector (31 downto 0);
        addend_in : in std_logic_vector (31 downto 0);
        accumulator_sum : out std_logic_vector (31 downto 0);
        done_sig : out std_logic
    );
end SerialAdder_FSM;

-- states
architecture Behavioral of SerialAdder_FSM is
    signal