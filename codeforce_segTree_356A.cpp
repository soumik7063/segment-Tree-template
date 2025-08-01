#include<bits/stdc++.h>
using namespace std;
#define int long long
 
int n;
 
// Point update
void build(int idx,int low,int high){
    
}
void query(int idx, int low, int high, int l, int r,int val, vector<int>& v) {
    if(r<low || l>high) return;
    if (low == high ) {
        if(v[low] == 0 && low != val-1){
          v[low] = val;
        }
        return;
    }
    
    int mid = (low + high) / 2;
    
    query(2 * mid + 1, low, mid, l, r,val,v);
    query(2 * mid + 2, mid + 1, high, l,r,val,v);
    
}
 
signed main() {
    int q;
    cin >> n >> q;
    vector<int> v(n,0);
 
    // vector<int> segment(4 * size);
    // segmentTree(0, 0, size - 1, segment, v, 0);
 
    while (q--) {
        int l, r,k;
        cin >> l >> r>>k;
        query(0, 0, n - 1, l - 1, r-1,k,v);
    }
    for(auto it:v) cout<<it<<" ";
 
    return 0;
}