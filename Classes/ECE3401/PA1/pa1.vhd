library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.array_pkg.all;

entity pa1 is
port(
    matA   : in  matrix;
    matB   : in  matrix;
    clk    : in  std_logic;
    reset  : in  std_logic;
    start  : in  std_logic;
    matC   : out matrix;
    ready  : out std_logic
);
end pa1;

architecture Behavioral of pa1 is

    -----------------
    -- FSM STATES
    -----------------
    type state_type is (IDLE, MAC, DONE);
    signal state, n_state : state_type := IDLE;

    -----------------
    -- CONTROL SIGNALS
    -----------------
    signal i, j, k         : integer;

-- DO NOT MODIFY UP T0 THIS POINT
begin
    -----------------------------------
    -- CONTROLLER FSM related processes
    -----------------------------------
    fsm_ff : process(clk, reset)
    begin
        if reset = '1' then
            state <= IDLE;
        elsif rising_edge(clk) then
            state <= n_state;
        end if;
    end process;

    fsm_logic : process(state, start, i, j, k)
    begin
        n_state <= state;
        case state is
            when IDLE =>
                if start = '1' then
                    n_state <= MAC;
                else
                    n_state <= IDLE;
                end if;

            when MAC =>
                if (i = DIM-1) and (j = DIM-1) and (k = DIM-1) then
                    n_state <= DONE;
                else
                    n_state <= MAC;
                end if;

            when DONE =>
                if start = '1' then
                    n_state <= MAC;
                else
                    n_state <= IDLE;
                end if;
        end case;
    end process;

    -----------------------------------
    -- DATAPATH related processes
    -----------------------------------

    ready <= '1' when state = DONE else '0';

    i_process : process(clk, reset)
    begin
        if reset = '1' then
            i <= 0;
        elsif rising_edge(clk) then
            if (state = IDLE) or (state = DONE) then
                i <= 0;
            elsif state = MAC then
                if (k = DIM-1) and (j = DIM-1) then
                    if i = DIM-1 then
                        i <= 0;
                    else
                        i <= i + 1;
                    end if;
                end if;
            end if;
        end if;
    end process;

    j_process : process(clk, reset)
    begin
        if reset = '1' then
            j <= 0;
        elsif rising_edge(clk) then
            if (state = IDLE) or (state = DONE) then
                j <= 0;
            elsif state = MAC then
                if k = DIM-1 then
                    if j = DIM-1 then
                        j <= 0;
                    else
                        j <= j + 1;
                    end if;
                end if;
            end if;
        end if;
    end process;

    k_process : process(clk, reset)
    begin
        if reset = '1' then
            k <= 0;
        elsif rising_edge(clk) then
            if (state = IDLE) or (state = DONE) then
                k <= 0;
            elsif state = MAC then
                if k = DIM-1 then
                    k <= 0;
                else
                    k <= k + 1;
                end if;
            end if;
        end if;
    end process;

    -----------------
    -- MAC Datapath
    -----------------
    output_process : process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                matC <= (others => (others => 0));
            elsif state = MAC then
                if k = 0 then
                    matC(i, j) <= matA(i, k) * matB(k, j);
                else
                    matC(i, j) <= matC(i, j) + (matA(i, k) * matB(k, j));
                end if;
            end if;
        end if;
    end process;

end Behavioral;
