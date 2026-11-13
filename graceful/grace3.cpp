// A399946 via edge-first enumeration: a graceful path on {0..n-1} is a Hamiltonian path
// whose edge differences are exactly {1..n-1}. Place differences d = n-1, n-2, ..., 1, each as
// an edge {x, x+d}, keeping max degree <= 2 and no cycles (union-find with rollback).
// Each undirected path is found once (it corresponds to 2 permutations); the Gilbreath
// terminal value is invariant under reversal. Prune: every remaining difference must still
// fit between two vertices of degree < 2.
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef unsigned long long u64;
static int n, deg[64], adj[64][2], par[64], sz[64];
static u64 M; // vertices with degree < 2
static u64 paths, hist[64];
static int stk[256], sp;
static int find(int x){ while(par[x]!=x) x=par[x]; return x; }
static void leaf(){
  int s=-1; for(int v=0;v<n;v++) if(deg[v]==1){s=v;break;}
  int row[64], prev=-1, cur=s;
  for(int i=0;i<n;i++){ row[i]=cur; int nx=(adj[cur][0]!=prev)?adj[cur][0]:adj[cur][1]; if(deg[cur]==1&&i>0) nx=-1; prev=cur; cur=nx; }
  for(int len=n;len>1;len--) for(int i=0;i<len-1;i++) row[i]=abs(row[i]-row[i+1]);
  paths++; hist[row[0]]++;
}
static void place(int d){
  if(d==0){ leaf(); return; }
  for(int e=d;e>=1;e--) if(!(M&(M>>e))) return;      // feasibility prune
  for(int x=0;x+d<n;x++){
    int y=x+d; if(deg[x]>=2||deg[y]>=2) continue;
    int rx=find(x), ry=find(y); if(rx==ry) continue;
    if(sz[rx]<sz[ry]){int t=rx;rx=ry;ry=t;}
    par[ry]=rx; sz[rx]+=sz[ry];
    adj[x][deg[x]++]=y; adj[y][deg[y]++]=x;
    u64 oldM=M; if(deg[x]==2) M&=~(1ULL<<x); if(deg[y]==2) M&=~(1ULL<<y);
    place(d-1);
    M=oldM; deg[x]--; deg[y]--; par[ry]=ry; sz[rx]-=sz[ry];
  }
}
int main(int argc,char**argv){
  n=atoi(argv[1]);
  if(n==1){ printf("1 0 perms=1\n"); return 0; }
  for(int v=0;v<n;v++){par[v]=v;sz[v]=1;deg[v]=0;} M=(n==64)?~0ULL:((1ULL<<n)-1);
  // optional split of the first branching for parallel runs: argv[2]=P, argv[3]=p (on d=n-2 choice) -- not used
  place(n-1);
  int mx=-1; for(int t=0;t<64;t++) if(hist[t]) mx=t;
  printf("%d %d perms=%llu values:",n,mx,2*paths); for(int t=0;t<64;t++) if(hist[t]) printf(" %d",t); printf("\n");
}
