#include <iostream>
#include <iomanip>
using namespace std;
long n,x[200001],y[200001],s[200001];
bool check(double v)
{
	long i;
	long double now;
	now=0;
	for (i=1;i<=n;i++){
		now+=(long double)(s[i])/v;
		if (now<x[i]) now=x[i];
		if (now>y[i]) return false;
	}
	return true;
}
main()
{
	long i;
	long double L,R,Mid;
	bool t;
	cin>>n;
	R=0;
	for (i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>s[i];
	L=0; R=100000000;
	while (R-L>1e-6){
		Mid=(L+R)/2;
		if (check(Mid)) R=Mid;
		else L=Mid;
	}
	cout<<setiosflags(ios::fixed)<<setprecision(2)<<L;
}