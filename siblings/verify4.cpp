// Independent verifier #4: level-by-level forward merge using sorted vectors
// (sort + reduce), states encoded in mixed radix B = 2^(n-1-m)+1, row-0 weights explicit.
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
typedef unsigned long long u64; typedef unsigned __int128 u128;
struct E{u64 k,c;}; static bool lt(const E&a,const E&b){return a.k<b.k;}
static void reduce(std::vector<E>& v){ std::sort(v.begin(),v.end(),lt); size_t w=0;
  for(size_t i=0;i<v.size();i++){ if(w&&v[w-1].k==v[i].k) v[w-1].c+=v[i].c; else v[w++]=v[i]; } v.resize(w); v.shrink_to_fit(); }
static void mergeinto(std::vector<E>& acc, std::vector<E>& buf){ reduce(buf);
  std::vector<E> out; out.reserve(acc.size()+buf.size()); size_t i=0,j=0;
  while(i<acc.size()||j<buf.size()){
    if(j==buf.size()||(i<acc.size()&&acc[i].k<buf[j].k)) out.push_back(acc[i++]);
    else if(i==acc.size()||buf[j].k<acc[i].k) out.push_back(buf[j++]);
    else { E e=acc[i++]; e.c+=buf[j++].c; out.push_back(e);} }
  acc.swap(out); std::vector<E>().swap(out); buf.clear(); }
int main(int argc,char**argv){
  int MODE=atoi(argv[1]), n=atoi(argv[2]); size_t BUF=argc>3?atoll(argv[3]):40000000;
  auto B=[&](int m)->u64{ return (1ULL<<(n-1-m))+1; };
  std::vector<E> L; { int m=n-1; u64 k=0,b=B(m); for(int i=0;i<m;i++) k=k*b+1; L.push_back({k,1}); }
  for(int m=n-1;m>=1;m--){
    std::vector<E> acc, buf; buf.reserve(BUF);
    u64 b=B(m), b2=B(m-1); int s[16],t[16],ch[16];
    for(const E& e:L){
      u64 k=e.k; for(int i=m-1;i>=0;i--){ s[i]=k%b; k/=b; }
      u64 c=e.c*(u64)((MODE==1)?1:(s[0]>0?2:1));
      for(int i=0;i<m-1;i++) ch[i]=0;
      while(true){
        bool ok=true;
        for(int i=0;i<m-1;i++){int x=s[i],y=s[i+1]; if(!ch[i]) t[i]=x+y; else {if(y==0||x<y){ok=false;break;} t[i]=x-y;}}
        if(ok){ u64 key=0; for(int i=0;i<m-1;i++){ if((u64)t[i]>=b2){fprintf(stderr,"radix overflow\n");return 1;} key=key*b2+t[i]; }
                buf.push_back({key,c}); if(buf.size()>=BUF) mergeinto(acc,buf); }
        int i=0; while(i<m-1&&ch[i]){ch[i]=0;i++;} if(i>=m-1) break; ch[i]=1;
      }
    }
    mergeinto(acc,buf); std::vector<E>().swap(L); L.swap(acc);
    fprintf(stderr,"level m=%d states=%zu\n",m-1,L.size());
  }
  u128 tot=0; for(auto&e:L) tot+=e.c;
  char bb[64]; int q=63; bb[q]=0; if(!tot) bb[--q]='0'; while(tot){bb[--q]='0'+(int)(tot%10); tot/=10;}
  printf("%d %s\n",n,bb+q);
}
