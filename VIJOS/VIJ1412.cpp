#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
long v[201],w[201],dp[5001][51];
long t[201];
bool compare(long a,long b)
{
	return a>b;
}
int main()
{
	long i,j,nk,n,V,k;
	long long ans=0;
	cin>>k>>V>>n;
	for (i=1;i<=n;i++) cin>>w[i]>>v[i];
	memset(dp,128,sizeof(dp));
	dp[0][1]=0;
	for (i=1;i<=n;i++){
		for (j=V;j>=w[i];j--){
			for (nk=1;nk<=k;nk++){
				t[2*nk-1]=dp[j][nk];
				t[2*nk]=dp[j-w[i]][nk]+v[i];
			}
			sort(t+1,t+2*k+1,compare);
			memcpy(dp[j],t,sizeof(dp[j]));
		}
	}
	for (i=1;i<=k;i++)
		ans+=dp[V][i];
	cout<<ans;
}