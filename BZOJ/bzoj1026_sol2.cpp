#include <bits/stdc++.h>
using namespace std;
long long dp[20][11];
int digits[20];
long long dfs(int x,int y,int eq){
    if (x==0) return 1;
    if (!eq && ~dp[x][y]) return dp[x][y];
    int maxx=eq?digits[x-1]:9;
    long long ans=0;
    for (int i=0;i<=maxx;++i){
        if (y==10){
            if (i==0) ans+=dfs(x-1,10,eq&&(i==maxx));
            else ans+=dfs(x-1,i,eq&&(i==maxx));
        } else if (abs(y-i)>=2){
            ans+=dfs(x-1,i,eq&&(i==maxx));
        }
    }
    if (!eq) dp[x][y]=ans;
    return ans;
}
long long solve(long long n){
    int tot=0;
    while (n>0){
        digits[tot++]=n%10;
        n/=10;
    }
    return dfs(tot,10,1);
}
int main(){
    memset(dp,-1,sizeof(dp));
    long long a,b;
    cin>>a>>b;
    cout<<solve(b)-solve(a-1);
}