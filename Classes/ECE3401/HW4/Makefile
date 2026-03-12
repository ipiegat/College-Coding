GHDL=ghdl
FLAGS="--std=08"

all:
	@$(GHDL) -a $(FLAGS) serialadd32.vhd tb_serialadd32.vhd
	@$(GHDL) -e $(FLAGS) tb_SerialAdder_FSM
	@$(GHDL) -r $(FLAGS) tb_SerialAdder_FSM --wave=serialadd32.ghw --stop-time=1000ns

clean:
	rm -r work*.cf *ghw 