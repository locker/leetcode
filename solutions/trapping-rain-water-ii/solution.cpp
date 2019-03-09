#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& map)
{
	out << '[' << endl;
	for (auto& row: map) {
		out << "  [";
		for (auto it = row.begin(); it != row.end(); ++it) {
			if (it != row.begin())
				out << ", ";
			out << *it;
		}
		out << ']' << endl;
	}
	out << ']' << endl;
	return out;
}

class Solution {
public:
	int trapRainWater(const vector<vector<int>>& height_map) {
		// Less than three cells can't trap any water.
		int n_rows = height_map.size();
		if (n_rows < 3)
			return 0;
		int n_cols = height_map[0].size();
		if (n_cols < 3)
			return 0;

		// Coordinate of a cell on the height map.
		struct coord {
			int row, col;
			coord(int r, int c) : row(r), col(c) {}
			int height(const vector<vector<int>>& map) const {
				return map[row][col];
			}
		};

		// Heap of coordinates to check next, arranged so that
		// the min height coordinate is at the top.
		auto cmp = [&](const coord& c1, const coord& c2) {
			int h1 = c1.height(height_map);
			int h2 = c2.height(height_map);
			return h1 > h2;
		};
		vector<coord> heap;

		// We start with the map boundary, because we know
		// how much water those cells can trap (none).
		for (int i = 0; i < n_cols; ++i) {
			heap.emplace_back(0, i);
			heap.emplace_back(n_rows - 1, i);
		}
		for (int i = 0; i < n_rows; ++i) {
			heap.emplace_back(i, 0);
			heap.emplace_back(i, n_cols - 1);
		}
		make_heap(heap.begin(), heap.end(), cmp);

		// Map of coordinates that have been visited.
		vector<vector<bool>> visited(n_rows);
		for (int i = 0; i < n_rows; ++i) {
			visited[i].resize(n_cols, i == 0 || i == n_rows - 1);
			visited[i][0] = true;
			visited[i][n_cols - 1] = true;
		}

		// Push a coordinate to the heap unless it has been visited.
		auto visit = [&](int row, int col) {
			if (!visited[row][col]) {
				visited[row][col] = true;
				heap.emplace_back(row, col);
				push_heap(heap.begin(), heap.end(), cmp);
			}
		};

		// Total amount of trapped water.
		int result = 0;

		// Height of the wall that stops water from leaking from
		// the cells that have yet to be checked.
		int stop_height = 0;

		// Pop a coordinate from the heap. It can trap as much
		// water as can be stopped by the cells checked so far.
		// Update the final result accordingly and advance the
		// boundary inwards, adjusting the stop height. Repeat
		// until all cells have been checked.
		while (!heap.empty()) {
			pop_heap(heap.begin(), heap.end(), cmp);
			auto c = heap.back();
			heap.pop_back();
			int h = c.height(height_map);
			if (h < stop_height)
				result += stop_height - h;
			else
				stop_height = h;
			if (c.row > 0)
				visit(c.row - 1, c.col);
			if (c.row < n_rows - 1)
				visit(c.row + 1, c.col);
			if (c.col > 0)
				visit(c.row, c.col - 1);
			if (c.col < n_cols - 1)
				visit(c.row, c.col + 1);
		}
		return result;
	}
};

void test(const vector<vector<int>>& height_map)
{
	cout << "Input: " << endl << height_map <<
		"Output: " << Solution().trapRainWater(height_map) <<
		endl << endl;
}

int main()
{
	test({
		{1, 4, 3, 1, 3, 2},
		{3, 2, 1, 3, 2, 4},
		{2, 3, 3, 2, 3, 1},
	}); // 4
	test({
		{12, 13,  1, 12},
		{13,  4, 13, 12},
		{13,  8, 10, 12},
		{12, 13, 12, 12},
		{13, 13, 13, 13},
	}); // 14
	test({
		{5, 5, 5, 1},
		{5, 1, 1, 5},
		{5, 1, 5, 5},
		{5, 2, 5, 8},
	}); // 3
	return 0;
}
