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


private:
	vector<T> arr;

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
	map<int, vector<int>> vs;
	map<pair<int, int>, double> ws;
};


int my_gcd(int a, int b) {
  int c = 0;
  if (a < b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
  while ((c = a % b) != 0) {
    a = b;
    b = c;
  }
  return b;
}

Data generate_gcd_input() {
  Data out;
  double weight, gcd;
  vector<int> conns;
  for (int i = 2; i <= 50; i++) {
    out.vs[i] = {};
    for (int j = 2; j <= 50; j++) {
      weight = 1.0 / ((double)(my_gcd(i, j)));
      if (weight < 1) {
        out.vs[i].push_back(j);
        out.ws[{i, j}] = weight;
      }
    }
  }
  return out;
}

double dijkstra_dist(int src, int dst,
	map<int, vector<int>>& vs,
	map<pair<int, int>, double>& ws,
	PrioQ<pair<int, double>>& pq) {

	pq.insert({src, 0.0});
	auto [cur, cur_dist] = pq.pop_top();
	double dist, mindist;
	while (cur != dst) {
		for (int v : vs[cur]) {
			dist = cur_dist + ws[{cur, v}];
      pq.insert({v, dist});
		}
		auto popped = pq.pop_top();
		cur = popped.first;
		cur_dist = popped.second;
	}
	return cur_dist;
}


class is_node_better {
public:
bool operator()(pair<int, double>& a, pair<int, double>& b) {
	return a.second < b.second;
}
};

int main() {
	auto [vs, ws] = generate_gcd_input();

	BinHeap<pair<int, double>, is_node_better> pq;
	double min_dist = dijkstra_dist(9, 50, vs, ws, pq);
	std::cout << "Minimum distance: " << min_dist << std::endl;
}
