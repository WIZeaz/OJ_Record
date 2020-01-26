#include <bits/stdc++.h>
using namespace std;
vector<int> to[3001];
long long dp[3001][3];// 0: no select no cover 1: no select but cover 2:select & cover
long long k[3001];
const long long INF=0x3f3f3f3f3f3f3f3f;
void solve(int x){
    long long s1=0;
    long long s2=0;
    long long mins=INF;
    dp[x][0]=0;
    for (auto i:to[x]){
        solve(i);
        s1+=min(dp[i][0],min(dp[i][2],dp[i][1]));
        s2+=min(dp[i][2],dp[i][1]);
        mins=min(mins,dp[i][2]-dp[i][1]);
        dp[x][0]+=min(dp[i][2],dp[i][1]);
    }
    dp[x][1]=s2+max(0LL,mins);
    dp[x][2]=s1+k[x];
}
int deg[3001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        int ind,m;
        scanf("%d",&ind);
        scanf("%lld%d",&k[ind],&m);
        while(m--){
            int t;
            scanf("%d",&t);
            to[ind].push_back(t);
            deg[t]++;
        }
    }
    int root=0;
    for (int i=1;i<=n;++i) if (!deg[i]) {root=i; break;}
    solve(root);
    //cout<<dp[root][1]<<' '<<dp[root][2]<<endl;
    printf("%lld",min(dp[root][1],dp[root][2]));
}