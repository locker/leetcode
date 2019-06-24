#include <iostream>
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
	int hIndex(const vector<int>& citations) {
		int h = 0;
		auto begin = citations.begin();
		auto end = citations.end();
		while (begin != end) {
			auto mid = begin + (end - begin) / 2;
			int count = citations.end() - mid;
			if (*mid >= count) {
				h = count;
				end = mid;
			} else {
				begin = mid + 1;
			}
		}
		return h;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{0}, // 0
		{1}, // 1
		{2}, // 1
		{1, 2}, // 1
		{2, 3}, // 2
		{20, 30, 40}, // 3
		{0, 0, 4, 4}, // 2
		{1, 2, 3, 4, 5}, // 3
		{0, 1, 3, 5, 6}, // 3
		{2, 3, 4, 5, 5, 5}, // 4
	};
	Solution solution;
	for (const auto& citations: input)
		cout << citations << " => " << solution.hIndex(citations) << endl;
	return 0;
}
