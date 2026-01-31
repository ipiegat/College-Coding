# Variables
GHDL = ghdl
TOP_ENTITY = TEST_ADD
SRC_FILES = lab0.vhd test0.vhd
VCD_FILE = pa0.vcd
STOP_TIME = 500ns

# Default target
all: run

# Analyze VHDL files
analyze:
	$(GHDL) -a $(SRC_FILES)

# Elaborate the top-level entity
elaborate: analyze
	$(GHDL) -e $(TOP_ENTITY)

# Run the simulation
run: elaborate
	$(GHDL) -r $(TOP_ENTITY) --stop-time=$(STOP_TIME) --vcd=$(VCD_FILE)

# Clean generated files
clean:
	rm -f *.o *.cf $(VCD_FILE) $(TOP_ENTITY)

# Phony targets to avoid conflicts with file names
.PHONY: all analyze elaborate run clean
