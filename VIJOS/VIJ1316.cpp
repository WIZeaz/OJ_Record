#include <iostream>
#include <cstring>
using namespace std;
long a[101];
bool f[1001];
void Qsort(long l,long r)
{
	long i,j,k,mid;
	i=l; j=r; mid=a[(l+r)/2];
	while (i<=j){
		while (a[i]<mid) i++;
		while (a[j]>mid) j--;
		if (i<=j){
			k=a[i];
			a[i]=a[j];
			a[j]=k;
			i++; j--;
		}
	}
	if (l<j) Qsort(l,j);
	if (i<r) Qsort(i,r);
}
main()
{
	long n,i,s,past;
	cin>>n;
	s=n;
	for (i=1;i<=n;i++){
		cin>>a[i];
		if (f[a[i]]) s--;
		else f[a[i]]=true;
	}
	Qsort(1,n);
	cout<<s<<endl;
	past=0;
	for (i=1;i<=n;i++){
		if (a[i]!=past) cout<<a[i]<<' ';
		past=a[i];
	}
}