#include <iostream>
#include <cstring>
using namespace std;
long sum[500001],rest[100000];
int main()
{
	long i,j,k,n,t,ans;
	ios::sync_with_stdio(false);
	cin>>n>>k;
	memset(rest,0,sizeof(rest));
	sum[0]=0;
	rest[0]=1;
	ans=0;
	for (i=1;i<=n;i++){
		cin>>t;
		sum[i]=sum[i-1]+t;
		rest[sum[i]%k]++;
	}
	for (i=0;i<k;i++){
		ans+=rest[i]*(rest[i]-1)/2;
		ans%=1234567;
	}
	cout<<ans;
}