#ifndef GEN_H_
#define GEN_H_

#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <functional>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

// =============================================================================
// gen.h  —  Stress-test generator utilities for competitive programming
//
// USAGE:
//   1. #include "gen.h" in your gen.cc
//   2. Call Gen::init(argc, argv) at the top of main().
//      Pass a seed on the command line, e.g. ./gen 42
//      Omit the seed to use a random time-based seed.
//   3. Use Gen::rng() for raw engine access, or the helpers below.
// =============================================================================

namespace Gen {

// ---------------------------------------------------------------------------
// RNG engine (Mersenne Twister, seeded from CLI arg or system clock)
// ---------------------------------------------------------------------------
extern std::mt19937_64 rng;

// Seed and initialise the RNG. Call once at the start of main().
void init(int argc, char *argv[]);

// ---------------------------------------------------------------------------
// Integer helpers
// ---------------------------------------------------------------------------

// Uniform integer in [lo, hi] (inclusive).
long long randInt(long long lo, long long hi);

// Uniform integer in [0, n-1].
long long randIndex(long long n);

// ---------------------------------------------------------------------------
// Floating-point helpers
// ---------------------------------------------------------------------------

// Uniform double in [lo, hi).
double randDouble(double lo, double hi);

// ---------------------------------------------------------------------------
// String helpers
// ---------------------------------------------------------------------------

// Random lowercase-alpha string of exactly `len` characters.
std::string randString(int len, char lo = 'a', char hi = 'z');

// Random string whose length is uniform in [minLen, maxLen].
std::string randString(int min_len, int max_len, char lo = 'a', char hi = 'z');

// ---------------------------------------------------------------------------
// Container helpers
// ---------------------------------------------------------------------------

// Shuffle a vector in-place.
template <typename T> void shuffle(std::vector<T> &v) {
  std::shuffle(v.begin(), v.end(), rng);
}

// Random element from a non-empty vector.
template <typename T> T &choice(std::vector<T> &v) {
  assert(!v.empty());
  return v[randIndex(static_cast<long long>(v.size()))];
}

// Random permutation of [0, n-1]  (0-indexed).
std::vector<int> randPermutation(int n);

// Sorted vector of `count` distinct integers drawn from [lo, hi].
std::vector<long long> randDistinct(int count, long long lo, long long hi);

// Vector of `n` integers, each uniform in [lo, hi].
std::vector<long long> randArray(int n, long long lo, long long hi);

// ---------------------------------------------------------------------------
// Graph helpers
// ---------------------------------------------------------------------------
// Edges are returned as pairs (u, v) with u < v (0-indexed).

// Simple random undirected graph with exactly `edges` edges.
std::vector<std::pair<int, int>> randGraph(int nodes, int edges);

// Random tree on `nodes` nodes (Prüfer-sequence based, 0-indexed).
std::vector<std::pair<int, int>> randTree(int nodes);

// ---------------------------------------------------------------------------
// Weighted graph helpers
// ---------------------------------------------------------------------------
// Returns adjacency as {u, v, weight}.
struct WeightedEdge {
  int u, v;
  long long w;
};

// Random weighted undirected graph.
std::vector<WeightedEdge> randWeightedGraph(int nodes, int edges,
                                            long long w_lo, long long w_hi);

// Random weighted tree.
std::vector<WeightedEdge> randWeightedTree(int nodes, long long w_lo,
                                           long long w_hi);

// ---------------------------------------------------------------------------
// Sequence / array helpers
// ---------------------------------------------------------------------------

// Array that is almost-sorted: fully sorted, then `swaps` random swaps.
std::vector<long long> almostSortedArray(int n, long long lo, long long hi,
                                         int swaps = 3);

// Non-decreasing array of length n with values in [lo, hi].
std::vector<long long> sortedArray(int n, long long lo, long long hi);

// Reverse-sorted array.
std::vector<long long> reverseSortedArray(int n, long long lo, long long hi);

} // namespace Gen

#endif // GEN_H_
