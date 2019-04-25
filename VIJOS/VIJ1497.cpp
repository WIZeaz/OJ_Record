#include <iostream>
#include <cstring>
using namespace std;
const char block[6][7]={{'.','.','+','-','-','-','+'},
								{'.','/',' ',' ',' ','/','|'},
								{'+','-','-','-','+',' ','|'},
								{'|',' ',' ',' ','|',' ','+'},
								{'|',' ',' ',' ','|','/','.'},
								{'+','-','-','-','+','.','.'}
};
long map[51][51];
char out[1001][1001];
void paintblock(long x,long y)
{
	long i,j;
	for (i=0;i<=5;i++)
		for (j=0;j<=6;j++)
			if (block[i][j]!='.')
				out[x+i][y+j]=block[i][j];
	

}
int main()
{
	long i,j,k,n,m,K,L,sx,sy,MaxU;
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			cin>>map[i][j];
	L=4*m+1+2*n;
	MaxU=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			MaxU=max(MaxU,3*(map[i][j]+1)-2*i);
	K=MaxU+2*n;
	memset(out,'.',sizeof(out));
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++){
			sx=MaxU+2*(i-1); //Standard Line
			sy=2*(n-i)+4*j-3;
			for (k=1;k<=map[i][j];k++)
				paintblock(sx-3*k,sy);
		}
	for (i=1;i<=K;i++){
		for (j=1;j<=L;j++)
			cout<<out[i][j];
		cout<<endl;
	}
	return 0;
}