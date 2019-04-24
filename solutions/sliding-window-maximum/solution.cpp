#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v)
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
	vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
		// Queue invariant: max out of k-window always comes first.
		deque<int> q;
		// Max sliding window.
		vector<int> result;
		result.reserve(nums.size() - k + 1);
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			// We are not interested in elements less than
			// the current one as it will always be chosen
			// over them. So evict them from the queue.
			while (!q.empty() && q.back() < *it)
				q.pop_back();
			// Add the current element to the queue.
			q.push_back(*it);
			// Nothing else to do if the window is too small.
			if (it - nums.begin() + 1 < k)
				continue;
			// The next element of the max sliding window
			// is at the front of the queue (invariant).
			result.push_back(q.front());
			// If the element to be removed from the k-window
			// on the next iteration is the max one, we need
			// to remove it from the queue so that the queue
			// invariant holds.
			if (*(it - k + 1) == q.front())
				q.pop_front();
		}
		return result;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{1}, 1}, // {1}
		{{1, 2, 3}, 1}, // {1, 2, 3}
		{{1, 2, 3, 4}, 2}, // {2, 3, 4}
		{{1, 2, 3, 4, 5}, 3}, // {3, 4, 5}
		{{1, 2, 3, 2, 1}, 3}, // {3, 3, 3}
		{{1, 5, 1, 5, 1, 5}, 2}, // {5, 5, 5, 5}
		{{5, 5, 6, 6, 4, 4, 7, 7}, 3}, // {6, 6, 6, 6, 7, 7}
		{{1, 3, -1, -3, 5, 3, 6, 7}, 3}, // {3, 3, 5, 5, 6, 7}
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& nums = p.first;
		auto k = p.second;
		cout << "Input: nums = " << nums << ", k = " << k << endl <<
			"Output: " << solution.maxSlidingWindow(nums, k) << endl;
	}
	return 0;
}
