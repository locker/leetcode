#include <algorithm>
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
	// Given an array each element of which denotes the number of
	// times the candidate with the same index is chosen, return
	// the resulting array.
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
	vector<vector<int>> combinationSum2(const vector<int>& candidates,
					    int target) {
		vector<vector<int>> result_set;
		if (candidates.empty())
			return result_set;

		// First, remove and count duplicates.
		auto candidates_wo_dups = candidates;
		sort(candidates_wo_dups.begin(), candidates_wo_dups.end());
		int size = 1;
		vector<int> candidate_count;
		candidate_count.push_back(1);
		for (auto it = candidates_wo_dups.begin() + 1;
		     it != candidates_wo_dups.end(); ++it) {
			if (*it != *(it - 1)) {
				candidates_wo_dups[size++] = *it;
				candidate_count.push_back(1);
			} else
				++candidate_count.back();
		}
		candidates_wo_dups.resize(size);

		// Now simply enumerate all possible combinations and
		// add those that sum to the target to the result set.

		// Array entry i denotes the number of times candidate i
		// has been chosen.
		vector<int> chosen(size);

		int sum = 0;
		do {
			for (int i = 0; i < size; ++i) {
				if (chosen[i] < candidate_count[i] &&
				    sum + candidates_wo_dups[i] <= target) {
					sum += candidates_wo_dups[i];
					++chosen[i];
					break;
				} else {
					sum -= candidates_wo_dups[i] * chosen[i];
					chosen[i] = 0;
				}
			}
			if (sum == target) {
				auto result = getResult(candidates_wo_dups, chosen);
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
		{ {2, 5, 2, 1, 2}, 5 },
		{ {10, 1, 2, 7, 6, 1, 5}, 8 },
		{ {4, 4, 2, 1, 4, 2, 2, 1, 3}, 6 },
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& candidates = p.first;
		auto target = p.second;
		cout << "Input: candidates = " << candidates <<
			", target = " << target << endl << "Output:" << endl <<
			solution.combinationSum2(candidates, target) <<
			endl << endl;
	}
	return 0;
}
