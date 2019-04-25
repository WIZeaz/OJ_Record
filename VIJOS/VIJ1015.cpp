#include <iostream>
using namespace std;
char amap[301][301],bmap[301][301];
bool visit[301][301];
long num,ans;
void dfs(long x,long y) //lower right
{
	long s=0;
	visit[x][y]=true;
	if ((amap[x][y]=='X' || amap[x][y]=='\\')){ 
		if(!visit[x+1][y+1]){
			dfs(x+1,y+1);
		}
		s++;
	}
	if ((amap[x][y-1]=='X' || amap[x][y-1]=='/')){
		if(!visit[x+1][y-1]){
			dfs(x+1,y-1);
		}
		s++;
	}
	if ((amap[x-1][y-1]=='X' || amap[x-1][y-1]=='\\')){
		if(!visit[x-1][y-1]){
			dfs(x-1,y-1);
		}
		s++;
	}
	if ((amap[x-1][y]=='X' || amap[x-1][y]=='/')){
		if(!visit[x-1][y+1]){
			dfs(x-1,y+1);
		}
		s++;
	}
	
	if ((bmap[x][y]=='X' || bmap[x][y]=='\\')){ 
		if(!visit[x+1][y+1]){
			dfs(x+1,y+1);
		}
		s--;
	}
	if ((bmap[x][y-1]=='X' || bmap[x][y-1]=='/')){
		if(!visit[x+1][y-1]){
			dfs(x+1,y-1);
		}
		s--;
	}
	if ((bmap[x-1][y-1]=='X' || bmap[x-1][y-1]=='\\')){
		if(!visit[x-1][y-1]){
			dfs(x-1,y-1);
		}
		s--;
	}
	if ((bmap[x-1][y]=='X' || bmap[x-1][y]=='/')){
		if(!visit[x-1][y+1]){
			dfs(x-1,y+1);
		}
		s--;
	}
	if (s>=0) num+=s;
	else num-=s;
}
bool check(long x,long y)
{
	if ((amap[x][y]=='X' || amap[x][y]=='\\')) return true;
	if ((amap[x][y-1]=='X' || amap[x][y-1]=='/')) return true;
	if ((amap[x-1][y-1]=='X' || amap[x-1][y-1]=='\\')) return true;
	if ((amap[x-1][y]=='X' || amap[x-1][y]=='/')) return true;
	
	if ((bmap[x][y]=='X' || bmap[x][y]=='\\')) return true;
	if ((bmap[x][y-1]=='X' || bmap[x][y-1]=='/')) return true;
	if ((bmap[x-1][y-1]=='X' || bmap[x-1][y-1]=='\\')) return true;
	if ((bmap[x-1][y]=='X' || bmap[x-1][y]=='/')) return true;
	return false;
}
int main()
{
	long n,m,i,j;
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			cin>>amap[i][j];
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			cin>>bmap[i][j];
	ans=0;
	for (i=1;i<=n+1;i++)
		for (j=1;j<=m+1;j++)
			if (!visit[i][j] && check(i,j)){
				num=0;
				dfs(i,j);
				num/=2;
				if (num>0) ans+=num;
				else ans++;
			}
	cout<<ans;
}