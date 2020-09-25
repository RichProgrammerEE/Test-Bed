import numpy as np
import math

# Array Test
x = 32e3
sampl = np.zeros(15)
for i in range(15):
    sampl[i] = x
    x = x * 2

# Single Test
# sampl = np.zeros(1)
# sampl[0] = 100e6

ffts = sampl / 50e3
bases = np.ones(15) * 2
ffts = np.ceil(np.log2(ffts))
ffts = np.power(bases, ffts)
ffts = np.clip(ffts, 64, 2048)

print('\nSampling Rates (FFT Sizes):')
for i in range(len(sampl)):
    if(sampl[i] / 1e6 < 1):
        print('{} kHz, ({})'.format(sampl[i]/1e3, ffts[i]))
    else:
        print('{} MHz, ({})'.format(sampl[i]/1e6, ffts[i]))