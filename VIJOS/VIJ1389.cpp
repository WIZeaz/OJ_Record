#include <iostream>
#include <cstring>
#include <string>
using namespace std;
long a[1001];
string f[1001];
void Qsort(long l,long r)
{
	long i,j,k,mid;
	string k2;
	i=l; j=r; mid=a[(l+r)/2];
	while (i<=j){
		while (a[i]<mid) i++;
		while (a[j]>mid) j--;
		if (i<=j){
			k=a[i];
			a[i]=a[j];
			a[j]=k;
			k2=f[i]; f[i]=f[j]; f[j]=k2;
			i++; j--;
		}
	}
	if (l<j) Qsort(l,j);
	if (i<r) Qsort(i,r);
}
main()
{
	long n,i,past;
	char tmp;
	tmp=' ';
	n=0;
	while (tmp!='\n'){
		n++;
		cin>>a[n];
		cin.get(tmp);
	}
	for (i=1;i<=n;i++) cin>>f[i];
		Qsort(1,n);
	for (i=1;i<=n;i++) cout<<f[i]<<endl;
}