#include <iostream>
#include <cstring>
using namespace std;
bool d[2001][2001];//d[i][j]=d[i-h[k]][j]||d[i][j-h[k]]||d[i][j]
long h[201];
int main()
{
	long n,i,j,k;
	cin>>n;
	for (i=1;i<=n;i++) cin>>h[i];
	memset(d,false,sizeof(d));
	d[0][0]=true;
	for (k=1;k<=n;k++)
		for (i=2000;i>=0;i--)
			for (j=2000;j>=0;j--){
				if (i>=h[k]) d[i][j]=d[i][j] || d[i-h[k]][j];
				if (j>=h[k]) d[i][j]=d[i][j] || d[i][j-h[k]];
			}
	for (i=2000;i>=1;i--)
		if (d[i][i]) {cout<<i; return 0;}
	cout<<"Impossible\n";
	return 0;
}