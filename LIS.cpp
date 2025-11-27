#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    vector<int> a(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> dp(n, 1);   // dp[i] = length of LIS ending at index i
    vector<int> parent(n, -1); // to reconstruct LIS
    int maxLen = 1, lastIndex = 0;
    // Build LIS DP
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIndex = i;
        }
    }
    // Reconstruct LIS
    vector<int> lis;
    while (lastIndex != -1) {
        lis.push_back(a[lastIndex]);
        lastIndex = parent[lastIndex];
    }
    reverse(lis.begin(), lis.end());
    cout << "\nLength of LIS: " << maxLen << endl;
    cout << "LIS sequence: ";
    for (int x : lis) cout << x << " ";
    cout << endl;
    return 0;
}
//Build the DP table → dp[i] = LIS length ending at i
//Build the Parent array → to reconstruct the LIS later
//Loop through all previous elements → if smaller and new LIS is longer → update
//Track the maximum length (maxLen)
//Backtrack to get the LIS sequence
//Print the output
