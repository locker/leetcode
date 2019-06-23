#include <iostream>
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
	int findJudge(int n, const vector<vector<int>>& trust) {
		if (n == 0)
			return -1;
		if (n == 1)
			return 1;

		// Candidate for the judge: the one who is trusted by
		// everybody else.
		int candidate = -1;

		// Element i (0-base) stores the number of people
		// who trust person i + 1.
		vector<int> indegree(n);
		for (const auto& t: trust) {
			int i = t[1] - 1;
			if (++indegree[i] == n - 1) {
				candidate = i + 1;
				break;
			}
		}

		// Check that the candidate trusts nobody.
		if (candidate >= 0) {
			for (const auto& t: trust) {
				if (t[0] == candidate) {
					candidate = -1;
					break;
				}
			}
		}
		return candidate;
	}
};

int main()
{
	pair<int, vector<vector<int>>> input[] = {
		{0, {}}, // -1
		{1, {}}, // 1
		{2, {}}, // -1
		{2, {{1, 2}}}, // 2
		{3, {{1, 2}, {2, 3}}}, // -1
		{3, {{1, 3}, {2, 3}}}, // 3
		{3, {{1, 3}, {2, 3}, {3, 1}}}, // -1
		{4, {{1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3}}}, // 3
	};
	Solution solution;
	for (const auto& p: input) {
		int n = p.first;
		const auto& trust = p.second;
		int judge = solution.findJudge(n, trust);
		cout << "Input: N = " << n << ", trust = " << trust << endl <<
			"Output: " << judge << endl;
	}
	return 0;
}
