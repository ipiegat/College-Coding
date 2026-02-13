library ieee;
use ieee.std_logic_1164.all;

entity fsm_q4 is
    Port (
        clk   : in std_logic;
        reset : in std_logic;
        X     : in std_logic;
        Y     : out std_logic
    );
end fsm_q4;

architecture rtl of fsm_q4 is

    type state_type is (S0, S1, S2, S3, S4, S5);
    signal state, next_state : state_type;

begin

    -- State register
    process(clk, reset)
    begin
        if reset = '1' then
            state <= S0;
        elsif rising_edge(clk) then
            state <= next_state;
        end if;
    end process;

    -- Next state logic
    process(state, X)
    begin
        case state is

            when S0 =>
                if X = '1' then
                    next_state <= S1;
                else
                    next_state <= S0;
                end if;

            when S1 =>
                if X = '1' then
                    next_state <= S2;
                else
                    next_state <= S0;
                end if;

            when S2 =>
                if X = '1' then
                    next_state <= S3;
                else
                    next_state <= S0;
                end if;

            when S3 =>
                if X = '0' then
                    next_state <= S4;
                else
                    next_state <= S3;
                end if;

            when S4 =>
                if X = '0' then
                    next_state <= S5;
                else
                    next_state <= S3;
                end if;

            when S5 =>
                if X = '0' then
                    next_state <= S0;
                else
                    next_state <= S3;
                end if;

        end case;
    end process;

    -- Moore output logic
    process(state)
    begin
        case state is
            when S0 | S1 | S2 =>
                Y <= '0';
            when S3 | S4 | S5 =>
                Y <= '1';
        end case;
    end process;

end rtl;
