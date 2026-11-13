// A399946: max terminal value of the Gilbreath reduction over graceful paths of order n.
// Backtracking over graceful permutations; the antidiagonal of the difference triangle
// is updated incrementally (O(n) per node). Symmetry: reversal and complement v->n-1-v
// preserve gracefulness and the terminal value, so we fix pi(0) <= (n-1)/2 and count both
// halves only for checking. Also records the full set of terminal values.
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef unsigned long long u64;
static int n; static int D[40][40]; static bool used[40], usedd[40];
static u64 cnt; static u64 hist[64]; static u64 AV; static u64 DU;
static void bt(int idx){
  if(idx==n){ cnt++; hist[D[n-1][n-1]]++; return; }
  // prune: every unused difference d needs a pair {x, x+d} inside AV = unused vertices + current end
  { u64 av=AV|(1ULL<<D[idx-1][0]); u64 du=DU;
    while(du){ int d=__builtin_ctzll(du); du&=du-1; if(!(av&(av>>d))) return; } }
  for(int v=0; v<n; v++){
    if(used[v]) continue;
    int d=abs(v-D[idx-1][0]); if(d==0||usedd[d]) continue;
    used[v]=usedd[d]=true; AV&=~(1ULL<<v); DU&=~(1ULL<<d);
    int* P=D[idx-1]; int* Q=D[idx]; Q[0]=v;
    for(int k=1;k<=idx;k++) Q[k]=abs(Q[k-1]-P[k-1]);
    bt(idx+1);
    used[v]=usedd[d]=false; AV|=1ULL<<v; DU|=1ULL<<d;
  }
}
int main(int argc,char**argv){
  n=atoi(argv[1]); int lo=argc>2?atoi(argv[2]):0, hi=argc>3?atoi(argv[3]):n-1;
  if(n==1){ printf("1 0 count=1\n"); return 0; }
  for(int s=lo;s<=hi;s++){ memset(used,0,sizeof used); memset(usedd,0,sizeof usedd);
    AV=((1ULL<<n)-1)&~(1ULL<<s); DU=((1ULL<<n)-1)&~1ULL;
    used[s]=true; D[0][0]=s; bt(1); used[s]=false; }
  int mx=-1; for(int t=0;t<64;t++) if(hist[t]) mx=t;
  printf("%d %d count=%llu values:",n,mx,cnt); for(int t=0;t<64;t++) if(hist[t]) printf(" %d",t); printf("\n");
}
