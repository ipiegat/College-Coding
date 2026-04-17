process(clk, reset)
begin
    if reset = '1' then
        state <= IDLE;
        last_served <= 2;
    elsif rising_edge(clk) then
        state <= next_state;
        if state = 'GNT1' then
            last_served <= '1';
        elsif state = 'GNT2' then
            last_served <= 2;
        end if;
    end if;
end process;

process(state, empty_flag, read_req1, read_req2, last_served)
begin
    next_state <= IDLE;
    last_served <= '0';
    read_gnt1 <= '0';
    read_gnt2 <= '0';
    
    case state is
        when IDLE =>
            if empty_flag = '0' then
                if last_served = '2' then
                    if read_req1 = '1' then 
                        next_state <= GNT1;
                    elsif read_req2 = '1' then
                        next_state <= GNT2;
                    end if;
                elsif last_served = '1' then
                    if read_req2 = '1' then 
                        next_state <= GNT2;
                    elsif read_req1 = '1' then
                        next_state <= GNT1;

                end if;
            end if;

        when GNT1 =>
            read_gnt1 <= '1';
            read_enable <= '1';
            next_state <= IDLE;
        
        when GNT2 =>
            read_gnt2 <= '1';
            read_enable <= '1';
            next_state <= IDLE; 
        
        end case;
end process;                    

dout <= memory(read_ptr);