#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Debug (local only)
// ---------------------------------------------------------------------------
#ifdef LOCAL
#define DBG_MACRO_NO_WARNING
#include "dbg.h"
#else
#define dbg(...) (__VA_ARGS__)
#endif

using namespace std;

// ---------------------------------------------------------------------------
// Aliases
// ---------------------------------------------------------------------------
using ll = long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using vs = vector<string>;

// ---------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define endl "\n"
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define REP(i, k, n) for (ll i = (k); (i) < (n); (i)++)
#define repr(i, k, n) for (ll i = (k); (i) >= (n); (i)--)
#define sortinc(x) sort(all(x))
#define sortdec(x) sort(rall(x))
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define p0(a) cout << (a) << " "
#define p1(a) cout << (a) << endl

// ---------------------------------------------------------------------------
// Numeric Limits
// ---------------------------------------------------------------------------
constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = 0x3f3f3f3f3f3f3f3fLL;
constexpr double EPS = 1e-9;

constexpr ll MOD = 1e9 + 7;
constexpr ll MOD2 = 998244353;

// ---------------------------------------------------------------------------
// START
// ---------------------------------------------------------------------------
void solve() {
  // Start here
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
