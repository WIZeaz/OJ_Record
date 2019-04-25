#include <iostream>
using namespace std;
long contor_code(long x[],long n)
{
	long i,j,t,v;
	v=0;
	for (i=1;i<=n-1;i++){
		t=x[i]-1;
		for (j=1;j<i;j++)
			if (x[j]<x[i]) t--;
		v=(v+t)*(n-i);
	}
	return v;
}
long contor_encode(long x,long n)
{
	long t,s,i,j,ans;
	bool f[101];
	memset(f,false,sizeof(f));
	s=1;
	ans=0;
	for (i=1;i<=n-1;i++) s*=i;
	for (i=1;i<n;i++){
		t=x/s;
		x%=s;
		s=s/(n-i);
		for (j=1;j<=n;j++){
			if (!f[j]){
				if (t==0){
					f[j]=true;
					break;
				}
				t--;
			}
		}
		ans=ans*10+j;
	}
	for(j=1;j<=n;j++)
		if (!f[j]) return ans*10+j;
}
main()
{
	long n,tmp,i,t[101];
	char x;
	cin>>n;
	while (cin>>i){
		tmp=contor_encode(i-1,n);
		cout<<tmp<<endl;
			for (i=1;i<=n;i++) {
				t[n-i+1]=tmp%10;
				tmp/=10;
			}
		cout<<contor_code(t,n)+1<<endl;
	}
}