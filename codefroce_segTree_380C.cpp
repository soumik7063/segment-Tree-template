#include <bits/stdc++.h>
using namespace std;
#define int long long

struct sgt
{
    int open, close, full;

    sgt(int o = 0, int c = 0, int f = 0) : open(o), close(c), full(f) {}
};

sgt merge(sgt s1, sgt s2)
{
    int open = 0, close = 0, full = 0;
    full = s1.full + s2.full + min(s1.open, s2.close);
    open = s1.open + s2.open - min(s1.open, s2.close);
    close = s1.close + s2.close - min(s1.open, s2.close);
    return sgt (open, close, full);
}
// building the seg by taking the ( and ) brackets
void build(int idx, int low, int high, string &s, vector<sgt> &segment)
{
    if (low == high)
    {
        int open = 0, full = 0, close = 0;
        if (s[low] == '(')
            open = 1;
        else
            close = 1;
        sgt st(open, close, full);
        segment[idx] = st;
        return;
    }
    int mid = (low + high) / 2;

    build(2 * idx + 1, low, mid, s, segment);
    build(2 * idx + 2, mid + 1, high, s, segment);
    segment[idx] = merge(segment[2 * idx + 1], segment[2 * idx + 2]);
}

sgt query(int idx, int low, int high, int l, int r, vector<sgt> &segment)
{
    sgt st(0, 0, 0);
    if (r < low || high < l)
        return st;
    if (l <= low && high <= r)
        return segment[idx];

    int mid = (low + high) / 2;
    sgt left = query(2 * idx + 1, low, mid, l, r, segment);
    sgt right = query(2 * idx + 2, mid + 1, high, l, r, segment);
    return merge(left, right);
}
signed main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<sgt> segment(4 * n + 1);
    build(0, 0, n - 1, s, segment);
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        sgt ans = query(0, 0, n - 1, l, r, segment);
        cout << ans.full * 2 << endl;
    }
    return 0;
}