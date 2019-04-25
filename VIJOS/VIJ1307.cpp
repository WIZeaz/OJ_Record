#include <iostream>
using namespace std;
main()
{
	long long s;
	long n,i;
	cin>>n;
	s=0;
	for (i=1;i<=n;i++) s+=i*i;
	cout<<s;
}