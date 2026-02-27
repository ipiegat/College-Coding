GHDL=ghdl
FLAGS="--std=08"

all:
	@$(GHDL) -a $(FLAGS) array.vhd pa1.vhd tb_pa1.vhd
	@$(GHDL) -e $(FLAGS) tb_pa1
	@$(GHDL) -r $(FLAGS) tb_pa1 --wave=wave_tb.ghw --stop-time=5000ns

clean:
	rm -r work* wave_tb* 