#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
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

struct Line {
	// Slope numerator.
	int slope;
	// Intercept numerator.
	int icept;
	// Slope and intercept denominator.
	int denom;
	// True if the line is vertical and icept stores
	// interception with the abscissa line.
	bool is_vert;

	Line(int x1, int y1, int x2, int y2) {
		if (x1 == x2) {
			is_vert = true;
			icept = x1;
		} else {
			is_vert = false;
			denom = x2 - x1;
			slope = y2 - y1;
			icept = (long long)y1 * denom - (long long)x1 * slope;
		}
	}

	bool operator==(const Line& other) const {
		if (is_vert)
			return icept == other.icept;

		return ((long long)slope * other.denom ==
			(long long)other.slope * denom &&
			(long long)icept * other.denom ==
			(long long)other.icept * denom);
	}
};

namespace std {
template<> struct hash<Line> {
	size_t operator()(const Line& l) const {
		if (l.is_vert)
			return hash<int>{}(l.icept);
		long long mult = numeric_limits<int>::max();
		return (hash<long long>{}(mult * l.slope / l.denom) ^
			hash<long long>{}(mult * l.icept / l.denom) << 1);
	}
};
};

class Solution {
public:
	int maxPoints(const vector<vector<int>>& points) {
		// Map: line => number of points lying on it.
		unordered_map<Line, int> line_points;

		// Max number of points lying on the same line.
		int max_line_points = 0;

		for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
			// Pick a point and enumerate over all lines
			// passing through it.
			int x1 = (*it1)[0];
			int y1 = (*it1)[1];

			// Max number of other points lying on a line
			// passing through the chosen point.
			int max_points = 0;

			// Number of points equal to the chosen point,
			// including the chosen one itself.
			int same_points = 0;

			for (auto it2 = it1; it2 != points.end(); ++it2) {
				int x2 = (*it2)[0];
				int y2 = (*it2)[1];
				if (x1 == x2 && y1 == y2) {
					++same_points;
					continue;
				}
				int c = ++line_points[Line(x1, y1, x2, y2)];
				max_points = max(max_points, c);
			}

			max_line_points = max(max_line_points,
					      max_points + same_points);
			line_points.clear();
		}
		return max_line_points;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{}, // 0
		{{0, 0}}, // 1
		{{0, 0}, {0, 0}}, // 2
		{{1, 2}, {2, 1}}, // 2
		{{1, 1}, {2, 2}, {3, 3}}, // 3
		{{1, 1}, {1, 2}, {1, 3}}, // 3
		{{1, 1}, {2, 1}, {3, 1}, {1, 1}}, // 4
		{{3, 1}, {12, 3}, {3, 1}, {-6, -1}}, // 4
		{{1, 1}, {2, 2}, {3, 3}, {2, 2}, {1, 2}}, // 4
		{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}, // 4
		{{84, 250}, {0, 0}, {1, 0}, {0, -70}, {0, -70}, {1, -1}, {21, 10}, {42, 90}, {-42, -230}}, // 6
	};
	Solution solution;
	for (const auto& points: input)
		cout << points << " => " << solution.maxPoints(points) << endl;
	return 0;
}
