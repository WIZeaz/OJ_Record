#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
struct node
{
	int l,r,lc,rc,ans;
};
struct point
{
	int val,rank;
	bool operator < (const point& c) const{
		return val<c.val;
	}
};
point a[100001];
int b[100001];
int list[100001];
struct segment_tree{
	int num;
	node tr[2000001];
	void build(int x,int l,int r){
		tr[x].l=l; tr[x].r=r; tr[x].ans=0;
		if (l!=r){
			int mid=(l+r)>>1;
			++num;
			tr[x].lc=num;
			++num;
			tr[x].rc=num;
			build(tr[x].lc,l,mid);
			build(tr[x].rc,mid+1,r);
		}
	}
	int insert(int x,int pos){
		int t=++num;
		tr[t]=tr[x];
		int mid=(tr[x].l+tr[x].r)>>1;
		if (tr[x].l==tr[x].r){
			tr[t].ans+=1;
		}else{
			if (pos<=mid){
				tr[t].lc=insert(tr[x].lc,pos);
			}
			else{
				tr[t].rc=insert(tr[x].rc,pos);
			}
			tr[t].ans=tr[tr[t].lc].ans+tr[tr[t].rc].ans;
		}
		return t;
	}
	int query(int x1,int x2,int k) //list l-1 and r
	{
		int ans=tr[tr[x2].lc].ans-tr[tr[x1].lc].ans;
		if (tr[x1].l==tr[x1].r) return tr[x1].l;
		if (ans>=k){
			return query(tr[x1].lc,tr[x2].lc,k);
		} else {
			return query(tr[x1].rc,tr[x2].rc,k-ans);
		}
	}
} tr;



int main()
{
	int n,m,l,r,k;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i){
		scanf("%d",&a[i].val);
		a[i].rank=i;
	}
	
	sort(a+1,a+n+1);
	for (int i=1;i<=n;++i){
		b[a[i].rank]=i;
	}
	tr.num=0;
	tr.build(0,1,n);
	list[0]=0;
	for (int i=1;i<=n;++i){
		list[i]=tr.insert(list[i-1],b[i]);
	}
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",a[tr.query(list[l-1],list[r],k)].val);
	}
	return 0;
}