import math

pi = math.pi
r = .157
theta = 19.9
E = 40.1

result = E*pi*(r**2)*math.cos(math.radians(theta))

print(result)