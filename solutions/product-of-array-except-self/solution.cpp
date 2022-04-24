#include <iostream>
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
	vector<int> productExceptSelf(const vector<int>& nums) {
		int size = nums.size();
		vector<int> products;
		products.resize(size);
		int product = 1;
		for (int i = size - 1; i >= 0; --i) {
			product *= nums[i];
			products[i] = product;
		}
		product = 1;
		for (int i = 0; i < size; ++i) {
			products[i] = product;
			if (i < size - 1)
				products[i] *= products[i + 1];
			product *= nums[i];
		}
		return products;
	}
};

int main()
{
	const pair<vector<int>, vector<int>> test_data[] = {
		{{1, 2}, {2, 1}},
		{{-1, 2}, {2, -1}},
		{{3, 1, 2}, {2, 6, 3}},
		{{1, 2, 3, 4}, {24, 12, 8, 6}},
		{{-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		auto result = solution.productExceptSelf(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
