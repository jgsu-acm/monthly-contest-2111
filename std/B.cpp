#include <iostream>
using namespace std;
const int MAXN = 5e5+5;
const int MOD = 1e9+7;
typedef long long ll;
ll a[MAXN],b[MAXN];
ll prea[MAXN],preb[MAXN],preab[MAXN];
ll preprea[MAXN],prepreb[MAXN],prepreab[MAXN];
int n;
inline void calcPre(ll a[], ll pre[])   // 计算a数组的前缀和存于pre数组中
{
    for(int i=1;i<=n;i++)
        pre[i]=(a[i]+pre[i-1]) % MOD;
}
ll solve()
{
    ll sum = 0;
    for(int l=1;l<=n;l++)
    {
        sum = (sum + prepreab[n]-prepreab[l-1]+MOD) % MOD;  // 第一项
        sum = (sum + (n-l+1)*preab[l-1]%MOD) % MOD;         // 第二项
        sum -= (preprea[n]-preprea[l-1])*preb[l-1]%MOD;     // 第三项
        sum = (sum + MOD) % MOD;    // 有可能出现负数，转为正数
        sum -= (prepreb[n]-prepreb[l-1])*prea[l-1]%MOD;     // 第四项
        sum = (sum + MOD) % MOD;    // 有可能出现负数，转为正数
    }
    return sum;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    calcPre(a, prea);
    calcPre(b, preb);
    for(int i=1;i<=n;i++) preab[i]=prea[i]*preb[i]%MOD;
    calcPre(prea, preprea);
    calcPre(preb, prepreb);
    calcPre(preab, prepreab);
    cout<<solve()<<endl;
    return 0;
}