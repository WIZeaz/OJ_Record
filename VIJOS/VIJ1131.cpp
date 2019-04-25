#include <iostream>
using namespace std;
long gcd(long x,long y)
{
	long c;
	c=x%y;
	while (c!=0){
		x=y;
		y=c;
		c=x%y;
	}
	return y;
}
main()
{
	long p,q,x,y,i,s;
	long long ans=0;
	cin>>x>>y;
	s=x*y;
	for (i=x;i<=y;i++){
		if (s%i==0)
			if (gcd(i,s/i)==x) ans++;
	}
	cout<<ans;
}