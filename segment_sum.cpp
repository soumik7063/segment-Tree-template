#include<bits/stdc++.h>
using namespace std;
#define int long long

int segmentTree(int idx,int low,int high,vector<int>&segment,vector<int>&v){
    if(low == high){
        segment[idx] = v[low];
        return v[low];
    }

    int mid = (low+high)/2;
    return segment[idx] = (segmentTree(2*mid+1,low,mid,segment,v)+segmentTree(2*mid+2,mid+1,high,segment,v));
}
int query(int idx,int low,int high,int l , int r,vector<int>&segment){
    if(r<low || l>high) return 0; // non overap;

    if(low >= l && high <= r) {
        return segment[idx];        // complete overalp
    }

    int mid = (low+high)/2;
    return query(mid*2+1,low,mid,l,r,segment)+query(mid*2+2,mid+1,high,l,r,segment); //partial overlap
}

signed main(){
   int n,q; 
   cin>>n>>q;
    vector<int>v(n);
    for(auto &i:v)cin>>i;
   vector<pair<int,int>>queries(q);
   for(int i = 0 ;i <q;i++){
    int l,r;
    cin>>l>>r;
    queries[i]=(make_pair(l,r));
   }
   vector<int>segments(4*n+1);
   segmentTree(0,0,n-1,segments,v);
//    for(auto it:segments)cout<<it<<" ";
   for(auto it:queries){
    int l = it.first;
    int r = it.second;

    cout<<query(0,0,n-1,l-1,r-1,segments)<<endl; 
   }

   return 0;
}