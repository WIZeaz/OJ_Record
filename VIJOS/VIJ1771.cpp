#include <iostream>
using namespace std;
void Qsort(long l,long r,long a[],long b[],long c[])
{
	long i,j,mid,mid2,k;
	i=l; j=r; mid=a[(l+r)/2]; mid2=b[(l+r)/2];
	while (i<=j){
		while (a[i]>mid || (a[i]==mid && b[i]<mid2)) i++;
		while (a[j]<mid || (a[j]==mid && b[j]>mid2)) j--;
		if (i<=j){
			k=a[i]; a[i]=a[j]; a[j]=k;
			k=b[i]; b[i]=b[j]; b[j]=k;
			k=c[i]; c[i]=c[j]; c[j]=k;
			i++; j--;
		}
	}
	if (l<j) Qsort(l,j,a,b,c);
	if (i<r) Qsort(i,r,a,b,c);
}
main()
{
	long n,r,q,i,j,w[200001],s[200001],num[200001];
	cin>>n>>r>>q;
	for (i=1;i<=2*n;i++) {cin>>s[i]; num[i]=i;}
	for (i=1;i<=2*n;i++) cin>>w[i]; 
	for (i=1;i<=r;i++){
		Qsort(1,2*n,s,num,w);
		for (j=1;j<=2*n;j=j+2)
			if (w[j]>=w[j+1]) s[j]++;
			else s[j+1]++;
	}
	Qsort(1,2*n,s,num,w);
	cout<<num[q];
}