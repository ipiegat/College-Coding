library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity fsm_q3 is
    Port (
        clk : in std_logic;
        X : in std_logic;
        reset : in std_logic;
        Y : out std_logic
    );
end fsm_q3;

architecture Behavioral of fsm_q3 is

    type state_type is (S0, S1, S2, S3);
    signal state, next_state : state_type;

begin

    -- State registers
    process(clk, reset)
        begin
            if (reset = '1') then
                state <= S0;
            elsif rising_edge(clk) then
                state <= next_state;
        end if;
    end process;

    -- Next state/output logic
    process(state, X)
    begin
        case state is

            when S0 =>
                if (X = '1') then
                    next_state <= S1;
                else
                    next_state <= S0;
                end if;

            when S1 =>
                if (X = '1') then
                    next_state <= S2;
                else
                    next_state <= S1;
                end if;

            when S2 =>
                if (X = '1') then
                    next_state <= S3;
                else
                    next_state <= S2;
                end if;

            when S3 =>
                next_state <= S3;

        end case;
    end process;

    Y <= '1' when (state = S3);
    
end Behavioral;