#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class segmentTree {
    private:

    ll n;
    vector < ll > seg;

    void buildTree(ll node, ll low, int high,
        const vector < ll > & Hotels) {
        if (low == high) {
            seg[node] = Hotels[low];
            return;
        }

        ll mid = low + (high - low) / 2;
        buildTree(2 * node + 1, low, mid, Hotels);
        buildTree(2 * node + 2, mid + 1, high, Hotels);

        seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
    }

    ll query(int node, int low, int high, int noOfPeople) {

        if (seg[node] < noOfPeople)
            return -1;

        if (low == high) {
            seg[node] -= noOfPeople;
            return low;
        }

        ll mid = low + (high - low) / 2;
        if (seg[2 * node + 1] >= noOfPeople) {
            int ans = query(2 * node + 1, low, mid, noOfPeople);
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
            return ans;
        }

        int ans = query(2 * node + 2, mid + 1, high, noOfPeople);
        seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        return ans;
    }

    public:

        segmentTree(const vector < ll > & Hotels) {
            n = Hotels.size();
            seg.resize(4 * n);
            buildTree(0, 0, n - 1, Hotels);
        }

    /*
        void printSegmentTree() {
            for (auto & ele: seg) {
                cout << ele << " ";
            }
        }
    */
    
    ll query(ll noOfPeople){
        return query(0, 0, n - 1, noOfPeople);
    }
};

int main() {

    ll n, m;
    cin >> n >> m;

    vector < ll > Hotels(n);
    for (int i = 0; i < n; i++) cin >> Hotels[i];

    vector < ll > Groups(m);
    for (int i = 0; i < m; i++) cin >> Groups[i];

    segmentTree obj(Hotels);
    // obj.printSegmentTree();

    vector < ll > ans;
    for (int i = 0; i < m; i++) {
        ll noOfPeople = Groups[i];
        
        int assigned = obj.query(noOfPeople);
        if(assigned != -1)
            ans.emplace_back(assigned + 1);
        else
            ans.emplace_back(0);
    }
    
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] <<" ";
    }

    return 0;

}