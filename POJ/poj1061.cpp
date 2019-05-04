#include <iostream>
#include <cstdio>
using namespace std;
long long exgcd(long long a,long long b,long long &x,long long&y){
    if (b==0){ x=1; y=0; return a;}
    long long t=exgcd(b,a%b,y,x);
    y=y-(a/b)*x;
    return t;
}
int main()
{
    long long x,y,m,n,l;
    long long t,k,a,b,c;
    while (~scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l)){
        a=n-m;
        b=l;
        c=x-y;
        long long gcd=exgcd(a,b,t,k);
        if (c%gcd==0){
            t*=c/gcd;
            b/=gcd;
            t=(t%b+b)%b;
            printf("%lld\n",t);
        } else printf("Impossible\n");
    }
    return 0;
}