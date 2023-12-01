#include <iostream>
#include <tuple>
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
	int countBattleships(const vector<vector<char>>& board) {
		const int m = board.size();
		const int n = board[0].size();
		int count = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == 'X' &&
				    (i == 0 || board[i - 1][j] == '.') &&
				    (j == 0 || board[i][j - 1] == '.'))
					++count;
			}
		}
		return count;
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<char>>, int> test_data[] = {
		{
			{
				{'X','.','.','X'},
				{'.','.','.','X'},
				{'.','.','.','X'},
			}, 2
		},
		{{{'.'}}, 0},
	};
	bool success = true;
	Solution solution;
	for (const auto& [board, expected] : test_data) {
		int result = solution.countBattleships(board);
		cout << board << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
