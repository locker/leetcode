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
	vector<int> gardenNoAdj(int n, const vector<vector<int>>& paths) {
		const int max_color = 4;

		vector<vector<int>> destinations(n);
		for (const auto& path: paths) {
			int i = path[0] - 1;
			int j = path[1] - 1;
			destinations[i].push_back(j);
			destinations[j].push_back(i);
		}

		vector<int> colors(n, -1);
		for (int i = 0; i < n; ++i) {
			for (int c = 1; c <= max_color; ++c) {
				bool busy = false;
				for (int j: destinations[i]) {
					if (colors[j] == c) {
						busy = true;
						break;
					}
				}
				if (!busy) {
					colors[i] = c;
					break;
				}
			}
		}
		return colors;
	}
};

int main()
{
	pair<int, vector<vector<int>>> input[] = {
		{0, {}}, // []
		{1, {}}, // [1]
		{2, {}}, // [1, 1]
		{2, {{1, 2}}}, // [1, 2]
		{3, {{1, 2}, {2, 3}, {3, 1}}}, // [1, 2, 3]
		{4, {{1, 2}, {3, 4}}}, // [1, 2, 1, 2]
		{4, {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {2, 4}}}, // [1, 2, 3, 4]
		{6, {{1, 2}, {1, 3}, {2, 4}, {3, 6}, {4, 5}, {4, 6}, {5, 6}}}, // [1, 2, 2, 1, 2, 3]
	};
	Solution solution;
	for (const auto& p: input) {
		int n = p.first;
		const auto& paths = p.second;
		auto colors = solution.gardenNoAdj(n, paths);
		cout << "Input: N = " << n << ", paths = " << paths << endl <<
			"Output: " << colors << endl;
	}
	return 0;
}
