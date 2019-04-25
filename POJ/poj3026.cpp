#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
using namespace std;
struct point{
    int x,y,s;
    point(){}
    point(int x,int y){this->x=x; this->y=y; s=0;}
    point(int x,int y,int s){this->x=x; this->y=y; this->s=s;}
} pts[501];
int map[100][100];
int edges[501][501];
int n,m;
const int mx[]={0,1,0,-1};
const int my[]={1,0,-1,0};
void bfs(int number){
    bool vis[501][501];
    memset(vis,0,sizeof(vis));
    queue<point> que;
    que.push(point(pts[number].x,pts[number].y,0));
    vis[pts[number].x][pts[number].y]=true;
    while (!que.empty()){
        point tmp=que.front();
        que.pop();
        for (int i=0;i<4;++i){
            int xx=tmp.x+mx[i],yy=tmp.y+my[i];
            if (xx>=0 && xx<n && yy>=0 && yy<m && !vis[xx][yy] && map[xx][yy]!=-1){
                vis[xx][yy]=true;
                que.push(point(xx,yy,tmp.s+1));
                if (map[xx][yy]>0){
                    edges[number][map[xx][yy]]=tmp.s+1;
                }
            }
        }
    }
}
int prim(int num){
    int dis[501];
    bool vis[501];
    int ans=0;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[1]=0;
    for (int k=1;k<=num;++k){
        int Min,Minx;
        Min=0x3f3f3f3f;
        for (int i=1;i<=num;++i)
            if (!vis[i] && dis[i]<Min){
                Min=dis[i];
                Minx=i;
            }
        vis[Minx]=true;
        ans+=Min;
        for (int i=1;i<=num;++i)
            if (!vis[i] && edges[Minx][i]<dis[i]){
                dis[i]=edges[Minx][i];
            }
    }
    return ans;
}
int main()
{
    int T;
    cin>>T;
    while (T--){
        memset(map,-1,sizeof(map));
        memset(edges,0x3f3f3f3f,sizeof(edges));
        cin>>m>>n;
        int num=0;
        char ch[1000];
        cin.getline(ch,1000);
        for (int i=0;i<n;++i){
            cin.getline(ch,1000);
            for (int j=0;j<m;++j){
                if (ch[j]==' ') map[i][j]=0;
                else if (ch[j]!='#'){
                    ++num;
                    pts[num]=point(i,j);
                    map[i][j]=num;
                }
            }
        }
        for (int i=1;i<=n;++i) bfs(i);
        cout<<prim(num)<<endl;
    }
    return 0;
}