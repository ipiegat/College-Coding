library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_q2 is
end tb_q2;

architecture Behavioral of tb_q2 is

    -- DUT signals
    signal clk   : std_logic := '0';
    signal rst   : std_logic := '0';
    signal ld    : std_logic := '0';
    signal W     : std_logic := '0';
    signal X     : std_logic := '0';
    signal Y     : std_logic := '0';
    signal Z     : std_logic := '0';
    signal Q_1    : std_logic;
    signal Q_2    : std_logic;
    signal Q_3    : std_logic;
    signal Q_4    : std_logic;

    constant clk_period : time := 10 ns;

begin

    -- Clock generation
    clk <= not clk after clk_period / 2;

    -- DUT instantiation
    uut: entity work.q2
        port map (
            clk => clk,
            rst => rst,
            ld  => ld,
            W   => W,
            X   => X,
            Y   => Y,
            Z   => Z,
            Q_1  => Q_1,
            Q_2  => Q_2,
            Q_3  => Q_3,
            Q_4  => Q_4
        );

    -- Stimulus process
    stim_proc: process
    begin
        -- Step 1: Set inputs W X Y Z = 1 1 0 1
        W <= '1';
        X <= '1';
        Y <= '0';
        Z <= '1';

        -- Step 2: Assert reset
        rst <= '1';
        ld  <= '0';
        wait for 2 * clk_period;

        -- Step 3: Deassert reset
        rst <= '0';
        wait for clk_period;

        -- Step 4: Parallel load
        ld <= '1';
        wait for clk_period;

        -- Step 5: Shift operation
        ld <= '0';
        wait for 4 * clk_period;  -- shift for several cycles

        -- Step 6: Assert reset again
        rst <= '1';
        wait for 2 * clk_period;

        -- End simulation
        wait;
    end process;

end Behavioral;
