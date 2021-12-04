#include <iostream>
using namespace std;
const int maxn = 505;
int fa[maxn*maxn], n, m, zhan[3], kuai[3], board[maxn][maxn];
int find(int x) { return x==fa[x]?x:x=find(fa[x]); }
inline void merge(int x,int y) { fa[find(x)]=find(y); }
inline int hs(int x,int y) { return (x-1)*n+y; }
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n*n;i++) fa[i]=i;    // 初始化并查集
    int mv[4][2]={{-1,0}, {1,0}, {0,-1}, {0,1}};
    for(int i=1;i<=m;i++) {
        int x,y,k,cnt=0;    // 每与周围同色棋子合并一下cnt就+1，当cnt为2时代表这一着棋是粘
        cin>>x>>y;
        board[x][y]=k=(i%2+1);    // 存下当前位置棋子黑白，黑为2白为1
        ++kuai[k];              // 如果是孤立棋子的话块数就会+1
        for(int j=0;j<4;j++) {  // 利用mv数组遍历上下左右四个方向的格子
            int p=x+mv[j][0], q=y+mv[j][1];
            if(board[x][y]==board[p][q]&&find(hs(x,y))!=find(hs(p,q))) { // 如果是同色不同块
                merge(hs(x,y), hs(p,q));
                --kuai[k];  // 每合并一次，块数就会减一
                if(++cnt==2) ++zhan[k];
            }
        }
    }
    cout<<zhan[2]<<' '<<zhan[1]<<endl<<kuai[2]<<' '<<kuai[1]<<endl;
    return 0;
}