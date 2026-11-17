/*＿＿＿＿＿＿
　　 ||　　　　  　|
　　 ||ACはこちらへ|
　　 ||　　　　  　|
　　 ||￣￣￣￣￣￣ 
∧_∧||
(`･ω･||
（ つ||０
　uｰu*/ //https://github.com/irohappa/library
#include <bits/stdc++.h>
using namespace std;


//output and debug
template <class T> using V = vector<T>;
template <class T, class U> 
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << "P(" << p.first << ", " << p.second << ")";
}
template <class T> ostream& operator<<(ostream& os,const V<T>& v) {
    bool f = false;
    for (auto d : v) {
        if (f) os << " ";
        f = true;
        os << d;
    }
    return os;
}
template <class T> ostream& operator<<(ostream& os,const set<T>& s) {
    os << "{";
    bool f = false;
    for (auto d : s) {
        if (f) os << ", ";
        f = true;
        os << d;
    }
    return os << "}";
}
template <class T> ostream& operator<<(ostream& os, const multiset<T>& s) {
    os << "{";
    bool f = false;
    for (auto d : s) {
        if (f) os << ", ";
        f = true;
        os << d;
    }
    return os << "}";
}
template <class T, class U>
ostream& operator<<(ostream& os, const map<T, U>& s) {
    os << "{";
    bool f = false;
    for (auto p : s) {
        if (f) os << ", ";
        f = true;
        os << p.first << ": " << p.second;
    }
    return os << "}";
}
// debug print (1D: [a, b, c] / 2D: one row per line)
template <class T> struct is_vec : false_type {};
template <class T> struct is_vec<V<T>> : true_type {};
template <class T> void dprint(ostream& os, const T& x) { os << x; }
template <class T> void dprint(ostream& os, const V<T>& v);
template <class T, class U> void dprint(ostream& os, const pair<T, U>& p) {
    os << "P("; dprint(os, p.first); os << ", "; dprint(os, p.second); os << ")";
}
template <class T> void dprint(ostream& os, const V<T>& v) {
    if constexpr (is_vec<T>::value) {
        os << "[\n";
        for (auto& row : v) { os << "  "; dprint(os, row); os << "\n"; }
        os << "]";
    } else {
        os << "[";
        bool f = false;
        for (auto& d : v) {
            if (f) os << ", ";
            f = true;
            dprint(os, d);
        }
        os << "]";
    }
}
template<class T, class... Ts>
void deo(const T& a, const Ts&... b){
    dprint(cerr, a);
    ((cerr << ' ', dprint(cerr, b)), ...);
    cerr << '\n';
}
template<class T, class... Ts>
void o(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
#ifdef LOCAL
#define dbg(...)                                            \
    do {                                                    \
        cerr << __LINE__ << " : " << #__VA_ARGS__ << " = "; \
        deo(__VA_ARGS__);                                   \
    } while (false)
#else
#define dbg(...)
#endif
// input
template<class... T>
void in(T&... a){
    (cin >> ... >> a);
}
template<class T> void in(vector<T>& a){ for(auto&& i : a) in(i); }
template<class T, class L> void in(pair<T, L>& p){ in(p.first); in(p.second); }
template<class T> void in(T& a){ cin >> a; }

#include <atcoder/all>
using namespace atcoder;
//using mint = modint998244353;


#define rep1(n)          for(ll i = 0; i < n; ++i)
#define rep2(i, n)       for(ll i = 0; i < n; ++i)
#define rep3(i, j, n)    for(ll i = j; i < n; ++i)
#define overload3(a, b, c,  e, ...) e
#define rep(...) overload3(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)
#define rrep1(n) rrep2(_,n)
#define rrep2(i,n) for(ll i=n;i--;)
#define rrep3(i,a,b) for(ll i=b;i-->(a);)
#define rrep(...) overload3(__VA_ARGS__,rrep3,rrep2,rrep1)(__VA_ARGS__)
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
using ll = long long ;
using ld = long double;
using pa = pair<ll,ll>;
using t2 = tuple<ll,ll>;
using tu = tuple<ll,ll,ll>;
using vi = vector<ll>;
using vs = vector<string>;
using vp = vector<pa>;
using vvi = vector<vi>;
using vvp = vector<vp>;
using vvvi = vector<vvi>;
using v4 = vector<vvvi>;
using vt = vector<tu>;
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define sz(a) ssize(a)
const ll INF = (1ll << 29);
const ll inf = INF*INF;
const ll dh[]={1,-1,0,0, 1,-1,1,-1};
const ll dw[]={0,0,1,-1, 1,1,-1,-1};
const string mv = "DURL";
template<class T> using pq = priority_queue<T, vector<T>, greater<>>;

void Yes(bool i = true){ return o(i?"Yes":"No"); }
#define uniq(a) (sort(all(a)), (a).erase(unique(all(a)), (a).end()))
bool chmin(auto& a, auto b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto& a, auto b) { return a < b ? a = b, 1 : 0; }
 
void solve(){
	ll n;in(n);

}

int main(){
    ll t = 1;
	// cin >> t //マルチテストケースか確認
	rep(t) solve();
}