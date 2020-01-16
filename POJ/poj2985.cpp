#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
//const int FastIO::LEN
struct FastIO {
	static const int LEN=1<<18|1;
	char buf[LEN],wbuf[LEN];
	int s,t,wpos;
    FastIO(){
        s=0;
        t=0;
        wpos=0;
    }
	inline int read(){
		return (s==t)&&(t=(s=0)+fread(buf,1,LEN,stdin)),s==t?-1:buf[s++];
	}
	inline void out(int x){
		wpos==LEN?fwrite(wbuf,1,LEN,stdout),wbuf[0]=x,wpos=1:wbuf[wpos++]=x;
	}
	// 有符号：
	inline int rint(){
		// 根据读入是int还是long long决定x的类型
		int c=read(),x=0,s=1;
		if(c==-1)return 0;
		while(c<=32)c=read();
		if(c=='-')s=-1,c=read();
		while(isdigit(c))x=x*10+c-'0',c=read();
		return x*s;
	}
	inline int ruint(){
		int c=read(),x=0;
		while(c<=32)c=read();
		while(isdigit(c))x=x*10+c-'0',c=read();
		return x;
	}
	inline void rstr(char *str){
		int c=read();
		while(c<=32)c=read();
		while(c>32)*str++=c,c=getchar();
		*str=0;
	}
	// 根据类型
	inline void wint(int x){
		// 如果含有负数，取消注释
		// if(x<0)wchar('-'),x=-x;
		char str[24];int n=0;
		while(x||!n)str[n++]='0'+x%10,x/=10;
		while(n--)out(str[n]);
	}
	inline void wchar(char str){
		out(str);
	}
	inline void wstr(const char *s){
		while(*s)out(*s++);
	}
	inline void over(){
		if(wpos)fwrite(wbuf,1,wpos,stdout),wpos=0;
	}
	~FastIO(){
		if(wpos)fwrite(wbuf,1,wpos,stdout),wpos=0;
	}
}io;

inline int lowbit(int x){return x&(-x);}
namespace tree_array{
    int n,st;
    int a[200001];
    inline void setRange(int N) {
        n=N;
        st=1;
        while ((st<<1)<=n) st<<=1;
    }
    inline void clear() {memset(a,0,sizeof(a));}
    inline void add(int pos,int val){
        for (int i=pos;i<=n;i+=lowbit(i)) a[i]+=val;
    }
    inline int query(int pos){
        int rnt=0;
        for (int i=pos;i>0;i-=lowbit(i)) rnt+=a[i];
        return rnt;
    }
    inline int smallestK(int k){
        int ans=0;
        for (int i=st;i>0;i>>=1)
            if (ans+i<=n && a[ans+i]<k){
                ans+=i;
                k-=a[ans];
            }
        return ans+1;
    }
}
int f[200001];
int Size[200001];
int len;
int find(int x){
    if (f[x]!=x) f[x]=find(f[x]);
    return f[x];
}
inline void Union(int x,int y){
    x=find(x); y=find(y);
    if (x==y) return;
    --len;
    tree_array::add(Size[y],-1);
    tree_array::add(Size[x],-1);
    tree_array::add(Size[x]+Size[y],1);
    f[y]=x;
    Size[x]+=Size[y];
    
}
int main(){
    int n,m;
    n=io.ruint();
    m=io.ruint();
    for (int i=1;i<=n;++i){
        f[i]=i;
        Size[i]=1;
    }
    tree_array::clear();
    tree_array::setRange(n);
    tree_array::add(1,n);
    len=n;
    while (m--){
        int op=io.ruint();
        if (op==0){
            int x,y;
            x=io.ruint();
            y=io.ruint();
            Union(x,y);
        } else {
            int k;
            k=io.ruint();
            io.wint(tree_array::smallestK(len-k+1));
            io.wchar('\n');
        }
    }

    return 0;
}