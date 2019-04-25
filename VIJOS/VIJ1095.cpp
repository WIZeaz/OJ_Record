#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;
const long mod=100000000;
const long d=8;
const long list[]={1,10,100,1000,10000,100000,1000000,10000000};
struct gjd{
	long num[102],n;
} a,b1,b2,c;
gjd multi_two(gjd x)
{
	long g,i;
	g=0;
	for (i=1;i<=x.n;i++){
		x.num[i]=x.num[i]*2+g;
		g=x.num[i]/mod;
		x.num[i]%=mod;
	}
	if (g>0) {x.n++; x.num[x.n]=g;}
	return x;
}
bool compare(gjd t1,gjd t2) //To judge whether t1 bigger than t2, if it is, return true, else return false.
{
	long i;
	if (t1.n>t2.n) return true;
	else if (t1.n<t2.n) return false;
	else {
		for (i=t1.n;i>=1;i--){	
			if (t1.num[i]>t2.num[i]) return true;
			else if (t1.num[i]<t2.num[i]) return false;
		}
		return false;
	}
}
gjd _minus(gjd x,gjd y){
	long i;
	for (i=1;i<=x.n;i++){
		x.num[i]-=y.num[i];
		if (x.num[i]<0) {x.num[i]+=mod; x.num[i+1]--;}
	}
	if (x.num[x.n]==0) x.n--;
	return x;
}
gjd _add(gjd x,gjd y){
	gjd t;
	long g,i,len;
	if (x.n>y.n) len=x.n;
	else len=y.n;
	g=0;
	for (i=1;i<=len;i++){
		t.num[i]=x.num[i]+y.num[i]+g;
		g=t.num[i]/mod;
		t.num[i]%=mod;
	}
	t.n=len;
	if (g>0) {t.n++; t.num[t.n]=g;}
	return t;
}
main()
{
	long i,j,len;
	string t;
	cin>>t;
	len=t.size();
	for (i=0;i<len;i++){
		if (i%d==0) a.n++;
		a.num[a.n]=(t[len-i-1]-'0')*list[i%d]+a.num[a.n];
	}
	memset(b1.num,0,sizeof(b1.num));
	b1.n=1;
	b2=b1;
	b1.num[1]=1; 
	c=b1;
	while (compare(a,b1)){
		b2=b1;
		c=multi_two(c);
		b1=_add(b1,c);
	}
	b1=_minus(a,b2); 
	b2=multi_two(b1);
	b2.num[1]--;
	i=1;
	while (b2.num[i]<0){
		b2.num[i]+=mod;
		i++;
		b2.num[i]--;
	}
	if (b2.num[b2.n]==0) b2.n--;
	cout<<b2.num[b2.n];
	for (i=b2.n-1;i>=1;i--){
		if (b2.num[i]==0) len=7;
		else len=7-long (log10(b2.num[i]));
		for (j=1;j<=len;j++) cout<<0;
		cout<<b2.num[i];
	}
}