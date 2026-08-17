#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class SegmentTree {

    private: 
    struct Node {
        ll sum;
        ll prefix;
        ll suffix;
        ll maxSum;
        Node(ll x = 0) {
            sum = x;
            prefix = suffix = maxSum = max(0LL, x);
        }
    };

    ll n;
    vector < Node > seg;
    
    Node merge(const Node& left, const Node& right) {
        Node res;

        res.sum = left.sum + right.sum;

        res.prefix = max(left.prefix, left.sum + right.prefix);

        res.suffix = max(right.suffix, right.sum + left.suffix);

        res.maxSum = max({ left.maxSum, right.maxSum, left.suffix + right.prefix });

        return res;
    }
    
    void buildTree(ll node, ll low, ll high, const vector < ll > & arr) {

        if (low == high) {
            seg[node] = Node(arr[low]);
            return ;
        }

        ll mid = low + (high - low) / 2;
        buildTree(2 * node + 1, low, mid, arr);
        buildTree(2 * node + 2, mid + 1, high, arr);

        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);

    }
    
    
     void update(ll node, ll low, ll high, ll index, ll value) {
        if (low == high) {
            seg[node] = Node(value);
            return;
        }

        ll mid = low + (high - low) / 2;

        if (index <= mid) {
            update(2 * node + 1, low, mid, index, value);
        } else {
            update(2 * node + 2, mid + 1, high, index, value);
        }

        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    public: 
    SegmentTree(const vector < ll > & arr) {
        n = arr.size();
        seg.resize(4 * n);
        buildTree(0, 0, n - 1, arr);
    }
    
    void update(ll index, ll value) {
        update(0, 0, n - 1, index, value);
    }

    ll getMaxSubarraySum() {
        return seg[0].maxSum;
    }
};

int main() {

    ll n, q;
    cin >> n >> q;

    vector < ll > arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    SegmentTree obj(arr);

    while (q--) {
        int index, value;
        cin >> index >> value;
        index--;
        
        obj.update(index, value);
        
        cout << obj.getMaxSubarraySum() <<"\n";
    }

    return 0;
}