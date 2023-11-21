#include <iostream>
#include <vector>
#include <string>

std::pair<int, std::string> lcs(std::string& a, std::string& b) {
	std::vector<std::vector<int>> dp (a.size()+1);
	std::vector<int> row (b.size()+1);
	std::string sub;
	for (int i = 0; i <= a.size(); i++) {
		for (int j = 0; j <= b.size(); j++) {
			if (i == 0 || j == 0) {
				dp[i].push_back(0);
			} else if (a[i-1] == b[j-1]) {
				dp[i].push_back(1 + dp[i-1][j-1]);
			} else {
				if (dp[i-1][j] > dp[i][j-1]) {
					dp[i].push_back(dp[i-1][j]);
				} else {
					dp[i].push_back(dp[i][j-1]);
				}
			}
		}
	}
	std::string longest_string;
	for (int bi = 0; bi < b.size(); bi++) {
		if (dp[a.size()][bi+1] > dp[a.size()][bi]) {
			longest_string += b[bi];
		}
	}


	return {dp[a.size()][b.size()], longest_string};
}

int main() {
  	std::string a = "aabaababaa";
  	std::string b = "ababaaabb";

	std::cout << "A: " << a << std::endl;
	std::cout << "B: " << b << std::endl;

	auto [outlen, longest_string] = lcs(a, b);
	std::cout << "Longest common subword: " << longest_string << " (len: "
		<< outlen << ")" << std::endl;
}
