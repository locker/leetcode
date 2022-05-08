#include <iostream>
#include <vector>
#include <utility>

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

class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int count = 0;
		auto out = nums.begin();
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			if (*it != 0) {
				if (out != it)
					*out = *it;
				++out;
			} else {
				++count;
			}
		}
		while (count > 0) {
			*out = 0;
			++out;
			--count;
		}
	}
};

int main()
{
	const pair<vector<int>, vector<int>> test_data[] = {
		{{}, {}},
		{{0}, {0}},
		{{1}, {1}},
		{{1, 0}, {1, 0}},
		{{0, 1}, {1, 0}},
		{{0, 0, 1}, {1, 0, 0}},
		{{0, 1, 0}, {1, 0, 0}},
		{{0, 1, 0, 3, 12}, {1, 3, 12, 0, 0}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [input, expected] : test_data) {
		auto nums = input;
		solution.moveZeroes(nums);
		cout << input << " -> " << nums << endl;
		if (nums != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
