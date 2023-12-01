#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <algorithm>

template <typename T>
void disp_cont(T cont) {
	for (auto el : cont) {
		std::cout << el << ",";
	}
	std::cout << std::endl;
}

std::list<int> dyn_prog(int value, std::vector<int> coins) {
	std::vector<std::vector<std::list<int>>> dp(value+1);

	int val;
	for (int v = 0; v <= value; v++) {
		for (int c = 0; c <= coins.size(); c++) {
			if (v == 0 || c == 0) {
				dp[v].push_back({});
			} else if (coins[c-1] > v) {
				dp[v].push_back(dp[v][c-1]);
			} else {
				std::list<int> new_opt = {};
				val = 0;
				for (int k = coins[c-1]; k <= v; k += coins[c-1]) {
					new_opt.push_back(coins[c-1]);
					val += coins[c-1];
				}
				if (v - val >= 0)
					new_opt.insert(new_opt.end(), dp[v-val][c-1].begin(), dp[v-val][c-1].end());
				if (dp[v][c-1].size() == 0 || new_opt.size() < dp[v][c-1].size()) {
					dp[v].push_back(new_opt);
				} else {
					dp[v].push_back(dp[v][c-1]);
				}
			}
		}
	}

	return dp[value][coins.size()];
}

std::list<int> greedy(int value, std::vector<int> coins) {
	std::list<int> out;
	for (int i = coins.size()-1; i >= 0; i--) {
		while (coins[i] <= value) {
			out.push_back(coins[i]);
			value -= coins[i];
		}
	}
	return out;
}

bool is_canonical(std::vector<int> coins) {
	int max_coin = *std::max_element(coins.begin(), coins.end());
	std::list<int> dyn_sol;
	std::list<int> greedy_sol;
	for (int i = 0; i <= 2*max_coin; i++) {
		dyn_sol = dyn_prog(i, coins);
		greedy_sol = greedy(i, coins);
		if (dyn_sol.size() != greedy_sol.size()) {
			return false;
		}
	}
	return true;
}

int main() {
	std::vector<int> coins = {1, 2, 4, 8, 18, 53};
	std::list<int> dynsol = dyn_prog(25, coins);
	std::list<int> greedysol = greedy(25, coins);
	std::cout << is_canonical(coins) << std::endl;
}
