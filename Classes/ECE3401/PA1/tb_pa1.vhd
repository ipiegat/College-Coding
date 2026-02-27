library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.array_pkg.all;

entity tb_pa1 is
end tb_pa1;

architecture Behavioral of tb_pa1 is

    -- DUT signals
    signal clk    : std_logic := '0';
    signal reset  : std_logic := '0';
    signal start  : std_logic := '0';
    signal ready  : std_logic;

    signal matA   : matrix;
    signal matB   : matrix;
    signal matC   : matrix;

    -- Clock period
    constant CLK_PERIOD : time := 10 ns;

begin

    -----------------
    -- DUT INSTANCE
    -----------------
    uut : entity work.pa1
        port map (
            matA   => matA,
            matB   => matB,
            clk    => clk,
            reset  => reset,
            start  => start,
            matC   => matC,
            ready  => ready
        );

    -----------------
    -- CLOCK PROCESS
    -----------------
    clk_process : process
    begin
        while true loop
            clk <= '0';
            wait for CLK_PERIOD / 2;
            clk <= '1';
            wait for CLK_PERIOD / 2;
        end loop;
    end process;

    -----------------
    -- STIMULUS
    -----------------
    stim_proc : process
    begin
        -- Initialize matrices
        matA <= (
            0 => (0 => 1, 1 => 2, 2 => 3),
            1 => (0 => 4, 1 => 5, 2 => 6),
            2 => (0 => 7, 1 => 8, 2 => 9)
        );

        matB <= (
            0 => (0 => 1, 1 => 1, 2 => 1),
            1 => (0 => 1, 1 => 1, 2 => 1),
            2 => (0 => 1, 1 => 1, 2 => 1)
        );

        -- Apply reset
        reset <= '1';
        start <= '0';
        wait for 2 * CLK_PERIOD;

        reset <= '0';
        wait for CLK_PERIOD;

        -- Start computation
        start <= '1';
        wait for CLK_PERIOD;
        start <= '0';

        -- Wait for completion
        wait until ready = '1';
        --wait for CLK_PERIOD;

        -- Report results
        report "Matrix multiplication complete";
        report "matC(0,0) = " & integer'image(matC(0,0));
        report "matC(0,1) = " & integer'image(matC(0,1));
        report "matC(0,2) = " & integer'image(matC(0,2));

        report "matC(1,0) = " & integer'image(matC(1,0));
        report "matC(1,1) = " & integer'image(matC(1,1));
        report "matC(1,2) = " & integer'image(matC(1,2));

        report "matC(2,0) = " & integer'image(matC(2,0));
        report "matC(2,1) = " & integer'image(matC(2,1));
        report "matC(2,2) = " & integer'image(matC(2,2));

        matA <= (
            0 => (0 => 2, 1 => 2, 2 => 2),
            1 => (0 => 4, 1 => 4, 2 => 4),
            2 => (0 => 8, 1 => 8, 2 => 8)
        );

        matB <= (
            0 => (0 => 1, 1 => 1, 2 => 1),
            1 => (0 => 1, 1 => 1, 2 => 1),
            2 => (0 => 1, 1 => 1, 2 => 1)
        );

        wait for 0 * CLK_PERIOD;

        -- Start computation
        start <= '1';
        wait for CLK_PERIOD;
        start <= '0';

        -- Wait for completion
        wait until ready = '1';
        wait for CLK_PERIOD;

        -- Report results
        report "Matrix multiplication complete";
        report "matC(0,0) = " & integer'image(matC(0,0));
        report "matC(0,1) = " & integer'image(matC(0,1));
        report "matC(0,2) = " & integer'image(matC(0,2));

        report "matC(1,0) = " & integer'image(matC(1,0));
        report "matC(1,1) = " & integer'image(matC(1,1));
        report "matC(1,2) = " & integer'image(matC(1,2));

        report "matC(2,0) = " & integer'image(matC(2,0));
        report "matC(2,1) = " & integer'image(matC(2,1));
        report "matC(2,2) = " & integer'image(matC(2,2));

        wait;
    end process;

end Behavioral;
