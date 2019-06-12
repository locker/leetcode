#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_set>
#include <utility>

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

namespace std {
template<> struct hash<pair<int, int>> {
	size_t operator()(const pair<int, int>& p) const {
		return p.first ^ (p.second << 1);
	}
};
}

class Solution {
	// Return digit count among which to search the next digit.
	// n1 - size of the first array
	// n2 - size of the second array
	// i1 - position in the first array
	// i2 - position in the second array
	// k - number of digits in the target number
	// l - number of digits appended to the target number
	int getSpan(int n1, int n2, int i1, int i2, int k, int l) {
		return n1 + n2 - i1 - i2 - k + l + 1;
	}
	// Return the max digit in range [start, start + span) or -1
	// if the range is empty.
	int findMaxDigit(const vector<int>& nums, int start, int span) {
		int digit = -1;
		int n = nums.size();
		for (int i = start; i < min(n, start + span); ++i)
			digit = max(digit, nums[i]);
		return digit;
	}
	// Return the index of the first digit equal to the given one
	// in range [start, start + span) or -1 if not found.
	int findDigitIdx(const vector<int>& nums,
			 int start, int span, int digit) {
		int n = nums.size();
		for (int i = start; i < min(n, start + span); ++i) {
			if (nums[i] == digit)
				return i;
		}
		return -1;
	}
public:
	vector<int> maxNumber(const vector<int>& nums1,
			      const vector<int>& nums2, int k) {
		if (k == 0)
			return {};

		int n1 = nums1.size();
		int n2 = nums2.size();

		unordered_set<pair<int, int>> todo, todo_next;
		todo.emplace(0, 0);

		vector<int> result(k);
		for (int l = 0; l < k; ++l) {
			// Find max digit.
			int max_digit = 0;
			for (const auto& p: todo) {
				int i1 = p.first;
				int i2 = p.second;
				int span = getSpan(n1, n2, i1, i2, k, l);
				max_digit = max(max_digit,
						findMaxDigit(nums1, i1, span));
				max_digit = max(max_digit,
						findMaxDigit(nums2, i2, span));
			}
			// Advance to max digit.
			for (const auto& p: todo) {
				int i1 = p.first;
				int i2 = p.second;
				int span = getSpan(n1, n2, i1, i2, k, l);
				int j1 = findDigitIdx(nums1, i1, span, max_digit);
				int j2 = findDigitIdx(nums2, i2, span, max_digit);
				if (j1 >= 0)
					todo_next.emplace(j1 + 1, i2);
				if (j2 >= 0)
					todo_next.emplace(i1, j2 + 1);
			}
			swap(todo, todo_next);
			todo_next.clear();
			result[l] = max_digit;
		}
		return result;
	}
};

int main()
{
	tuple<vector<int>, vector<int>, int> input[] = {
		{{3, 9}, {8, 9}, 3}, // [9, 8, 9]
		{{6, 7}, {6, 0, 4}, 5}, // [6, 7, 6, 0, 4]
		{{3, 4, 6, 5}, {9, 1, 2, 5, 8, 3}, 5}, // [9, 8, 6, 5, 3]
		{{3, 8, 5, 3, 4}, {8, 7, 3, 6, 8}, 5}, // [8, 8, 8, 5, 4]
		{{0, 1, 2, 1, 2}, {0, 1, 2, 1, 1}, 10},
		// [0, 1, 2, 1, 2, 0, 1, 2, 1, 1]
		{{2, 5, 6, 4, 4, 0}, {7, 3, 8, 0, 6, 5, 7, 6, 2}, 15},
		// [7, 3, 8, 2, 5, 6, 4, 4, 0, 6, 5, 7, 6, 2, 0]
	};
	Solution solution;
	for (const auto& t: input) {
		auto& nums1 = get<0>(t);
		auto& nums2 = get<1>(t);
		int k = get<2>(t);
		cout << "Input: nums1 = " << nums1 << ", nums2 = " <<
			nums2 << ", k = " << k << endl << "Output: " <<
			solution.maxNumber(nums1, nums2, k) << endl;
	}
	return 0;
}
