#include <bits/stdc++.h>

using namespace std;
using ll = long long;


class segmentTree {
    private :
        struct Node {
            ll sum;
            ll maxPrefixSum;
        };

        ll n;
        vector < Node > seg;

        Node merge(Node leftNode, Node rightNode) {
            Node res;
            res.sum = leftNode.sum + rightNode.sum;
            res.maxPrefixSum = max(leftNode.maxPrefixSum, leftNode.sum + rightNode.maxPrefixSum);
            return res;
        }

        void buildTree(ll node, ll low, ll high, const vector < ll >& arr) {

            if (low == high) {
                seg[node] = {arr[low], max(0LL, arr[low])};
                return;
            }

            ll mid = low + (high - low) / 2;
            buildTree(2 * node + 1, low, mid, arr);
            buildTree(2 * node + 2, mid + 1, high, arr);

            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);

        }

        void update(ll node, ll low, ll high, ll index, ll value) {

            if (low == high) {
                seg[node] = {value, max(0LL, value)};
                return;
            }

            ll mid = low + (high - low) / 2;
            if (index <= mid) {
                update(2 * node + 1, low, mid, index, value);
            }
            else {
                update(2 * node + 2, mid + 1, high, index, value);
            }

            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);

        }

        Node query(ll node, ll low, ll high, ll left, ll right) {

            if (low > right || high < left)
                return { 0LL, LLONG_MIN };

            if (low >= left && high <= right)
                return seg[node];

            ll mid = low + (high - low) / 2;
            Node l = query(2 * node + 1, low, mid, left, right);
            Node r = query(2 * node + 2, mid + 1, high, left, right);
            
            if (l.maxPrefixSum == LLONG_MIN)
                return r;

            if (r.maxPrefixSum == LLONG_MIN)
                return l;

            return merge(l, r);

        }

    public:

        segmentTree(const vector < ll > & arr) {
            n = arr.size();
            seg.resize(4 * n);
            buildTree(0, 0, n - 1, arr);
        }

        ll rangeMaxPrefixSum(ll left, ll right) {
            return query(0, 0, n - 1, left, right).maxPrefixSum;
        }

        void pointUpdate(ll index, ll value) {
            update(0, 0, n - 1, index, value);
        }

};


int main() {

    ll n, q;
    cin >> n >> q;

    vector < ll > arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    segmentTree obj(arr);

    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll index, value;
            cin >> index >> value;
            index--;
            obj.pointUpdate(index, value);
        }
        else {
            int left, right;
            cin >> left >> right;
            left--;
            right--;
            cout << obj.rangeMaxPrefixSum(left, right) <<"\n";
        }
    }
    return 0;
}
