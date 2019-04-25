#include <iostream>
#include <string>
using namespace std;
const long num[]={6,2,5,5,4,5,6,3,7,6,0};
long ans=0;
long Max;
long check(string x)
{
	long i,t,s=0;
	if (x.size()==1) return num[x[0]-'0'];
	else {
		for (i=0;i<x.size();i++)
			s+=num[x[i]-'0'];
		return s;
	}
}
string add(string a,string b)
{
	long i,x1,x2;
	string x,t;
	x1=x2=0;
	//cout<<a<<' '<<b<<endl;
	for (i=0;i<a.size();i++)
		x1=x1*10+a[i]-'0';
	for (i=0;i<b.size();i++)
		x2=x2*10+b[i]-'0';
	x1=x1+x2;
	if (x1==0) return "0";
	while (x1!=0){
		x=char(x1%10+'0')+x;
		x1/=10;
	}
	return x;
}
void dfs(string a,string b,long s)
{
	long i,j;
	string a1,b1;
	long t;
	for (i=0;i<=10;i++)
		for (j=0;j<=10;j++)
			if(!(i==10 && j==10)){
				if (i==10) a1=a;
				else a1=char('0'+i)+a;
				if (j==10) b1=b;
				else b1=char('0'+j)+b;
				t=s+num[i]+num[j]+check(add(a1,b1));
				if (t<Max && a1.size()>=1 && b1.size()>=1){
					dfs(a1,b1,t);
					
				}
				else if (t==Max && (((a1.size()==1) || (a1.size()>1 && a1[0]!='0')) && ((b1.size()==1) || (b1.size()>1 && b1[0]!='0')))){
					ans++;
					cout<<a1<<'+'<<b1<<'='<<add(a1,b1)<<endl;
				}
			}
}
main()
{
	long i,j;
	cin>>Max;
	Max-=4;
	dfs("\0","\0",0);
	cout<<ans;
}