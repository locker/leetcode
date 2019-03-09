#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
	typedef vector<int>::const_iterator iterator;

	// Lookup min element in [begin, end) that is greater than val.
	iterator lookupGT(iterator begin, iterator end, int val) {
		iterator ret = end;
		do {
			iterator mid = begin + (end - begin) / 2;
			if (*mid > val)
				end = ret = mid;
			else
				begin = mid + 1;
		} while (begin != end);
		return ret;
	}
public:
	double findMedianSortedArrays(const vector<int>& nums1,
				      const vector<int>& nums2) {
		// The algorithm below assumes the first array has
		// less elements than the second one.
		if (nums1.size() > nums2.size())
			return findMedianSortedArrays(nums2, nums1);

		// If the total number of elements is odd, there's
		// the only median element and so we simply return it.
		// Otherwise we need to calculate the average between
		// two elements sharing the title.
		bool odd = ((nums1.size() + nums2.size()) % 2 != 0);

		// Trivial case - one of the arrays is empty.
		if (nums1.size() == 0) {
			iterator beg = nums2.begin();
			iterator end = nums2.end();
			iterator mid = beg + (end - beg) / 2;
			return odd ? *mid : (*mid + *(mid - 1)) / 2.0;
		}

		// Narrow the first array down to one element while
		// keeping track of the interval in the second array
		// where the median falls.
		int left_carry = 0;
		int right_carry = 0;
		iterator beg1 = nums1.begin();
		iterator beg2 = nums2.begin();
		iterator end1 = nums1.end();
		iterator end2 = nums2.end();

		while (end1 - beg1 > 1) {
			iterator mid1 = beg1 + (end1 - beg1) / 2;
			iterator mid2 = lookupGT(beg2, end2, *mid1);

			int left = (mid1 - beg1) + (mid2 - beg2);
			int right = (end1 - mid1) + (end2 - mid2);
			int left_total = left + left_carry;
			int right_total = right + right_carry;
			if (left_total == right_total) {
				// Found the median.
				return (min(*mid1, *mid2) +
					max(*(mid1 - 1), *(mid2 - 1))) / 2.0;
			}
			if (left_total > right_total) {
				// Go left.
				end1 = mid1;
				end2 = mid2;
				right_carry += right;
			} else {
				// Go right;
				beg1 = mid1;
				beg2 = mid2;
				left_carry += left;
			}
		}

		// Now our task is relatively simple: given a point
		// in the first array, an interval in the second array,
		// where the median falls, and the number of elements
		// on both sides, find the median.
		int val = *beg1;
		iterator beg = beg2;
		iterator end = end2;
		iterator mid = beg + (end - beg + right_carry - left_carry) / 2;
		if (*mid <= val) {
			if (odd)
				return *mid;
			if (mid == end - 1 || *(mid + 1) > val)
				return (*mid + val) / 2.0;
			return (*mid + *(mid + 1)) / 2.0;
		} else {
			if (mid == beg || *(mid - 1) < val) {
				if (odd)
					return val;
				return (val + *mid) / 2.0;
			}
			if (odd)
				return *(mid - 1);
			return (*mid + *(mid - 1)) / 2.0;
		}
		return *mid;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{ {}, {1} },
		{ {}, {1, 2} },
		{ {1}, {10, 20, 30} },
		{ {1}, {10, 20, 30, 40} },
		{ {25}, {10, 20, 30} },
		{ {25}, {10, 20, 30, 40} },
		{ {50}, {10, 20, 30} },
		{ {50}, {10, 20, 30, 40} },
		{ {1, 3}, {2} },
		{ {1, 2}, {3, 4} },
		{ {1, 2}, {-1, 3} },
		{ {1, 3, 5, 7}, {2, 4, 6} },
		{ {1, 3, 5, 7}, {2, 4, 6, 8} },
		{ {1, 3, 5, 7}, {2, 4, 6, 8, 10} },
	};
	Solution solution;
	for (auto& it: input) {
		cout << it.first << ", " << it.second << " => " <<
			solution.findMedianSortedArrays(it.first, it.second) << endl;
	}
	return 0;
}
