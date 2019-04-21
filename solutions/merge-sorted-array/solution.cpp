#include <algorithm>
#include <iostream>
#include <tuple>
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
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		rotate(nums1.begin(), nums1.begin() + m, nums1.begin() + m + n);
		int i1, i2, out;
		i1 = i2 = out = 0;
		while (i2 < n) {
			if (i1 >= m || nums2[i2] < nums1[n + i1])
				nums1[out++] = nums2[i2++];
			else
				nums1[out++] = nums1[n + i1++];
		}
	}
};

int main()
{
	tuple<vector<int>, int, vector<int>, int> input[] = {
		{{}, 0, {}, 0},
		{{1, 2}, 2, {}, 0},
		{{0, 0}, 0, {1, 2}, 2},
		{{1, 3, 0}, 2, {2}, 1},
		{{4, 0, 0, 0}, 1, {1, 3, 5}, 3},
		{{4, 5, 0, 0, 0}, 2, {1, 3}, 2},
		{{1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3},
	};
	Solution solution;
	for (auto& t: input) {
		auto& nums1 = get<0>(t);
		auto m = get<1>(t);
		auto& nums2 = get<2>(t);
		auto n = get<3>(t);
		cout << "Input:" << endl;
		cout << "nums1 = " << nums1 << ", m = " << m << endl;
		cout << "nums2 = " << nums2 << ", n = " << n << endl;
		solution.merge(nums1, m, nums2, n);
		cout << "Output: " << nums1 << endl << endl;
	}
	return 0;
}
