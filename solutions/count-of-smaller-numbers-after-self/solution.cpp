#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class FenwickTree {
private:
	vector<int> data;

	int getParent(int i) const {
		return i - (i & (-i));
	}

	int getNext(int i) const {
		return i + (i & (-i));
	}

public:
	FenwickTree(int n) : data(n + 1, 0) {
	}

	int getSum(int i) const {
		int sum = 0;
		++i;
		while (i > 0) {
			sum += data[i];
			i = getParent(i);
		}
		return sum;
	}

	void update(int i, int v) {
		++i;
		while (i < static_cast<int>(data.size())) {
			data[i] += v;
			i = getNext(i);
		}
	}
};

class Solution {
public:
	vector<int> countSmaller(const vector<int>& nums) {
		vector<int> counts(nums.size());
		int min = *min_element(nums.begin(), nums.end());
		int max = *max_element(nums.begin(), nums.end());
		FenwickTree ft(max - min + 1);
		for (int i = nums.size() - 1; i >= 0; --i) {
			int v = nums[i] - min;
			ft.update(v, 1);
			counts[i] = ft.getSum(v - 1);
		}
		return counts;
	}
};

int main()
{
	const pair<vector<int>, vector<int>> test_data[] = {
		{{1}, {0}},
		{{1, 1}, {0, 0}},
		{{-1, -1}, {0, 0}},
		{{1, 2}, {0, 0}},
		{{2, 1}, {1, 0}},
		{{5, 2, 6, 1}, {2, 1, 1, 0}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		auto result = solution.countSmaller(nums);
		cout << nums << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
