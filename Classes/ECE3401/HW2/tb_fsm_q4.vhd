library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_fsm_q4 is
end tb_fsm_q4;

architecture Behavioral of tb_fsm_q4 is

    signal clk   : std_logic := '0';
    signal reset : std_logic := '0';
    signal X     : std_logic := '0';
    signal Y     : std_logic;

    constant clk_period : time := 10 ns;

begin

    --------------------------------------------------
    -- DUT instantiation
    --------------------------------------------------
    uut: entity work.fsm_q4
        port map (
            clk   => clk,
            reset => reset,
            X     => X,
            Y     => Y
        );

    --------------------------------------------------
    -- Clock generation
    --------------------------------------------------
    clk_process : process
    begin
        clk <= '1';
        wait for clk_period/2;
        clk <= '0';
        wait for clk_period/2;
    end process;

    --------------------------------------------------
    -- Stimulus
    --------------------------------------------------
    stim_proc : process
        variable input_sequence : std_logic_vector(19 downto 0) :=
            "01011101000111001000";
    begin
        -- Apply reset
        reset <= '1';
        wait for clk_period;
        reset <= '0';

        -- Apply input sequence
        for i in 0 to 19 loop
            X <= input_sequence(19 - i);
            wait for clk_period;
        end loop;

        wait;
    end process;

end Behavioral;
