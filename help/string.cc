//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimization ("unroll-loops")
#include "bits/stdc++.h"

using namespace std;

// TYPEDEFS
typedef long long int ll;
typedef unsigned long long int uli;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pllll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<int, int>> vpi;
typedef vector<pair<ll, ll>> vpll;
typedef set<int> si;
typedef set<ll> sll;
// DEFINES
#define endl "\n"
#define PI 3.1415926535897932384
#define fastIO std::ios::sync_with_stdio(false); cin.tie(NULL)
#define mod 1000000007
#define mod1 1000000009
#define mod2 998244353
#define gcd __gcd
#define lcm(a, b) ((a) * (b)) / gcd((a), (b))
#define rep(i, n) for (ll(i) = 0; (i) < (n); (i)++)
#define REP(i, k, n) for (ll(i) = (k); (i) < (n); (i)++)
#define repr(i, k, n) for (ll(i) = (k); (i) >= (n); (i)--)
#define collect(a) for (ll(i) = 0; (i) < (a.size()); (i)++) { cin >> a[(i)]; }
#define pb push_back
#define popb pop_back
#define pf push_front
#define popf pop_front()
#define sz(a) (ll) a.size()
#define be begin()
#define en end()
#define all(x) x.be, x.en
#define rall(x) x.rbegin(), x.rend()
#define sortinc(x) sort(all(x))
#define sortdec(x) sort(rall(x))
#define tr(it, a) for (auto(it) = a.begin(); (it) != a.end(); (it)++)
#define p0(a) cout << (a) << " "
#define p1(a) cout << (a) << endl
#define p2(a, b) cout << (a) << " " << (b) << endl
#define p3(a, b, c) cout << (a) << " " << (b) << " " << (c) << endl
#define p4(a, b, c, d) cout << (a) << " " << (b) << " " << (c) << " " << (d) << endl
#define cend cout << endl
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define r0 return 0
#define F first
#define S second
#define debug(x) cout << #x << " "; _print(x); cout << endl;

void _print(ll t) { cout << t; }
void _print(int t) { cout << t; }
void _print(string t) { cout << t; }
void _print(char t) { cout << t; }
void _print(ld t) { cout << t; }
void _print(double t) { cout << t; }
void _print(uli t) { cout << t; }
template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);
template <class T, class V> void _print(pair<T, V> p) { cout << "{"; _print(p.F); cout << ","; _print(p.S); cout << "}"; }
template <class T> void _print(vector<T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T> void _print(set<T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T> void _print(multiset<T> v) { cout << "[ "; for (T i : v) { _print(i); cout << " "; } cout << "]"; }
template <class T, class V> void _print(map<T, V> v) { cout << "[ "; for (auto i : v) { _print(i); cout << " "; } cout << "]"; }
template <typename... T> void see(T&... args) { ((cin >> args), ...); }
template <typename... T> void put(T&&... args) { ((cout << args << " "), ...); }
template <typename... T> void putl(T&&... args) { ((cout << args << " "), ...); cout << '\n'; }
template <typename T> void print(vector<T> v) { for (auto i : v) { cout << i << " "; } cout << endl; }
// TODO:
// Sliding window technique (Brute force approach) - O(|text|*|pattern|)
// returns the index of the substring pattern in string text if not found return -1
int slide(string text, string pattern) {
    int n = sz(text), m = sz(pattern);
    for (int i = 0; i <= n - m; i++) {
        bool isFound = 1;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                isFound = 0;
                break;
            }
        }
        if (isFound) {
            return i;
        }
    }
    return -1;
    // To find all occurence don't return in between rather store
}

// TODO:
// String Hashing - Not talking of hash precomputation, takes O(1) to compare the
// hashes 
// Since the hashes are just integers mapping of characters ::: 
// if set is [a,z] then take p=31 since size([a,z])=26 
// if we map a to 1(NOT 0, if mapped to 0 then there will many collisions), 
// b=2, ....z=26 
// if set is [a,z] U [A,Z] then take p=53 since size([a,z] U [A,Z])=52 
// if we map a to 1(NOT 0, if mapped to 0 then there will many collisions),
// b=2, ....z=26 if we map A to 27, b=28,....z=52 
// HASH FUNC = s[0]+s[1]*p+s[2]*p^2+....+s[n]*p^(n-1) % m 
// p is prime and something that is greater than the character set m is 
// some large prime number (take m=1e9+7)

// Takes a string and find the Hash value
ll getHash(string key) {
    ll value = 0;
    ll p = 31;
    ll p_power = 1;
    for (char ch : key) {
        value = (value + (ch - 'a' + 1) * p_power) % mod;
        p_power = (p_power * p) % mod;
    }
    return value;
}

// Finding the hash of a substring efficiently
// Since hash of s[0...n] is s[0]+s[1]*p+s[2]*p^2+....+s[n]*p^(n-1) % m
// For getting has of s[l...r] we want (hash(r)-has(l-1))/p^l
// since we use modular arithmetic here we require the modular inverse of p^l

// For Precomputations
ll dp[1000001];  // For storing the hashes of prefixes s[0..k] for all k in [0,n]
ll inv[1000001]; // Storing the modular inverse beforehand

// Modular Binary Exponentiation
ll power(ll a, ll n) {
    ll result = 1;
    while (n) {
        if (n & 1) result = (result * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
    }
    return result;
}

// Precomputes the hashes of the prefixes
void init(string input_string) {
    ll p = 31;
    ll p_power = 1;
    inv[0] = 1;
    dp[0] = (input_string[0] - 'a' + 1);
    for (int i = 1; i < input_string.size(); i++) {
        char ch = input_string[i];
        p_power = (p_power * p) % mod;
        inv[i] = power(p_power, mod - 2);
        dp[i] = (dp[i - 1] + (ch - 'a' + 1) * p_power) % mod;
    }
}

// Gives the substring hashes
ll substringHash(int L, int R) {
    int result = dp[R];
    if (L > 0) result -= dp[L - 1];
    result = (result * inv[L]) % mod;
    return result;
}


//TODO:
// Rabin-Karp Algorithm
// In substring hashing we need to know the inverse of p^l's but in this we do not need that 
// we rather use the fact that (hash(r)-has(l-1))/p^l = hash([l...r])
// is same as that of (hash(r)-has(l-1)) = p^l*hash[l...r]
// We can precompute p^l's to make algo a littile a faster
// Returns all the positions where t is occured in s
vector<int> rabin_karp(string t, string s) {
    // s == text and t == pattern
    const int p = 31; 
    const int m = 1e9 + 7;
    int S = sz(s), T = sz(t);

    vector<ll> p_pow(max(S, T));     // precomputing the p^l's
    p_pow[0] = 1; 
    for (int i = 1; i < sz(p_pow); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<ll> h(T + 1, 0);          // precomputing hashes of the prefixes of text string
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    ll h_s = 0;                      // hash of pattern string
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;                 // Storing all occurences of the pattern in text
    for (int i = 0; i + S - 1 < T; i++) { 
        ll cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}

// TODO:
// Z-function algo - O(|text|+|pattern|)
// returns the index of the substring pattern in string text if not found return -1
int zalgo(string text, string pattern) {
    if (text.empty() || pattern.empty()) return -1;
    string zString = pattern + '$' + text;
    // Calculating z-array
    vector<int> z(sz(zString));
    for (int i = 1, l = 0, r = 0; i < sz(zString); i++) {
        if (i <= r) {  // Optimization Part (Important)
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (z[i] + i < sz(zString) && zString[z[i]] == zString[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {  // Optimization Part (Important)
            l = i, r = i + z[i] - 1;
        }
    }
    // Looping through z-array to find mathches
    for (int i = 0; i < sz(text); i++) {
        if (z[i + sz(pattern) + 1] == sz(pattern)) {
            return i;
        }
    }
    return -1;
    // To find all occurence don't return in between rather store
}


//TODO:
// Knuth-Morris-Pratt algo- O(n)
// This algo requires to build a prefix array
// Prefix array = Pi-array = LPS(Longest prefix suffix) ==>
// This is the longest 'proper' prefix that is same as the proper suffix in the 
// substring s[0..i]
// If naively Done it requires O(n^3) 
// Note Pi(i+1) <= Pi(i)+1
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        // FIXME: WHY????
        while (j > 0 && s[i] != s[j])       // important part
            j = pi[j-1];                    // important part
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
// Gives all occurences of the pattern in text if not found then returns {-1}
vector<int> kmp(string text, string pattern){
    if (text.empty() || pattern.empty()) return {-1};
    string search = pattern + '$' + text;
    vector<int> pi_array = prefix_function(search);
    vector<int> occurences;
    // Looping through pi-array to find mathches
    for (int i = 0; i < sz(pi_array); i++) {
        if (pi_array[i] == sz(pattern)) {
            occurences.push_back(i-2*sz(pattern));
        }
    }
    if(occurences.empty()){
        occurences.push_back(-1);
    }
    return occurences;
}


int main() {
    fastIO;

    string a, b;
    see(a, b);
    // USAGE : Sliding Window technique
    // int pos = slide(a, b);
    // putl(pos);

    //USAGE : z-algo
    // int pos = zalgo(a,b);
    // putl(pos);

    // USAGE : String Hashing
    // int hashVal;
    // hashVal = getHash(a);
    // putl(hashVal);

    // USAGE : String Hashing for Substrings
    // init(a);    // Called for precomp. the prefix hashes
    // cout<<substringHash(0, 2)<<endl;

    // USAGE : Rabin- Karp algo
    // vector<int> occurencePos = rabin_karp(a,b);
    // debug(occurencePos);

    // USAGE : KMP
    vector<int> occurencePos = kmp(a,b);
    debug(occurencePos);
    return 0;
}
