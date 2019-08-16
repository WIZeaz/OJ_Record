#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
#define N 2000000
struct trie_node{
    int k[2];
    int c;
};
int p[32];
struct trie{
    vector<trie_node> tr;
    void clear(){
        //memset(tr,0,sizeof(tr));
        tr.clear();
        tr.push_back(trie_node());
    }
    void insert(int x){
        int now=0;
        for (int i=29;i>=0;--i){
            int t=x&p[i];
            if (t!=0) t=1;
            if (tr[now].k[t]==0){
                tr.push_back(trie_node());
                tr[now].k[t]=tr.size()-1;
            }
            now=tr[now].k[t];
            tr[now].c++;
        }
    }
    void del(int x){
        int now=0;
        for (int i=29;i>=0;--i){
            int t=x&p[i];
            if (t!=0) t=1;
            if (tr[now].k[t]==0){
                return;
            }
            now=tr[now].k[t];
            tr[now].c--;
        }
    }
    int match(int x){
        int now=0;
        int rnt=0;
        for (int i=29;i>=0;--i){
            int t=x&p[i];
            if (t!=0) t=1;
            if (tr[now].k[t]==0 || tr[tr[now].k[t]].c==0) t=1-t;
            rnt=(rnt<<1)+t;
            now=tr[now].k[t];
        }
        return rnt;
    }
    bool query(int x){
        int now=0;
        for (int i=29;i>=0;--i){
            int t=x&p[i];
            if (t!=0) t=1;
            if (tr[now].k[t]==0) return false;
            now=tr[now].k[t];
            if (tr[now].c<1) return false;
        }
        return true;
    }
};
trie a,b;
struct node{
    int type;
    int num;
    node(){}
    node(int _type,int _num){type=_type; num=_num;}
};
vector<int> ans;
void solve(int first){
    stack<node> st;
    node last=node(-1,0);
    st.push(node(0,first));
    while (!st.empty()){
        node tmp=st.top();
        //printf("Top is (%d, %d) | Last is (%d,%d)\n",tmp.type,tmp.num,last.type,last.num);
        if (tmp.type==0){
            int m=b.match(tmp.num);
            if (last.type!=-1 && last.num==m){
                a.del(tmp.num);
                b.del(m);
                ans.push_back(tmp.num^m);
                //printf("%d xor %d = %d [ansnum=%d]\n",tmp.num,m,tmp.num^m,ansnum);
                st.pop(); st.pop();
                if (st.size()>1) {
                    tmp=st.top(); st.pop(); last=st.top(); st.push(tmp);}
                else last=node(-1,0);
            } else {
                st.push(node(1,m));
                last=tmp;
            }
        } else {
            int m=a.match(tmp.num);
            if (last.type!=-1 && last.num==m){
                b.del(tmp.num);
                a.del(m);
                ans.push_back(tmp.num^m);
                //printf("%d xor %d = %d [ansnum=%d] \n",tmp.num,m,tmp.num^m,ansnum);
                st.pop(); st.pop();
                if (st.size()>1) {tmp=st.top(); st.pop(); last=st.top(); st.push(tmp);}
                else last=node(-1,0);
            } else{
                st.push(node(0,m));
                last=tmp;
            }
        }
        
    }
}
int anum[100001];
int main(){
    //freopen("D:\\Download\\hdu2019contest5\\1002\\data\\1.in","r",stdin);
    //freopen("output.txt","w",stdout);
    int T;
    for (int i=0;i<=31;++i) p[i]=1<<i;
    scanf("%d",&T);
    while (T--){
        int n;
        scanf("%d",&n);
        a.clear();
        b.clear();
        for (int i=0;i<n;++i){
            scanf("%d",&anum[i]);
            a.insert(anum[i]);
        }
        for (int i=0;i<n;++i){
            int t;
            scanf("%d",&t);
            b.insert(t);
        }
        ans.clear();
        for (int i=0;i<n;++i)
            if (a.query(anum[i])){
                solve(anum[i]);
            }
        sort(ans.begin(),ans.end());
        printf("%d",ans[0]);
        for (int i=1;i<ans.size();++i){
            printf(" %d",ans[i]);
        }
        printf("\n");
    }
}