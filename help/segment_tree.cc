#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9;

/*
KEYNOTES:
------------------------------------------
merge(X,identity_element) = X
------------------------------------------
------------------------------------------
identity_transformation.combine(X) = X
------------------------------------------
------------------------------------------
ALWAYS: older_update.combine(newer_update)
------------------------------------------
*/
/*
    # Used in range queries
    # Can be used in every operation that is associative, like +, max, min, gcd,
*/
// example: addition: identity element is 0, a + 0 = a or 0 + a = a
// example: min(x,INF) = x

struct node {
    int v=0;   //1
    // use more variables if you want more information
    // these default values should be identity_element
    node() {}
    node(int val) {  // 2
        v=val;
    }
    // store the thing you wanna query
    void merge(const node &l,const node &r) {  //3
        v=l.v+r.v;
        // if we wanted the maximum, then we would do
        // like v = max(l.v,r.v)
    }
};

// example: add on a range: identity transformation = 0
// old += new
// if old is identity which is 0, then 0 + new which new

struct update {
    int v = 0;  // 4
    // use more variables if you want more information
    // these default values should be identity_transformation
    update() {}
    update(int val) {
        v = val;  // 5
    }
    // combine the current update with the other update (see keynotes)
    void combine(update &other, const int32_t &tl, const int32_t &tr) {
        v += other.v;  // 6
        // you can be sure that the "other" is newer than current
    }
    // store the correct information in the node x
    void apply(node &x, const int32_t &tl, const int32_t &tr) {  // 7
        x.v += v*(tr-tr+1);
    }
};

// template <typename node, typename update>
struct segtree {
    int len;
    vector<node> t;
    vector<update> u;
    vector<bool> lazy;
    node identity_element;
    update identity_transformation;
    segtree(int l) {
        len = l;
        t.resize(4 * len);
        u.resize(4 * len);
        lazy.resize(4 * len);
        identity_element = node();
        identity_transformation = update();
    }

    void pushdown(const int32_t &v, const int32_t &tl, const int32_t &tr) {
        if (!lazy[v]) return;
        int32_t tm = (tl + tr) >> 1;
        apply(v << 1, tl, tm, u[v]);
        apply(v << 1 | 1, tm + 1, tr, u[v]);
        u[v] = identity_transformation;
        lazy[v] = 0;
    }

    void apply(const int32_t &v, const int32_t &tl, const int32_t &tr,update upd) {
        if (tl != tr) {
            lazy[v] = 1;
            u[v].combine(upd, tl, tr);
        }
        upd.apply(t[v], tl, tr);
    }

    template <typename T>
    void build(const T &arr, const int32_t &v, const int32_t &tl,const int32_t &tr) {
        if (tl == tr) {
            t[v] = arr[tl];
            return;
        }
        int32_t tm = (tl + tr) >> 1;
        build(arr, v << 1, tl, tm);
        build(arr, v << 1 | 1, tm + 1, tr);
        t[v].merge(t[v << 1], t[v << 1 | 1]);
    }

    node query(const int32_t &v, const int32_t &tl, const int32_t &tr,const int32_t &l, const int32_t &r) {
        if (l > tr || r < tl) {
            return identity_element;
        }
        if (tl >= l && tr <= r) {
            return t[v];
        }
        pushdown(v, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        node a = query(v << 1, tl, tm, l, r), b = query(v << 1 | 1, tm + 1, tr, l, r), ans;
        ans.merge(a, b);
        return ans;
    }

    // rupd = range update
    void rupd(const int32_t &v, const int32_t &tl, const int32_t &tr,const int32_t &l, const int32_t &r, const update &upd) {
        if (l > tr || r < tl) {
            return;
        }
        if (tl >= l && tr <= r) {
            apply(v, tl, tr, upd);
            return;
        }
        pushdown(v, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        rupd(v << 1, tl, tm, l, r, upd);
        rupd(v << 1 | 1, tm + 1, tr, l, r, upd);
        t[v].merge(t[v << 1], t[v << 1 | 1]);
    }

public:
    template <typename T>
    void build(const T &arr) {
        build(arr, 1, 0, len - 1);
    }
    node query(const int32_t &l, const int32_t &r) {
        return query(1, 0, len - 1, l, r);
    }
    void rupd(const int32_t &l, const int32_t &r, const update &upd) {
        rupd(1, 0, len - 1, l, r, upd);
    }
};

int main() {
    segtree s(1000);  // create a segment tree of length 1000

    s.rupd(2, 5, 8);
    s.rupd(1, 3, -4);

    for (int i = 0; i < 15; i++) {
        cout << s.query(i, i).v << " ";
    }
    return 0;
}













// 0-based indexing
ll a[100005], seg[4*100005];    
ll lazy[4*100005];

// ind = index of segment tree
// [low, high] is range of original array 

//O(n)
void build(int ind, int low, int high){
    if(low==high){
        seg[ind]=a[low];
        return;
    }
    int mid=(low+high)/2;
    build(2*ind+1, low, mid);
    build(2*ind+2, mid+1, high);
    seg[ind]=seg[2*ind+1] + seg[2*ind+2];
}

ll query(int ind, int low, int high, int &l, int &r){
    if(low>=l && high<=r){
        return seg[ind];
    }
    if(high<l || low>r)return 0;
    int mid=(low+high)/2;
    int left=query(2*ind+1, low, mid, l, r);
    int right=query(2*ind+2, mid+1, high, l, r);
    return left+right;
}

void pointUpdate(int ind, int low, int high, int &node, int &val){
    if(low==high){
        seg[ind]+=val;
    }else{
        int mid=(low+high)>>1;
        if(node<=mid && node>=low) pointUpdate(2*ind+1, low, mid, node, val);
        else pointUpdate(2*ind+2, mid+1, high, node, val);

        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
}

void rangeUpdate(int ind, int low, int high, int &l, int &r, int &val){
    if(lazy[ind!=0]){
        seg[ind]+=(high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    if(r<low || l>high || low>high)return;

    if(low<=l && high<=r){
        seg[ind]+=(high-low+1)*val;
        if(low!=high){
            lazy[2*ind+1]+=val;
            lazy[2*ind+2]+=val;
        }
        return;
    }
    int mid=(low+high)>>1;
    rangeUpdate(2*ind+1, low, mid, l, r, val);
    rangeUpdate(2*ind+2, mid+1, high, l, r, val);
    seg[ind]=seg[2*ind+1]+seg[2*ind+2];
}

ll queryLazy(int ind, int low, int high, int &l, int &r, int &val){
    if(lazy[ind]!=0){
        seg[ind]+=(high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    if(r<low || l>high || low>high)return 0;

    if(low<=l && high<=r){
        return seg[ind];
    }

    int mid=(low+high)>>1;
    ll left = queryLazy(2*ind+1, low, mid, l, r, val);
    ll right = queryLazy(2*ind+2, mid+1, high, l, r, val);
    return left+right;
}
// int main(){
//     fastIO;
    
//     int n;see(n);
//     rep(i,n){
//         see(a[i]);
//     }

//     build(0, 0, n-1);
//     int q;see(q);
//     while(q--){
//         int l, r;see(l,r);
//         putl(query(0,0,n-1,l,r));
//     }
//     int l=0, r=2, val=8;
//     pointUpdate(0,0,n-1,l,val); // 9 2 3 4 5 
//     putl(query(0,0,n-1,l,r));
//     val=4;
//     rangeUpdate(0,0,n-1,l,r,val);   // 13 6 7 4 5 
//     putl(queryLazy(0,0,n-1,l,r,val));
//     return 0;
// }