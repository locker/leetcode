#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
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
			cout << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
private:
	struct Key {
		int start;
		bool positive;
		Key(int s, bool p) : start(s), positive(p) {}
	};
	struct KeyHash {
		size_t operator()(const Key& k) const {
			return hash<int>()(k.start) ^
				(hash<bool>()(k.positive) << 1);
		}
	};
	struct KeyEqual {
		size_t operator()(const Key& a, const Key& b) const {
			return a.start == b.start && a.positive == b.positive;
		}
	};
	unordered_map<Key, int, KeyHash, KeyEqual> cache;
	int helper(const vector<int>& nums, int start, bool positive) {
		int size = nums.size();
		if (size - start == 1)
			return 1;
		auto cache_it = cache.find(Key(start, positive));
		if (cache_it != cache.end())
			return cache_it->second;
		int ret = helper(nums, start + 1, positive);
		for (int i = start + 1; i < size; ++i) {
			if (positive && nums[i] - nums[start] > 0) {
				ret = max(ret, helper(nums, i, false) + 1);
				break;
			}
			if (!positive && nums[i] - nums[start] < 0) {
				ret = max(ret, helper(nums, i, true) + 1);
				break;
			}
		}
		cache.emplace(Key(start, positive), ret);
		return ret;
	}
public:
	int wiggleMaxLength(const vector<int>& nums) {
		cache.clear();
		return max(helper(nums, 0, true), helper(nums, 0, false));
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int> test_data[] = {
		{{1}, 1},
		{{3, 5}, 2},
		{{5, 3}, 2},
		{{5, 5}, 1},
		{{1, 7, 4, 9, 2, 5}, 6},
		{{1, 17, 5, 10, 13, 15, 10, 5, 16, 8}, 7},
		{{1, 2, 3, 4, 5, 6, 7, 8, 9}, 2},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.wiggleMaxLength(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
