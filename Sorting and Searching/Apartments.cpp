#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& a, vector<int>& b, int k){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0, j = 0, ans = 0;
    while(i < a.size() && j < b.size()){
        if(abs(a[i] - b[j]) <= k){
            ans++;
            i++;
            j++;
        }
        else if((a[i] - b[j]) > k){
            j++;
        }
        else{
            i++;
        }
    }
    return ans;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for(int j = 0; j < m; ++j){
        cin >> b[j];
    }
    
    cout << solve(a, b, k) << endl;
	return 0;
}