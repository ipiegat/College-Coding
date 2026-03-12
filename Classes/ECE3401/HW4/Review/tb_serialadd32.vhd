library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_SerialAdder_FSM is
end tb_SerialAdder_FSM;

architecture sim of tb_SerialAdder_FSM is
    signal clk, async_rst, start, done_sig : STD_LOGIC := '0';
    signal acc_in, addend_in, accumulator : STD_LOGIC_VECTOR(31 downto 0);
    constant clk_period : time := 10 ns;

begin
    uut: entity work.SerialAdder_FSM 
        port map (clk, async_rst, start, acc_in, addend_in, accumulator, done_sig);

    clk_gen: process begin
        clk <= '0'; wait for clk_period/2;
        clk <= '1'; wait for clk_period/2;
    end process;

    stim: process begin
        async_rst <= '1'; wait for 20 ns;
        async_rst <= '0'; wait for clk_period;

        -- Test: 123 + 456
        acc_in    <= std_logic_vector(to_unsigned(123, 32));
        addend_in <= std_logic_vector(to_unsigned(456, 32));
        start <= '1'; wait for clk_period; start <= '0';

        wait until done_sig = '1';
        wait for 1 ns;
        report "Addition Result: " & integer'image(to_integer(unsigned(accumulator)));

        wait for clk_period;

        -- Test: 20 + 30
        acc_in    <= std_logic_vector(to_unsigned(20, 32));
        addend_in <= std_logic_vector(to_unsigned(30, 32));
        start <= '1'; wait for clk_period; start <= '0';

        wait until done_sig = '1';
        wait for 1 ns;
        report "Addition Result: " & integer'image(to_integer(unsigned(accumulator)));
        
        wait;
    end process;
end sim;