//LCS(最長共通部分列) 
//O(ST)
int LCS(string s, string t){
	int n = s.size(), m = t.size() ;
	vector<vector<int>> dp(n + 4 , vector<int> (m + 4, 0));
	rep(i, n)rep(j, m){
		if(s[i] == t[j]){
			dp[i+1][j+1]=dp[i][j]+1;
		}
		else {
			dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
		}
	}
	return dp[n][m] ;
}

//LCS(最長共通部分列) 
//O(ST) stringも返す
string LCS_string(string s, string t){
	int n = s.size(), m = t.size() ;
	vector<vector<int>> dp(n + 4 , vector<int> (m + 4, 0));
	rep(i, n)rep(j, m){
		if(s[i] == t[j]){
			dp[i+1][j+1]=dp[i][j]+1;
		}
		else {
			dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
		}
	}
	string res = "";
	int i = s.size(), j = t.size();
	while (i > 0 && j > 0) {
		if (dp[i][j] == dp[i - 1][j - 1] + 1 && s[i - 1] == t[j - 1]) {
			res = s[i - 1] + res ;
			--i;--j;
		}
		else if (dp[i][j] == dp[i - 1][j]) {
			--i;
		}
		else if (dp[i][j] == dp[i][j - 1]) {
			--j;
		}
	}
	return res ;
}
