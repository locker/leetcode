#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const struct vector<T>& v)
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
	int maximumGap(const vector<int>& nums) {
		const int count = nums.size();
		if (count <= 1)
			return 0;
		int min_num = numeric_limits<int>::max();
		int max_num = numeric_limits<int>::min();
		for (int num : nums) {
			min_num = min(min_num, num);
			max_num = max(max_num, num);
		}
		if (min_num == max_num)
			return 0;
		// Distribute the N input numbers among N equal-size buckets.
		// Note, neither the first nor the last bucket can be empty,
		// since they store the min and max numbers, respectively.
		// We only need to know the values of the min and max number
		// in each bucket.
		struct Bucket {
			int min = numeric_limits<int>::max();
			int max = numeric_limits<int>::min();
			bool empty() { return min > max; }
		};
		const double bucket_size = (double)(max_num - min_num) / count;
		assert(bucket_size > 0);
		vector<Bucket> buckets(count);
		for (int num : nums) {
			int i = (num - min_num) / bucket_size;
			i = min(i, count - 1);
			auto& bucket = buckets[i];
			bucket.min = min(bucket.min, num);
			bucket.max = max(bucket.max, num);
		}
		assert(!buckets.back().empty());
		assert(!buckets.front().empty());
		// The max gap must be between numbers that reside in different
		// buckets, because if there's more than one number in a bucket
		// then there must be an empty bucket and hence the max gap must
		// be greater than the bucket size.
		int max_gap = 0;
		int i, j;
		for (i = 0; i < count - 1; i = j) {
			assert(!buckets[i].empty());
			for (j = i + 1; ; ++j) {
				assert(j < count);
				if (!buckets[j].empty())
					break;
			}
			int gap = buckets[j].min - buckets[i].max;
			assert(gap > 0);
			max_gap = max(max_gap, gap);
		}
		return max_gap;
	}
};

int main()
{
	pair<vector<int>, int> test_data[] = {
		{{}, 0},
		{{10}, 0},
		{{1, 1}, 0},
		{{1, 4}, 3},
		{{7, 10, 8}, 2},
		{{3, 6, 9, 1}, 3},
		{{1, 2, 1, 2}, 1},
		{{1, 2, 102, 100}, 98},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.maximumGap(nums);
		cout << nums << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
