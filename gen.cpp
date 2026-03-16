// =============================================================================
// gen.cc  —  Stress-test generator for competitive programming
//
// BUILD:
//   g++ -std=c++17 -O2 -o gen gen.cc
//
// RUN (single test, seed = 42):
//   ./gen 42
//
// STRESS LOOP (bash):
//   for i in $(seq 1 1000); do
//       ./gen $i > input.txt
//       ./solution  < input.txt > out_fast.txt
//       ./brute     < input.txt > out_brute.txt
//       if ! diff -q out_fast.txt out_brute.txt >/dev/null 2>&1; then
//           echo "MISMATCH on seed $i"; cat input.txt; break
//       fi
//   done
//
// CUSTOMISE:
//   • Edit the "CONFIG" block to change constraints.
//   • Edit generateTestCase() to describe the structure you want.
//   • Switch the PROBLEM_TYPE define to select a built-in template.
// =============================================================================

#include "gen.h"

#include <iostream>

using namespace std;

// ============================================================================
// ██████╗ ██████╗  ██████╗ ██████╗ ██╗     ███████╗███╗   ███╗
// ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║     ██╔════╝████╗ ████║
// ██████╔╝██████╔╝██║   ██║██████╔╝██║     █████╗  ██╔████╔██║
// ██╔═══╝ ██╔══██╗██║   ██║██╔══██╗██║     ██╔══╝  ██║╚██╔╝██║
// ██║     ██║  ██║╚██████╔╝██████╔╝███████╗███████╗██║ ╚═╝ ██║
// ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝
//   T Y P E  —  pick ONE, comment out the rest
// ============================================================================
// #define PROBLEM_TYPE_ARRAY
// #define PROBLEM_TYPE_GRAPH
#define PROBLEM_TYPE_TREE
// #define PROBLEM_TYPE_STRING
// #define PROBLEM_TYPE_GRID
// #define PROBLEM_TYPE_CUSTOM   // ← define your own in generateTestCase()

// ============================================================================
//  CONFIG  —  tweak constraints here
// ============================================================================

// --- Array / sequence -------------------------------------------------------
constexpr int kArrayMinN = 1;
constexpr int kArrayMaxN = 10; // array length
constexpr long long kArrayMinVal = -100;
constexpr long long kArrayMaxVal = 100;

// --- Graph ------------------------------------------------------------------
constexpr int kGraphMinNodes = 2;
constexpr int kGraphMaxNodes = 8;
constexpr int kGraphMinEdges = 1;
constexpr int kGraphMaxEdges = 12; // capped to n*(n-1)/2 automatically
constexpr long long kGraphMinWeight = 1;
constexpr long long kGraphMaxWeight = 100;

// --- String -----------------------------------------------------------------
constexpr int kStringMinLen = 1;
constexpr int kStringMaxLen = 20;
constexpr char kStringCharLo = 'a';
constexpr char kStringCharHi = 'z';

// --- Grid -------------------------------------------------------------------
constexpr int kGridMinRows = 1;
constexpr int kGridMaxRows = 5;
constexpr int kGridMinCols = 1;
constexpr int kGridMaxCols = 5;
// Cell characters: '.' = empty, '#' = wall
constexpr double kGridWallProb = 0.25; // probability each cell is '#'

// --- Number of test cases per file ------------------------------------------
// Set kMultiTest = false for single-test problems.
constexpr bool kMultiTest = false;
constexpr int kMinTestCases = 1;
constexpr int kMaxTestCases = 5;

// ============================================================================
//  GENERATOR IMPLEMENTATIONS  (one per PROBLEM_TYPE)
// ============================================================================

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_ARRAY
// Generates: n  followed by n space-separated integers.
// Tweak kArrayVariant to change the distribution.
//   0 = fully random
//   1 = sorted
//   2 = reverse-sorted
//   3 = almost-sorted  (good for catching insertion-sort-like bugs)
constexpr int kArrayVariant = 0;

static void generateTestCase() {
  int n = static_cast<int>(Gen::randInt(kArrayMinN, kArrayMaxN));

  vector<long long> arr;
  switch (kArrayVariant) {
  case 1:
    arr = Gen::sortedArray(n, kArrayMinVal, kArrayMaxVal);
    break;
  case 2:
    arr = Gen::reverseSortedArray(n, kArrayMinVal, kArrayMaxVal);
    break;
  case 3:
    arr = Gen::almostSortedArray(n, kArrayMinVal, kArrayMaxVal, /*swaps=*/2);
    break;
  default:
    arr = Gen::randArray(n, kArrayMinVal, kArrayMaxVal);
  }

  cout << n << "\n";
  for (int i = 0; i < n; ++i) {
    cout << arr[i] << " \n"[i + 1 == n];
  }
}
#endif // PROBLEM_TYPE_ARRAY

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_GRAPH
// Generates: n m  followed by m lines of edges.
// Set kWeighted = true to add a weight column.
constexpr bool kWeighted = false;

static void generateTestCase() {
  int n = static_cast<int>(Gen::randInt(kGraphMinNodes, kGraphMaxNodes));
  int max_possible_edges = n * (n - 1) / 2;
  int max_edges = min(kGraphMaxEdges, max_possible_edges);
  int m = static_cast<int>(
    Gen::randInt(kGraphMinEdges, max(kGraphMinEdges, max_edges)));

  cout << n << " " << m << "\n";

  if (kWeighted) {
    auto edges = Gen::randWeightedGraph(n, m, kGraphMinWeight, kGraphMaxWeight);
    for (auto &e : edges) {
      // Convert to 1-indexed output
      cout << e.u + 1 << " " << e.v + 1 << " " << e.w << "\n";
    }
  } else {
    auto edges = Gen::randGraph(n, m);
    for (auto &[u, v] : edges) {
      cout << u + 1 << " " << v + 1 << "\n";
    }
  }
}
#endif // PROBLEM_TYPE_GRAPH

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_TREE
// Generates: n  followed by (n-1) edge lines.
// Set kWeighted = true to add a weight column.
constexpr bool kWeighted = false;

static void generateTestCase() {
  int n = static_cast<int>(Gen::randInt(2, kGraphMaxNodes));
  cout << n << "\n";

  if (kWeighted) {
    auto edges = Gen::randWeightedTree(n, kGraphMinWeight, kGraphMaxWeight);
    for (auto &e : edges) {
      cout << e.u + 1 << " " << e.v + 1 << " " << e.w << "\n";
    }
  } else {
    auto edges = Gen::randTree(n);
    for (auto &[u, v] : edges) {
      cout << u + 1 << " " << v + 1 << "\n";
    }
  }
}
#endif // PROBLEM_TYPE_TREE

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_STRING
// Generates: a single random string on its own line.
static void generateTestCase() {
  cout << Gen::randString(kStringMinLen, kStringMaxLen, kStringCharLo,
                          kStringCharHi)
       << "\n";
}
#endif // PROBLEM_TYPE_STRING

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_GRID
// Generates: r c  followed by r lines of c characters ('.' or '#').
static void generateTestCase() {
  int r = static_cast<int>(Gen::randInt(kGridMinRows, kGridMaxRows));
  int c = static_cast<int>(Gen::randInt(kGridMinCols, kGridMaxCols));
  cout << r << " " << c << "\n";
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      // Bernoulli trial for wall
      double p = static_cast<double>(Gen::rng()) /
                 static_cast<double>(numeric_limits<uint64_t>::max());
      cout << (p < kGridWallProb ? '#' : '.');
    }
    cout << "\n";
  }
}
#endif // PROBLEM_TYPE_GRID

//-----------------------------------------------------------------------------
#ifdef PROBLEM_TYPE_CUSTOM
// ↓↓↓  Write your own generator here  ↓↓↓
static void generateTestCase() {
  // Example: two integers followed by a list
  int n = static_cast<int>(Gen::randInt(1, 10));
  int q = static_cast<int>(Gen::randInt(1, 5)); // number of queries
  cout << n << " " << q << "\n";

  auto arr = Gen::randArray(n, 1, 100);
  for (int i = 0; i < n; ++i)
    cout << arr[i] << " \n"[i + 1 == n];

  for (int i = 0; i < q; ++i) {
    int l = static_cast<int>(Gen::randInt(1, n));
    int r = static_cast<int>(Gen::randInt(l, n));
    cout << l << " " << r << "\n";
  }
}
#endif // PROBLEM_TYPE_CUSTOM

// ============================================================================
//  MAIN
// ============================================================================

int main(int argc, char *argv[]) {
  Gen::init(argc, argv);

  if (kMultiTest) {
    int t = static_cast<int>(Gen::randInt(kMinTestCases, kMaxTestCases));
    cout << t << "\n";
    for (int i = 0; i < t; ++i)
      generateTestCase();
  } else {
    generateTestCase();
  }

  return 0;
}

// ============================================================================
//  Gen namespace — implementation
// ============================================================================

namespace Gen {

// ---------------------------------------------------------------------------
std::mt19937_64 rng;

// ---------------------------------------------------------------------------
void init(int argc, char *argv[]) {
  uint64_t seed;
  if (argc > 1) {
    seed = static_cast<uint64_t>(stoull(argv[1]));
  } else {
    seed = static_cast<uint64_t>(
      chrono::steady_clock::now().time_since_epoch().count());
  }
  rng.seed(seed);
  // Print seed to stderr so failing cases are reproducible
  cerr << "[gen] seed = " << seed << "\n";
}

//-----------------------------------------------------------------------------
long long randInt(long long lo, long long hi) {
  assert(lo <= hi);
  return uniform_int_distribution<long long>{lo, hi}(rng);
}

//-----------------------------------------------------------------------------
long long randIndex(long long n) {
  assert(n > 0);
  return randInt(0, n - 1);
}

//-----------------------------------------------------------------------------
double randDouble(double lo, double hi) {
  assert(lo < hi);
  return uniform_real_distribution<double>{lo, hi}(rng);
}

//-----------------------------------------------------------------------------
string randString(int len, char lo, char hi) {
  assert(len >= 0 && lo <= hi);
  string s(len, ' ');
  for (char &c : s)
    c = static_cast<char>(randInt(lo, hi));
  return s;
}

//-----------------------------------------------------------------------------
string randString(int min_len, int max_len, char lo, char hi) {
  return randString(static_cast<int>(randInt(min_len, max_len)), lo, hi);
}

//-----------------------------------------------------------------------------
vector<int> randPermutation(int n) {
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  shuffle(p);
  return p;
}

//-----------------------------------------------------------------------------
vector<long long> randDistinct(int count, long long lo, long long hi) {
  assert(hi - lo + 1 >= count);
  set<long long> s;
  while (static_cast<int>(s.size()) < count)
    s.insert(randInt(lo, hi));
  return vector<long long>(s.begin(), s.end());
}

//-----------------------------------------------------------------------------
vector<long long> randArray(int n, long long lo, long long hi) {
  vector<long long> v(n);
  for (auto &x : v)
    x = randInt(lo, hi);
  return v;
}

//-----------------------------------------------------------------------------
vector<pair<int, int>> randGraph(int nodes, int edges) {
  int max_e = nodes * (nodes - 1) / 2;
  edges = min(edges, max_e);

  // Collect all possible undirected edges, then sample.
  vector<pair<int, int>> all;
  all.reserve(max_e);
  for (int u = 0; u < nodes; ++u)
    for (int v = u + 1; v < nodes; ++v)
      all.emplace_back(u, v);

  shuffle(all);
  all.resize(edges);
  return all;
}

//-----------------------------------------------------------------------------
// Prüfer sequence → tree
vector<pair<int, int>> randTree(int nodes) {
  if (nodes == 1)
    return {};
  if (nodes == 2)
    return {{0, 1}};

  // Build a random Prüfer sequence of length (nodes - 2)
  vector<int> prufer(nodes - 2);
  for (auto &x : prufer)
    x = static_cast<int>(randInt(0, nodes - 1));

  // Decode
  vector<int> degree(nodes, 1);
  for (int x : prufer)
    ++degree[x];

  vector<pair<int, int>> edges;
  edges.reserve(nodes - 1);
  for (int x : prufer) {
    for (int leaf = 0; leaf < nodes; ++leaf) {
      if (degree[leaf] == 1) {
        edges.emplace_back(leaf, x);
        --degree[leaf];
        --degree[x];
        break;
      }
    }
  }
  // Last edge
  vector<int> last;
  for (int i = 0; i < nodes; ++i)
    if (degree[i] == 1)
      last.push_back(i);
  edges.emplace_back(last[0], last[1]);
  return edges;
}

//-----------------------------------------------------------------------------
vector<WeightedEdge> randWeightedGraph(int nodes, int edges, long long w_lo,
                                       long long w_hi) {
  auto raw = randGraph(nodes, edges);
  vector<WeightedEdge> result;
  result.reserve(raw.size());
  for (auto &[u, v] : raw)
    result.push_back({u, v, randInt(w_lo, w_hi)});
  return result;
}

//-----------------------------------------------------------------------------
vector<WeightedEdge> randWeightedTree(int nodes, long long w_lo,
                                      long long w_hi) {
  auto raw = randTree(nodes);
  vector<WeightedEdge> result;
  result.reserve(raw.size());
  for (auto &[u, v] : raw)
    result.push_back({u, v, randInt(w_lo, w_hi)});
  return result;
}

//-----------------------------------------------------------------------------
vector<long long> almostSortedArray(int n, long long lo, long long hi,
                                    int swaps) {
  auto v = sortedArray(n, lo, hi);
  for (int i = 0; i < swaps && n > 1; ++i) {
    int a = static_cast<int>(randIndex(n));
    int b = static_cast<int>(randIndex(n));
    swap(v[a], v[b]);
  }
  return v;
}

//-----------------------------------------------------------------------------
vector<long long> sortedArray(int n, long long lo, long long hi) {
  auto v = randArray(n, lo, hi);
  sort(v.begin(), v.end());
  return v;
}

//-----------------------------------------------------------------------------
vector<long long> reverseSortedArray(int n, long long lo, long long hi) {
  auto v = sortedArray(n, lo, hi);
  reverse(v.begin(), v.end());
  return v;
}

} // namespace Gen
