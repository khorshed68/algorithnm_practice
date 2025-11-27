#include <bits/stdc++.h>
using namespace std;
int main() {
    string a, b;
    cout << "Enter first string: ";
    cin >> a;
    cout << "Enter second string: ";
    cin >> b;
    int n = a.size();
    int m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    // Reconstruct the LCS string
    int i = n, j = m;
    string lcs = "";
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs += a[i - 1];
            i--;
            j--;
        }
        else {
            if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << "\nLength of LCS: " << dp[n][m] << endl;
    cout << "LCS string: " << lcs << endl;
    return 0;
}
//Build the DP table
//If characters match → take diagonal + 1
//If characters don’t match → take max(left, up)
//Finally, backtrack through the table to get the LCS string
