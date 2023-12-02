#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// priority queue interface
template <typename T>
class PrioQ {
public:
	virtual void insert(T val) = 0;
	virtual T get_top() = 0;
	virtual T pop_top() = 0;
	virtual int find_cond(function<bool(T)>) = 0;
	virtual T get_idx(int) = 0;
	virtual void change_idx(int, T) = 0;
	virtual ~PrioQ() {}
};

// min heap with binary heap
template <class T, class Compare = std::greater<T>>
class BinHeap : public PrioQ<T> {
public:
	BinHeap() {}

	void insert(T val) {
		arr.push_back(val);
		int val_idx = arr.size()-1;
		for (int par_idx = BinHeap::parent_idx(val_idx);
			Compare{}(val, arr[par_idx]);
			par_idx = BinHeap::parent_idx(val_idx)) {
			// swap it with the parent if it is smaller
			swap(val_idx, par_idx);
			val_idx = par_idx;
		}
	}
		
	T get_top() {
		return arr[0];
	}

	T pop_top() {
		T out = arr[0];
		if (arr.size() > 1) {
			arr[0] = arr[arr.size() - 1];
		}
		arr.pop_back();
		heapify(0);
		return out;
	}

	void heapify(int idx) {
		if (arr.size() == 1) {
			return;
		}
		int l_child = BinHeap::left_child(idx);
		int r_child = BinHeap::right_child(idx);

		if (l_child < arr.size() && Compare{}(arr[l_child], arr[idx])) {
			swap(l_child, idx);
			heapify(l_child);
		} else if (r_child < arr.size() && Compare{}(arr[r_child], arr[idx])) {
			swap(r_child, idx);
			heapify(r_child);
		} else {
			// base case for recursion
			return;
		}
	}

	T get_idx(int idx) {
		return arr[idx];
	}

	void change_idx(int idx, T val) {
		arr[idx] = val;
		heapify(idx);
	}


	int find_cond(function<bool(T)> cond) {
		for (int i = 0; i < arr.size(); i++) {
			if (cond(arr[i])) {
				return i;
			}
		}
		return -1;
	}
private:
	vector<T> arr;


	void swap(int i1, int i2) {
		T tmp = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = tmp;
	}

	static int parent_idx(int idx) {
		return (idx - 1) / 2;
	}

	static int left_child(int idx) {
		return idx * 2 + 1;
	}

	static int right_child(int idx) {
		return idx * 2 + 2;
	}
};

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
		map<pair<string, string>, int>& ws,
		PrioQ<pair<string, int>>& pq) {
	//map<string, int> distm;
	vector<string> touched = {src};
	//distm[src] = 0;
	pq.insert({src, 0});
	auto [cur, cur_dist] = pq.pop_top();
	int dist, mindist;
	while (cur != dst) {
		for (string& v : vs[cur]) {
			//dist = distm[cur] + ws[{cur, v}];
			dist = cur_dist + ws[{cur, v}];
			int dist_idx = pq.find_cond(
					[&](pair<string, int> a) {
						return a.first == v;
					});
			if (dist_idx != -1) {
				if (dist < pq.get_idx(dist_idx).second) {
					//distm[v] = dist;
					pq.change_idx(dist_idx, {v, dist});
				}
			} else {
				pq.insert({v, dist});
			}
		}
		touched.push_back(cur);
		auto popped = pq.pop_top();
		cur = popped.first;
		cur_dist = popped.second;
	}
	return cur_dist;
}

class is_node_better {
public:
bool operator()(pair<string, int>& a, pair<string, int>& b) {
	return a.second < b.second;
}
};

int main() {
	vector<string> input = {"AB1", "AC2", "CE1", "BD1", "EF3", "FI1", "EH1", "HG1"};

	auto [vs, ws] = parse_input(input);

	BinHeap<pair<string, int>, is_node_better> pq;
	int min_dist = dijkstra_dist("A", "G", vs, ws, pq);
	std::cout << "Minimum distance: " << min_dist << std::endl;
}
