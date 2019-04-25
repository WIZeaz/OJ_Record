#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
long stone[201];
const long INF=0x3f3f3f3f;
queue <long> d;
int main()
{
	long i,k,j,l,s,t,st,to,m,Min;
	
	cin>>l>>s>>t>>m;
	for (i=1;i<=m;i++) cin>>stone[i];
	sort(stone+1,stone+m+1);
	st=1;
	while (stone[st]<s) st++;
		
	memset(d,127,sizeof(d));
	d[0]=0;
	if (stone[st]<=100) to=stone[st]-1;
	else to=100;
	if (to<=t){
		for (i=s;i<=to;i++) d[i]=0;
	} else {
		for (i=s;i<=t;i++) d[i]=0;
		for (i=t+1;i<=to;i++)
			for (j=i-t;j<=i-s;j++)
				d[i%(t+1)]=min(d[i%(t+1)],d[j%(t+1)]);
	}
	

	stone[m+1]=stone[m]+101;
	for (k=st;k<=m;k++){
		for (j=stone[k]-t;j<=stone[k]-s;j++)
			if (j>=0) d[stone[k]%(t+1)]=min(d[stone[k]%(t+1)],d[j%(t+1)]);
		d[stone[k]%(t+1)]++;
		if (stone[k]+100>=stone[k+1]) to=stone[k+1]-1;
		else to=stone[k]+100;	
		for (i=stone[k]+1;i<=to;i++){
			for (j=i-t;j<=i-s;j++)
				if (j>=0) d[i%(t+1)]=min(d[i%(t+1)],d[j%(t+1)]);
		}
	}
	Min=INF;
	for (i=1;i<=100;i++)
		Min=min(Min,d[i]);
	cout<<Min;
}
