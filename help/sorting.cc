#include "bits/stdc++.h"

using namespace std;

//TYPEDEFS
typedef long long int ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pllll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<int,int>> vpi;
typedef vector<pair<ll,ll>> vpll;
//DEFINES
#define endl "\n"
#define fastIO  std::ios::sync_with_stdio(false);cin.tie(NULL)
#define rep(i, n) for (ll (i) = 0; (i) < (n); (i)++)
#define REP(i, k, n) for (ll (i) = (k); (i) < (n); (i)++)
#define repr(i, k, n) for (ll (i) = (k); (i) >= (n); (i)--)
#define pb push_back
#define popb pop_back
#define pf push_front
#define popf pop_front()
#define sz(a) (ll)a.size()
#define be begin()
#define en end()
#define all(x) x.be,x.en
#define rall(x) x.rbegin(),x.rend()
#define sortinc(x) sort(all(x))
#define sortdec(x) sort(rall(x))
#define cend cout<<endl
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define r0 return 0
#define F first
#define S second
#define debug(x) cout << #x <<" "; _print(x); cout << endl;

void _print(ll t) {cout<< t;}
void _print(int t) {cout<< t;}
void _print(string t) {cout<< t;}
void _print(char t) {cout<< t;}
void _print(double t) {cout<< t;}
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cout<< "{"; _print(p.F); cout<< ","; _print(p.S); cout<< "}";}
template <class T> void _print(vector <T> v) {cout<< "[ "; for (T i : v) {_print(i); cout << " ";} cout<< "]";}
template <class T> void _print(set <T> v) {cout<< "[ "; for (T i : v) {_print(i); cout<< " ";} cout<< "]";}
template <class T> void _print(multiset <T> v) {cout<< "[ "; for (T i : v) {_print(i); cout<< " ";} cout<< "]";}
template <class T, class V> void _print(map <T, V> v) {cout<< "[ "; for (auto i : v) {_print(i); cout<< " ";} cout<< "]";}
template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << " "), ...); cout<<'\n';}
template <typename T>
void print(vector<T> v){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

//TODO: Bubble Sort
void bs(vector<int> a){
    int n = sz(a);
    print(a);
    for(int i=0;i<n-1;i++){
        for(int j=1;j<n-i;j++){
            if(a[j-1]>a[j])swap(a[j-1], a[j]);
        }
        print(a);
    }
    print(a);
}


//TODO: Selection Sort
void ss(vector<int> a){
    int n=sz(a);
    print(a);
    for(int i=0;i<n-1;i++){
        int mini=a[i];
        int pos=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<mini){
                mini=a[j];
                pos=j;
            }
        }
        swap(a[i], a[pos]);
        print(a);
    }
    print(a);
}

//TODO: Insertion Sort
void is(vector<int> a){
    int n = sz(a);
    print(a);
    for(int i=1;i<n;i++){
        int temp=a[i], j;
        for(j=i-1;j>=0;j--){
            if(a[j]<temp){
                break;
            } else{
                a[j+1]=a[j];
            }
        }
        a[j+1]=temp;
        print(a);
    }
    print(a);
}

//TODO: Merge Sort
void merge(vector<int> &a, int s, int m, int e){
    vector<int> b(m-s), c(e-m+1);
    int k=s;
    for(int i=0;i<m-s;i++){
        b[i]=a[s+i];
    }
    for(int i=0;i<e-m+1;i++){
        c[i]=a[m+i];
    }    
    int i=0, j=0;
    while(i<m-s && j<e-m+1){
        if(b[i]<c[j]){
            a[k++]=b[i++];
        }else{
            a[k++]=c[j++];
        }
    }
    while(i<m-s){
        a[k++]=b[i++];
    }
    while(j<e-m+1){
        a[k++]=c[j++];
    }
}

void ms_helper(vector<int> &a, int s, int e){
    if(s==e)return;
    int m = (e-s)/2+s; // Overflow avoided
    ms_helper(a, s, m);
    ms_helper(a, m+1, e);
    merge(a,s,m+1,e); 
}

void ms(vector<int> a){
    int n=sz(a);
    print(a);
    ms_helper(a, 0, n-1);
    print(a);
}

//TODO: Quick Sort
int partition(vector<int> &a, int s, int e){
    int pivot = a[e];
    int j=s-1;
    for (int i=s;i<e;i++){
        if (a[i] <= pivot) {
            j++;
            swap(a[j], a[i]);
        }
    }
    swap(a[j + 1], a[e]);
    return j + 1;
}

void qs_helper(vector<int> &a, int s, int e){
    if (s >= e) return;
    int mid = (e-s)/2+s; // Overflow avoided
    swap(a[mid], a[e]);
    int q = partition(a, s, e);
    qs_helper(a, s, q - 1);
    qs_helper(a, q + 1, e);
}

void qs(vector<int> a){
    int n=sz(a);
    print(a);
    qs_helper(a, 0, n-1);
    print(a);
}

//TODO: Counting Sort

//TODO: Heap Sort

//TODO: Radix Sort

//TODO: Bucket Sort

//TODO: Shell Sort

int main(){
    fastIO;
    
    // vector<int> a = {2,4,3,1,267,45,74,8,56};
    // bs(a);
    // ss(a);
    // is(a);
    // ms(a);
    // qs(a);
    return 0;
}
