#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {

    string str;
    cin >> str;

    ll i = 0, j = 0, n = str.length();
    ll max_len = 0;
    char prev = '\0';

    while (j < n) {
        char ch = str[j];
        if (prev == ch) {
            max_len = max(max_len, j - i + 1);
        } 
        else {
            i = j;
            max_len = max(max_len, j - i); 
        }
        prev = ch;
        j++;
    }
    max_len = max(max_len, j - i);
    cout << max_len << endl;
    return 0;

}


/* Solution 2
void solve(string& str){

    int n = str.length();
    int max_len = 1, curr_len = 1;

    for (int i = 1; i < n; i++) {
        if (str[i] == str[i - 1]) {
            curr_len++;
            max_len = max(max_len, curr_len);
        } else {
            curr_len = 1;
        }
    }

    cout << max_len << endl;
}
*/
