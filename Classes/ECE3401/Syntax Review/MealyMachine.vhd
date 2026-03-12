entity MooreMachine is
    Port(
        X: in std_logic;
        Y: out std_logic;
        clk: in std_logic;
        rst: in std_logic
    );
end entity;

architecture Behavioral of MooreMachine is
    type state_type(S0, S1, S2, S3, S4, S5);
    state, next_state : state_type;


architecture copies of MooreMachine is
    component Addr4
        port(
            X, Y, Cin : in std_logic;
            
        )


begin
    process(clk, rst)
    begin
        if (rst = '1') then
            state <= S0;
        elsif rising_edge(clk) then
            state <= next_state;
        end if;
    end process;

    process(X, state)
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
                    next_state <= S0;
                end if;
            
            when S2 =>
                if (X = '1') then
                    next_state <= S3;
                else
                    next_state <= S0;
                end if;

            when S3 =>
                if (X = '1') then
                    next_state <= S3;
                else
                    next_state <= S4;
                end if;

            when S4 =>
                if (X = '1') then
                    next_state <= S3;
                else
                    next_state <= S5;
                end if;

            when S5 =>
                if (X = '1') then
                    next_state <= S3;
                else
                    next_state <= S0;
                end if;
            
        end case;

    end process;

    Y <= '1' when (state = S3 or state = S4 or state = S5) else '0';
end Behavioral;

