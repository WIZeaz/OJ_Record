#include <iostream>
using namespace std;
long d[2][200001];
long long lowbit(long long x)
{
	return x&(-x);
}
main()
{
	long long T,tmp,s;
	long n,i,j,l,r;
	cin>>n>>T;
	s=T;
	for (i=1;i<=n;i++){
		cin>>d[1][2*i-1];
		d[1][2*i-1]--;
	}
	j=1;
	while (T!=0){
		tmp=lowbit(T);
		T=T^tmp;
		tmp=tmp%(2*n);
		for (i=1;i<=2*n;i++){
			l=i-tmp; r=i+tmp;
			if (l<=0) l+=2*n;
			if (r>2*n) r-=2*n;
			d[(j+1)%2][i]=d[j%2][l]^d[j%2][r];
		}
		j++;
	}
	if (s%2==1) for (i=1;i<=n;i++) cout<<"0 "<<d[j%2][2*i]+1<<' ';
	else for (i=1;i<=n;i++) cout<<d[j%2][2*i-1]+1<<" 0 ";
}