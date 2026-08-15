#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    vector<long long> arr(n - 1);
    for(int i = 0; i < n - 1 ; i++){
        cin >> arr[i];
    }
    
    int xor1 = 0, xor2 = 0;
    for(int i = 0; i < n - 1; i++){
        xor1 ^= arr[i];
    }

    for(int i = 1; i <= n; i++){
        xor2 ^= i;
    }

    cout << (xor1 ^ xor2) << endl;
    
    return 0;
}