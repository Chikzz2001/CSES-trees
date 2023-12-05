#include <bits/stdc++.h>
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
#define co(n) __builtin_popcountll(n)
#define cz(n) __builtin_ctzll(n)
#define yes cout<<"YES\n";
#define no cout<<"NO\n";
const int MAXN=200100;
const int M=1e9+7;
vector<int>fact(MAXN,1);
vector<bool>sieve(MAXN,1);
vector<int>dsieve(MAXN,0);


bool isPrime(int n){for(int i=2;i*i<=n;i++){if(n%i==0)return 0;}return 1;}
void primeSieve(){sieve[0]=sieve[1]=0;for (int i=2;i*i<MAXN;i++){if(sieve[i]){for(int j=i*i;j<MAXN;j+=i)sieve[j]=0;}}}
void divSieve(){for(int i=1;i<MAXN;i++){for(int j=i;j<MAXN;j=j+i){++dsieve[j];}}}
void factSieve(){for(int i=1;i<MAXN;i++)fact[i]=(fact[i-1]%M*1LL*i%M)%M;}
map<int,int> primeFactorise(int n){map<int,int> m;for(int i=2;i*i<=n;i++){if(n%i==0){int cnt=0;while(n%i==0){++cnt;n=n/i;}m[i]=cnt;}}if(n>1)m[n]=1;return m;}
int gcd(int a,int b){if(b==0)return a;return gcd(b,a%b);}
int binexp(int x,int n){int a=x;int prod=1;while(n){if(n%2==1)prod=prod*a;a=a*a;n=n/2;}return prod;}
int modexp(int a, int b, int m) {a%=m;int res=1LL;while(b>0){if(b&1) res=(res%m*1LL*a%m)%m;a=(a%m*1LL*a%m)%m;b>>=1;}return res%m;}
int modadd(int a,int b,int m){return (a%m+b%m)%m;}
int modsub(int a,int b,int m){return (a%m-b%m+m)%m;}
int modmul(int a,int b,int m){return (a%m*1LL*b%m)%m;}
int modinv(int a,int m){return modexp(a,m-2,m);}
int moddiv(int a,int b,int m){return (a%m*1LL*modinv(b,m)%m)%m;}
int nCr(int n,int r){if(n<r||r<0)return 0;if(r==1)return n;int nmr=fact[n]%M;int dmr=(fact[r]%M*1LL*fact[n-r]%M)%M;return (nmr%M*1LL*modinv(dmr,M)%M)%M;}

int dp[MAXN][2];
int dfs(vector<int>g[],int n,int p,int take) {
    if(dp[n][take]!=-1)return dp[n][take];
    int maxx=0,s=0;
    vector<int>v;
    for(int c:g[n]) {
        if(c!=p) {
            int tk=dfs(g,c,n,1);
            int ntk=dfs(g,c,n,0);
            v.push_back(tk-ntk);
            s+=tk;
        }
    }

    for(int x:v) {
        maxx=max(maxx,1+s-x);
    }
    return dp[n][take]=!take?s:max(s,maxx);
}

void solve() {
    int n;cin>>n;
    vector<int>g[n+1];
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<n;i++) {
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout<<dfs(g,1,0,1)<<"\n";
}

signed main()
{
    fio
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    //primeSieve();
    int t=1;
    // cin>>t;
    for(int i=1;i<=t;i++) {
        //cout<<"Case #"<<i<<": ";
        solve();
    }
}