# GHDL executable
GHDL = ghdl
STOP_TIME = 500ns

# Default target
all: q4

#---------------------------
# q2
#---------------------------
q2_SRC = q2.vhd tb_q2.vhd
q2_TOP = tb_q2
q2_WAVE = q2.ghw

q2:
	$(GHDL) -a $(q2_SRC)
	$(GHDL) -e $(q2_TOP)
	$(GHDL) -r $(q2_TOP) --stop-time=$(STOP_TIME) --wave=$(q2_WAVE)

#---------------------------
# q3 FSM
#---------------------------
q3_SRC = fsm_q3.vhd tb_fsm_q3.vhd
q3_TOP = tb_fsm_q3
q3_WAVE = q3.ghw

q3:
	$(GHDL) -a $(q3_SRC)
	$(GHDL) -e $(q3_TOP)
	$(GHDL) -r $(q3_TOP) --stop-time=$(STOP_TIME) --wave=$(q3_WAVE)

#---------------------------
# q4 FSM
#---------------------------
q4_SRC = fsm_q4.vhd tb_fsm_q4.vhd
q4_TOP = tb_fsm_q4
q4_WAVE = q4.ghw

q4:
	$(GHDL) -a $(q4_SRC)
	$(GHDL) -e $(q4_TOP)
	$(GHDL) -r $(q4_TOP)  --stop-time=$(STOP_TIME) --wave=$(q4_WAVE)


#---------------------------
# Clean all generated files
#---------------------------
clean:
	rm -f *.o *.cf *.ghw $(q2_TOP) $(q3_TOP) $(q4_TOP)

.PHONY: all q2 q3 q4 clean
