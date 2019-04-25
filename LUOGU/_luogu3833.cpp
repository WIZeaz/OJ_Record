#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

struct Seg_Tree
{
    int left,right,add;
    long long value;
}son[400050];

int n,m;

vector <int> graph[100050];

int fa[100050][16],size[100050],depth[100050];

int Time,pos[100050],belong[100050];

long long delta[500050];

bool vis[100050];

int read()
{
    int w=0,c=1; 
    char ch=getchar();
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') 
            c=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        w=w*10+ch-'0';
        ch=getchar();
    }
    return w*c;
}

void Build(int id,int left,int right)
{
    son[id].value=son[id].add=0;
    son[id].left=left;
    son[id].right=right;
    if (left==right)
        return;
    Build(id<<1,left,(left+right)>>1);
    Build(id<<1|1,((left+right)>>1)+1,right);
    son[id].value=son[id<<1].value+son[id<<1|1].value;
}

void Change_delta(int id,long long value,int left,int right)
{
    son[id].value+=value*(right-left+1);
    delta[id]+=value;
}

void Push_Up(int id)
{
    son[id].value=son[id<<1].value+son[id<<1|1].value;
}

void Push_Down(int id,int left,int right)
{
    int mid=(left+right)/2;
    Change_delta(id<<1,delta[id],left,mid);
    Change_delta(id<<1|1,delta[id],mid+1,right);
    delta[id]=0;
}

void Update(int id,int left,int right,long long value,int pos1,int pos2)
{
    int mid=(left+right)/2;
    //cout << id << " " << left << " " << right << " " << value << " " << pos1 << " " << pos2 << endl;
    //system("pause");
    if (pos1<=left && pos2>=right)
    {
        Change_delta(id,value,left,right);
        return;
    }
    Push_Down(id,left,right);
    if (pos1<=mid)
        Update(id<<1,left,mid,value,pos1,pos2);
    if (pos2>mid)
        Update(id<<1|1,mid+1,right,value,pos1,pos2);
    Push_Up(id);
}

void getlca(int u)
{
    vis[u]=true;
    size[u]=1;
    for (int i=1;i<=16;i++)
    {
        if (depth[u]<(1<<i))
            break;
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for (int i=0;i<graph[u].size();i++)
    {
        int v=graph[u][i];
        if (vis[v])
            continue;
        depth[v]=depth[u]+1;
        fa[v][0]=u;
        getlca(v);
        size[u]+=size[v];
    }
}

void dfs(int k,int num)
{
    int x=0;
    //cout << k << " " << num << endl;
    //system("pause");
    Time++;
    pos[k]=Time;
    belong[k]=num;
    for (int i=0;i<graph[k].size();i++)
    {
        int v=graph[k][i];
        if (depth[v]>depth[k] && size[v]>size[x])
            x=v;
    }
    if (x==0)
        return;
    dfs(x,num);
    for (int i=0;i<graph[k].size();i++)
    {
        int v=graph[k][i];
        if (depth[v]>depth[k] && x!=v)
            dfs(v,v);
    }
}

void Insert(int x,int y,long long z)
{
    for (;belong[x]!=belong[y];x=fa[belong[x]][0])
    {
        //cout << x << " " << y << endl;
        if (depth[belong[x]]<depth[belong[y]])
            swap(x,y);
        Update(1,1,n,z,pos[belong[x]],pos[x]);
    }
    if (depth[x]<depth[y])
        swap(x,y);
    //cout << x << " " << y << " " << pos[x] << " " << pos[y] << endl;
    Update(1,1,n,z,pos[y],pos[x]);
}

long long Query(int id,int left,int right,int pos1,int pos2)
{
    int mid=(left+right)/2;
    long long ans=0;
    //cout << id << " " << left << " " << right << " " << son[id].value << " " << pos1 << " " << pos2 << endl;
    if (pos1<=left && pos2>=right)
        return son[id].value;
    Push_Down(id,left,right);
    if (pos1<=mid)
        ans+=Query(id<<1,left,mid,pos1,pos2);
    if (pos2>mid)
        ans+=Query(id<<1|1,mid+1,right,pos1,pos2);
    Push_Up(id);
    return ans;
}

int main()
{
    //freopen("tree.in","r",stdin);
    //freopen("tree.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        u++;
        v++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    getlca(1);
    dfs(1,1);
    Build(1,1,n);
    m=read();
    //for (int i=1;i<=n;i++)
    //    cout << belong[i] << endl;
    for (int i=1;i<=m;i++)
    {
        char chr;
        int x;
        scanf("%s",&chr);
        scanf("%d",&x);
        x++;
        if (chr=='A')
        {
            int y,z;
            scanf("%d%d",&y,&z);
            y++;
            Insert(x,y,z);
        }
        if (chr=='Q')
            printf("%lld\n",Query(1,1,n,pos[x],pos[x]+size[x]-1));
    }
    return 0;
}