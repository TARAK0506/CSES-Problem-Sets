#include<bits/stdc++.h>
using namespace std;

int countSetBits(int n){
    int cnt = 0;
    while(n){
        if((n & 1) == 1) cnt++;
        n = n >> 1; 
    }
    return cnt;
}

int main(){
    long long n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += countSetBits(i);
    }
    cout << ans << endl;
    return 0;
}