#ifdef LOCAL
#define DBG_MACRO_NO_WARNING
#include "dbg.h"
#else
#define dbg(...) (__VA_ARGS__)
#endif

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vld = vector<ld>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

struct Point {
  int x, y;
  friend ostream &operator<<(ostream &os, const Point &p) {
    return os << "Point(" << p.x << ", " << p.y << ")";
  }
};

void _test_dbg() {
#ifdef LOCAL
  // ── 1. Primitives ────────────────────────────────────────────────────────
  int a = 42;
  ll b = 1e18;
  ull ub = 1e19;
  double c = 3.14159;
  ld d = 3.14159265358979L;
  char e = 'X';
  bool f = true;
  string g = "hello cp";
  dbg(a, b, ub, c, d, e, f, g);

  // ── 2. Inline / Expression (killer feature) ──────────────────────────────
  int x = dbg(42 * 2 + 1); // returns value, assigns to x
  if (dbg(x > 10)) {
  } // usable in conditions
  int arr[] = {5, 4, 3, 2, 1};
  sort(arr, arr + 5);
  dbg(arr[dbg(2)]); // nested dbg

  // ── 3. STL Sequences ─────────────────────────────────────────────────────
  vi v = {1, 2, 3, 4, 5};
  vvi vv = {{1, 2}, {3, 4}, {5, 6}};
  vld vld = {1e9, 2e9, 3e9};
  deque<int> dq = {10, 20, 30};
  array<int, 5> ar = {5, 4, 3, 2, 1};
  list<int> ls = {1, 2, 3, 4};
  dbg(v, vv, vld, dq, ar, ls);

  // ── 4. STL Associative ───────────────────────────────────────────────────
  set<int> s = {3, 1, 4, 1, 5, 9}; // duplicates dropped
  multiset<int> ms = {1, 1, 2, 3, 3};
  map<string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};
  multimap<int, int> mm = {{1, 10}, {1, 20}, {2, 30}};
  unordered_map<string, int> um = {{"x", 7}, {"y", 8}};
  unordered_set<int> us = {100, 200, 300};
  dbg(s, ms, m, mm, um, us);

  // ── 5. Pairs & Tuples ────────────────────────────────────────────────────
  pii p1 = {3, 7};
  pll p2 = {1e9, 2e9};
  pair<string, vi> p3 = {"vec", {1, 2, 3}};
  tuple<int, string, double> t1 = {1, "hello", 3.14};
  tuple<vi, pii, bool> t2 = {{1, 2, 3}, {4, 5}, true};
  dbg(p1, p2, p3, t1, t2);

  // ── 6. Nested Containers ─────────────────────────────────────────────────
  vector<pii> vp = {{1, 2}, {3, 4}, {5, 6}};
  vector<set<int>> vs = {{1, 2, 3}, {4, 5, 6}};
  map<int, vi> mv = {{1, {1, 2, 3}}, {2, {4, 5, 6}}};
  map<int, map<int, int>> mm2 = {{1, {{2, 3}}}, {4, {{5, 6}}}};
  dbg(vp, vs, mv, mm2);

  // ── 7. Stack & Queue (not directly printable — convert first) ────────────
  // dbg-macro doesn't support stack/queue directly; dump to vector
  stack<int> stk;
  for (int i : {1, 2, 3, 4, 5})
    stk.push(i);
  queue<int> que;
  for (int i : {10, 20, 30})
    que.push(i);
  priority_queue<int> pq;
  for (int i : {3, 1, 4, 1, 5})
    pq.push(i);

  // Dump helpers
  auto dump_stack = [](stack<int> s) {
    vi tmp;
    while (!s.empty()) {
      tmp.pb(s.top());
      s.pop();
    }
    return tmp;
  };
  auto dump_queue = [](queue<int> q) {
    vi tmp;
    while (!q.empty()) {
      tmp.pb(q.front());
      q.pop();
    }
    return tmp;
  };
  auto dump_pq = [](priority_queue<int> q) {
    vi tmp;
    while (!q.empty()) {
      tmp.pb(q.top());
      q.pop();
    }
    return tmp;
  };
  dbg(dump_stack(stk), dump_queue(que), dump_pq(pq));

  // ── 8. 2D Grid (very common in CP) ───────────────────────────────────────
  vvi grid = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  dbg(grid);

  vector<string> char_grid = {"S.#", "..#", "#.E"};
  dbg(char_grid);

  // ── 9. Optional & Variant (C++17) ────────────────────────────────────────
  optional<int> opt1 = 42;
  optional<int> opt2 = nullopt;
  variant<int, string, vi> var1 = 99;
  variant<int, string, vi> var2 = string("hello");
  variant<int, string, vi> var3 = vi{1, 2, 3};
  dbg(opt1, opt2, var1, var2, var3);

  // ── 10. Pointer & nullptr ────────────────────────────────────────────────
  int *ptr1 = &a;
  int *ptr2 = nullptr;
  dbg(ptr1, *ptr1, ptr2);

  // ── 11. Enum & Enum Class ────────────────────────────────────────────────
  enum Direction { NORTH, SOUTH, EAST, WEST };
  enum class Color { RED, GREEN, BLUE };
  Direction dir = EAST;
  Color col = Color::GREEN;
  dbg(dir, col); // prints underlying int value

  // ── 12. Structs (with operator<<) ────────────────────────────────────────
  Point pt = {3, 7};
  vector<Point> pts = {{1, 2}, {3, 4}, {5, 6}};
  dbg(pt, pts);

  // ── 13. Lambda / Function result ─────────────────────────────────────────
  auto gcd = [](int a, int b) { return __gcd(a, b); };
  dbg(gcd(48, 18));           // prints expression + result
  dbg(gcd(dbg(48), dbg(18))); // nested — prints intermediate values

  // ── 14. Chained / Multi-arg ──────────────────────────────────────────────
  // up to any number of args in one call
  dbg(a, b, c, v, p1, m, grid);

  // ── 15. Bitset ───────────────────────────────────────────────────────────
  bitset<8> bs("10110101");
  dbg(bs);
  dbg(bs.count(), bs.any(), bs.none());

#endif
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  _test_dbg();

  return 0;
}
