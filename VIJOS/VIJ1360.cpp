#include <iostream>
#include <cstring>
using namespace std;
bool f[9][9][9][9][9][9][9][9];
const long mx[]={0,1,0,-1};
const long my[]={1,0,-1,0};
struct node{
	long x[3][3];
	long zx,zy;
	long s;
} a[100001];
bool check(long x[3][3])
{
	if (f[x[0][0]][x[0][1]][x[0][2]][x[1][0]][x[1][1]][x[1][2]][x[2][0]][x[2][1]]) return false;
	else return true;
}
void push(long x[3][3])
{
	f[x[0][0]][x[0][1]][x[0][2]][x[1][0]][x[1][1]][x[1][2]][x[2][0]][x[2][1]]=true;
}
bool compare(long x[3][3]) //123804765
{
	if (x[0][0]==1 && x[0][1]==2 && x[0][2]==3 && x[1][0]==8 && x[1][1]==0 && x[1][2]==4 && x[2][0]==7 && x[2][1]==6) return true;
	else return false;
}
void debug(long x[3][3])
{
	long i,j;
	for (i=0;i<=2;i++){
		for (j=0;j<=2;j++) cout<<x[i][j]<<' ';
		cout<<endl;
	}
			
}
int main()
{
	long st,i,j,q,p;
	long tmp[3][3];
	cin>>st;
	for (i=2;i>=0;i--)
		for (j=2;j>=0;j--){
			a[1].x[i][j]=st%10;
			if (a[1].x[i][j]==0) {a[1].zx=i; a[1].zy=j;}
			st/=10;
		}
	a[1].s=0;
		push(a[1].x);
	p=1; q=2;
	memset(f,false,sizeof(f));
	while (p<q){
		for (i=0;i<=3;i++)
			if (a[p].zx+mx[i]>=0 && a[p].zx+mx[i]<=2 && a[p].zy+my[i]>=0 && a[p].zy+my[i]<=2){
				memcpy(tmp,a[p].x,sizeof(tmp));
				tmp[a[p].zx][a[p].zy]=tmp[a[p].zx+mx[i]][a[p].zy+my[i]];
				tmp[a[p].zx+mx[i]][a[p].zy+my[i]]=0;
				if (check(tmp)){
					push(tmp);
					memcpy(a[q].x,tmp,sizeof(tmp));
					a[q].s=a[p].s+1;
					a[q].zx=a[p].zx+mx[i];
					a[q].zy=a[p].zy+my[i];
					//cout<<endl;
					//cout<<q<<endl;
					//debug(a[q].x);
					if (compare(a[q].x)) {cout<<a[q].s; return 0;}
					q++;
				}
			}
		p++;
		//cout<<"p:"<<p<<endl;
	}
	return 0;
}