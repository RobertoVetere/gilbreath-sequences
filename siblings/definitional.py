# Check straight from the definition: extend row 0 one term at a time, recompute the new
# antidiagonal by absolute differences, require the new leading entry to be 1.
import sys
def count(n,mode):
    tot=0
    def rec(anti,j):   # anti = last antidiagonal: anti[0]=x(0,j), anti[k]=x(k,j-k)
        nonlocal tot
        if j==n-1: tot+=1; return
        R=2**(j+2)+2
        lo = anti[0] + (1 if mode==0 else 0) if mode in (0,1) else -R
        for x in range(lo, R+1):
            new=[x]
            for k in range(len(anti)): new.append(abs(new[-1]-anti[k]))
            if new[-1]==1: rec(new,j+1)
    rec([1],0); return tot
mode=int(sys.argv[1]); print([count(n,mode) for n in range(1,int(sys.argv[2])+1)])
