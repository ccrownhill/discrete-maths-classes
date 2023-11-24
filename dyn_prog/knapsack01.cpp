#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Item {
	std::string name;
	int weight;
	int value;
};

int main() {
	int max_weight = 50;
	std::vector<Item> valuables = {{"Crown", 10, 60}, {"Treasure", 20, 100}, {"Dragon", 30, 120}};

	std::vector<std::vector<int>> best_prices (max_weight+1);

	int best_price, cur_price;
	for (int w = 0; w <= max_weight; w++) {
		for (int i = 0; i < valuables.size(); i++) {
			if (w >= valuables[i].weight) {
				if (i > 0)
					best_prices[w].push_back(std::max(valuables[i].value + best_prices[w - valuables[i].weight][i-1], best_prices[w][i-1]));
				else
					best_prices[w].push_back(valuables[i].value);
			} else if (i > 0) {
				best_prices[w].push_back(best_prices[w][i-1]);
			} else {
				best_prices[w].push_back(0);
			}
		}
	}

	std::cout << best_prices[max_weight][valuables.size()-1] << std::endl;
}
