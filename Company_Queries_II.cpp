#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
//#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
#define int long long int
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define all(a) a.begin(), a.end()
#define mp make_pair
#define pb push_back
#define ppb pop_back
#define pr pair<int, int>
#define ff first
#define ss second
#define pie 3.1415926535898
#define inf LLONG_MAX
#define co(n) __builtin_popcount(n)
#define cz(n) __builtin_ctz(n)
const int M=1e9+7;
int mult(int a, int b, int p = M)
{
    return ((a % p) * (b % p)) % p;
}
int gcd(int a,int b){if(b==0)return a;return gcd(b,a%b);}
int binexp(int x,int n){int a=x;int prod=1;while(n){if(n%2==1)prod=prod*a;a=a*a;n=n/2;}return prod;}
int modexp(int a, int b, int m) {a %= m;int res = 1LL;while (b > 0) {if (b & 1)res = (res%m *1LL* a%m) % m;a = (a%m *1LL* a%m) % m;b >>= 1;}return res%m;}
int modadd(int a,int b,int m){return (a%m+b%m)%m;}
int modsub(int a,int b,int m){return (a%m-b%m+m)%m;}
int modmul(int a,int b,int m){return (a%m*1LL*b%m)%m;}
int modinv(int a,int m){return modexp(a,m-2,m);}
int moddiv(int a,int b,int m){return (a%m*1LL*modinv(b,m)%m)%m;}

int fpow(int x, int y)
{
    int res = 1;
    x = x % M;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1LL)
            res = (res * x) % M;
        y = y >> 1LL;
        x = (x * x) % M;
    }
    return res;
}
int inv(int a, int p = M) { return fpow(a, p - 2); }

class DSU
{
public:
    vector<int> par, size;
    DSU(int n)
    {
        par = vector<int>(n);
        size = vector<int>(n);

        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        if (x == par[x])
            return x;
        return par[x] = find(par[x]);
    }

    bool is_joined(int a, int b)
    {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb)
            return 1;

        if (size[pa] <= size[pb])
        {
            par[pa] = pb;
            size[pb] += size[pa];
        }
        else
        {
            par[pb] = pa;
            size[pa] += size[pb];
        }

        return 0;
    }
};

int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
bool valid(int x, int y, int n, int m)
{
    if (x < 0 || y < 0 || x >= n || y >= m)
        return false;
    return true;
}
#define maxn 500005

vector<bool> isprime(1e9 + 1, true);
void prime()
{
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= 1e9; i++)
    {
        if (isprime[i] && i * i <= 1e9)
        {
            for (int j = i * i; j <= 1e9; j += i)
                isprime[j] = false;
        }
    }
}

bool ispalin(string s)
{
    int n = s.length(), l;
    if (n == 1)
        return true;
    if (n % 2 == 0)
        l = n / 2 - 1;
    else
        l = (n - 1) / 2 - 1;
    for (int i = 0; i <= l; i++)
        if (s[i] != s[n - i - 1])
            return false;
    return true;
}

void printprime(int n)
{
    int c = 1;
    for (int x = 2; c <= n; x++)
    {
        if (isprime[x])
        {
            cout << x << " ";
            c++;
        }
    }
    cout << "\n";
}

bool cprime(int x)
{
    if (x == 1)
        return false;
    if (x <= 3)
        return true;
    if (x % 2 == 0 || x % 3 == 0)
        return false;
    for (int i = 5; i <= sqrt(x); i += 6)
        if (x % i == 0 || x % (i + 2) == 0)
            return false;
    return true;
}

int dp[200005][20];
int lvl[200005];
void dfs(vector<vector<int>>& g,int node,int p,int l)
{
    lvl[node]=l;
    for(int c:g[node])
    {
        if(c!=p)dfs(g,c,node,l+1);
    }
}

int lift_node(int u,int d)
{
    if(!d)return u;
    int c=0;
    while(d)
    {
        if(d&1)u=dp[u][c];
        c++;
        d>>=1;
    }
    return u;
}

void solve()
{
    int n,q;
    cin>>n>>q;

    vector<vector<int>>g(n+1);
    for(int i=2;i<=n;i++)
    {
        int x;cin>>x;
        dp[i][0]=x;
        g[x].push_back(i);
        g[i].push_back(x);
    }

    dfs(g,1,0,0);

    for(int j=1;j<20;j++)
    {
        for(int i=2;i<=n;i++)
        {
            if(dp[i][j-1])dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }

    while(q--)
    {
        int u,v;
        cin>>u>>v;

        if(lvl[u]>lvl[v])
            u=lift_node(u,lvl[u]-lvl[v]);
        else
            v=lift_node(v,lvl[v]-lvl[u]);
    
        int l=0,r=lvl[u],res=1;
        
        while(l<=r)
        {
            int m=l+(r-l)/2;
            int lu=lift_node(u,lvl[u]-m);
            int lv=lift_node(v,lvl[u]-m);
            if(lu==lv)
            {
                res=lu;
                l=m+1;
            }
            else
            r=m-1;
        }
        cout<<res<<"\n";

        // if(u==v){cout<<u<<"\n";continue;}
        // if(min(u,v)==1){cout<<1<<"\n";continue;}
        // for(int i=19;i>=0;i--)
        // {
        //     if(dp[u][i]!=dp[v][i])
        //     {
        //         u=dp[u][i];
        //         v=dp[v][i];
        //     }
        // }
        // cout<<dp[u][0]<<"\n";
    }
}

signed main()
{
    fio
        // prime();
        int t;
     t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}