#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

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
	string makeRange(int first, int last) {
		if (first == last)
			return to_string(first);
		return to_string(first) + "->" + to_string(last);
	}
public:
	vector<string> summaryRanges(const vector<int>& nums) {
		vector<string> ranges;
		int prev = 0;
		int first = 0;
		bool started = false;
		for (int x : nums) {
			if (started && x == prev + 1) {
				prev = x;
				continue;
			}
			if (started)
				ranges.push_back(makeRange(first, prev));
			first = prev = x;
			started = true;
		}
		if (started)
			ranges.push_back(makeRange(first, prev));
		return ranges;
	}
};

int main()
{
	pair<vector<int>, vector<string>> test_data[] = {
		{{}, {}},
		{{1}, {"1"}},
		{{1, 2}, {"1->2"}},
		{{1, 2, 3}, {"1->3"}},
		{{0, 1, 2, 4, 5, 7}, {"0->2", "4->5", "7"}},
		{{0, 2, 3, 4, 6, 8, 9}, {"0", "2->4", "6", "8->9"}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		auto result = solution.summaryRanges(nums);
		cout << nums << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
