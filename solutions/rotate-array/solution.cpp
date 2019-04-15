#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		int n = nums.size();
		if (n == 0)
			return;
		k %= n;
		if (k == 0)
			return;
		//
		// Let i = 0, initially. Move value of entry i to i + k,
		// i + k to i + k * 2, and so forth until we are back at
		// entry i, where we started. Then increment i and start
		// over. How many times do we have to repeat? Intuitively,
		// until the number of moved entries is equal to n.
		//
		int moved = 0;
		for (int i = 0; moved < n; ++i) {
			int val = nums[i];
			int j = i;
			do {
				j += k;
				j %= n;
				swap(nums[j], val);
				++moved;
			} while (j != i);
		}
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {1, 2}, 1},
		{ {1, 2}, 2},
		{ {1, 2, 3}, 1},
		{ {1, 2, 3}, 2},
		{ {1, 2, 3}, 3},
		{ {1, 2, 3, 4}, 1},
		{ {1, 2, 3, 4}, 2},
		{ {1, 2, 3, 4}, 3},
		{ {1, 2, 3, 4}, 4},
		{ {1, 2, 3, 4, 5}, 1},
		{ {1, 2, 3, 4, 5}, 2},
		{ {1, 2, 3, 4, 5}, 3},
		{ {1, 2, 3, 4, 5}, 4},
		{ {1, 2, 3, 4, 5}, 5},
		{ {1, 2, 3, 4, 5, 6}, 1},
		{ {1, 2, 3, 4, 5, 6}, 2},
		{ {1, 2, 3, 4, 5, 6}, 3},
		{ {1, 2, 3, 4, 5, 6}, 4},
		{ {1, 2, 3, 4, 5, 6}, 5},
		{ {1, 2, 3, 4, 5, 6}, 6},
		{ {1, 2, 3, 4, 5, 6, 7}, 1},
		{ {1, 2, 3, 4, 5, 6, 7}, 2},
		{ {1, 2, 3, 4, 5, 6, 7}, 3},
		{ {1, 2, 3, 4, 5, 6, 7}, 4},
		{ {1, 2, 3, 4, 5, 6, 7}, 5},
		{ {1, 2, 3, 4, 5, 6, 7}, 6},
		{ {1, 2, 3, 4, 5, 6, 7}, 7},
	};
	Solution solution;
	for (auto& p: input) {
		auto& nums = p.first;
		auto k = p.second;
		cout << "Input: " << nums << " and k = " << k << endl;
		solution.rotate(nums, k);
		cout << "Output: " << nums << endl << endl;
	}
	return 0;
}
