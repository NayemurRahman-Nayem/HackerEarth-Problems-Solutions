// Bismillahir Rahmanir Rahim


#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
typedef unsigned long long ull ;
typedef vector<int> vi ;
typedef vector<ll> vl ;
typedef vector<vi> vvi ;
typedef vector<vl> vvl ;
typedef pair<int, int> pii ;
typedef pair<ll, ll> pll ;
typedef pair<float, float> pff ;
typedef pair<double, double> pdd ;
typedef pair<ll, ll> pll ;
#define pb push_back
#define el << '\n' ;
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).begin(),(a).end()
#define F first
#define S second
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
#define pb push_back
#define PI 3.14159265358979323
#define file() freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#define fastIO	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0) ;
ll bin_expo(ll base, ll pow, ll m) {
    if (pow == 0) return 1;ll ret = bin_expo(base, pow / 2, m) % m ;
    if (pow & 1) return (ret % m * ret % m * base % m) % m;else return (ret % m * ret % m) % m ; }
ll ncr(ll n , ll r) {ll mul = 1 ; for(ll i=1;i<=r;i++) {mul = mul * (n-i+1) ; mul = mul/i ; }return mul ; }
ll mod_add(ll a, ll b, ll m) { return ((a % m) + (b % m)) % m ; }
ll mod_sub(ll a, ll b, ll m) { return (a-b+m)%m ; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m ; }
ll mod_div(ll a, ll b, ll m) { return ((a % m) * bin_expo(b, m - 2, m)) % m ; }
ll aModB(ll a , ll b) { if(a<0 ) { return ((a+(abs(a)/b)*b)+b)%b ; } else { return a%b; } }
ll lcm(ll a, ll b) { return (a * b) / __gcd(a, b) ; }
int dx[] = {0, 0, +1, -1, +1, -1, -1, +1} ;
int dy[] = {+1, -1, 0, 0, +1, -1, +1, -1} ;
const ll infLL = 4e18 + 123 ;
const ll inf = 1e12 + 7 ;
const ll mod = 1e9 + 7 ;
const ll mod2 = 998244353 ;
const ll mx = 1e5 + 10 ;
const ll LOG = 20 ;

// ---------------------------------------------------------------------------------------------------------------------


int anc[mx][LOG] , par[mx] , depth[mx] , vis[mx] , mvalInPath[mx][LOG] ;
vector<pair<int,int>> adj[mx] ;
int n ;


void dfs(int node) {

    vis[node] = 1 ;
    for(auto p:adj[node]) {
        int u = p.F ;
        int w = p.S ;
        if(!vis[u]) {
            depth[u] = depth[node] + 1 ;
            anc[u][0] = node ;
            mvalInPath[u][0] = w ;
            dfs(u) ;
        }
    }
}


void preProcess() {
    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=n;i++) {
            anc[i][j] = anc[ anc[i][j-1] ][j-1] ;
            mvalInPath[i][j] = max(mvalInPath[i][j-1] , mvalInPath[ anc[i][j-1] ][j-1] ) ;
        }
    }
}


int LCA(int a , int b) {
    int ret = 0 ;
    if(depth[a] < depth[b]) {
        swap(a,b) ;
    }
    int k = depth[a] - depth[b] ;
    for(int j=LOG-1;j>=0;j--) {
        if(k>=(1<<j)) {
            ret = max(ret,mvalInPath[a][j]) ;
            a = anc[a][j] ;
            k -= (1<<j) ;
        }
    }
    if(a==b) {
        return ret ;
    }
    for(int j=LOG-1;j>=0;j--) {
        if(anc[a][j]!=anc[b][j]) {
            ret = max(ret , max(mvalInPath[a][j] , mvalInPath[b][j]) ) ;
            a = anc[a][j] ;
            b = anc[b][j] ;
        }
    }
    return max(ret , max(mvalInPath[a][0] , mvalInPath[b][0])) ;
}


void solution(ll cs) {

    cin >> n ;
    for(ll i=1;i<n;i++) {
        ll u , v , w ;
        cin >> u >> v >> w ;
        adj[u].pb({v,w}) ;
        adj[v].pb({u,w}) ;
    }
    depth[1] = 0 ;
    dfs(1) ;
    preProcess() ;
    int q ;
    cin >> q ;
    while(q--) {
        int u , v , w ;
        cin >> u >> v >> w ;
        int z = LCA(u,v) ;
        if(w<z) {
            cout << "YES" el ;
        }
        else {
            cout << "NO" el ;
        }
    }
}


int main() {

    fastIO  ;
    #ifndef ONLINE_JUDGE
    file() ;
    #endif
    ll cs = 1 ;
    //cin >> cs ;
    for(ll i=1;i<=cs;i++) solution(i) ;
    return   0 ;
}
