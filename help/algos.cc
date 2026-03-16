#include<bits/stdc++.h>

using namespace std;

//TYPEDEFS
typedef long long int ll;
typedef unsigned long long int uli;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pllll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<int, int> > vpi;
typedef vector<pair<ll, ll> > vpll;
//DEFINES
#define mod 1000000007
#define gcd __gcd
#define lcm(a, b) ((a) * (b)) / gcd((a), (b))
#define rep(i, n) for (ll(i) = 0; (i) < (n); (i)++)
#define REP(i, k, n) for (ll(i) = (k); (i) < (n); (i)++)
#define repr(i, k, n) for (ll(i) = (k); (i) >= (n); (i)--)
#define pb push_back
#define popb pop_back
#define pf push_front
#define mp make_pair
#define mt make_tuple
#define popf pop_front()
#define si size()
#define be begin()
#define en end()
#define all(x) x.be, x.en
#define rall(x) x.rbegin(), x.rend()
#define sortinc(x) sort(all(x))
#define sortdec(x) sort(rall(x))
#define F first
#define S second



/*
    ! generates random string
    srand(time(NULL));
    n = (rand()%20+1);
    s="";
    rep(i,n){
        s+=(rand()%26 + 'a');
    }
*/



/*
    ! Alternative for to_lower and to_upper
    char c='A';
    cout<< c | ' ' <<endl;  // to lower
    c='a';
    cout<< c | '_' <<endl;  // to upper
*/



/*
    ! Achieving from bit manipulation
    x & (x-1) will clear the lowest set bit of x
    x & ~(x-1) extracts the lowest set bit of x (all others are clear). Pretty patterns when applied to a linear sequence.
    x & (x + (1 << n)) = x, with the run of set bits (possibly length 0) starting at bit n cleared.
    x & ~(x + (1 << n)) = the run of set bits (possibly length 0) in x, starting at bit n.
    x | (x + 1) = x with the lowest cleared bit set.
    x | ~(x + 1) = extracts the lowest cleared bit of x (all others are set).
    x | (x - (1 << n)) = x, with the run of cleared bits (possibly length 0) starting at bit n set.
    x | ~(x - (1 << n)) = the lowest run of cleared bits (possibly length 0) in x, starting at bit n are the only clear bits.
    the formula x | (1 << k) sets the kth bit of x to one, the formula x &
    ~(1 << k) sets the kth bit of x to zero, and the formula x ^ (1 << k) inverts the
    kth bit of x.
*/



// Syntax of memset (setting every element of array, vector, .. to 0 or -1 doesn't work for value any other than that)
void set_zero_or_one() {  
    // this has to be inside a function main() or user-defined
    int str[10];
    memset(str, -1, sizeof(str));
}



// binary_search, lower_bound and upper_bound
void explaining_bounds(){
    vi a(n);

    int element_to_search;
    bool isFound = binary_search(all(a), element_to_search); // just gives if present or not



    // for getting the exact index use :=
    int pos = lower_bound(all(a), element_to_search) - a.begin();
    if(pos != n && a[pos]==element_to_search) std::cout<<pos<<endl;    
    else std::cout<<"Not found"<<endl;
    // this extra checking is to be done because lower bound on shown below array for
    // lower_bound(4), lower_bound(2) will point to same location
    // and lower_bound(12) will point to end of the array
    // a : 1 4 4 4 4 4 5 5 5 6 8 9
    //       ^                     ^
    // NOTE : same method can be used to get the first occurence of any element



    // to find the last occurence use :=
    pos = upper_bound(all(a), element_to_search) - a.begin();
    pos--;
    if(pos != n && a[pos]==element_to_search) std::cout<<pos<<endl;    
    else std::cout<<"Not found"<<endl;
}



/*
    ! Tuples
    tuple<int, int, char, int> t1{1, 2, 'a', 3};

    ! To access the ith element of a tuple we can use get<i>(nameOfTuple)
    cout<<get<0>(t1) << " " << get<2>(t1) << endl; 
    ! Prints 1 and 'a'
*/



/*
    ! fixed double values
    cout << fixed << setprecision(6) << 1.0 << endl;
*/



/*
    ! accumulate() and partial_sum() used for finding total sum and prefix sum 
    https://www.geeksforgeeks.org/accumulate-and-partial_sum-in-c-stl-numeric-header/
*/



// Check if n is an integer or not
bool intornot(ld n) {
    if (floor(n) == ceil(n))   return 1;
    else return 0;
}



// Printing Map
void printmap(map<int, int> ms) {
    for (auto i : ms) {
        cout << "{" << i.F << " " << i.S << "}";
    }
}



// Lambda functions syntax
void Lambda_func() {
    [](int &a, int &b) {return a > b;};
}



// Finding maximum element and minimum element or there position in a vector
void mmvec(vi a) {
    auto maximum = *max_element(all(a));
    auto minimum = *min_element(all(a));
    // De-reference them to get their positon (address)
}



// Check if set or map S have a key or not
void func1(int key) {
    set<int> S;
    // OR map<int> S;
    if (S.find(key) != S.end()) {
        // ...
    }
    //However, set and map have a.count() method which returns 1 iff the key is in the container, otherwise 0:
    if (S.count(key)) {
        // ...
    }
}



// Minimum and maximum amongst variable values
int n = min({1, 2, 3/*,...*/});
int m = max({1, 33, 234, 432/*,...*/});



// Printing binary representation of n of "last L bits"
void print_binary(int n, const int L = 64) {
    cout << bitset<64>(n) << "\n";         // 'L' should be const and given to it before the compilation
    cout << oct << n << "\n";           // Prints octal
    cout << hex << n << "\n";           // Prints hexadecimal
}



// Counting number of 1's in binary representation
int set_bits(ll n){ 
    // O(no. of set bits )
    int ans=0;
    while (n & (n-1)){  ans++;  }

    // O(log n)
    while(n){
        if(n & 1) ans++;
        n>>1;
    }
    return ans;    
}



// ***************Bit Manipulation ***********************
int i, val;
// Conventional way to check ith bit set or not.
bool isSet(int num,int i){ // bit is counted from lsb to msb ..in this order 0th bit,1st bit...and so on
    for(int j=0;j<i;j++){
        num=num/2;
    }
    if(num&1)return true;
    return false;
}



// Using shift operator 
int t = val & (1<<i); // t is non zero (2^(i)) to be exact if ith bit is set else 0



// Setting ith bit
val = val | (1<<i);



// flipping ith bit
val = val ^ (1<<i); // ^ is the xor operator



// clearing the ith bit
val = val & ~(1<<i);



// *****************************Taking input made easier***************************
template <typename T>
T in()
{
    T x;
    cin >> x;
    return x;
}
int a = in<int>();         //calling the function template



// Cyclic shift of a vector by k>0 places
void shift(vi vec, char rl, int k) {
    if (rl == 'R' || rl == 'r')
        rotate(vec.rbegin(), vec.rbegin() + k, vec.rend());         //Right cyclic shift
    else if (rl == 'L' || rl == 'l')
        rotate(vec.begin(), vec.begin() + k, vec.end());            //Left cyclic shift
}



// Making elements of the vector unique;
vector<int> v = {1, 3, 3, 3, 2, 2, 2, 4, 4, 2, 412, 3, 314, 3, 3, 8};
// sort(all(v));            if comented : v=> 1 3 2 4 2 412 3 314 3 8
//                          else : v=> 1 2 3 4 8 314 412
v.resize(unique(all(v)) - v.begin());




// Returns if number is prime or not
bool IsPrime(ll number)
{
    ll root = sqrt(number);
    for (ll i = 2; i <= root; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}



// Returns the maximum subarray sum (Kadane's Algo)
int maxSubArraySum(int v[], int size)
{
    int max_so_far = v[0];
    int curr_max = v[0];
    for (int i = 1; i < size; i++)
    {
        curr_max = max(v[i], curr_max + v[i]);
        max_so_far = max(max_so_far, curr_max);
    }
    return max_so_far;
}



// Returns the sum of digits of n
int sumofdigits(ll n) {
    int v = 0;
    while (n != 0) {
        v += (n % 10);
        n /= 10;
    }
    return v;
}



// Returns boolean value if x is any power of 2 or not
bool isPowerOfTwo(int x) {
    return (x && !(x & (x - 1)));
}



// Returns if number is a perfect square or not
bool isPerfectSquare(long double x)
{
    long double sr = sqrt(x);
    return ((sr - floor(sr)) == 0);
}



// Returns a map of prime divisors(key) with multiplicity(value)
map<ll, ll> factorize(ll n)
{
    map<ll, ll> ans;
    for (ll i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            ans[i]++;
            n /= i;
        }
    }
    if (n > 1)
    {
        ans[n]++;
        n = 1;
    }
    return ans;
}



// Returns the number of ways in which n can be written as the sum positive numbers less than or equal to n
int no_of_possible_ways_to_sum_up_n(int n)
{
    if (n == 0)
    {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += no_of_possible_ways_to_sum_up_n(i);
    }
    return sum;
}



// extended euclids algorithm
int GCD(int a, int b, int &x, int &y){
    if(b==0){
        x=1, y=0;
        return a;
    }
    int x1, y1;
    int d = GCD(b, a%b, x1, y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}



// Return factorial n % mod
ll fac(ll n, ll x = mod)
{
    int res = 1, i;
    for (i = 2; i <= n; i++) {
        res *= i;
        res %= x;
    }
    return res % x;
}


// ********************** Modular Arithmetic ***********************
// (n+m)%mod
inline ll modadd(ll n, ll m, ll p = mod)
{
    return ((n + m) % p + p) % p;
}
// (n-m)%mod
inline ll modsub(ll n, ll m, ll p = mod)
{
    return ((n - m + p) % p + p) % p;
}
// (n*m)%mod
inline ll modpro(ll n, ll m, ll p = mod)
{
    return (((n % p) * (m % p)) % p + p) % p;
}
// x^y
uli powe(ll x, ll y)
{
    uli res = 1;
    while (y > 0)
    {
        if (y & 1)
            res = res * x;
        y = y >> 1;
        x = x * x;
    }
    return res;
}
// (x^y)%mod
ll modpow(ll x, ll y, ll p = mod)
{
    ll res = 1;
    while (y > 0)
    {
        if (y & 1)
            res = modpro(res, x, p);
        y = y >> 1;
        x = modpro(x, x, p);
    }
    return res;
}
// (n^(-1))%mod (Fermats Little Theorem)
inline ll modInverse(ll n, ll p = mod)
{
    if (n == 1)
        return 1;
    return modpow(n, p - 2, p);
}
// (n/m)%mod
inline ll moddiv(ll n, ll m, ll p = mod)
{
    return modpro(n, modInverse(m, p), p);
}
// (x+y+z)%mod
inline ll modadd3(ll x, ll y, ll z, ll p = mod)
{
    return modadd(modadd(x, y, p), z, p);
}
// (x+y+z+w)%mod
inline ll modadd4(ll x, ll y, ll z, ll w, ll p = mod)
{
    return modadd(modadd(x, y, p), modadd(z, w, p), p);
}
// nCr%mod
inline ll modnCr(ll fac[], int n, int r, ll p = mod)
{
    if (r == 0)
        return 1;
    return modpro(fac[n], modInverse(modpro(fac[r], fac[n - r], p), p), p);
}
// * IMP for nCr
    ll fac_[200005]; // Global
    void fac_init(int n)
    {
        fac_[0] = 1;
        REP(i, 1, n + 1) fac_[i] = modpro(fac_[i - 1], i);
    }
    // Fun calling
    fac_init(1005);



////////////////////Some famous conventional problems////////////////////////

// Prints every step for Tower of Hanoi Problem
void toh(int n, char source, char auxillary, char destination)
{
    if (n == 1)
    {
        cout << "Move " << n << " from '" << source << "' to '" << destination << "'" << endl;
        return;
    }
    toh(n - 1, source, destination, auxillary);
    cout << "Move " << n << " from '" << source << "' to '" << destination << "'" << endl;
    toh(n - 1, auxillary, source, destination);
}

// Prints every stage of josephus problem ,dir here is direction of elimination of the elements 1:clockwise !1:anti-clockwise
void josephus_problem()
{
    int n, m, dir;
    cin >> n >> m >> dir;
    vi linked;
    if (dir == 1)
    {
        rep(i, n)
        {
            linked.pb(i + 1);
        }
    }
    else
    {
        linked.pb(1);
        repr(i, n, 2)
        {
            linked.pb(i);
        }
    }
    print(linked);
    int i = m - 1;
    while (linked.size() != 1)
    {
        linked.erase(linked.begin() + i);
        print(linked);
        i += (m - 1);
        if (i >= linked.size())
        {
            i = i % linked.size();
        }
    }
}




// Calculates time to run the program
auto clk = clock();
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
void run_time()
{
#ifdef local
    cout << endl;
    cout << "Time elapsed: " << (double)(clock() - clk) / CLOCKS_PER_SEC << endl;
#endif
    return;
}