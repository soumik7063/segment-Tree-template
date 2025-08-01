#include<bits/stdc++.h>
using namespace std;
#define int long long
#define soumik_7063 ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


// soumik's lazy propagation template
// this is for 
// 1. increase each value in range [a,b] by u
// 2. what is the value at position k?

class SGTree{
    vector<int>segments,lazy;
    public:
    SGTree(int n){
        segments.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }
    void build(int idx,int low,int high,vector<int>&a){

        if(low == high){
            segments[idx] = a[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2*idx+1,low,mid,a);
        build(2*idx+2,mid+1,high,a);
    }

    // change logic according to problem

    void update(int idx,int low,int high,int l,int r,int val){
        if(lazy[idx] != 0){
            segments[idx] += (high-low+1)*lazy[idx];

            if(low != high){
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }

            lazy[idx] = 0;
        }
        if(r<low || l> high) return;
        if(low>=l && high <= r){
            segments[idx] += (high-low+1)*val;

            if(low != high){
                lazy[2*idx+1] += val;
                lazy[2*idx+2] += val;
            }
            return;
        }

        int mid = (low + high) >> 1;
        update(2*idx+1,low,mid,l,r,val);
        update(2*idx+2,mid+1,high,l,r,val);
    }

    // change logic according to problem

    int query(int idx,int low,int high,int i){
        if(lazy[idx] != 0){
            segments[idx] += (high-low+1)*lazy[idx];

            if(low != high){
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }

            lazy[idx] = 0;
        }
        if(low== high) {
            return segments[idx];
        }

        int mid = (low + high) >> 1;
        if(i<=mid) return query(2*idx+1,low,mid,i);
        return query(2*idx+2,mid+1,high,i);
    }
};

signed main(){
    soumik_7063
   int n,q;
   cin>>n>>q;
   vector<int>a(n);
   SGTree sg(n);
   for(int i = 0;i <n;i++) cin>>a[i];
   sg.build(0,0,n-1,a);

    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            int l,r,val;
            cin>>l>>r>>val;
            l--;
            r--;
            sg.update(0,0,n-1,l,r,val);
        }else{
            int k;
            cin>>k;
            k--;
            cout<<sg.query(0,0,n-1,k)<<endl;;
        }
    }
   return 0;
}