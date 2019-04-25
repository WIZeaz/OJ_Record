#include <iostream>
using namespace std;
long a[50001],f[50001],e[11];
void Qsort(long l,long r)
{
	long i,j,k,mid,midx;
	i=l; j=r; mid=a[(l+r)/2]; midx=f[(l+r)/2];
	while (i<=j){
		while (a[i]>mid || (a[i]==mid && f[i]<midx)) i++;
		while (a[j]<mid || (a[j]==mid && f[j]>midx)) j--;
		if (i<=j){
			k=a[i]; a[i]=a[j]; a[j]=k;
			k=f[i]; f[i]=f[j]; f[j]=k;
			i++; j--;
		}
	}
	if (l<j) Qsort(l,j);
	if (i<r) Qsort(i,r);
}
int main()
{
	long n,k,i,j;
	cin>>n>>k;
	for (i=1;i<=10;i++) cin>>e[i];
	for (i=1;i<=n;i++){cin>>a[i]; f[i]=i;}
	Qsort(1,n);
	j=0;
	for (i=1;i<=n;i++){
		a[i]+=e[(i-1)%10+1];
	}
	Qsort(1,n);
	for (i=1;i<=k;i++) cout<<f[i]<<' ';
	return 0;
}