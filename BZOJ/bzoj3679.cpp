#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
using namespace std;
typedef map<long long,long long> Ans;
Ans dp[30][10];
long long sum[30][10];
int digits[30];
long long solve(long long n,long long fn){
    if (n==0) return 0;
    memset(dp,0,sizeof(dp));
    memset(sum,0,sizeof(sum));
    //memset(digits,0,sizeof(digits));
    int num=0;
    while (n){
        digits[num++]=n%10;
        n/=10;
    } 
    for (int i=0;i<num;++i)
        for(int j=0;j<=9;++j) dp[i][j].clear();
    for (int i=1;i<10;++i){
        if (i>fn) break;
        dp[0][i][i]=1;
        sum[0][i]=1;
    }

    for (int i=1;i<num;++i){
        for (int j=1;j<=9;++j)
            for (int k=0;k<=9;++k)
                for (Ans::iterator m=dp[i-1][k].begin();m!=dp[i-1][k].end();m++){
                    if ((m->first)*j>fn) break;
                    dp[i][j][(m->first)*j]+=(m->second);
                    sum[i][j]+=(m->second);
                }
        
    }
   
    long long ans=0;
    for (int i=0;i<num-1;++i){
        for (int j=1;j<=9;++j){
            ans+=sum[i][j];
        }
    }
   // printf(" -ans1=%lld- ",ans);
    long long now=1;
    for (int i=num-1;i>=0;--i){
        for (int j=1;j<digits[i];++j)
            for (Ans::iterator k=dp[i][j].begin();k!=dp[i][j].end();k++){
                if (now*k->first>fn) break;
                ans+=k->second;
            }
        now*=digits[i];
        if (now==0 || now>fn) return ans;
    }
    return ans+1;
}
int main(){
    long long n,l,r;
    scanf("%lld%lld%lld",&n,&l,&r);
    //for (int i=0;i<=20;++i) printf("%lld ",solve(i,5));
    printf("%lld",solve(r-1,n)-solve(l-1,n));
}