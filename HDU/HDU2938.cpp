#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;


#define CRT_N 100000
long long a[CRT_N],m[CRT_N];
long long mul(long long x,long long y,long long mod){
    long long ans=0;
    x%=mod;
    y%=mod;
    while (y){
        if (y&1) ans=(ans+x)%mod;
        x=(x<<1)%mod;
        y>>=1;
    }
    return ans;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if (b==0){ x=1; y=0; return a;}
    long long t=exgcd(b,a%b,y,x);
    y=y-(a/b)*x;
    return t;
}
long long exCRT(int len){
    long long M=m[0];
    long long x=a[0];
    for (int i=1;i<len;++i){
        long long t,y,c;
        long long b=m[i];
        long long gcd=exgcd(M,b,t,y);
        c=((a[i]-x)%b+b)%b;
        if (c%gcd!=0) return -1;
        c/=gcd; b/=gcd; 
        t=mul(t,c,b); t=(t+b)%b;
        x=x+t*M;
        M*=b; x=(x%M+M)%M;
    }
    return x;
}


int n;
int list[100001];
int ti[100001];
int in[100001];
int to[100001];
int d[100001];
int di;
bool flag;
int dfs(int x,int s){
    int t;
    ti[x]=s;
    d[x]=di;
    if (ti[list[x]]==-1) t=dfs(list[x],s+1);
    else t=ti[x];
    if (d[to[x]]!=d[x]) flag=false;
    m[x-1]=t;
    a[x-1]=((ti[to[x]]-ti[x])%t+t)%t;
    return t;
}


int main()
{
    while (~scanf("%d",&n)){
        if (n==0) break;
        memset(ti,-1,sizeof(ti));
        memset(to,0,sizeof(to));
        memset(d,-1,sizeof(d));
        for (int i=1;i<=n;++i){
            scanf("%d",&list[i]);
            ++to[list[i]];
        }
        for (int i=1;i<=n;++i){
            scanf("%d",&to[i]);
        }
        flag=true;

        for (int i=1;i<=n;++i)
            if (in[i]>0) {flag=false; break;}
        if (!flag) continue;
        di=0;
        for (int i=1;i<=n;++i)
            if (flag && ti[i]==-1){
                dfs(i,1);
                ++di;
            }
        
        //for (int i=0;i<n;++i) printf("%lld %lld\n",a[i],m[i]);
        if (flag) printf("%lld\n",exCRT(n));
        else printf("-1\n");
    }
    return 0;
}