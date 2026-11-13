# Independent implementation: plain Python dictionaries, explicit row-0 choices, no bit packing,
# no closed forms, no cache tricks. Forward BFS over full columns rows 1..m.
import sys
from collections import Counter
from itertools import product
def a(n,mode):
    L=Counter({(1,)*(n-1):1})
    for m in range(n-1,-1,-1):
        M=Counter()
        for s,c in L.items():
            if m==0: M[()]+=c; continue
            s0=s[0]
            r0 = [1] if mode==1 else ([+1,-1] if s0>0 else [+1])  # row-0 step choices
            nxt=[]
            for x,y in zip(s,s[1:]):
                ch={x+y}
                if x-y>=0: ch.add(x-y)
                nxt.append(sorted(ch))
            for t in product(*nxt):
                M[t]+=c*len(r0)
        L=M
    return sum(L.values())
mode=int(sys.argv[1]); n=int(sys.argv[2]); print(n,a(n,mode))
