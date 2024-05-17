#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lb;
#define pii pair<int,int>
#define all(x) (x).begin(), (x).end()
#define debug(x){cerr<<#x<<'='<<x<<endl;}
#define endl '\n'
const ll INF = 2005020600;
//cout<<fixed<<setprecision(5)<< x <<endl;

int n, m, s, t;
ll w, ans, dis[520010];
int tot = 1, now[520010], head[520010];

struct node
{
    int to, nxt;
    ll val;
}e[520010];

void add(int u, int v, ll w)
{
    e[++tot].to = v, e[tot].val = w, e[tot].nxt = head[u], head[u] = tot;
    e[++tot].to = u, e[tot].val = 0, e[tot].nxt = head[v], head[v] = tot;
}

int bfs()
{
    for(int i = 1; i <= n; i++) dis[i] = INF;
    queue<int>q;
    q.push(s);
    dis[s] = 0;
    now[s] = head[s];
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = head[x]; i ; i = e[i].nxt)
        {
            int v = e[i].to;
            if(e[i].val > 0 && dis[v] == INF)
            {
                q.push(v);
                now[v] = head[v];
                dis[v] = dis[x] + 1;
                if(v == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int x, ll sum)
{
    if(x == t) return sum;
    ll k, res = 0;
    for(int i = now[x]; i && sum; i = e[i].nxt)
    {
        now[x] = i;
        int v = e[i].to;
        if(e[i].val > 0 && (dis[v] == dis[x] + 1))
        {
            k = dfs(v, min(sum, e[i].val));
            if(k == 0) dis[v] = INF;
            e[i].val -= k;
            e[i ^ 1].val += k;
            res += k;
            sum -= k;
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    while(m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    while(bfs())
    {
        ans += dfs(s,INF);
    }

    cout << ans << endl;
    return 0;
}
