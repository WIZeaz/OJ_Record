#include <iostream>
using namespace std;
long ti[101],v[101];
long dp[1001];
int main()
{
	long t,m,i,j;
	long ans;
	cin>>t>>m;
	for (i=1;i<=m;i++)
		cin>>ti[i]>>v[i];
	for (i=1;i<=m;i++){
		for (j=t;j>=ti[i];j--)
			dp[j]=max(dp[j],dp[j-ti[i]]+v[i]);
	}
	ans=0;
	for (i=0;i<=t;i++)
		ans=max(ans,dp[i]);
	cout<<ans;
}