#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class SegmentTree {
    ll n;
    vector < ll > seg;

    public:
        SegmentTree(vector < ll > & arr) {
            n = arr.size();
            seg.resize(4 * n);
            buildTree(0, 0, n - 1, arr);
        }

    void buildTree(ll node, ll low, ll high, vector < ll > & arr) {
        if (low == high) {
            seg[node] = arr[low];
            return;
        }

        ll mid = low + (high - low) / 2;

        buildTree(2 * node + 1, low, mid, arr);
        buildTree(2 * node + 2, mid + 1, high, arr);

        seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
    }

    ll query(ll node, ll low, ll high, ll left, ll right) {
   
        if (high < left || low > right)
            return 0;


        if (left <= low && high <= right)
            return seg[node];

        ll mid = low + (high - low) / 2;

        ll leftSum = query(2 * node + 1, low, mid, left, right);
        ll rightSum = query(2 * node + 2, mid + 1, high, left, right);

        return leftSum + rightSum;
    }

    ll rangeSum(ll left, ll right) {
        return query(0, 0, n - 1, left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    vector < ll > arr(n);

    for (ll i = 0; i < n; i++)
        cin >> arr[i];

    SegmentTree obj(arr);

    while (q--) {
        ll a, b;
        cin >> a >> b;

        cout << obj.rangeSum(a - 1, b - 1) << '\n';
    }

    return 0;
}