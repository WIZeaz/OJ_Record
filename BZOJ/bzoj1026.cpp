#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
long long dp[101][10];
int digits[101];
int abs(int a){
    if (a<0) return -a;
    return a;
}
void init(){
    //dp solve problem
    //memset(dp,0,sizeof(dp));
    int MAXNUM=10;
    for (int i=0;i<10;++i)
        dp[0][i]=1;
    for (int i=1;i<MAXNUM;++i)
        for (int j=0;j<10;++j)
            for (int k=0;k<10;++k)
                if (abs(j-k)>=2){
                    dp[i][j]+=dp[i-1][k];
                }
}
long long solve(long long n){
    if (n==0) return 0;
    //memset(digits,0,sizeof(digits));
    int num=0;
    while (n){
        digits[num++]=n%10;
        n/=10;
    }
    //count answer
    long long ans=0;
    for (int i=0;i<num-1;++i)
        for (int j=1;j<10;++j) ans+=dp[i][j];
    for (int i=1;i<digits[num-1];++i) ans+=dp[num-1][i];
    //if (num==1) ++ans;
    for (int i=num-2;i>=0;--i){
        for (int j=0;j<digits[i];++j)
            if (abs(j-digits[i+1])>=2) ans+=dp[i][j];
        if (abs(digits[i]-digits[i+1])<2) return ans;
    }
    return ans+1;
}
int main(){
    long long a,b;
    init();
    scanf("%lld%lld",&a,&b);
    printf("%lld",solve(b)-solve(a-1));
}