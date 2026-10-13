# `math.hpp` 関数一覧

競技プログラミング用の数学ライブラリ。提出時は、使う関数とその依存関係を提出テンプレートへコピーして使う想定。

## 前提

- `ll` は普段使っている提出テンプレートで `long long` として定義しておく。
- `i128` はこのファイル内で `__int128_t` として定義している。
- `bits/stdc++.h`、`using namespace std;` なども提出テンプレート側にある想定。
- 整数型の範囲を超える演算はできない。各関数の制約を確認して使う。

## 一覧

| 関数・型 | 用途 | 計算量 |
|---|---|---:|
| `extGCD` | 拡張 Euclid の互除法。最大公約数と Bézout 係数を求める | `O(log max(|a|, |b|))` |
| `solve_equation` | `a*x + b*y = c` の整数解を1組求める | `O(log max(|a|, |b|))` |
| `mod_norm` | `m` を法として `x` を `0 <= r < m` に正規化する | `O(1)` |
| `mod_inv` | `a*x ≡ 1 (mod m)` の逆元を求める | `O(log m)` |
| `CRT` | 2つの合同式を中国剰余定理で併合する | `O(log max(m1, m2))` |
| `floor_div` | 実数としての `a / b` の床関数（小数部分を切り下げた整数） | `O(1)` |
| `ceil_div` | 実数としての `a / b` の天井関数（小数部分を切り上げた整数） | `O(1)` |
| `LinearDiophantineCounter` | 区間制約つき `a*x + b*y = c` の整数解の個数を数える | 構築 `O(log max(a,b))`、クエリ `O(1)` |

---

## `extGCD`

```cpp
ll extGCD(ll a, ll b, ll &x, ll &y);
```

`g = gcd(a,b)` と、次の等式を満たす整数 `x, y` を求める。

\[
a x + b y = g
\]

- 戻り値：`gcd(a,b)`（非負）
- 出力引数：`x, y` は Bézout 係数
- 典型用途：一次不定方程式、モジュラ逆元、CRT の実装

**注意：** `abs(LLONG_MIN)` や中間計算のオーバーフローを避ける必要がある。`a`、`b` が `LLONG_MIN` にならず、再帰中の係数計算が `ll` に収まる範囲で使う。

## `solve_equation`

```cpp
bool solve_equation(ll a, ll b, ll c, ll &x, ll &y);
```

一次不定方程式

\[
a x + b y = c
\]

の整数解を1組求める。

- 解が存在する場合：`true` を返し、`x, y` に解を格納する。
- 解が存在しない場合：`false` を返す。
- `a == 0 && b == 0` の場合は、`c == 0` なら `true`（`x = y = 0`）、それ以外は `false`。
- 解が存在する条件（`a,b` が同時に 0 ではない場合）：`gcd(a,b)` が `c` を割り切ること。
- 計算量：`O(log max(|a|, |b|))`

**注意：** 求めた `x, y` が `ll` に収まることが前提。収まらない値を `ll` に変換すると正しい結果にならない。

## `mod_norm`

```cpp
ll mod_norm(ll x, ll m);
```

`m > 0` のとき、`x` と合同な値 `r` を

\[
0 \le r < m
\]

の範囲から返す。負の `x` にも対応する。

- 前提：`m > 0`
- 計算量：`O(1)`

例：`mod_norm(-1, 5) == 4`。

## `mod_inv`

```cpp
bool mod_inv(ll a, ll m, ll &x);
```

合同式

\[
a x \equiv 1 \pmod m
\]

の逆元 `x` を求める。

- 前提：`m > 0`
- 逆元が存在するとき：`true` を返し、`x` に `0 <= x < m` の逆元を格納する。
- 逆元が存在しないとき：`false` を返す。
- 逆元が存在する条件：`gcd(a,m) == 1`
- 計算量：`O(log m)`

## `CRT`

```cpp
bool CRT(ll r1, ll m1, ll r2, ll m2, ll &r, ll &m);
```

次の2つの合同式を併合する。

\[
x \equiv r_1 \pmod {m_1}, \qquad
x \equiv r_2 \pmod {m_2}
\]

- 前提：`m1 > 0`, `m2 > 0`
- 解が存在しないとき：`false` を返す。
- 解が存在するとき：`true` を返し、`r, m` に
  \[
  x \equiv r \pmod m,\qquad 0 \le r < m
  \]
  を格納する。ここで `m = lcm(m1,m2)`。
- 解が存在する条件：`(r2-r1)` が `gcd(m1,m2)` で割り切れること。
- 計算量：`O(log max(m1,m2))`

**注意：** `r` と `m` は `ll` に収まる必要がある。`i128` の中間計算もオーバーフローしない範囲で使う。

## `floor_div` / `ceil_div`

```cpp
ll floor_div(ll a, ll b);
ll ceil_div(ll a, ll b);

i128 floor_div(i128 a, i128 b);
i128 ceil_div(i128 a, i128 b);
```

C++ の整数除算は 0 方向への切り捨てだが、これらは数学的な床関数・天井関数に対応する。

- `floor_div(a,b)`：実数としての `a / b` 以下で最大の整数。
- `ceil_div(a,b)`：実数としての `a / b` 以上で最小の整数。
- 前提：`b != 0`。`ll` 版では `(a,b) == (LLONG_MIN,-1)` を使わない。
- `i128` 版は `b != 0` を `assert` で確認する。

例：

| `a` | `b` | `floor_div(a,b)` | `ceil_div(a,b)` |
|---:|---:|---:|---:|
| 7 | 3 | 2 | 3 |
| -7 | 3 | -3 | -2 |
| 7 | -3 | -3 | -2 |
| -7 | -3 | 2 | 3 |
| 6 | 3 | 2 | 2 |

## `LinearDiophantineCounter`

```cpp
LinearDiophantineCounter(ll a, ll b);

ll count(ll c, ll lx, ll rx, ll ly, ll ry) const;
```

次の条件をすべて満たす整数組 `(x,y)` の個数を数える。

\[
a x + b y = c,\qquad
l_x \le x \le r_x,\qquad
l_y \le y \le r_y
\]

コンストラクタで係数 `a,b` を指定し、その後 `count` で右辺 `c` や区間を変えながら解の個数を求める。

- 前提：`a > 0`, `b > 0`
- 区間が空（`lx > rx` または `ly > ry`）なら `0` を返す。
- 解が存在しない場合も `0` を返す。
- 戻り値：条件を満たす整数組の個数
- 構築：`O(log max(a,b))`
- `count`：`O(1)`
- 個数が `ll` に収まることが前提。

### 使用例

`a*x + b*y = c` のうち、`1 <= x,y <= N` を満たす組の個数を数える例：

```cpp
LinearDiophantineCounter counter(a, b);
ll ways = counter.count(c, 1, N, 1, N);
```

`c` だけを変えて何度も数える場合、係数 `a,b` に対する拡張 Euclid の計算を毎回やり直さずに済む。

---

## コピペ時の依存関係

- `solve_equation`、`mod_inv`、`CRT`、`LinearDiophantineCounter` は `extGCD` に依存する。
- `mod_inv` と `CRT` は `mod_norm` に依存する。
- `LinearDiophantineCounter` は `floor_div` / `ceil_div` の `i128` 版に依存する。
- `i128` の型エイリアスも必要。
- `ll` は普段の提出テンプレート側で定義しておく。
