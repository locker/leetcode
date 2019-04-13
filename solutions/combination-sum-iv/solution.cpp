#include <iostream>
#include <utility>
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
	int combinationSum4(const vector<int>& nums, int target) {
		//
		// Map: sum -> number of combinations.
		//
		// Use 'unsigned' to suppress integer overflow
		// warning - we don't care about overflows.
		//
		vector<unsigned> sums(target + 1);

		// Start with the only combination - the empty one.
		sums[0] = 1;

		// After iteration s, sums[s] stores the number of
		// combinations summing to the target.
		for (int s = 0; s < target; ++s) {
			if (sums[s] == 0)
				continue;
			for (int n: nums) {
				if (n + s <= target)
					sums[n + s] += sums[s];
			}
		}
		return sums[target];
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {1}, 1 },
		{ {1, 2}, 3 },
		{ {1, 2, 3}, 4 },
		{ {4, 2, 1}, 32 },
		{ {5, 1, 8}, 24 },
		{ { 10,  20,  30,  40,  50,  60,  70,  80,  90, 100, 110,
		   120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220,
		   230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330,
		   340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440,
		   450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550,
		   560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660,
		   670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770,
		   780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880,
		   890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990,
		   111},  999 },
		{ {3, 33, 333}, 10000 },
	};
	Solution solution;
	for (auto& p: input) {
		const auto& nums = p.first;
		auto target = p.second;
		cout << "Input: nums = " << nums << ", target = " <<
			target << endl << "Output: " <<
			solution.combinationSum4(nums, target) <<
			endl << endl;
	}
	return 0;
}
