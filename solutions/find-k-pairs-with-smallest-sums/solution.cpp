#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
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
    vector<vector<int>> kSmallestPairs(const vector<int>& nums1,
				       const vector<int>& nums2, int k) {
	    using pos = pair<int, int>;
	    auto cmp = [&nums1, &nums2](const pos& p1, const pos& p2) {
		    return nums1[p1.first] + nums2[p1.second] >
			    nums1[p2.first] + nums2[p2.second];
	    };
	    vector<pos> q;
	    int q_size = min(k, (int)nums1.size());
	    q.reserve(q_size);
	    for (int i = 0; i < q_size; ++i)
		    q.emplace_back(i, 0);
	    make_heap(q.begin(), q.end(), cmp);
	    vector<vector<int>> result;
	    result.reserve(q_size);
	    for ( ; k > 0 && q_size > 0; --k) {
		    pop_heap(q.begin(), q.begin() + q_size, cmp);
		    auto& p = q[q_size - 1];
		    result.push_back({nums1[p.first], nums2[p.second]});
		    if (++p.second < (int)nums2.size()) {
			    push_heap(q.begin(), q.begin() + q_size, cmp);
		    } else {
			    --q_size;
		    }
	    }
	    return result;
    }
};

} // namespace

int main()
{
	const tuple<vector<int>, vector<int>, int,
		    vector<vector<int>>> test_data[] = {
		{{1, 7, 11}, {2, 4, 6}, 3, {{1, 2}, {1, 4}, {1, 6}}},
		{{1, 1, 2}, {1, 2, 3}, 2, {{1, 1}, {1, 1}}},
		{{1, 2}, {3}, 3, {{1, 3}, {2, 3}}},
		{{1, 1, 2}, {1, 2, 3}, 10, {{1, 1}, {1, 1}, {2, 1}, {1, 2}, {1, 2}, {2, 2}, {1, 3}, {1, 3}, {2, 3}}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums1, nums2, k, expected] : test_data) {
		auto result = solution.kSmallestPairs(nums1, nums2, k);
		cout << "nums1 = " << nums1 << ", nums2 = " << nums2 <<
			", k = " << k << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
