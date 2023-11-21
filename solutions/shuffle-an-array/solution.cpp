#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
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

class Solution {
private:
	vector<int> nums_;
public:
	Solution(vector<int> nums) {
		nums_ = move(nums);
	}

	vector<int> reset() {
		return nums_;
	}

	vector<int> shuffle() {
		vector<int> nums = nums_;
		int n = nums.size();
		for (int i = 0; i < n - 1; ++i) {
			int j = rand() % (n - i);
			swap(nums[i], nums[i + j]);
		}
		return nums;
	}
};

} // namespace

int main()
{
	Solution solution({1, 2, 3, 4, 5, 6, 7, 8, 9});
	for (int i = 0; i < 5; ++i) {
		cout << solution.shuffle() << endl;
		cout << solution.reset() << endl;
	}
	return 0;
}
