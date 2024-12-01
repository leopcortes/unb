import numpy as np

L1 = 0.5
I1 = 2.148 #+ (56j/41)
L2 = 1
I2 = 10.733 #+ (48j/5)
M = 0.2


w = (1/2) * L1 * (I1**2) + (1/2) * L2 * (I2**2) - M * I1 * I2
print(w)

r = np.sqrt(((56/41)**2) + ((68/41)**2))
# t = np.arctan((48/5)/(-24/5))
print(r)
# print(t)