#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#include<set>
using namespace std;
inline const int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(x<'0'||x>'9') {
        if(x=='-')bj=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9') {
        num=num*10+x-'0';
        x=getchar();
    }
    return num*bj;
}
const int Factorial[10]= {0,40320,5040,720,120,24,6,2,1},Dirx[]= {0,1,0},Diry[]= {0,0,1};
set<int>Ans;
int vst[500005];
struct Square {
    int a[4][4],step;
} Start;
int Contor(Square x) { //康托展开
    int ans=0,tmp[10];
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
            tmp[(i-1)*3+j]=x.a[i][j];
    for(int i=1; i<9; i++) {
        int sum=0;
        for(int j=i+1; j<=9; j++)
            if(tmp[j]<tmp[i])sum++;
        ans+=sum*Factorial[i];
    }
    return ans;
}
void Bfs(int s) {
    queue<Square>Q;
    Q.push(Start);
    vst[s]=1;
    while(!Q.empty()) {
        Square Now=Q.front();
        Q.pop();
        if(Ans.count(Contor(Now))) {
            printf("%d\n",Now.step);
            return;
        }
        for(int x=1; x<=3; x++)
            for(int y=1; y<=3; y++)
                for(int i=1; i<=2; i++) {
                    int xx=x+Dirx[i],yy=y+Diry[i];
                    if(xx<1||yy<1||xx>3||yy>3)continue;
                    Square Next=Now;
                    Next.step++;
                    swap(Next.a[x][y],Next.a[xx][yy]);
                    int num=Contor(Next);
                    if(vst[num])continue;
                    Q.push(Next);
                    vst[num]=1;
                }
    }
    puts("-1");
}
int main() {
    ios::sync_with_stdio(false);
    Ans.insert(69074),Ans.insert(77576),Ans.insert(135289),Ans.insert(157120),Ans.insert(205759),Ans.insert(227590),Ans.insert(285303),Ans.insert(293805);
    while(cin>>Start.a[1][1]>>Start.a[1][2]>>Start.a[1][3]) {
        memset(vst,0,sizeof(vst));
        for(int i=2; i<=3; i++)
            for(int j=1; j<=3; j++)
                cin>>Start.a[i][j];
        Bfs(Contor(Start)); 
    }
    return 0;
}

