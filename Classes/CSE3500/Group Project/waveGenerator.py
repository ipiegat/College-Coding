# -*- coding: utf-8 -*-
from sys import argv
from math import pi, sin

SAMPLES = 16384
DURATION = 1

def main():
	global SAMPLES
	global DURATION

	if len(argv) < 3:
		print("Usage: python waveGenerator.py <output filename> <frequency (Hz)> [number of samples] [duration (s)]")
		exit()

	with open(argv[1], "w+") as out_file:
		fr = float(argv[2])

		if len(argv) > 3: 
			SAMPLES = int(argv[3])

		if len(argv) == 5: 
			DURATION = int(argv[4])

		out_file.write(str(DURATION))

		for i in range(SAMPLES):
			out_file.write("\n" + str(sin(2*pi*fr * (i*DURATION)/SAMPLES)))

if __name__ == "__main__":
	main()
