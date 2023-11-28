#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

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
	vector<vector<int>> reconstructQueue(vector<vector<int>> people) {
		const int n = people.size();
		sort(people.begin(), people.end(),
		     [](const vector<int>& a, const vector<int>& b) {
				if (a[0] == b[0])
					return a[1] < b[1];
				return a[0] > b[0];
		});
		for (int i = 1; i < n; ++i) {
			for (int j = i; j > 0; --j) {
				if (j == people[j][1])
					break;
				swap(people[j], people[j - 1]);
			}
		}
		return people;
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<int>>, vector<vector<int>>> test_data[] = {
		{
			{{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}},
			{{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}},
		},
		{
			{{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}},
			{{4,0},{5,0},{2,2},{3,2},{1,4},{6,0}},
		},
		{
			{{2,4},{3,4},{9,0},{0,6},{7,1},{6,0},{7,3},{2,5},{1,1},{8,0}},
			{{6,0},{1,1},{8,0},{7,1},{9,0},{2,4},{0,6},{2,5},{3,4},{7,3}},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [people, expected] : test_data) {
		auto result = solution.reconstructQueue(people);
		cout << people << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
