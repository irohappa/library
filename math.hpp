using i128 = __int128_t;

// in : g = gcd(a, b) >= 0
// out: (x,y)  ax + by = g.
ll extGCD(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = (a < 0 ? -1 : 1);
        y = 0;
        return abs(a);
    }

    ll p, q;
    ll g = extGCD(b, a%b, p, q);
    x = q;
    y = p - (a/b) * q;
    return g;
}

// find (x,y) ax + by = c.
// false 解なし。解が ll に収まることを仮定する。
bool solve_equation(ll a, ll b, ll c, ll &x, ll &y){
    if(a == 0 && b == 0){
        x = y = 0;
        return c == 0;
    }

    ll g = extGCD(a, b, x, y);
    if(c % g != 0) return false;

    x = (i128)x * (c / g);
    y = (i128)y * (c / g);
    return true;
}


ll mod_norm(ll x, ll m){
    assert(m > 0);
    ll r = x % m;
    if(r < 0) r += m;
    return r;
}

// find x such that a*x ≡ 1 (mod m)
// return false if no inverse exists
// constraint: m > 0
// out: 0 <= x < m
bool mod_inv(ll a, ll m, ll &x){
    ll y;
    ll g = extGCD(a, m, x, y);
    if(g != 1) return false;

    x = mod_norm(x, m);
    return true;
}

// Merge:
//   x ≡ r1 (mod m1)
//   x ≡ r2 (mod m2)
//
// Returns false if no solution exists.
// Otherwise, returns:
//   x ≡ r (mod m), 0 <= r < m
// where m = lcm(m1, m2).
// Constraints: m1 > 0, m2 > 0.
// The lcm and all intermediate values must fit in i128; r and m must fit in ll.
bool CRT(ll r1, ll m1, ll r2, ll m2, ll &r, ll &m){
    r1 = mod_norm(r1, m1);
    r2 = mod_norm(r2, m2);

    ll p, q;
    ll g = extGCD(m1, m2, p, q);

    ll diff = r2 - r1;
    if (diff % g != 0) return false;

    ll m2g = m2 / g;

    // t = (diff / g) * inv(m1 / g) (mod m2 / g)
    ll t = (ll)((i128)(diff / g) * p % m2g);
    t = mod_norm(t, m2g);

    i128 lcm = (i128)m1 * m2g;
    i128 ans = (i128)r1 + (i128)m1 * t;
    ans %= lcm;

    r = (ll)ans;
    m = (ll)lcm;
    return true;
}
// floor(a / b)
// constraint: b != 0, (a, b) != (LLONG_MIN, -1)
ll floor_div(ll a, ll b){
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a < 0) != (b < 0))) --q;
    return q;
}

// ceil(a / b)
// constraint: b != 0, (a, b) != (LLONG_MIN, -1)
ll ceil_div(ll a, ll b){
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a < 0) == (b < 0))) ++q;
    return q;
}
i128 floor_div(i128 a, i128 b){
    assert(b != 0);
    i128 q = a / b;
    i128 r = a % b;
    if (r != 0 && ((a < 0) != (b < 0))) --q;
    return q;
}

i128 ceil_div(i128 a, i128 b){
    assert(b != 0);
    i128 q = a / b;
    i128 r = a % b;
    if (r != 0 && ((a < 0) == (b < 0))) ++q;
    return q;
}
// Count integer solutions of
//   a*x + b*y = c
//   lx <= x <= rx
//   ly <= y <= ry
//
// Preconditions:
//   a > 0, b > 0
//   lx <= rx, ly <= ry
//   The answer fits in ll.
//
// After construction, each count query takes O(1).
struct LinearDiophantineCounter {
    ll a, b, g, p, q;

    // a*p + b*q = g = gcd(a,b)
    LinearDiophantineCounter(ll a_, ll b_)
        : a(a_), b(b_){
        assert(a > 0 && b > 0);
        g = extGCD(a, b, p, q);
    }

    ll count(ll c, ll lx, ll rx, ll ly, ll ry) const{
        if (lx > rx || ly > ry) return 0;
        if (c % g != 0) return 0;

        // One particular solution.
        i128 mul = (i128)(c / g);
        i128 x0 = (i128)p * mul;
        i128 y0 = (i128)q * mul;

        // General solution:
        // x = x0 + (b/g)*t
        // y = y0 - (a/g)*t
        i128 dx = b / g;
        i128 dy = a / g;

        // Bounds derived from lx <= x <= rx.
        i128 lo = ceil_div((i128)lx - x0, dx);
        i128 hi = floor_div((i128)rx - x0, dx);

        // Bounds derived from ly <= y <= ry.
        lo = max(lo, ceil_div(y0 - (i128)ry, dy));
        hi = min(hi, floor_div(y0 - (i128)ly, dy));

        if (lo > hi) return 0;
        return (ll)(hi - lo + 1);
    }
};