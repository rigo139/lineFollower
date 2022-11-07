import numpy as np

#1k, 1k5, 2k2, 4k7, 10k, 120R

RTable = [120.0, 1e3, 1.5e3, 2.2e3, 4.7e3, 10e3]
r_comb = []

def getVout(R1, R2, Vref=1.23):
    return Vref*(1 + R2/R1)

def getR2(R1, Vout, Vref=1.23):
    return R1*( (Vout/Vref) - 1)

for r1 in RTable:
    for r3 in RTable:
        for r2 in RTable:
            r_comb.append( [r1+r3,r2] )
r_comb  = np.array( r_comb )
N = len(r_comb)

v_comb = np.zeros( N )
for i in range(N):
    [r1, r2] = r_comb[i]
    v_comb[i] = getVout(r1, r2)

argsort = np.argsort( v_comb )
v_comb  = v_comb[argsort]
r_comb  = r_comb[argsort]

for i, vi in enumerate( v_comb ):
    print( "%10f %5d %5d" % (v_comb[i], r_comb[i][0], r_comb[i][1]) )
