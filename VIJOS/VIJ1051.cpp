#include<iostream>
using namespace std;
const long mx[]={0,0,0,0,1,1,1,-1,-1,-1,2,-2};
const long my[]={1,2,-1,-2,-1,0,1,-1,0,1,0,0};
//12
char map[201][201];
void dfs(long x,long y)
{
	long i;
	map[x][y]='-';
	for (i=0;i<=11;i++)
		if (map[x+mx[i]][y+my[i]]=='#')
			dfs(x+mx[i],y+my[i]);
		
}
int main()
{
	long n,m,i,j,ans=0;
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++) cin>>map[i][j];
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (map[i][j]=='#') {
				ans++;
				dfs(i,j);
			}
	cout<<ans;
	return 0;
}