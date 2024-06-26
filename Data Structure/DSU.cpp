//秩的优化
//分为三步，初始化，查询，合并
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN 5500
int fa[MAXN];
int _rank[MAXN];
inline void init(int n)
{
    for(int i=1;i<=n;i++){
        fa[i]=i;
        _rank[i]=1;
    }
}
int find(int x)
{
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

inline void merge(int i,int j)
{
    int x=find(i),y=find(j);
    if(_rank[x]<=_rank[y])
        fa[x]=y;
    else 
        fa[y]=x;
    if(_rank[x]==_rank[y]&&x!=y)
        _rank[y]++;
}
