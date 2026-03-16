// -----------------------------------------------------------------------------
// C++98 / C++03 — Always available
// -----------------------------------------------------------------------------
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound,
#include <bitset>     // bitset (bitmask problems)
#include <cstdio>     // printf, scanf (C-style)
#include <deque>      // deque
#include <iomanip>    // setprecision, setw, fixed
#include <iostream>   // cin, cout, cerr
#include <list>       // doubly linked list
#include <map>        // map, multimap
#include <queue>      // queue, priority_queue
#include <set>        // set, multiset
#include <sstream>    // stringstream
#include <stack>      // stack
#include <vector>     // vector
                      // next_permutation, min, max, reverse, fill,
                      // count, find
#include <cassert>    // assert()
#include <cctype>     // isdigit, isalpha, toupper, tolower
#include <cfloat>     // DBL_MAX, FLT_MAX
#include <climits>    // INT_MAX, INT_MIN, LLONG_MAX, LLONG_MIN
#include <cmath>      // sqrt, pow, log, floor, ceil, abs, sin, cos
#include <cstdlib>    // abs (integer), rand, srand
#include <cstring>    // strlen, strcmp, memset, memcpy (C-style)
#include <functional> // greater<>, less<>, bind, function
#include <iterator>   // begin, end, advance, distance
#include <numeric>    // accumulate, partial_sum
#include <string>     // std::string
#include <utility>    // pair, make_pair, swap

// -----------------------------------------------------------------------------
// C++11 and above
// -----------------------------------------------------------------------------
#if __cplusplus >= 201103L

#include <array>            // std::array — fixed-size array
#include <initializer_list> // initializer_list support
#include <tuple>            // tuple, make_tuple, tie
#include <unordered_map>    // hash map
#include <unordered_set>    // hash set

#endif // C++11

// -----------------------------------------------------------------------------
// C++20 and above
// -----------------------------------------------------------------------------
#if __cplusplus >= 202002L

#include <bit>     // std::popcount, std::countl_zero, std::has_single_bit
#include <format>  // std::format (Python-style string formatting)
#include <numbers> // std::numbers::pi, std::numbers::e (math constants)
#include <ranges>  // std::ranges::sort, views::filter, views::transform

#endif // C++20

// -----------------------------------------------------------------------------
// C++23 and above
// -----------------------------------------------------------------------------
#if __cplusplus >= 202302L

#include <flat_map> // std::flat_map (sorted contiguous map)
#include <flat_set> // std::flat_set (sorted contiguous set)
#include <print>    // std::print, std::println (formatted console output)

#endif // C++23

// ---------------------------------------------------------------------------
// Use dbg.h in local machines
// ---------------------------------------------------------------------------
#ifdef LOCAL
#define DBG_MACRO_NO_WARNING
#include "dbg.h"
#else
#define dbg(...) (__VA_ARGS__)
#endif

// ---------------------------------------------------------------------------
// Overloading >> operator
// ---------------------------------------------------------------------------
// =============================================================================
// std::pair  (C++98)
// Input format: "first second"
// =============================================================================
template <typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
  is >> p.first >> p.second;
  return is;
}

// =============================================================================
// Sequence containers — reads into pre-sized container
// Usage: vec.resize(n); cin >> vec;
// =============================================================================

// std::vector
template <typename T, typename Alloc>
std::istream &operator>>(std::istream &is, std::vector<T, Alloc> &v) {
  for (auto &elem : v) {
    is >> elem;
  }
  return is;
}

// std::list
template <typename T, typename Alloc>
std::istream &operator>>(std::istream &is, std::list<T, Alloc> &l) {
  for (auto &elem : l) {
    is >> elem;
  }
  return is;
}

// std::deque
template <typename T, typename Alloc>
std::istream &operator>>(std::istream &is, std::deque<T, Alloc> &d) {
  for (auto &elem : d) {
    is >> elem;
  }
  return is;
}

// =============================================================================
// C++11 and above
// =============================================================================
#if __cplusplus >= 201103L

// std::array — reads exactly N elements
template <typename T, std::size_t N>
std::istream &operator>>(std::istream &is, std::array<T, N> &arr) {
  for (auto &elem : arr) {
    is >> elem;
  }
  return is;
}

// -----------------------------------------------------------------------------
// std::tuple — reads elements in order using index sequence
// Input format: "e0 e1 e2 ..."
// -----------------------------------------------------------------------------
namespace detail {

template <typename Tuple, std::size_t... Is>
void ReadTuple(std::istream &is, Tuple &t, std::index_sequence<Is...>) {
  (void)std::initializer_list<int>{(is >> std::get<Is>(t), 0)...};
}

} // namespace detail

template <typename... Args>
std::istream &operator>>(std::istream &is, std::tuple<Args...> &t) {
  detail::ReadTuple(is, t, std::index_sequence_for<Args...>{});
  return is;
}

#endif // C++11

// =============================================================================
// Associative containers — reads size prefix, then elements
// Input format: "n e0 e1 ... en-1"
// =============================================================================

// std::set
template <typename T, typename Compare, typename Alloc>
std::istream &operator>>(std::istream &is, std::set<T, Compare, Alloc> &s) {
  std::size_t n;
  is >> n;
  s.clear();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    s.insert(val);
  }
  return is;
}

// std::multiset
template <typename T, typename Compare, typename Alloc>
std::istream &operator>>(std::istream &is,
                         std::multiset<T, Compare, Alloc> &ms) {
  std::size_t n;
  is >> n;
  ms.clear();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    ms.insert(val);
  }
  return is;
}

// std::unordered_set
template <typename T, typename Hash, typename KeyEqual, typename Alloc>
std::istream &operator>>(std::istream &is,
                         std::unordered_set<T, Hash, KeyEqual, Alloc> &us) {
  std::size_t n;
  is >> n;
  us.clear();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    us.insert(val);
  }
  return is;
}

// std::map
// Input format: "n k0 v0 k1 v1 ... kn-1 vn-1"
template <typename K, typename V, typename Compare, typename Alloc>
std::istream &operator>>(std::istream &is, std::map<K, V, Compare, Alloc> &m) {
  std::size_t n;
  is >> n;
  m.clear();
  for (std::size_t i = 0; i < n; ++i) {
    K key;
    V val;
    is >> key >> val;
    m[key] = val;
  }
  return is;
}

// std::multimap
// Input format: "n k0 v0 k1 v1 ... kn-1 vn-1"
template <typename K, typename V, typename Compare, typename Alloc>
std::istream &operator>>(std::istream &is,
                         std::multimap<K, V, Compare, Alloc> &mm) {
  std::size_t n;
  is >> n;
  mm.clear();
  for (std::size_t i = 0; i < n; ++i) {
    K key;
    V val;
    is >> key >> val;
    mm.insert({key, val});
  }
  return is;
}

// std::unordered_map
// Input format: "n k0 v0 k1 v1 ... kn-1 vn-1"
template <typename K, typename V, typename Hash, typename KeyEqual,
          typename Alloc>
std::istream &operator>>(std::istream &is,
                         std::unordered_map<K, V, Hash, KeyEqual, Alloc> &um) {
  std::size_t n;
  is >> n;
  um.clear();
  for (std::size_t i = 0; i < n; ++i) {
    K key;
    V val;
    is >> key >> val;
    um[key] = val;
  }
  return is;
}

// =============================================================================
// Adapter containers — reads size prefix, then elements
// Input format: "n e0 e1 ... en-1"
// =============================================================================

// std::stack — input is bottom to top order
template <typename T, typename Container>
std::istream &operator>>(std::istream &is, std::stack<T, Container> &stk) {
  std::size_t n;
  is >> n;
  stk = std::stack<T, Container>();
  std::vector<T> tmp(n);
  for (auto &elem : tmp) {
    is >> elem;
  }
  for (auto &elem : tmp) {
    stk.push(elem);
  }
  return is;
}

// std::queue — input is front to back order
template <typename T, typename Container>
std::istream &operator>>(std::istream &is, std::queue<T, Container> &q) {
  std::size_t n;
  is >> n;
  q = std::queue<T, Container>();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    q.push(val);
  }
  return is;
}

// std::priority_queue
template <typename T, typename Container, typename Compare>
std::istream &operator>>(std::istream &is,
                         std::priority_queue<T, Container, Compare> &pq) {
  std::size_t n;
  is >> n;
  pq = std::priority_queue<T, Container, Compare>();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    pq.push(val);
  }
  return is;
}

// =============================================================================
// Helper: ReadN — reads exactly n elements into any sequence container
// without requiring a size prefix in the input stream
// Usage: ReadN(cin, vec, 5);
//        ReadN(cin, s, 4);    // works for set too
// =============================================================================
template <typename Container>
void ReadN(std::istream &is, Container &container, std::size_t n) {
  container.clear();
  for (std::size_t i = 0; i < n; ++i) {
    typename Container::value_type val;
    is >> val;
    container.insert(container.end(), val);
  }
}

// Specialization of ReadN for associative containers (set, map, etc.)
// that don't support insert(end(), val)
template <typename T, typename Compare, typename Alloc>
void ReadN(std::istream &is, std::set<T, Compare, Alloc> &s, std::size_t n) {
  s.clear();
  for (std::size_t i = 0; i < n; ++i) {
    T val;
    is >> val;
    s.insert(val);
  }
}

template <typename K, typename V, typename Compare, typename Alloc>
void ReadN(std::istream &is, std::map<K, V, Compare, Alloc> &m, std::size_t n) {
  m.clear();
  for (std::size_t i = 0; i < n; ++i) {
    K key;
    V val;
    is >> key >> val;
    m[key] = val;
  }
}

using namespace std;

// ---------------------------------------------------------------------------
// Using overloaded >>
// ---------------------------------------------------------------------------
void _cin_usage() {
  // --- vector (pre-size then read) ---
  int n;
  cin >> n;
  vector<int> v(n);
  cin >> v; // reads n ints

  // --- pair ---
  pair<int, string> p;
  cin >> p; // reads int then string

  // --- tuple ---
  tuple<int, double, string> t;
  cin >> t; // reads int, double, string

  // --- array ---
  array<int, 5> arr;
  cin >> arr; // reads exactly 5 ints

  // --- set (reads size first, then elements) ---
  set<int> s;
  cin >> s; // input: "3 10 20 30"

  // --- map (reads size first, then key-value pairs) ---
  map<string, int> m;
  cin >> m; // input: "2 alice 90 bob 85"

  // --- stack (reads size first, pushed bottom to top) ---
  stack<int> stk;
  cin >> stk; // input: "3 1 2 3"

  // --- nested: vector of pairs ---
  int k;
  cin >> k;
  vector<pair<int, int>> vp(k);
  cin >> vp; // reads k pairs

  // --- ReadN helper ---
  set<int> s2;
  ReadN(cin, s2, 4); // reads exactly 4 elements, no size prefix
}

// ---------------------------------------------------------------------------
// Alias
// ---------------------------------------------------------------------------
using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;

using vvi = vector<vi>;
using vvll = vector<vll>;

using vpii = vector<pii>;
using vpll = vector<pll>;

using vs = vector<string>;

// ---------------------------------------------------------------------------
// Defines
// ---------------------------------------------------------------------------
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define popb pop_back
#define pf push_front
#define mp make_pair
#define mt make_tuple
#define popf pop_front
#define fi first
#define se second
#define endl "\n"
#define lcm(a, b) ((a) * (b)) / gcd((a), (b))
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define REP(i, k, n) for (ll i = (k); (i) < (n); (i)++)
#define repr(i, k, n) for (ll i = (k); (i) >= (n); (i)--)
#define fill(val, a)                                                           \
  for (ll i = 0; (i) < (a.size()); (i)++) {                                   \
    a[(i)] = (val);                                                            \
  }
#define sortinc(x) sort(all(x))
#define sortdec(x) sort(rall(x))
#define p0(a) cout << (a) << " "
#define p1(a) cout << (a) << endl
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// ---------------------------------------------------------------------------
// Numeric Limits
// ---------------------------------------------------------------------------
constexpr int INF = 0x3f3f3f3f;           // ~1e9, safe for addition
constexpr ll LINF = 0x3f3f3f3f3f3f3f3fLL; // ~4.6e18, safe for addition
constexpr int NINF = -INF;
constexpr ll NLINF = -LINF;
constexpr double EPS = 1e-9; // epsilon for float compare
constexpr ld LPS = 1e-12;    // tighter epsilon for ld

// ---------------------------------------------------------------------------
// Modular
// ---------------------------------------------------------------------------
constexpr int MOD = 1e9 + 7;    // most common
constexpr int MOD2 = 998244353; // NTT-friendly prime
constexpr int MOD3 = 1e9 + 9;   // stress test anti-hack

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------
constexpr ld PI = 3.14159265359;

// ---------------------------------------------------------------------------
// Common Sizes
// ---------------------------------------------------------------------------
constexpr int MAXN = 2e5 + 5; // standard array size
constexpr int MAXM = 1e6 + 5; // for edges / strings
constexpr int MAXLOG = 20;    // log2(1e6) ~ 20, for LCA/sparse table
constexpr int MAXSQ = 320;    // sqrt(1e5) ~ 316, for sqrt decomp
constexpr int MAXK = 26;      // alphabet size

// ---------------------------------------------------------------------------
// Directions (Grid Problems)
// ---------------------------------------------------------------------------
// 4-directional (up, down, left, right)
constexpr int DX4[] = {-1, 1, 0, 0};
constexpr int DY4[] = {0, 0, -1, 1};

// 8-directional (includes diagonals)
constexpr int DX8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int DY8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Named 4-dir indices (use with DX4/DY4)
constexpr int UP = 0;
constexpr int DOWN = 1;
constexpr int LEFT = 2;
constexpr int RIGHT = 3;

// ---------------------------------------------------------------------------
// Bit Manipulation
// ---------------------------------------------------------------------------
// Use as functions, not constants
// Check if k-th bit is set
auto bit = [](ll n, int k) { return (n >> k) & 1; };
// Set k-th bit
auto bset = [](ll n, int k) { return n | (1LL << k); };
// Clear k-th bit
auto bclr = [](ll n, int k) { return n & ~(1LL << k); };
// Toggle k-th bit
auto btog = [](ll n, int k) { return n ^ (1LL << k); };
// Count set bits
auto bcnt = [](ll n) { return __builtin_popcountll(n); };
// Lowest set bit
auto blsb = [](ll n) { return n & (-n); };
// log2 floor (position of highest set bit)
auto blog = [](ll n) { return 63 - __builtin_clzll(n); };

// ---------------------------------------------------------------------------
// Modular Arithmetic
// ---------------------------------------------------------------------------
// (n+m)%MOD
inline ll madd(ll n, ll m, ll p = MOD) { return ((n + m) % p + p) % p; }
// (n-m)%MOD
inline ll msub(ll n, ll m, ll p = MOD) { return ((n - m + p) % p + p) % p; }
// (n*m)%MOD
inline ll mmul(ll n, ll m, ll p = MOD) {
  return (((n % p) * (m % p)) % p + p) % p;
}
// x^y
ull exp(ll x, ll y) {
  ull res = 1;
  while (y > 0) {
    if (y & 1)
      res = res * x;
    y = y >> 1;
    x = x * x;
  }
  return res;
}
// (x^y)%MOD
ll mexp(ll x, ll y, ll p = MOD) {
  ll res = 1;
  while (y > 0) {
    if (y & 1)
      res = mmul(res, x, p);
    y = y >> 1;
    x = mmul(x, x, p);
  }
  return res;
}
// (n^(-1))%MOD (Fermats Little Theorem)
inline ll minv(ll n, ll p = MOD) {
  if (n == 1)
    return 1;
  return mexp(n, p - 2, p);
}
// (n/m)%MOD
inline ll mdiv(ll n, ll m, ll p = MOD) { return mmul(n, minv(m, p), p); }
// nCr%MOD
inline ll mncr(ll fac[], int n, int r, ll p = MOD) {
  if (r == 0)
    return 1;
  return mmul(fac[n], minv(mmul(fac[r], fac[n - r], p), p), p);
}
ll fac_[MAXN];
void fac_init(int n) {
  fac_[0] = 1;
  REP(i, 1, n + 1) fac_[i] = mmul(fac_[i - 1], i);
}

// ---------------------------------------------------------------------------
// START
// ---------------------------------------------------------------------------

void solve() {
  // Start here
  ll s, e, i, j;
  cin >> i >> j;
  s = max(i, j) * max(i, j);
  e = (max(i, j) - 1) * (max(i, j) - 1) + 1;
  dbg(s, e);
  if (i < j) {
    if (max(i, j) % 2 == 1)
      p1(s - min(j, i) + 1);
    else
      p1(e + min(i, j) - 1);
  } else {
    if (max(i, j) % 2 == 0)
      p1(s - min(j, i) + 1);
    else
      p1(e + min(i, j) - 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
