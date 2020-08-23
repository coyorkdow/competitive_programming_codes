#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define space putchar(' ')
#define enter putchar('\n')
#define eps 1e-10
#define ba 47
#define MAXN 200005
//#define ivorysi
using namespace std;
typedef long long int64;
typedef unsigned int u32;
typedef double db;
template <class T>
void read(T &res)
{
    res = 0;
    T f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        res = res * 10 + c - '0';
        c = getchar();
    }
    res *= f;
}
template <class T>
void out(T x)
{
    if (x < 0)
    {
        x = -x;
        putchar('-');
    }
    if (x >= 10)
    {
        out(x / 10);
    }
    putchar('0' + x % 10);
}
struct node
{
    int to, next, cap;
    int64 val;
} E[1000005];
int head[405], sumE = 1, Ncnt, S, T;
int64 ans, c[405];
int N, K, A, B;
bool vis[405];
void add(int u, int v, int c, int a)
{
    E[++sumE].to = v;
    E[sumE].next = head[u];
    E[sumE].cap = c;
    E[sumE].val = a;
    head[u] = sumE;
}
void addtwo(int u, int v, int c, int a)
{
    add(u, v, c, a);
    add(v, u, 0, -a);
}
int64 dis[405];
bool inq[405];
queue<int> Q;
bool SPFA()
{
    for (int i = 1; i <= Ncnt; ++i)
        dis[i] = -1e18;
    dis[S] = 0;
    Q.push(S);
    memset(inq, 0, sizeof(inq));
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = 0;
        for (int i = head[u]; i; i = E[i].next)
        {
            int v = E[i].to;
            if (E[i].cap)
            {
                if (dis[u] + E[i].val > dis[v])
                {
                    dis[v] = dis[u] + E[i].val;
                    if (!inq[v])
                    {
                        Q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
    }
    return dis[T] > -1e18;
}
int dfs(int u, int aug)
{
    if (u == T)
    {
        ans += aug * dis[T];
        return aug;
    }
    vis[u] = 1;
    for (int i = head[u]; i; i = E[i].next)
    {
        int v = E[i].to;
        if (!vis[v] && E[i].cap && dis[v] == dis[u] + E[i].val)
        {
            int t = dfs(v, min(E[i].cap, aug));
            if (t)
            {
                E[i].cap -= t;
                E[i ^ 1].cap += t;
                return t;
            }
        }
    }
    return 0;
}
void MCMF()
{
    while (SPFA())
    {
        do
        {
            memset(vis, 0, sizeof(vis));
        } while (dfs(S, 0x7fffffff));
    }
}
void Solve()
{
    ans = 0;
    memset(head, 0, sizeof(head));
    sumE = 1;
    // read(N);
    // read(K);
    // read(A);
    // read(B);
    scanf("%d%d%d%d",&N,&K,&A,&B);
    for (int i = 1; i <= N; ++i)
    {
        // read(c[i]);
        scanf("%d",&c[i]);
    }
    int d = N - K + 2;
    S = d + 1;
    T = d + 2;
    Ncnt = d + 2;
    for (int i = 1; i <= K; ++i)
    {
        addtwo(min(i + 1, d), 1, 1, c[i]);
    }
    for (int i = K + 1; i <= N; ++i)
    {
        addtwo(min(i + 1, d), i - K + 1, 1, c[i]);
    }
    for (int i = 2; i <= d; ++i)
    {
        addtwo(i, i - 1, B - A, 0);
    }
    addtwo(1, T, B, 0);
    addtwo(S, d, B, 0);
    MCMF();
    out(ans);
    enter;
}
int main()
{
#ifdef ivorysi
    freopen("f1.in", "r", stdin);
#endif
    int T;
    // read(T);
    scanf("%d",&T);
    for (int i = 1; i <= T; ++i)
        Solve();
    return 0;
}