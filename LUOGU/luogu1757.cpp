#include <iostream>
#include <vector>
using namespace std;
int a[1001],b[1001];
vector<int> item_list[1001];
int dp[1001];
int main(){
    int n,m;
    scanf("%d%d",&m,&n);
    for (int i=0;i<n;++i){
        int t;
        scanf("%d%d%d",&a[i],&b[i],&t);
        item_list[t].push_back(i);
    }
    for (int i=0;i<=1000;++i){
        for (int j=m;j>=0;--j) 
            for (auto k:item_list[i])
                if (j>=a[k]) dp[j]=max(dp[j],dp[j-a[k]]+b[k]);

    }
    int ans=0;
    for (int i=0;i<=m;++i) ans=max(ans,dp[i]);
    printf("%d",ans);
}