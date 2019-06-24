#include <iostream>
#include <vector>
#include <unordered_map>

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
	int leastBricks(const vector<vector<int>>& wall) {
		int max_edge_count = 0;
		unordered_map<int, int> edge_count;
		for (int i = 0; i < static_cast<int>(wall.size()); ++i) {
			int pos = 0;
			const auto& row = wall[i];
			for (int j = 0; j < static_cast<int>(row.size()) - 1; ++j) {
				pos += row[j];
				max_edge_count = max(max_edge_count,
						     ++edge_count[pos]);
			}
		}
		return wall.size() - max_edge_count;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{2}}, // 1
		{{2}, {2}}, // 2
		{{1, 1}, {2}}, // 1
		{{1, 2}, {3}, {2, 1}}, // 2
		{{1, 2}, {1, 1, 1}, {3}}, // 1
		{{1, 2}, {1, 1, 1}, {1, 2}}, // 0
		{{4}, {2, 2}, {1, 1, 2}, {1, 1, 1, 1}}, // 1
		{{1, 2, 2, 1},
		 {3, 1, 2},
		 {1, 3, 2},
		 {2, 4},
		 {3, 1, 2},
		 {1, 3, 1, 1}}, // 2
	};
	Solution solution;
	for (const auto& wall: input)
		cout << wall << " => " << solution.leastBricks(wall) << endl;
	return 0;
}
