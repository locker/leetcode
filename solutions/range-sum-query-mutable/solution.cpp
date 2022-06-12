#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
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

class NumArray {
private:
	int len;
	vector<int> sums;

	int sumCount(int count) const {
		int sum = 0;
		int s = 0;
		int l, next_l = len;
		do {
			l = next_l;
			next_l = (l + 1) / 2;
			if (count % 2 == 1)
				sum += sums[s + count - 1];
			count /= 2;
			s += l;
		} while (next_l != l);
		return sum;
	}
public:
	NumArray(vector<int> nums) : len(nums.size()), sums(move(nums)) {
		int s = 0;
		int l = len;
		while (l > 1) {
			for (int i = 0; i < l; i += 2) {
				int sum = sums[s + i];
				if (i + 1 < l)
					sum += sums[s + i + 1];
				sums.push_back(sum);
			}
			s += l;
			l = (l + 1) / 2;
		}
	}
	void update(int i, int val) {
		int old_val = sums[i];
		int s = 0;
		int l, next_l = len;
		do {
			l = next_l;
			next_l = (l + 1) / 2;
			sums[s + i] += val - old_val;
			i /= 2;
			s += l;
		} while (next_l != l);
	}
	int sumRange(int left, int right) const {
		int sum = sumCount(right + 1);
		if (left > 0)
			sum -= sumCount(left);
		return sum;
	}
};

bool success = true;

NumArray testCreate(vector<int> nums) {
	cout << "NumArray(" << nums << ")" << endl;
	return NumArray(move(nums));
}

void testUpdate(NumArray& nums, int index, int val) {
	cout << "update(" << index << ", " << val << ")" << endl;
	nums.update(index, val);
}

int testSumRange(const NumArray& nums, int left, int right, int expected) {
	int result = nums.sumRange(left, right);
	cout << "sumRange(" << left << ", " << right << ") -> " << result << endl;
	if (result != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
	return result;
}

int main()
{
	{
		auto nums = testCreate({10});
		testSumRange(nums, 0, 0, 10);
		testUpdate(nums, 0, 5);
		testSumRange(nums, 0, 0, 5);
	}
	{
		auto nums = testCreate({10, 5});
		testSumRange(nums, 0, 0, 10);
		testSumRange(nums, 1, 1, 5);
		testSumRange(nums, 0, 1, 15);
		testUpdate(nums, 1, 20);
		testSumRange(nums, 0, 0, 10);
		testSumRange(nums, 1, 1, 20);
		testSumRange(nums, 0, 1, 30);
	}
	{
		auto nums = testCreate({1, 3, 5});
		testSumRange(nums, 0, 2, 9);
		testUpdate(nums, 1, 2);
		testSumRange(nums, 0, 1, 3);
		testSumRange(nums, 1, 2, 7);
		testSumRange(nums, 0, 2, 8);
	}
	return success ? 0 : 1;
}
