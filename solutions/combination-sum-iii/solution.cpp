#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T> v)
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

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>> v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> result_set;

		const int MAX = 9;
		if (k > MAX)
			return result_set;

		int sum = 0;
		vector<int> result(k);

		int i = 0;
		do {
			//
			// Fill the resulting array in ascending order to
			// ensure absence of duplicates in the result set.
			//
			if (i < k - 1) {
				result[i] = i > 0 ? result[i - 1] + 1 : 1;
				if (result[i] <= MAX) {
					sum += result[i++];
					continue;
				}
			} else {
				//
				// If it is the last entry, we know exactly
				// what it should be equal to. Append the
				// result provided the last entry does not
				// violate the ascending order.
				//
				result[i] = n - sum;
				if (result[i] <= MAX &&
				    (i == 0 || result[i - 1] < result[i]))
					result_set.push_back(result);
			}
			//
			// Iterate backwards until we find an integer we can
			// increment, then repeat.
			//
			for (i = i - 1; i >= 0; --i) {
				sum -= result[i];
				//
				// Max number of integers we can append after
				// this one without violating the ascending
				// order equals
				//
				//   MAX - (result_i + 1)
				//
				// No need to go on if it is less than the
				// number of entries left, i.e.
				//
				//   k - i - 1
				//
				if (MAX - (result[i] + 1) < k - i - 1)
					continue;
				//
				// Min sum we can get equals:
				//
				//   sum + (result_i + 1) +
				//         (result_i + 2) +
				//         ...
				//         (result_i + k - i) =
				//
				//   sum + (2 * result_i + k - i - 1) *
				//                            (k - i) / 2
				//
				// No need to go on if it is greater than n.
				//
				if (sum + (2 * result[i] + k - i + 1) *
							(k - i) / 2 > n)
					continue;
				++result[i];
				sum += result[i++];
				break;
			}
		} while (i > 0);

		return result_set;
	}
};

int main()
{
	pair<int, int> input[] = {
		{1, 2},
		{2, 3},
		{3, 7},
		{3, 9},
		{4, 3},
		{4, 10},
		{2, 18},
		{10, 20},
	};
	Solution solution;
	for (auto& p: input) {
		int k = p.first;
		int n = p.second;
		cout << "Input: k = " << k << ", n = " << n << endl <<
			"Output:" << endl << solution.combinationSum3(k, n) <<
			endl << endl;
	}
	return 0;
}
