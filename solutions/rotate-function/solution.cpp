#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
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
	//
	// S(l,m) = A[l] + A[l+1] + ... + A[m-1]
	//
	// G(k) = 0*A[k] + 1*A[k+1] + 2*A[k+2] + ... + (n-k-1)*A[n-1]
	// G(k+1) = 0*A[k+1] + 1*A[k+2] + ... + (n-k-2)*A[n-1]
	// G(k) - G(k+1) = A[k+1] + A[k+2] + ... + A[n-1] = S(k+1,n)
	//
	// H(k) = (n-1)*A[k-1] + (n-2)*A[k-2] + ... + (n-k)*A[0]
	// H(k+1) = (n-1)*A[k] + (n-2)*A[k-1] + ... + (n-k-1)*A[0]
	// H(k) - H(k+1) = -(n-1)*A[k] + A[k-1] + A[k-2] + ... + A[0]
	//               = S(0,k) - (n-1)*A[k]
	//
	// F(k) = 0*A[k] + 1*A[k+1] + ... + (n-2)*A[k-2] + (n-1)*A[k-1]
	// F(k+1) = H(k+1) + G(k+1) =
	//        = H(k) - S(0,k) + (n-1)*A[k] + G(k) - S(k+1,n)
	//        = F(k) - S(0,n) + n*A[k]
	//
	int maxRotateFunction(const vector<int>& nums) {
		int n = nums.size();
		int S = 0;
		int F = 0;
		for (int k = 0; k < n; ++k) {
			S += nums[k];
			F += k * nums[k];
		}
		int ret = F;
		for (int k = 1; k < n; ++k) {
			F = F - S + n * nums[k - 1];
			ret = max(ret, F);
		}
		return ret;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int> test_data[] = {
		{{100}, 0},
		{{3, 5}, 5},
		{{5, 3}, 5},
		{{2, 3, 1}, 8},
		{{4,3,2,6}, 26},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.maxRotateFunction(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
