#include <iostream>
#include <cmath>
using namespace std;
const long M=100000000;
const long Mnum=8;
struct BigNum{
	long len,num[201];
};
BigNum multi(BigNum x,long t){
	long i,g;
	g=0;
	for (i=1;i<=x.len;i++){
		x.num[i]=x.num[i]*t+g;
		g=x.num[i]/M;
		x.num[i]%=M;
	}
	while (g!=0) {x.len++; x.num[x.len]=g%M; g=g/M;}
	return x;
}

BigNum pow2(long x){ //x<=3500
	long i;
	BigNum t;
	t.len=1;
	t.num[1]=1;
	for (i=1;i<=x;i++)
		t=multi(t,2);
	return t;
}
BigNum add(BigNum x,long y){
	long i,g;
	g=0;
	x.num[1]+=y;
	g=x.num[1]/M;
	x.num[1]%=M;
	i=1;
	while (g!=0){
		x.num[i+1]+=g;
		g=x.num[i+1]/M;
		x.num[i+1]%=M;
		i++;
	}
	if (i>x.len) x.len=i;
	return x;
}
main()
{
	long n,k,t,i,j,dn,L,R,Mid;
	BigNum tmp;
	cin>>n>>k;
	if (n==1){
		if (k==1) cout<<1;
		else cout<<-1;
	} else if (n==2){
		if (k<=3) cout<<k;
		else cout<<-1;
	} else if (n==3){
		if (k==1) cout<<1;
		else if (k==2) cout<<2;
		else {
			t=(k-1)/3+1;
			k=(k-1)%3+1;
			tmp=add(pow2(t),k-2);
			cout<<tmp.num[tmp.len];
			for (i=tmp.len-1;i>=1;i--){
				if (tmp.num[i]==0) dn=Mnum;
				else dn=Mnum-log10(tmp.num[i])-1;
				for (j=1;j<=dn;j++) cout<<0;
				cout<<tmp.num[i];
			}
		}
	} else {
		L=1; R=3500; Mid=(L+R)/2;
		while (L<R){
			
		}
	}
}