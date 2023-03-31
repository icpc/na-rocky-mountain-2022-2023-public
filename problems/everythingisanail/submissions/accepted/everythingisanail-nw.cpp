#include<bits/stdc++.h>
using namespace std;
int t;
int tasks[300300];
int dp[300300][3][8];
int solve(int i, int tool, int used) {
    if (i < 0) return 0;
    int &x = dp[i][tool][used];
    if (x == -1)
        if (tool == tasks[i])
            x = max(x, solve(i-1, tool, used)+1);
        else for (int j = 0; j < 3; j++)
            if (~used>>j&1 || j==tool)
                x = max(x, solve(i-1, j, used|(1<<j)) + (tasks[i] == j));
    return x;
}
int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        cin >> tasks[i];
    memset(dp, -1, sizeof dp);
    cout << max(solve(t-1, 0, 1), max(solve(t-1, 1, 2), solve(t-1, 2, 4))) << endl;
}
