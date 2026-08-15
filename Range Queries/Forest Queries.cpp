#include <bits/stdc++.h>
using namespace std;

int main() {

    long long n, q;
    cin >> n >> q;

    vector<vector<long long>> matrix(n, vector<long long>(n));

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            char ch;
            cin >> ch;

            matrix[i][j] = (ch == '.') ? 0 : 1;
        }
    }

    vector<vector<long long>> prefixSum(n + 1, vector<long long>(n + 1, 0));

    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= n; j++) {
            prefixSum[i][j] = matrix[i - 1][j - 1]
                + prefixSum[i - 1][j]
                + prefixSum[i][j - 1]
                - prefixSum[i - 1][j - 1];
        }
    }

    while (q--) {
        long long y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        long long answer = prefixSum[y2][x2]
            - prefixSum[y1 - 1][x2]
            - prefixSum[y2][x1 - 1]
            + prefixSum[y1 - 1][x1 - 1];

        cout << answer << '\n';
    }

    return 0;
}