library ieee;
use ieee.std_logic_1164.all;

entity fsm_q3 is 
 Port ( 
  clk   : in std_logic; 
  reset : in std_logic; 
  X     : in std_logic; 
  Y     : out std_logic 
 ); 
end fsm_q3;

architecture rtl of fsm_q3 is

    type state_type is (S0, S1, S2, S3);
    signal state, next_state : state_type;

begin

    -- State register (sequential)
    process(clk, reset)
    begin
        if reset = '1' then
            state <= S0;
        elsif rising_edge(clk) then
            state <= next_state;
        end if;
    end process;

    -- Next state logic + Mealy output
    process(state, X)
    begin
        case state is

            when S0 =>
                if X = '1' then
                    next_state <= S1;
                    Y <= '0';
                else
                    next_state <= S0;
                    Y <= '0';
                end if;

            when S1 =>
                if X = '1' then
                    next_state <= S2;
                    Y <= '0';
                else
                    next_state <= S1;
                    Y <= '0';
                end if;

            when S2 =>
                if X = '1' then
                    next_state <= S3;
                    Y <= '0';
                else
                    next_state <= S2;
                    Y <= '0';
                end if;

            when S3 =>
                if X = '0' then
                    next_state <= S0;
                    Y <= '1';
                else
                    next_state <= S3;
                    Y <= '1';
                end if;

        end case;
    end process;

end rtl;
