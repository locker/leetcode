#include <algorithm>
#include <iostream>
#include <queue>
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
	int scheduleCourse(vector<vector<int>>& courses) {
		// Sort the courses by the closing date, ascending.
		sort(courses.begin(), courses.end(),
		     [](const vector<int>& a, const vector<int>& b) {
			return a[1] < b[1];
		});

		// Heap of scheduled courses, given by their durations.
		// The longest course is always at the top.
		priority_queue<int> scheduled;

		// Sum duration of scheduled courses.
		int time = 0;

		for (auto it = courses.begin(); it != courses.end(); ++it) {
			auto& c = *it;
			if (c[1] - c[0] >= time) {
				// The course can be scheduled right away.
				// So schedule it.
				scheduled.push(c[0]);
				time += c[0];
			} else if (!scheduled.empty()) {
				// We need to preempt some other course to
				// schedule this one. It can possibly increase
				// the total number of taken courses only if
				// the duration of the preempted course is
				// greater than the duration of this course.
				int max_duration = scheduled.top();
				if (max_duration > c[0]) {
					scheduled.pop();
					scheduled.push(c[0]);
					time += c[0] - max_duration;
				}
			}
		}
		return scheduled.size();
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{}, // 0
		{{2, 1}}, // 0
		{{1, 1}}, // 1
		{{1, 1}, {1, 1}}, // 1
		{{1, 2}, {1, 1}}, // 2
		{{3, 4}, {1, 3}, {4, 5}}, // 2
		{{3, 4}, {1, 2}, {1, 3}, {1, 2}}, // 3
		{{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}, // 3
		{{7, 16}, {2, 3}, {3, 12}, {3, 14}, {10, 19},
		 {10, 16}, {6, 8}, {6, 11}, {3, 13}, {6, 16}}, // 4
	};
	Solution solution;
	for (auto& courses: input) {
		cout << "Input: " << courses << endl <<
			"Output: " << solution.scheduleCourse(courses) << endl;
	}
	return 0;
}
