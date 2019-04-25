#include <iostream>
#include <cstring>
#include <string>
using namespace std;
string a,b;
void dfs(long l1,long r1,long l2,long r2)
{
	long i;
	cout<<b[r2];
	if (l1<r1){
		for (i=l1;i<=r1;i++)
			if (a[i]==b[r2]){
				if (l1<=i-1) dfs(l1,i-1,l2,l2+i-1-l1); //left sub tree
				if (i+1<=r1)dfs(i+1,r1,l2+i-l1,r2-1); //right sub tree
				return;
			}
	}
}
main()
{
	long x;
	cin>>a>>b;
	x=a.size();
	dfs(0,x-1,0,x-1);
}