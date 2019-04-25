#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;
long s[1001],n;
bool tr[1001][1001],f[1001];
string list[1001];
void sort(string t[],long nn)
{
	long i,j;
	string k;
	for (i=1;i<nn;i++)
		for (j=i+1;j<=nn;j++)
			if (t[i]>t[j]){
				k=t[i];
				t[i]=t[j];
				t[j]=k;
			}
}
string traversal(long x)
{
	long i,sn;
	string t[1001],k;
	sn=0;
	for (i=1;i<=n;i++)
		if (tr[x][i]){
			sn++;
			t[sn]=traversal(i);
		}
	k="(";
	sort(t,sn);
	for (i=1;i<=sn;i++) k+=t[i];
	k+=")";
	return k;
}
int main()
{
	long i,j,k,x,y;
	cin>>k>>n;
	memset(f,true,sizeof(f));
	for (j=1;j<=k;j++){
		memset(tr,false,sizeof(tr));
		memset(s,0,sizeof(s));
		for (i=1;i<n;i++){
			cin>>x>>y;
			tr[x][y]=true;
			s[y]++;
		}
		for (i=1;i<=n;i++)
			if (s[i]==0){
				list[j]=traversal(i);
				break;
			}
	}
	for (i=1;i<=k;i++)
		if (f[i]){
			cout<<i;
			for (j=i+1;j<=k;j++)
				if (list[i]==list[j]){
					cout<<"="<<j;
					f[j]=false;
				}
			cout<<endl;
		}
	return 0;
}
