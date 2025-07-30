#include <bits/stdc++.h>
using namespace std;

class SGTree
{
public:
    vector<int> segment;
    SGTree(int n)
    {
        segment.resize(4 * n + 1, 0);
    }

    void build(int idx, int low, int high, vector<int> &v)
    {
        if (low == high)
        {
            segment[idx] = v[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * mid + 1, low, mid, v);
        build(2 * mid + 2, mid + 1, high, v);
        segment[idx] = min(segment[2 * mid + 1], segment[2 * mid + 2]);
    }
    void update(int idx, int low, int high, int i, int val)
    {
        if (low == high)
        {
            segment[idx] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid)
        {
            update(2 * mid + 1, low, mid, i, val);
        }
        else
            update(2 * mid + 2, mid + 1, high, i, val);
        segment[idx] = min(segment[2 * mid + 1], segment[2 * mid + 2]);
    }
    // minimum in range
    int query(int idx, int low, int high, int l, int r)
    {
        if (r < low || l > high)
            return INT_MAX; // non overap;

        if (low >= l && high <= r)
        {
            return segment[idx]; // complete overalp
        }

        int mid = (low + high) / 2;
        return min(query(mid * 2 + 1, low, mid, l, r), query(mid * 2 + 2, mid + 1, high, l, r)); // partial overlap
    }
};

int main()
{

    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (auto &i : v)
        cin >> i;
    SGTree sgt(n);

    sgt.build(0, 0, n - 1, v);

    for (int i = 0; i < q; i++)
    {
        int k;
        cin >> k;

        if (k == 2)
        {
            // query
            int l, r;
            cin >> l >> r;
            cout << sgt.query(0, 0, n - 1, l - 1, r - 1) << endl;
        }
        else
        {
            // update
            int i, val;
            cin >> i >> val;
            sgt.update(0, 0, n - 1, i - 1, val);
        }
    }
    return 0;
}