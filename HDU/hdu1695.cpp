/*
Linear Sieve 
适用于各种积性函数
*/
#include <iostream>
#include <cstring>
using namespace std;
#define N 200000
int primeList[N+1];
bool isPrime[N+1];
int mo[N+1];
int num;
void Sieve(int n)
{
    num=0;
    memset(isPrime,true,sizeof(isPrime));
    mo[1]=1;
    for (int i=2;i<=n;++i){
        if (isPrime[i]) {
            primeList[num]=i;
            mo[i]=-1;
            ++num;
        }
        for (int j=0;j<num && primeList[j]*i<=n;++j){
            isPrime[primeList[j]*i]=false;
            if (i%primeList[j]==0){ mo[primeList[j]*i]=0; break;}
            else mo[primeList[j]*i]=-mo[i];
        }
    }
}
long long solve(int b,int d)
{
    int len=b<d?b:d;
    long long ans1=0;
    long long ans2=0;
    for (int i=1;i<=len;++i){
        ans1+=mo[i]*(long long)(b/i)*(long long)(d/i);
        ans2+=mo[i]*(long long)(len/i)*(long long)(len/i);
    }
    return ans1-ans2/2;
}
int main()
{
    int a,b,c,d,k;
    int T;
    Sieve(150000);
    scanf("%d",&T);
    for (int i=1;i<=T;++i){
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        if (k==0) printf("Case %d: %d\n",i,0);
        else {
            b/=k; d/=k;
            printf("Case %d: %lld\n",i,solve(b,d));
        }
    }
    return 0;
}