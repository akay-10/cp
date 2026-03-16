// Longest Common subsequence
// Child Problems : longest common substring(put dp[][] = 0 in the else part), longest palindromic subsequence(find lsc in s and reverse.s)
int lcs(string a, string b, int a.len, int b.len){
    int dp[a.len + 1][b.len+1] = {0}
    for (i = 1 to a.len) {
        for(j=1 to b.len){
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[a.len][b.len]
}