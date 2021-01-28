#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;
#define INF 0x3f3f3f3f
int num=0;
struct node{
    int l,r,lc,rc;
    int val;
    node(){}
    node(int l,int r,int lc,int rc,int val):l(l),r(r),lc(lc),rc(rc),val(val){}
};
vector<node> tr;

class SegmentTree{
    //constants and innerclass

    //variables 
    //methods

    private:
    int addNode(int l,int r){
        tr.push_back(node(l,r,0,0,INF));
        //tr[num++]=node(l,r,0,0,INF);
        //assert(num==tr.size());
        return tr.size()-1;
    }
    int pushup(int lc,int rc){
        if (lc==0 && rc==0) return INF;
        if (lc==0) return tr[rc].val;
        if (rc==0) return tr[lc].val;
        return min(tr[lc].val,tr[rc].val);
    }

    public:
    void update(int pos,int val,int now){
        if (tr[now].l==tr[now].r) {
            tr[now].val=min(tr[now].val,val); 
            return;
        }
        

        int mid=(tr[now].l+tr[now].r)>>1;
        if (pos<=mid){
            if (tr[now].lc==0){
                /* int t=addNode(tr[now].l,mid);
                tr[now].lc=t; */
                tr[now].lc=addNode(tr[now].l,mid);
            }
            update(pos,val,tr[now].lc);
        } else {

            if (tr[now].rc==0){
               /*  int t=addNode(mid+1,tr[now].r);
                tr[now].rc=t; */
                tr[now].rc=addNode(mid+1,tr[now].r);
            }

            update(pos,val,tr[now].rc);
        }
        //write parent update here
        tr[now].val=pushup(tr[now].lc,tr[now].rc);
    }

    int query(int l,int r,int now){
        if (l>r) return INF;
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;

        int mid=(tr[now].l+tr[now].r)>>1;
        if (r<=mid){
            if (tr[now].lc==0) return INF;
            return query(l,r,tr[now].lc);
        } else if (l>mid){
            if (tr[now].rc==0) return INF;
            return query(l,r,tr[now].rc);
        }
        else{
            if (tr[now].lc==0 && tr[now].rc==0) return INF;
            if (tr[now].lc==0) return query(mid+1,r,tr[now].rc);
            if (tr[now].rc==0) return query(l,mid,tr[now].lc);
            return min(query(l,mid,tr[now].lc),query(mid+1,r,tr[now].rc));
        }
        
    }

};
SegmentTree colors[51];

int main(){
    int op;
    //tr.resize(10000000);
    /*for (int i=0;i<=50;++i){
        tr[i]=node(1,1000000,0,0,INF);
    }
    num=51;*/
    while (~scanf("%d",&op)){
        if (op==0){
            tr.clear();
            for (int i=0;i<=50;++i){
                tr.push_back(node(1,1000000,0,0,INF));
            }
            num=51;
            assert(num==tr.size());
        } else if (op==1){
            int x,y,c;
            scanf("%d%d%d",&x,&y,&c);
            colors[c].update(y,x,c);
        } else if (op==2){
            int y1,y2,x;
            scanf("%d%d%d",&x,&y1,&y2);
            int ans=0;
            /*for (int i=0;i<tr.size();++i){
            }*/
            for (int i=0;i<=50;++i)
                if (colors[i].query(y1,y2,i)<=x){
                    ++ans;
                }
            printf("%d\n",ans);
        } else return 0;
    }
}