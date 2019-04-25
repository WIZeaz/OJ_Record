#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct node{
	int v,val;
	node (int a,int b):v(a),val(b){}
	node(){}
};
vector <node> list[10001];
int sum,root,Min;
int mxson[10001],num[10001],dis[10001];
int tot;
int ans;
int n,k;
bool vis[10001];
void getroot(int x)
{
	vis[x]=true;
	num[x]=1;
	mxson[x]=0;
	for (int i=0;i<list[x].size();++i)
		if (!vis[list[x][i].v]){
			getroot(list[x][i].v);
			num[x]+=num[list[x][i].v];
			mxson[x]=max(mxson[x],num[list[x][i].v]);
		}
	mxson[x]=max(mxson[x],sum-num[x]);
	if (mxson[x]<Min) {Min=mxson[x]; root=x;}
	vis[x]=false;
}
void getdis(int x,int dist)
{
	++tot;
	dis[tot]=dist;
	vis[x]=true;
	for (int i=0;i<list[x].size();++i)
		if (!vis[list[x][i].v]){
			getdis(list[x][i].v,dist+list[x][i].val);
		}
	vis[x]=false;
}
int solve(int x,int len){
	int s=0;
	tot=0;
	getdis(x,len);
	sort(dis+1,dis+tot+1);
	int l,r,mid;
	l=1; r=tot;
	while (l<r)
		if (dis[l]+dis[r]<=k) {s+=r-l; ++l;}
		else --r;
	return s;
}
void divide(int x){
	ans+=solve(x,0);
	vis[x]=true;
	for (int i=0;i<list[x].size();++i)
		if (!vis[list[x][i].v]){
			ans-=solve(list[x][i].v,list[x][i].val);
			sum=num[list[x][i].v];
			Min=num[list[x][i].v];
			getroot(list[x][i].v);
			//cout<<list[x][i].v<<' '<<root<<endl;
			divide(root);
		}
	vis[x]=false;
}
int main()
{
	memset(vis,false,sizeof(vis));
	while (~scanf("%d%d",&n,&k)){
		if (n==0 && k==0) break;
		for (int i=1;i<=n;++i) list[i].clear();
		for (int i=1;i<n;++i){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			list[u].push_back(node(v,c));
			list[v].push_back(node(u,c));
		}
		sum=n; Min=n;
		ans=0;
		getroot(1);
		divide(root);
		printf("%d\n",ans);
	}
	return 0;
}