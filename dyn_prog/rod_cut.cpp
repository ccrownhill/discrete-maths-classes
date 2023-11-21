#include <iostream>
#include <vector>
#include <map>

// rod cutting function should return pair with best price and vector of cuts
// use map for memoization
std::pair<int, int> rod_cut_top_down(int n, std::vector<int>& p, std::map<int, std::pair<int, int>>& memo) {
	if (memo.find(n) == memo.end()) {
		int bestprice = 0, curprice, bestcut;
		for (int i = 1; i <= n; i++) {
			auto [restprice, restcut] = rod_cut_top_down(n - i, p, memo);
			curprice = p[i] + restprice;
			if (curprice > bestprice) {
				bestcut = i;
				bestprice = curprice;
			}
		}
		memo[n] = {bestprice, bestcut};
	}


	return memo[n];
}

std::pair<int, std::vector<int>> run_rod_cut_top_down(int n, std::vector<int>& p) {
	std::map<int, std::pair<int, int>> memo;
	memo[0] = {0, 0};
	memo[1] = {p[1], 1};

	auto [price, cut] = rod_cut_top_down(n, p, memo);

	std::vector<int> cuts {};
	while (n > 0) {
		cut = memo[n].second;
		cuts.push_back(cut);
		n -= cut;
	}

	return {price, cuts};

}

std::pair<int, std::vector<int>> rod_cut_bot_up(int n, std::vector<int>& p) {
	std::vector<std::pair<int, int>> bestprices = {{0, 0}, {p[1], 1}};

	for (int len = 2; len <= n; len++) {
		int bestprice = 0, bestcut, curprice;
		for (int i = 1; i <= len; i++) {
			curprice = p[i] + bestprices[len-i].first;
			if (curprice > bestprice) {
				bestprice = curprice;
				bestcut = i;
			}
		}
		bestprices.push_back({bestprice, bestcut});
	}

	// generate vector of cuts
	std::vector<int> cuts {};
	int cut, len = n;
	for (; len > 0; len -= cut) {
		cut = bestprices[len].second;
		cuts.push_back(cut);
	}
	return {bestprices[n].first, cuts};
}

std::pair<int, std::vector<int>> rod_cut_bot_up_cutprice(int n, std::vector<int>& p, int cutprice = 0) {
	std::vector<std::pair<int, int>> bestprices = {{0, 0}, {p[1], 1}};

	for (int len = 2; len <= n; len++) {
		int bestprice = 0, bestcut, curprice;
		for (int i = 1; i <= len; i++) {
			curprice = p[i] + bestprices[len-i].first;
			if (i != len) {
				curprice -= cutprice;
			}
			if (curprice > bestprice) {
				bestprice = curprice;
				bestcut = i;
			}
		}
		bestprices.push_back({bestprice, bestcut});
	}

	// generate vector of cuts
	std::vector<int> cuts {};
	int cut, len = n;
	for (; len > 0; len -= cut) {
		cut = bestprices[len].second;
		cuts.push_back(cut);
	}
	return {bestprices[n].first, cuts};
}


void display_rod_cut_results(std::pair<int, std::vector<int>> res) {
	std::cout << "Best price: " << res.first << std::endl;
	std::cout << "Cuts: ";
	for (auto cut : res.second) {
		std::cout << cut << " ";
	}
	std::cout << std::endl;
}

int main() {
// 	std::vector<int> p {0, 1, 5, 8, 9, 10, 17, 17, 20};
	std::vector<int> p {0, 2, 7, 12, 15, 18, 19, 23, 25, 26, 31};

	auto top_down_res = run_rod_cut_top_down(10, p);	
	auto bot_up_res = rod_cut_bot_up_cutprice(10, p, 6);

	std::cout << "Top down:" << std::endl;
	display_rod_cut_results(top_down_res);
	std::cout << std::endl;
	std::cout << "Bottom up:" << std::endl;
	display_rod_cut_results(bot_up_res);

}
