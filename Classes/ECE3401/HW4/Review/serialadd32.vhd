library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- serial adder
entity SerialAdder_FSM is
    port(
        clk : in std_logic;
        async_reset : in std_logic;
        start : in std_logic;
        acc_in : in std_logic_vector (31 downto 0);
        addend_in : in std_logic_vector (31 downto 0);
        accumulator : out std_logic_vector (31 downto 0);
        done_sig : out std_logic
    );
end SerialAdder_FSM;

-- states
architecture Behavioral of SerialAdder_FSM is
    type state_type is (IDLE, LOAD, SH_ADD, DONE);
    signal state, next_state : state_type;

    -- internal registers
    signal acc_reg : std_logic_vector(31 downto 0);
    signal add_reg : std_logic_vector(31 downto 0);
    signal carry_ff : std_logic;
    signal bit_count : unsigned(4 downto 0);

    -- combinational logic signals
    signal carry_next : std_logic;
    signal sum_bit : std_logic;


begin
    -- s = a xor b xor cin; cnext = ab + cin(a xor b)
    sum_bit <= acc_reg(0) xor add_reg(0) xor carry_ff;
    carry_next <= (acc_reg(0) and add_reg(0)) or (carry_ff and (acc_reg(0) xor add_reg(0)));

    -- output
    accumulator <= acc_reg;

    process(clk, async_reset)
    begin
        if (async_reset = '1') then
            state <= IDLE;
            acc_reg <= (others => '0');
            add_reg <= (others => '0');
            carry_ff <= '0';
            bit_count <= (others => '0');
            done_sig <= '0';
        elsif rising_edge(clk) then

            next_state <= state;

            case state is 
                when IDLE =>
                    done_sig <= '0';
                    if (start = '1') then
                        next_state <= LOAD;
                    else
                        next_state <= IDLE;
                    end if;
                
                when LOAD =>
                    acc_reg <= acc_in;
                    add_reg <= addend_in;
                    bit_count <= (others => '0');
                    carry_ff <= '0';
                    next_state <= SH_ADD;
                
                when SH_ADD =>
                    acc_reg <= sum_bit & acc_reg(31 downto 1);
                    add_reg <= '0' & add_reg(31 downto 1);
                    carry_ff <= carry_next;

                    if (bit_count = 31) then
                        next_state <= DONE;
                    else
                        bit_count <= bit_count + 1;
                        next_state <= SH_ADD;
                    end if;
                
                when DONE =>
                    done_sig <= '1';
                    if start = '0' then
                        next_state <= IDLE;
                    else
                        next_state <= DONE;
                    end if;
            end case;
            
            state <= next_state;

        end if;
    end process;
end Behavioral;





