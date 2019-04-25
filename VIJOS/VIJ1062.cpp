#include <iostream>
using namespace std;
long d[1501];
long a[1501];
main()
{
	long n,i,j;
	cin>>n;
	for (i=1;i<=n;i++){
		cin>>d[i];
		a[i]=d[i]-d[i-1];
	}
	d[0]=0;
	for (i=1;i<=n;i++){
		for (j=i;j>=1;j--)
			if (a[j]>0){
				a[j]--;
				cout<<i-j+1<<' ';
				break;
			}
	}
}