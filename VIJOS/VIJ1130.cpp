#include <iostream>
using namespace std;
int main()
{
	long d[1001],n,i,j;
	cin>>n;
	d[1]=1;
	for (i=2;i<=n;i++){
		d[i]=0;
		for (j=1;j<=i/2;j++)
			d[i]+=d[j];
		d[i]++;
	}
	cout<<d[n];
	return 0;
}