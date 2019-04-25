#include <iostream>
#include <cstring>
using namespace std;
const long INF=100000000;
long road[201][201],w[201][201];
long ans,n;
int main()
{
	long m,t1,t2,i,j,k;
	cin.sync_with_stdio(false);
	while (cin>>n>>m){
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				road[i][j]=INF;
		for (i=1;i<=m;i++){
			cin>>t1>>t2;
			cin>>road[t1][t2];
			road[t2][t1]=road[t1][t2];
		}
		memcpy(w,road,sizeof(w));
		ans=INF;
		for (k=1;k<=n;k++){
			for (i=1;i<k;i++)
				for (j=i+1;j<k;j++)
						ans=min(ans,w[i][k]+w[k][j]+road[i][j]);
						
			for (i=1;i<=n;i++)
				for (j=1;j<=n;j++)
					if (i!=j)
						road[i][j]=min(road[i][j],road[i][k]+road[k][j]);
		}
		if (ans<INF) cout<<ans<<endl;
		else cout<<"No solution.\n";
	}
}