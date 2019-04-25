#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
class BigNum{
private:
    enum {blen=4,MAX=53,base=10000};
    int len;
    int a[MAX];
public:
    explicit BigNum(int num=0);
    BigNum(const BigNum& b);
    BigNum(int x,int b);
    explicit BigNum(string num);
    BigNum operator+ (const BigNum& b)const;
    BigNum operator+ (const int b)const;
    BigNum operator- (const BigNum& b)const;
    BigNum operator- (const int b)const;
    BigNum operator* (const BigNum& b)const;
    BigNum operator* (const int b)const;
    const int& operator[] (int i)const;
    int& operator[] (int i);
    bool operator< (const BigNum& b)const;
    bool operator> (const BigNum& b)const;
    bool operator== (const BigNum& b)const;
    bool operator!= (const BigNum& b)const;
    string toString()const;
    friend ostream& operator<< (ostream& os,const BigNum& a);
};
BigNum::BigNum(int num){
    if (num==0){
        len=0;
        memset(a,0,sizeof(a));
        return;
    }
    len=0;
    memset(a,0,sizeof(a));
    while (num>0){
        a[len++]=num%base;
        num/=base;
    }
}
BigNum::BigNum(int x,int b){ // x*10^b
    if (x==0){
        len=0;
        memset(a,0,sizeof(a));
        return;
    }
    len=(b+1)/blen+1;
    if ((b+1)%blen==0) len--;
    memset(a,0,sizeof(a));
    int i=b%blen,j=1;
    while (i>0){
        j*=10;
        i--;
    }
    a[len-1]=x*j;
}
BigNum::BigNum(string num){
    const int nn[blen]={1,10,100,1000};
    if (num==string(num.size(),'0')){
        len=0;
        memset(a,0,sizeof(a));
        return;
    }
    memset(a,0,sizeof(a));
    len=0;
    for (int i=0;i<int(num.size());i++){
        if (i%blen==0) len++;
        a[len-1]+=(num[num.size()-i-1]-'0')*nn[i%blen];
    }
}
BigNum::BigNum(const BigNum& b){
    len=b.len;
    memcpy(a,b.a,sizeof(b.a));
}
int& BigNum::operator[](int i){
    return a[i];
}
const int& BigNum::operator[](int i)const{
    return a[i];
}
BigNum BigNum::operator+(const BigNum& b)const{
    BigNum c=BigNum();
    int k=0;
    c.len=max(len,b.len);
    for (int i=0;i<c.len;i++){
        c[i]=(a[i]+b[i]+k)%base;
        k=(a[i]+b[i]+k)/base;
    }
    while (k>0){
        c[c.len++]=k%base;
        k/=base;
    }
    return c;
}
BigNum BigNum::operator+(const int b)const{
    BigNum c=*this;
    int i=0;
    c[0]+=b;
    while (c[i]>=base){
        c[i+1]+=c[i]/base;
        c[i]%=base;
        i++;
    }
    while (c[c.len]>0) c.len++;
    return c;
}
BigNum BigNum::operator-(const BigNum& b)const{ //ensure that a>b
    BigNum c=BigNum();
    c.len=max(len,b.len);
    int k=0;
    for (int i=0;i<len;i++)
        if (a[i]-b[i]-k>=0)
            c[i]=a[i]-b[i]-k;
        else{
            k++;
            c[i]=a[i]-b[i]+base;
        }
    while (c.len>0 && c[c.len-1]==0) c.len--;
    return c;
}
BigNum BigNum::operator-(const int b)const{
    BigNum c=*this;
    int i=0;
    c[i]-=b;
    while (c[i]<0){
        c[i+1]--;
        c[i]+=base;
        i++;
    }
    while (c.len>0 && c[c.len-1]==0) c.len--;
    return c;
}
BigNum BigNum::operator*(const BigNum& b)const{
    BigNum c=BigNum();
    c.len=0;
    int t;
    for (int j=0;j<b.len;j++)
        for (int i=0;i<len;i++){
            t=c[i+j]+a[i]*b[j];
            c[i+j]=t%base;
            c[i+j+1]+=t/base;
            if (c[i+j]>0) c.len=max(c.len,i+j);
            if (c[i+j+1]>0) c.len=max(c.len,i+j+1);
        }
    c.len++;
    return c;
}
BigNum BigNum::operator*(const int b)const{
    BigNum c=BigNum();
    c.len=len;
    int k=0;
    for (int i=0;i<len;i++){
        c[i]=(a[i]*b+k)%base;
        k=(a[i]*b+k)/base;
    }
    while (k>0){
        c[c.len++]=k%base;
        k/=base;
    }
    return c;
}
bool BigNum::operator< (const BigNum& b)const{
    if (len<b.len) return true;
    if (len>b.len) return false;
    for (int i=len-1;i>=0;i--)
        if (a[i]<b[i]) return true;
        else if (a[i]>b[i]) return false;
    return false;
}
bool BigNum::operator> (const BigNum& b)const{
    if (len>b.len) return true;
    if (len<b.len) return false;
    for (int i=len-1;i>=0;i--)
        if (a[i]>b[i]) return true;
        else if (a[i]<b[i]) return false;
    return false;
}
bool BigNum::operator== (const BigNum& b)const{
    if (len!=b.len) return false;
    for (int i=0;i<len;i++)
        if (a[i]!=b[i]) return false;
    return true;
}
bool BigNum::operator!= (const BigNum& b)const{
    return !(*this==b);
}
ostream& operator<< (ostream& os,const BigNum& a){
    int i=a.len-1;
    os << a[i];
    for (i-=1;i>=0;i--){
        if (a[i]<a.base/10) os << '0';
        if (a[i]<a.base/100) os << '0';
        if (a[i]<a.base/1000) os << '0';
        os << a[i];
    }
    return os;
}
string BigNum::toString()const{
    int i=len-1;
    char s[MAX*blen+1];
    sprintf(s,"%d",a[i]);
    for (i-=1;i>=0;i--)
    {
        if (a[i]<base/10) sprintf(s+strlen(s),"%d",0);
        if (a[i]<base/100) sprintf(s+strlen(s),"%d",0);
        if (a[i]<base/1000) sprintf(s+strlen(s),"%d",0);
        sprintf(s+strlen(s),"%d",a[i]);
    }
    return string(s,s+strlen(s));
}
BigNum cal(BigNum a){
    string s=a.toString();
    int x=s[0]-'0';
    int b=s.size();
    if (b==1) return BigNum(x);
    BigNum tmp;
    for (int i=0;i<b-1;i++)
        tmp=tmp+BigNum(9,i)*(i+1);
    tmp=tmp+(a-BigNum(1,b-1)+1)*b;
    return tmp;
}
int get(string s1,string s2){
    int i,ans=0;
    for (i=1;i<=int(min(s1.size(),s2.size()));i++){
        string ss1=s1.substr(0,i);
        string ss2=s2.substr(s2.size()-i,i);
        if (ss1==ss2) ans=i;
    }
    return ans;
}
int main(){
    //freopen("in.txt","r",stdin);
    int i,j,len,n,k,slen;
    bool ff;
    BigNum ans,tmp;
    string s,ss,st,sp,s1,s2;
    cin >> s;
    n=s.size();
    if (s==string(n,'0')){
        ans=cal(BigNum(1,n))-n+1;
        cout << ans << endl;
        return 0;
    }
    if (n==1){
        cout << s << endl;
        return 0;
    }
    for (len=1;len<n;len++)
        for (i=0;i+len-1<n;i++){
            j=i+len-1;
            if (j>=n) continue;
            ff=true;
            st=s.substr(i,len);
            if (st[0]=='0') continue;
            if (i>0){
                sp=(BigNum(st)-1).toString();
                ss=s.substr(0,i);
                if (ss.size()>sp.size()) continue;
                if (sp.rfind(ss)!=sp.size()-ss.size()) ff=false;
            }
            if (!ff) continue;
            slen=len;
            for (k=j+1;k+slen-1<n;k+=slen){
                st=(BigNum(st)+1).toString();
                slen=st.size();
                if (k+slen-1>=n) break;
                if (st!=s.substr(k,slen)){
                    ff=false;
                    break;
                }
            }
            if (!ff) continue;
            if (k<n){
                st=(BigNum(st)+1).toString();
                ss=s.substr(k,n-k);
                if (st.find(ss)!=0) ff=false;
            }
            if (ff){
                st=s.substr(i,len);
                ans=cal(BigNum(st))-i-st.size()+1;
                goto ppp;
            }
        }
    ppp:
    for (i=0;i<n;i++){
        st=s.substr(0,i);
        st=(BigNum("1"+st)+1).toString();
        st=st.substr(1,st.size()-1);
        s2=s.substr(i,n-i);
        k=get(st,s2);
        if (k>=int(s2.size())) continue;
        st=s.substr(i,n-i-k)+st;
        if (st[0]=='0') continue;
        tmp=cal(BigNum(st)-1)-i+1;
        if (ans==BigNum(0)) ans=tmp;
        else if (tmp<ans) ans=tmp;
    }
    if (s[0]>'0'){
        tmp=cal(BigNum(s))-n+1;
        if (ans==BigNum(0)) ans=tmp;
        else if (tmp<ans) ans=tmp;
    }
    else{
        s="1"+s;
        tmp=cal(BigNum(s))-n;
        if (ans==BigNum(0)) ans=tmp;
        else if (tmp<ans) ans=tmp;
    }
    cout<< ans << endl;
}
