#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class segmentTree {
    ll n;
    vector < ll > seg;

    public:
        segmentTree(const vector < ll > & arr) {
            n = arr.size();
            seg.resize(4 * n, 0);
            buildTree(0, 0, n - 1, arr);
        }

    void buildTree(ll node, ll low, ll high, const vector < ll > & arr) {

        if (low == high) {
            seg[node] = arr[low];
            return;
        }

        ll mid = low + (high - low) / 2;

        buildTree(2 * node + 1, low, mid, arr);
        buildTree(2 * node + 2, mid + 1, high, arr);
    }


    void update(ll node, ll low, ll high, ll left, ll right, ll value) {


        if (high < left || low > right)
            return;


        if (low >= left && high <= right) {
            seg[node] += value;
            return;
        }

        ll mid = low + (high - low) / 2;

        update(2 * node + 1, low, mid, left, right, value);

        update(2 * node + 2, mid + 1, high, left, right, value);
    }

    ll query(ll node, ll low, ll high, ll index) {

        if (low == high)
            return seg[node];

        ll mid = low + (high - low) / 2;

        if (index <= mid) {
            return seg[node] + query(2 * node + 1, low, mid, index);
        }
        else {
            return seg[node] + query(2 * node + 2, mid + 1, high, index);
        }
    }

    void update(ll left, ll right, ll value) {
        update(0, 0, n - 1, left, right, value);
    }

    ll query(ll index) {
        return query(0, 0, n - 1, index);
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

    segmentTree obj(arr);

    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll left, right, value;
            cin >> left >> right >> value;
            left--;
            right--;
            obj.update(left, right, value);
        }
        else {
            ll k;
            cin >> k;
            k--;
            cout << obj.query(k) << '\n';
        }
    }

    return 0;
}