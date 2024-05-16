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

const int MAXN = 1e5 + 5;
ll tree[MAXN << 2], mark[MAXN << 2], n, m, A[MAXN];
void build(int p = 1, int cl = 1, int cr = n)
{
    if(cl == cr) return void(tree[p] = A[cl]);
    int mid = (cl + cr) >> 1;
    build(p << 1, cl, mid);
    build(p << 1 | 1, mid + 1, cr);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

void push_down(int p, int len)
{
    if(len <= 1) return;
    tree[p << 1] += mark[p] * (len - len / 2);
    mark[p << 1] += mark[p];
    tree[p << 1 | 1] += mark[p] * (len / 2);
    mark[p << 1 | 1] += mark[p];
    mark[p] = 0;
}

void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n)
{
    if(cl >= l && cr <= r)
    {
        tree[p] += d * (cr - cl + 1);
        mark[p] += d;
        return;
    }
    push_down(p, cr - cl + 1);
    int mid = (cl + cr) / 2;
    if(mid >= l) update(l,r,d,p << 1,cl,mid);
    if(mid < r) update(l,r,d,p << 1 | 1,mid + 1, cr);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

ll query(int l, int r, int p = 1, int cl = 1, int cr = n)
{
    if(cl >= l && cr <= r) return tree[p];
    push_down(p, cr - cl + 1);
    ll mid = (cl + cr) >> 1, ans = 0;
    if(mid >= l) ans += query(l,r,p << 1, cl, mid);
    if(mid < r) ans += query(l,r,p << 1 | 1, mid + 1,cr);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> A[i];
    build();
    while(m--)
    {
        int op, l, r, d;
        cin >> op >> l >> r;
        if(op == 1) cin >> d, update(l,r,d);
        else cout << query(l,r) << endl;
    }
    return 0;
}