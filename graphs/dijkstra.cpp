#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Data {
	map<string, vector<string>> vs;
	map<pair<string, string>, int> ws;
};

Data parse_input(vector<string> input) {
	Data out;
	string src, dest;
	int weight;
	for (string& s : input) {
		src = s[0];
		dest = s[1];
		weight = s[2] - '0';
		if (out.vs[src].size() == 0)
			out.vs[src] = {dest};
		else
			out.vs[src].push_back(dest);
		if (out.vs[dest].size() == 0)
			out.vs[dest] = {src};
		else
			out.vs[dest].push_back(src);
		out.ws[{src, dest}] = weight;
		out.ws[{dest, src}] = weight;
	}
	return out;
}

int dijkstra_dist(string src, string dst,
		map<string, vector<string>>& vs,
		map<pair<string, string>, int>& ws) {
	map<string, int> distm;
	vector<string> touched = {src};
	distm[src] = 0;
	string cur = src;
	int dist, mindist;
	while (cur != dst) {
		for (string& v : vs[cur]) {
			dist = distm[cur] + ws[{cur, v}];
			if (distm.find(v) != distm.end()) {
				if (dist < distm[v])
					distm[v] = dist;
			} else {
				distm[v] = dist;
			}
		}
		touched.push_back(cur);
		mindist = -1;
		for (const auto& [v, conns] : vs) {
			if (find(touched.begin(), touched.end(), v) == touched.end()
				&& distm.find(v) != distm.end()
				&& (distm[v] < mindist || mindist == -1)) {
				mindist = distm[v];
				cur = v;
			}
		}
		if (mindist == -1) {
			return -1; // no path found
		}
	}
	return distm[dst];
}

int main() {
	vector<string> input = {"AB1", "AC2", "CE1", "BD1", "EF3", "FI1", "EH1", "HG1"};

	auto [vs, ws] = parse_input(input);

	int min_dist = dijkstra_dist("A", "G", vs, ws);
	std::cout << "Minimum distance: " << min_dist << std::endl;
}
