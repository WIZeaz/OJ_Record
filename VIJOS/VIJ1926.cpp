#include <iostream>
using namespace std;
const long mu[]={0,2,4,8,16,32,64,128,256,512,1024};
bool f[1025];
long divide(long l,long r)//0 B 0,1 I 1,01 F 2
{
	long x,x1,x2;
	if (l<r){
		x1=divide(l,(l+r)/2);
		x2=divide((l+r)/2+1,r);
		if (x1==0 && x2==0){ x=0; cout<<'B';}
		else if (x1==1 && x2==1){ x=1; cout<<'I';}
		else{ x=2; cout<<'F';}
		return x;
	} else{
		if (f[l]) cout<<'I';
		else cout<<'B';
		return f[l];
	}
}
main()
{
	long n,i;
	char ch;
	cin>>n;
	for (i=1;i<=mu[n];i++) {
		cin>>ch;
		if (ch=='0') f[i]=false;
		else f[i]=true;
	}
	divide(1,mu[n]);
}