#include <iostream>
#include <cstring>
using namespace std;
struct item{
	long v[3],w[3],s;
} t[1001];
long num;
long d[50001];
long list[1001];
int main()
{
	long n,m,i,j,k,v,p,q,ans;
	cin.sync_with_stdio(false);
	cin>>m>>n;
	num=0;
	for (i=1;i<=n;i++){
		cin>>v>>p>>q;
		if (q==0){
			num++;
			list[i]=num;
			t[num].v[0]=v;
			t[num].w[0]=v*p;
			t[num].s=0;
		} else {
			q=list[q];
			t[q].s++;
			t[q].v[t[q].s]=v;
			t[q].w[t[q].s]=v*p;
		}
	}
	memset(d,0,sizeof(d));
	for (i=1;i<=num;i++)
		for (j=m;j>=t[i].v[0];j--){
			d[j]=max(d[j],d[j-t[i].v[0]]+t[i].w[0]);
			for (k=1;k<=t[i].s;k++)
				if (j-t[i].v[0]-t[i].v[k]>=0)
					d[j]=max(d[j],d[j-t[i].v[0]-t[i].v[k]]+t[i].w[0]+t[i].w[k]);
			if (t[i].s==2 && j-t[i].v[0]-t[i].v[1]-t[i].v[2]>=0)
				d[j]=max(d[j],d[j-t[i].v[0]-t[i].v[1]-t[i].v[2]]+t[i].w[0]+t[i].w[1]+t[i].w[2]);
		}
	ans=0;
	for (i=0;i<=m;i++) ans=max(ans,d[i]);
	cout<<ans;
    return 0;
}
