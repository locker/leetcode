#include <iostream>
#include <stack>
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
	int largestRectangleArea(const vector<int>& heights) {
		int end_pos = heights.size();

		// Candidate for the rectangle spanning max area.
		struct Rect {
			int start_pos;
			int height;
			Rect(int p, int h) : start_pos(p), height(h) {}
		};

		// Upon encountering a column of height X, we can compute
		// the max area among all rectangles of heights greater
		// than X scanned before. So we push columns to the stack
		// until a column of a lower height is found - then we pop
		// all higher columns computing areas of the corresponding
		// rectangles.
		stack<Rect> max_rect;

		int max_area = 0;
		for (int pos = 0; pos <= end_pos; ++pos) {
			int height = pos < end_pos ? heights[pos] : 0;
			int start_pos = pos;
			while (!max_rect.empty() &&
			       max_rect.top().height >= height) {
				Rect& rect = max_rect.top();
				int area = (pos - rect.start_pos) * rect.height;
				if (max_area < area)
					max_area = area;
				start_pos = rect.start_pos;
				max_rect.pop();
			}
			max_rect.emplace(start_pos, height);
		}
		return max_area;
	}
};

int main()
{
	vector<int> input[] = {
		{0}, // 0
		{1}, // 1
		{1, 1}, // 2
		{2, 3}, // 4
		{2, 3, 4, 3}, // 9
		{2, 3, 4, 3, 2}, // 10
		{2, 1, 5, 6, 2, 3}, // 10
	};
	Solution solution;
	for (const auto& heights: input) {
		cout << heights << " => " <<
			solution.largestRectangleArea(heights) << endl;
	}
	return 0;
}
