#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;
inline int rpow(long long x,int y){
    long long l=0;
    long long r=1LL<<(long long)(62/y)+1;
    while (l+1<r){
        long long mid=l+r>>1;
        long long s=1;
        for (int i=0;i<y;++i) s*=mid;
        if (s<=x) l=mid;
        else r=mid;
    }
    return l;
}
int num=0;
int p[4001];
bool isPrime[4001];
void seive(){
    memset(isPrime,true,sizeof(isPrime));
    for (int i=2;i<=4000;++i){
        if (isPrime[i]) p[num++]=i;
        for (int j=0;j<num && i*p[j]<=4000;++j){
            isPrime[i*p[j]]=false;
            if (i%p[j]==0) break;
        }
    }   
}
int main(){
    int T;
    seive();
    scanf("%d",&T);
    while (T--){
        long long n;
        scanf("%lld",&n);
        int len=rpow(n,5);
        int ans=99999999;
        for (int i=0;p[i]<=len && i<num;++i)
            if (n%p[i]==0){
                int t=0;
                while (n%p[i]==0) {n/=p[i]; ++t;}
                ans=min(ans,t);
            }
        if (n>1){
            long long l1=rpow(n,4);
            if (l1*l1*l1*l1==n) ans=min(ans,4);
            else {
                l1=rpow(n,3);
                if (l1*l1*l1==n) ans=min(ans,3);
                else {
                    l1=rpow(n,2);
                    if (l1*l1==n) ans=min(ans,2);
                    else ans=1;
                }
            }
        }
        printf("%d\n",ans);
    }
}