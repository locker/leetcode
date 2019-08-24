#include <algorithm>
#include <iostream>
#include <limits>
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
	int minSwap(const vector<int>& A, const vector<int>& B) {
		//
		// At iteration i, swap_last (keep_last) stores the minimum
		// number of swaps required to make sequences A[0..i] and
		// B[0..i] strictly increasing in case A[i] and B[i] are
		// (are not) swapped.
		//
		int swap_last = 1;
		int keep_last = 0;
		for (int i = 1; i < static_cast<int>(A.size()); ++i) {
			int next_swap_last = numeric_limits<int>::max();
			int next_keep_last = numeric_limits<int>::max();
			if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
				next_keep_last = min(next_keep_last, keep_last);
				next_swap_last = min(next_swap_last, 1 + swap_last);
			}
			if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
				next_keep_last = min(next_keep_last, swap_last);
				next_swap_last = min(next_swap_last, 1 + keep_last);
			}
			swap_last = next_swap_last;
			keep_last = next_keep_last;
		}
		return min(swap_last, keep_last);
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{1}, {1}}, // 0
		{{5}, {2}}, // 0
		{{1, 2}, {3, 5}}, // 0
		{{5, 2}, {1, 10}}, // 1
		{{1, 5, 3}, {1, 2, 6}}, // 1
		{{1, 3, 5, 4}, {1, 2, 3, 7}}, // 1
		{{1, 20, 3, 40}, {10, 2, 30, 4}}, // 2
	};
	Solution solution;
	for (auto& p: input) {
		cout << p.first << ", " << p.second << " => " <<
			solution.minSwap(p.first, p.second) << endl;
	}
	return 0;
}
