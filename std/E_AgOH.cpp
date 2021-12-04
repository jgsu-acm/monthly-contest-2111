#include <iostream>
using namespace std;
const int maxn = 2e5+5;
int a[maxn], mod;
typedef pair<int,int> pii;
struct Node { int l,r; pii val; }sgt[maxn<<2];
inline int ls(int k) { return k<<1; }
inline int rs(int k) { return k<<1|1; }
inline pii max(pii x, pii y)
{
    if(x.first<y.first) return y;
    else if(x.first>y.first) return x;
    else if(x.second<y.second) return x;    // 值相等时返回下标比较小的
    else return y;
}
inline void pushup(int k) { sgt[k].val=max(sgt[ls(k)].val, sgt[rs(k)].val); }
void build(int l,int r,int k=1)
{
    sgt[k].l=l, sgt[k].r=r;
    if(l==r) sgt[k].val={a[l],l};
    else 
    {
        int m = (l+r)>>1;
        build(l,m,ls(k));
        build(m+1,r,rs(k));
        pushup(k);
    }
}
void modify(int p,int z,int k=1)
{
    int l=sgt[k].l, r=sgt[k].r;
    if(l==r) sgt[k].val.first=(sgt[k].val.first+z)%mod;
    else 
    {
        int m = (l+r)>>1;
        if(p<=m) modify(p,z,ls(k));
        else modify(p,z,rs(k));
        pushup(k);
    }
}
auto query(int x,int y,int k=1)
{
    int l=sgt[k].l, r=sgt[k].r;
    if(x<=l&&y>=r) return sgt[k].val;
    int m = (l+r)>>1;
    pii ret = {-1,0};
    if(x<=m) ret=query(x,y,ls(k));
    if(y>m) ret=max(ret, query(x,y,rs(k)));
    return ret;
}
int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin>>n>>mod;
    ++mod;  //! 注意
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,n);
    cin>>m;
    while(m--)
    {
        int opt,x,y;
        cin>>opt>>x>>y;
        if(opt==1)
        {
            if(!(1<=x&&x<=n)) cout<<"invalid"<<endl;
            else modify(x,y), cout<<endl;
        }
        else 
        {
            if(!(1<=x&&x<=y&&y<=n)) cout<<"invalid"<<endl;
            else
            {
                auto tmp = query(x,y);
                cout<<tmp.first<<' '<<tmp.second<<endl;
            }
        }
    }
    return 0;
}