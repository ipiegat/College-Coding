library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity GEMM is
    port(
        clk, reset  : in std_logic;
        Gemm_start  : in std_logic;

        regf_A      : in std_logic_vector(31 downto 0);
        regf_B      : in std_logic_vector(31 downto 0);
        regf_C      : in std_logic_vector(31 downto 0);

        A_addr      : out std_logic_vector(4 downto 0);
        B_addr      : out std_logic_vector(4 downto 0);
        C_addr      : out std_logic_vector(4 downto 0);

        regfwd_C    : out std_logic_vector(31 downto 0);
        regf_we_gemm: out std_logic;
        ready       : out std_logic
    );
end GEMM;

architecture Behavioral of GEMM is

    type state_t is (IDLE, MAC);
    signal state : state_t := IDLE;

    signal i : integer range 0 to 1 := 0;
    signal j : integer range 0 to 1 := 0;
    signal k : integer range 0 to 1 := 0;

    signal mul_res : signed(63 downto 0);
    signal acc_res : signed(31 downto 0);

begin

    mul_res <= signed(regf_A) * signed(regf_B);
    acc_res <= signed(mul_res(31 downto 0)) when k = 0 else
               signed(regf_C) + signed(mul_res(31 downto 0));

    -----------------
    -- CONTROLLER FSM
    -----------------
    controller : process(clk, reset)
    begin
        if reset = '1' then
            state <= IDLE;
            i <= 0;
            j <= 0;
            k <= 0;

        elsif rising_edge(clk) then
            case state is
                when IDLE =>
                    if Gemm_start = '1' then
                        state <= MAC;
                        i <= 0;
                        j <= 0;
                        k <= 0;
                    end if;

                when MAC =>
                    if k = 0 then
                        k <= 1;
                    else
                        k <= 0;
                        if j = 0 then
                            j <= 1;
                        else
                            j <= 0;
                            if i = 0 then
                                i <= 1;
                            else
                                state <= IDLE;
                                i <= 0;
                                j <= 0;
                                k <= 0;
                            end if;
                        end if;
                    end if;
            end case;
        end if;
    end process;

    -----------------
    -- MAC Datapath
    -----------------
    datapath : process(state, i, j, k, acc_res)
    begin
        if state = MAC then
            A_addr       <= std_logic_vector(to_unsigned(5  + (2 * i) + k, 5));
            B_addr       <= std_logic_vector(to_unsigned(9  + (2 * k) + j, 5));
            C_addr       <= std_logic_vector(to_unsigned(13 + (2 * i) + j, 5));
            regfwd_C     <= std_logic_vector(acc_res);
            regf_we_gemm <= '1';
            ready        <= '0';
        else
            A_addr       <= (others => '0');
            B_addr       <= (others => '0');
            C_addr       <= (others => '0');
            regfwd_C     <= (others => '0');
            regf_we_gemm <= '0';
            ready        <= '1';
        end if;
    end process;

end Behavioral;