#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

template <typename T>
struct ListEl {
	ListEl<T>* next;
	T val;
};

template <typename T>
class List {
public:
	List() : last {NULL}, sz {0} {
	}

	void insert(T val) {
		ListEl<T>* inserted = new ListEl<T>;
		inserted->next = last;
		inserted->val = val;
		last = inserted;
		sz++;
	}

	void filter(std::function<bool(const T&)> filter_fn) {
		ListEl<T>* tmp = last;
		ListEl<T>* prev = last;
		while (tmp != NULL) {
			if (!filter_fn(last->val)) {
				if (tmp == last) {
					last = last->next;
				} else {
					delete tmp;
					sz--;
					prev->next = tmp->next;
				}
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}

	void display() {
		for (ListEl<T>* tmp = last; tmp != NULL; tmp = tmp->next) {
			std::cout << (tmp->val).title << " ";
		}
		std::cout << std::endl;
	}

	~List() {
		ListEl<T>* tmp1 = last;
		ListEl<T>* tmp2;
		while (tmp1 != NULL) {
			tmp2 = tmp1->next;
			delete tmp1;
			tmp1 = tmp2;
		}
	}

	int size() {
		return sz;
	}
private:
	ListEl<T>* last;
	int sz;

};

struct Lecture {
	std::string title;
	int start_time;
	int end_time;
};

int main() {
	std::vector<Lecture> lec_list {
		{"Advanced Criminal Law", 1, 2},
		{"Social Psychology", 2, 3},
		{"Introduction to Film", 1, 3},
		{"Spanish 101", 0, 3}
	};

	std::sort(lec_list.begin(), lec_list.end(), [](Lecture a, Lecture b){return a.end_time < b.end_time;});

	std::cout << lec_list.size() << std::endl;
	for (auto i : lec_list) {
		std::cout << i.title << std::endl;
	}

	std::vector<Lecture> result;
	int last_end_time = 0;
	for (auto el : lec_list) {
		if (el.start_time >= last_end_time) {
			result.push_back(el);
			last_end_time = el.end_time;
		}
	}
	
	std::cout << "\nresult" << std::endl;
	for (auto i : result) {
		std::cout << i.title << std::endl;
	}
}
