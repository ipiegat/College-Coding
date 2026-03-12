-- define entity
entity Addr4 is
    -- input/outputs
    -- std_logic_vector for multiple bits (101, 01, etc)
    -- std_logic for single bits
    -- in & out
    Port(
        A : in std_logic_vector(31 downto 0);
        B : in std_logic_vector(31 downto 0);
        Ci : in bit;
        Co : out bit;
        S : out std_logic_vector(3 downto 0);

        -- arent used in this example but this is where you put them
        rst : in std_logic;
        clk : in std_logic;
    );
end Addr4;

-- define Structure architecture if reusing module
architecture Structure of design is

    -- define component
    component Adder4
        port(
            X, Y, Cin : in bit;
            Cout, Sum : out bit
        );
    end component;

    signal C: std_logic_vector (3 downto 1);

begin
    -- create as many copies of Adder4 as you want
    FA0: Adder4 port map (A(0), B(0), Ci, Co(1), S(0));
    FA1: Adder4 port map (A(1), B(1), Ci, Co(2), S(1));
    FA2: Adder4 port map (A(2), B(2), Ci, Co(3), S(2));
    FA3: Adder4 port map (A(3), B(3), Ci, Co,    S(3));

end Structure;


