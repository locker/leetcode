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
	// Given an array with the number of times each candidate should
	// be added to the result (chosen), return the resulting array.
	vector<int> getResult(const vector<int>& candidates,
			      const vector<int>& chosen) {
		vector<int> result;
		int size = candidates.size();
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < chosen[i]; ++j)
				result.push_back(candidates[i]);
		}
		return result;
	}
public:
	vector<vector<int>> combinationSum(const vector<int>& candidates,
					   int target) {
		vector<vector<int>> result_set;
		int size = candidates.size();
		if (size == 0)
			return result_set;

		// Element i of this array stores the number of times
		// candidate i is added to the result.
		vector<int> chosen(size);

		int sum = 0;
		do {
			for (int i = 0; i < size; ++i) {
				if (sum + candidates[i] <= target) {
					sum += candidates[i];
					++chosen[i];
					break;
				}
				sum -= candidates[i] * chosen[i];
				chosen[i] = 0;
			}
			if (sum == target) {
				auto result = getResult(candidates, chosen);
				result_set.push_back(move(result));
			}
		} while (sum > 0);

		return result_set;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 },
		{ {1}, 2 },
		{ {3}, 3 },
		{ {4, 2}, 6 },
		{ {2, 3, 5}, 8 },
		{ {2, 3, 6, 7}, 7 },
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& candidates = p.first;
		auto target = p.second;
		cout << "Input: candidates = " << candidates <<
			", target = " << target << endl << "Output:" << endl <<
			solution.combinationSum(candidates, target) <<
			endl << endl;
	}
	return 0;
}
