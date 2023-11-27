#include <cstdlib>
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
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
private:
	unordered_map<int, vector<int>> num_index;
public:
	Solution(const vector<int>& nums) {
		for (int i = 0; i < (int)nums.size(); ++i)
			num_index[nums[i]].push_back(i);
	}

	int pick(int target) {
		const auto& index = num_index[target];
		return index[rand() % index.size()];
	}
};

void test(const vector<int>& nums, const vector<int>& targets)
{
	cout << nums << endl;
	Solution solution(nums);
	for (int target : targets)
		cout << target << " -> " << solution.pick(target) << endl;
}

} // namespace

int main()
{
	test({1, 2, 3, 3, 3}, {3, 1, 1});
	test({1, 2, 1, 2, 1}, {1, 1, 1, 2, 2, 2});
	return 0;
}
