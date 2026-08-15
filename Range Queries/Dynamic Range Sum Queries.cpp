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

    void update(ll node, ll low, ll high, ll index, ll value) {
        if (low == high) {
            seg[node] = value;
            return;
        }
        ll mid = low + (high - low) / 2;
        if (index <= mid) {
            update(2 * node + 1, low, mid, index, value);
        }
        else {
            update(2 * node + 2, mid + 1, high, index, value);
        }

        seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
    }

    ll rangeMin(ll left, ll right) {
        return query(0, 0, n - 1, left, right);
    }

    void pointUpdate(ll index, ll value) {
        update(0, 0, n - 1, index, value);
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
        ll type;
        cin >> type;
        if (type == 1) {
            ll index, value;
            cin >> index >> value;
            obj.pointUpdate(index - 1, value);
        }
        else {
            ll a, b;
            cin >> a >> b;

            cout << obj.rangeMin(a - 1, b - 1) << '\n';
        }
    }

    return 0;
}