#include <iostream>
#include <unordered_set>
#include <tuple>
#include <vector>

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
public:
	vector<int> intersect(const vector<int>& nums1,
			      const vector<int>& nums2) {
		unordered_multiset<int> nums(nums1.begin(), nums1.end());
		vector<int> result;
		for (int num : nums2) {
			auto it = nums.find(num);
			if (it != nums.end()) {
				nums.erase(it);
				result.push_back(num);
			}
		}
		return result;
	}
};

int main()
{
	const tuple<vector<int>, vector<int>, vector<int>> test_data[] = {
		{{1}, {2}, {}},
		{{1}, {1}, {1}},
		{{1}, {1, 1}, {1}},
		{{1, 1}, {1, 1}, {1, 1}},
		{{2, 1}, {1, 1}, {1}},
		{{2, 1}, {1, 2}, {1, 2}},
		{{1, 2, 2, 1}, {2, 2}, {2, 2}},
		{{4, 9, 5}, {9, 4, 9, 8, 4}, {9, 4}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums1, nums2, expected] : test_data) {
		auto result = solution.intersect(nums1, nums2);
		cout << nums1 << " & " << nums2 << " = " << result << endl;
		if (unordered_multiset<int>(result.begin(), result.end()) !=
		    unordered_multiset<int>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
