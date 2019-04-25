#include <iostream>
using namespace std;
struct Number{
	long num[301];
	long len;
};
Number t;
char a[200];
Number add1(Number x){
	long i,g;
	x.num[1]++;
	i=1;
	g=0;
	while (x.num[i]>=10){
		g=x.num[i]/10;
		x.num[i]%=10;
		x.num[i+1]+=g;
		i++;
	}
	if (i>x.len) x.len=i;
	return x;
}
Number minus1(Number x){
	long i,g;
	x.num[1]--;
	i=1;
	while (x.num[i]<0){
		x.num[i]+=10;
		x.num[i+1]--;
		i++;
	}
	if (x.num[x.len]==0) x.len--;
	return x;
}
Number getNum(long l,long r){
	Number x;
	long i;
	x.len=r-l+1;
	for (i=l;i<=r;i++)
		x.num[r-i+1]=a[i]-'0';
	return x;
}
bool check(Number t,long st){
	long i;
	for (i=1;i<=t.len && st+i<length(a);i++)
		if (t.num[t.len-i+1]!=(a[st+i-1]-'0')) return false;
	return true;
}
bool checkFormBack(Number t,long st){
	long i;
	for (i=1;i<=t.len && st-i+1>=0;i++)
		if (t.num[t]!=(a[st-i+1]-'0')) return false;
	return true;
}
main()
{

	long i,j,k,len;
	bool suc;
	Number t,tmp;
	cin.getline(a,200);
	len=length(a);
	for (i=1;i<=len;i++)
		for (j=0;j<i;j++){
			t=getNum(j,j+i-1);
			suc=true;
			if (j==0){
				tmp=t;
				k=0;
				while (k<len){
					if (!check(tmp,k)) {suc=false; break;}
					tmp=add1(tmp);
					k+=i;
				}
			} else {
				t=minus1(t);
				if (!checkFormBack(t,j-1)) suc=false;
				if (suc){
					k=j;
					tmp=t;
					while (k<len){
						if (!check(tmp,k)) {suc=false; break;}
						tmp=add1(tmp);
						k+=i;
					}
				}
			}
			
			if (suc){
				
			}
		}
}