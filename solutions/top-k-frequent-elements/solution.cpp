#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

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
	vector<int> topKFrequent(const vector<int>& nums, int k) {
		unordered_map<int, int> num_counts;
		for (int num : nums)
			++num_counts[num];
		vector<pair<int, int>> counts;
		for (const auto& v : num_counts)
			counts.push_back(v);
		int begin = 0;
		int end = counts.size();
		while (true) {
			int middle = (end - begin) / 2;
			int pivot = counts[middle].second;
			int pivot_pos = begin;
			swap(counts[pivot_pos], counts[middle]);
			for (int i = begin + 1; i < end; ++i) {
				int val = counts[i].second;
				if (val < pivot)
					continue;
				swap(counts[i], counts[pivot_pos]);
				if (i > pivot_pos + 1)
					swap(counts[i], counts[pivot_pos + 1]);
				++pivot_pos;
			}
			if (pivot_pos + 1 == k)
				break;
			if (pivot_pos < k) {
				begin = pivot_pos + 1;
			} else {
				end = pivot_pos;
			}
		}
		vector<int> topk(k);
		for (int i = 0; i < k; ++i)
			topk[i] = counts[i].first;
		return topk;
	}
};

int main()
{
	const tuple<vector<int>, int, vector<int>> test_data[] = {
		{{1}, 1, {1}},
		{{1, 1, 2}, 1, {1}},
		{{2, 1, 2}, 1, {2}},
		{{1, 1, 1, 2, 2, 3}, 2, {1, 2}},
		{{3, 3, 1, 2, 2, 3}, 2, {3, 2}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, k, expected] : test_data) {
		auto result = solution.topKFrequent(nums, k);
		cout << "nums=" << nums << ", k=" << k << " => " << result << endl;
		if (unordered_set<int>(result.begin(), result.end()) !=
		    unordered_set<int>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
