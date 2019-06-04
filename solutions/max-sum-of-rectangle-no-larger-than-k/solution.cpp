#include <iomanip>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& matrix)
{
	out << '[' << endl;
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		out << ' ' << ' ';
		for (auto cell = row->begin(); cell != row->end(); ++cell)
			out << setw(3) << *cell << ',';
		out << endl;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>>& m, int k) {
		//
		// First, compute sums of each row so that m[r][c] stores
		// the sum of values m[r][<=c]. This way we can calculate
		// the sum of row r of any sub-matrix r1,c1,r2,c2 as
		//
		//   m[r][c2] - m[r][c1-1]    if c1 > 0
		//   m[r][c2]                 otherwise
		//
		//   r1 <= r <= r2
		//
		// in O(1) time.
		//
		int n_rows = m.size();
		int n_cols = m[0].size();
		for (int r = 0; r < n_rows; ++r) {
			for (int c = 1; c < n_cols; ++c)
				m[r][c] += m[r][c - 1];
		}
		//
		// Now iterate over all possible sub-matrix columns
		//
		//   0 <= c1 <= c2 <= n_cols
		//
		// For each pair find start and end rows r1 and r2 such
		// that sub-matrix r1,c1,r2,c2 sums as close to <= k as
		// possible. Keep track of the max sum.
		//
		// If we iterated over all possible combinations of r1
		// and r2, we'd end up with quartic complexity
		//
		//   n_rows^2 * n_cols^2
		//
		// We can optimize: since we need to find max sum <= k
		// we can keep all found sums of values <= r in a tree
		// and look up the min sum such that
		//
		//   sum(0, r1) >= sum(0, r2) - k
		//
		// This is equivalent to finding the max sum such that
		//
		//   sum(r1, r2) <= k
		//
		// This gives us time complexity
		//
		//   n_rows * log(n_rows) * n_cols^2
		//
		set<int> sums;
		int found = false;
		int max_sum = k + 1;
		for (int c1 = 0; c1 < n_cols; ++c1) {
			for (int c2 = c1; c2 < n_cols; ++c2) {
				int sum = 0;
				for (int r = 0; r < n_rows; ++r) {
					sums.insert(sum);
					int row_sum = m[r][c2];
					if (c1 > 0)
						row_sum -= m[r][c1 - 1];
					sum += row_sum;
					auto it = sums.lower_bound(sum - k);
					if (it == sums.end())
						continue;
					int sub_sum = sum - *it;
					if (sub_sum == k) {
						// No need to continue if we've
						// found an exact match.
						return sub_sum;
					}
					if (!found || sub_sum > max_sum) {
						max_sum = sub_sum;
						found = true;
					}
				}
				sums.clear();
			}
		}
		return max_sum;
	}
};

int main()
{
	pair<vector<vector<int>>, int> input[] = {

		{ {{1, 2, 3}}, 2 }, // 2

		{ {{1, -2, 3}}, 2 }, // 2

		{ {{2, 2, -5, 2}}, 1 }, // 1

		{ {{2}, {2}, {-5}, {1}}, 1}, // 1

		{ {{1,  0, 1},
		   {0, -2, 3}}, 2 }, // 2

		{ {{ 5, -3,  5},
		   {-4, -4,  1},
		   {-3,  4,  5},
		   { 4,  5, -4}}, 8 }, // 8

		{ {{ 5, -4, -3,  4},
		   {-3, -4,  4,  5},
		   { 5,  1,  5, -4}}, 8 }, // 8
	};
	Solution solution;
	for (auto& p: input) {
		auto& matrix = p.first;
		int k = p.second;
		cout << "Input: matrix = " << matrix << ", k = " << k << endl;
		cout << "Output: " << solution.maxSumSubmatrix(matrix, k) <<
			endl << endl;
	}
	return 0;
}
