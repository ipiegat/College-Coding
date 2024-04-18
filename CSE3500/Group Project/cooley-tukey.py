import math, functools, sys, matplotlib
from time import time

SECONDS = 0	# Wave duration.
OP = 0		# Operations performed.
TIME = 0	# Execution time.

# FFT implementation
def fft(x):
	global OP

	N = len(x)

	if N == 1:
		return [x[0]]

	X = [0] * N
	
	even = fft(x[:N:2])
	odd = fft(x[1:N:2])

	for k in range(N//2):
		w = math.e**(-2j*math.pi * k/N)
		X[k] = even[k] + w * odd[k]
		X[k + N//2] = even[k] - w * odd[k]
		OP += 2

	return X

# DFT implementation
def dft(x):
	global OP

	OP = 0

	N = len(x)
	X = [0] * N

	for k in range(N):
		for n in range(k):
			X[k] += x[n] * math.e**(-2j*math.pi * k*n/N)
			OP += 1

	return X

# Interprets the DFT results into a group of frequency-domain samples
def interpret(X, t):
	l = [0] * (len(X) // t)
	for i in range(len(l)):
		for j in range(t):
			l[i] += X[t*i + j]

	return l

# Reads a wave from a file
def readWave(name):
	# File format:
	# 1st line: an integer stating the difference in seconds between the first
	# and the last samples.
	# Next lines: a real, the value of each sample.
	# (One sample per line.)
	global SECONDS

	with open(name, "r") as file:
		f = file.readlines()
		
	SECONDS = int(f.pop(0)[:-1])

	return map(lambda x : float(x[:-1]), f)
	
if __name__ == "__main__":
	x = list(readWave(sys.argv[1]))
	N = len(x)	# Number of samples

	X = fft(x)
	
	X_ = interpret(X[:N//2], SECONDS)
	
	s = functools.reduce(lambda a, b: abs(a) + abs(b), X_)	# Sum of all the values of the transform
	X_ = list(map(lambda x : abs(x) / s, X_))

	print("\nCooley-Tukey algorithm:\n" + str(OP) + " operations.\n" + str(TIME) + " seconds.\n\n")

	TIME = time()
	dft(x)	
	TIME = time() - TIME
	
	print("Definition-based algorithm:\n" + str(OP) + " operations.\n" + str(TIME) + " seconds.\n\n")