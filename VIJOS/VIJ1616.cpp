#include <iostream>
#include <cstring>
using namespace std;
int d[1001][101][101][2];
char str[10001];
char inv(char s){
    if (s=='z') return 'j';
    if (s=='j') return 'z';
    return '#';
}
int check(char a,char b){
    if (a=='j' && b=='z') return 1;
    return 0;
}
int main(){
    int n,K;
    scanf("%d%d",&n,&K);
    scanf("%s",str+1);
    str[0]=str[n+1]='#';
    memset(d,0x80,sizeof(d));
    d[0][0][0][0]=d[0][0][0][1]=0;
    for (int i=1;i<=n;++i){
        // no change
        char Inv=inv(str[i-1]);
        char Invnow=inv(str[i]);
        for (int j=0;j<=K;++j){

            for (int k=0;k<=K;++k){
                d[i][j][k][0]=max(d[i][j][k][0],d[i-1][j][k][0]+check(str[i-1],str[i]));
                d[i][j][k][0]=max(d[i][j][k][0],d[i-1][j][k][1]+check(Inv,str[i]));
            }
        }
        //change
        int t1,t2;
        t1=t2=0;
        if (str[i]=='j') t1=1;
        else t2=1;

        for (int j=t1;j<=K;++j){
            char Inv=inv(str[i-1]);
            for (int k=t2;k<=K;++k){
                d[i][j][k][1]=max(d[i][j][k][1],d[i-1][j-t1][k-t2][0]+check(str[i-1],Invnow));
                d[i][j][k][1]=max(d[i][j][k][1],d[i-1][j-t1][k-t2][1]+check(Inv,Invnow));
            }
        }
    }

    int ans=0;
    for (int i=0;i<=K;++i){
        ans=max(ans,max(d[n][i][i][0],d[n][i][i][1]));
    }
    printf("%d",ans);
}