#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100001];
int d[100001];
int stones[100001];
int main(){
	int L,l,r,m;
	scanf("%d%d%d%d",&L,&l,&r,&m);
	if (l==r){
		int ans=0;
		for (int i=0;i<m;++i){
			int pos;
			scanf("%d",&pos);
			if (pos%l==0) ++ans;
		}
		printf("%d",ans);
	} else {
		memset(d,0x3f,sizeof(d));
		memset(a,0,sizeof(a));
		int pos=0;
		int bound=r*r;
		for (int i=0;i<m;++i) scanf("%d",&stones[i]);
		sort(stones,stones+m);
		if (stones[0]>=bound) pos=bound;
		else pos=stones[0];
		a[pos]=1;
		for (int i=1;i<m;++i){
			pos+=min(bound,stones[i]-stones[i-1]);
			a[pos]=1;
		}
		pos+=min(L-stones[m-1],bound);
		L=pos;
		d[0]=0;
		for (int i=1;i<=L+r;++i){
			for (int j=max(i-r,0);j<=i-l;++j)
				d[i]=min(d[i],d[j]+a[i]);
		}
		int ans=d[L];
		for (int i=L+1;i<=L+r;++i) ans=min(ans,d[i]);
		printf("%d",ans);
	}
	return 0;
}