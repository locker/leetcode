#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& grid)
{
	out << '[';
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		if (row != grid.begin())
			out << ',';
		out << endl << "  [";
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (cell != row->begin())
				out << ',';
			out << *cell;
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		//
		// Fill cells with the min HP needed to get to the princess
		// starting from the bottom right corner and going up to the
		// cell where the knight is initially located (top-left).
		//
		int n_rows = dungeon.size();
		int n_cols = dungeon[0].size();
		//
		// If the room represented by the bottom-right cell contains a
		// daemon, we need at least as many HP as the damage inflicted
		// by the daemon plus 1, otherwise we just need to be alive,
		// i.e. have exactly 1 HP.
		//
		dungeon[n_rows - 1][n_cols - 1] =
			max(-dungeon[n_rows - 1][n_cols - 1], 0) + 1;
		//
		// For bottom and right cells, we only have one way to go.
		// If there's a power-up in a room, we need as fewer HP to
		// get to the princess in comparison to the next room as
		// the power-up strength, i.e. we need to decrease the value
		// stored in the next room by the power-up strength as long
		// as it stays positive, of course. Similarly, if there's a
		// daemon, we need to increase the value stored in the next
		// room by the daemon strength.
		//
		// For the rest of the cells we need to consider bottom and
		// right neighbor cells and choose the one that requires fewer
		// HP to reach the princess.
		//
		for (int row = n_rows - 1; row >= 0; --row) {
			for (int col = n_cols - 1; col >= 0; --col) {
				if (row == n_rows - 1 && col == n_cols - 1)
					continue; // final cell
				int val;
				if (col < n_cols - 1 &&
				    (row == n_rows - 1 ||
				     dungeon[row + 1][col] >
				     dungeon[row][col + 1])) {
					// go right
					val = dungeon[row][col + 1];
				} else {
					// go down
					val = dungeon[row + 1][col];
				}
				dungeon[row][col] = val - dungeon[row][col];
				dungeon[row][col] = max(dungeon[row][col], 1);
			}
		}
		return dungeon[0][0];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{0}}, // 1
		{{1}}, // 1
		{{-1}}, // 2
		{{-1, 1, 1}}, // 2
		{{-1, -1, 10}}, // 3
		{{-1, -1, -1}}, // 4
		{
			{10, -100, 1000},
			{10, 100, -1000},
		}, // 91
		{
			{-2, -3, 3},
			{-5, -10, 1},
			{10, 30, -5},
		}, // 7
	};
	Solution solution;
	for (auto& grid: input) {
		cout << "Input: " << grid << endl;
		cout << "Output: " << solution.calculateMinimumHP(grid) << endl;
	}
	return 0;
}
