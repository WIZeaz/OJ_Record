#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define CRT_N 200000
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
/*long long CRT(int len){
    long long M=1;
    long long ans=0;
    for (int i=0;i<len;++i) M*=m[i];
    for (int i=0;i<len;++i){
        long long x,y;
        long long gcd=exgcd(M/m[i],m[i],x,y);
        x=(x%m[i]+m[i])%m[i];
        ans=(ans+M/m[i]*x*a[i]%M)%M;
    }
    return ans;
}*/
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
    if (x==0) return M;
    return x;
}
int number[100];
bool vis[100];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        int n;
        memset(vis,false,sizeof(vis));
        scanf("%d",&n);
        for (int i=0;i<n;++i){
            int t;
            scanf("%d",&t);
            number[t-1]=i;
        }
        int now=0,p;
        for (int i=0;i<n;++i){
            p=1;
            while (now!=number[i]){
                if (!vis[now]) ++p;
                now=(now+1)%n;
            }
            vis[now]=true;
            a[i]=p%(n-i);
            m[i]=n-i;
        }
       // for (int i=0;i<n;++i) cout<<a[i]<<' '<<m[i]<<endl;
        long long t=exCRT(n);
        if (t==-1) printf("Creation August is a SB!\n");
        else printf("%lld\n",t);
    }
}