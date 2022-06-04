#include <cassert>
#include <iostream>
#include <tuple>
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

class NumArray {
private:
	vector<int> sums;
public:
	NumArray(vector<int> nums) {
		assert(!nums.empty());
		sums = move(nums);
		for (auto it = sums.begin() + 1; it != sums.end(); ++it)
			*it += *(it - 1);
	}

	int sumRange(int left, int right) {
		assert(left >= 0);
		assert(right < static_cast<int>(sums.size()));
		assert(right >= left);
		int sum = sums[right];
		if (left > 0)
			sum -= sums[left - 1];
		return sum;
	}
};

int main()
{
	const tuple<vector<int>, int, int, int> test_data[] = {
		{{1}, 0, 0, 1},
		{{1, 10}, 0, 0, 1},
		{{1, 10}, 1, 1, 10},
		{{1, 10}, 0, 1, 11},
		{{-2, 0, 3, -5, 2, -1}, 0, 2, 1},
		{{-2, 0, 3, -5, 2, -1}, 2, 5, -1},
		{{-2, 0, 3, -5, 2, -1}, 0, 5, -3},
	};
	bool success = true;
	for (const auto& [nums, left, right, expected] : test_data) {
		int result = NumArray(nums).sumRange(left, right);
		cout << "nums=" << nums << ", range=[" << left <<
			"," << right << "] -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
