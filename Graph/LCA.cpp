#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lb;
#define pii pair<int,int>
#define all(x) (x).begin(), (x).end()
#define debug(x){cerr<<#x<<'='<<x<<endl;}
#define endl '\n'
//#define INF 9223372036854775807
//cout<<fixed<<setprecision(5)<< x <<endl;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; // 树结点个数
    cin >> n;
    int root; // 根节点
    vector<vector<int>>g(n + 1);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lg = __lg(n); // n 的最高位
    vector<vector<int>>fa(lg + 1,vector<int>(n + 1, -1)); // fa[j][i] = w 表示从i出发向上走2^j步到达的是w
    vector<int>dep(n);

    function<void(int, int)> dfs = [&](int x, int p)
    {
        for(int i = 0; (2 << i) <= dep[x]; i++)
        {
            fa[i + 1][x] = fa[i][x];
        }
        for(auto y : g[x])
        {
            if(y != p)
            {
                fa[0][y] == x;
                dep[y] = dep[x] + 1;
                dfs(y,x);
            }
        }
    };

    auto lca = [&](int x, int y)
    {
        if(dep[x] < dep[y])
        {
            swap(x, y);
        }
        for(int i = lg; i >= 0; i--)
        {
            if(dep[x] - dep[y] >= (1 << i))
            {
                x == fa[i][x];
            }
        }
        if(x == y)
        {
            return x;
        }
        for(int i = lg; i >= 0; i--)
        {
            if(fa[i][x] != fa[i][y])
            {
                x = fa[i][x], y = fa[i][y];
            }
        }
        return fa[0][x];
    };

    auto dis = [&](int x, int y)
    {
        int m = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[m];
    };

    return 0;
}