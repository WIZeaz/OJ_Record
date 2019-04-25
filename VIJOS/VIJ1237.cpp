#include <iostream>
using namespace std;
long n,a[30001];
const double st=0.6180339887498949;
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
			i++;
			j--;
		}
	}
	if (i<r) Qsort(i,r);
	if (l<j) Qsort(l,j);
}
double abs(double x)
{
	if (x<0) return -x;
	return x;
}
long find(long t)
{
	long l=t+1,r=n,mid;
	while (r-l>1){
		mid=(l+r)/2;
		if ((double)a[t]/(double)a[mid]<st) r=mid;
		else l=mid;
	}
	if (abs((double )a[t]/(double)a[l]-st)<abs((double )a[t]/(double)a[r]-st))
		return l;
	else return r;
}
main()
{
	long i,t;
	long m1,m2;
	double MinD;
	cin>>n;
	for (i=1;i<=n;i++) cin>>a[i];
	Qsort(1,n);
	MinD=1e5;
	for (i=1;i<n;i++){
		t=find(i);
		if (abs((double )a[i]/(double )a[t]-st)<MinD){
			MinD=abs((double )a[i]/(double )a[t]-st);
			m1=i;
			m2=t;
		}
	}
	cout<<a[m1]<<'\n'<<a[m2];
}