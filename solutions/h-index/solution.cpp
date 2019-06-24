#include <algorithm>
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
		int max_citations = 0;
		for (int c: citations)
			max_citations = max(max_citations, c);
		// Map citation count to paper count.
		vector<int> papers(max_citations + 1);
		for (int c: citations) {
			++papers[c];
		}
		// Find the H-index.
		int count = 0;
		for (int c = max_citations; c >= 0; --c) {
			count += papers[c];
			if (count >= c)
				return c;
		}
		return 0;
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
		{5, 4, 3, 2, 1}, // 3
		{3, 0, 6, 1, 5}, // 3
		{5, 4, 5, 3, 5, 2}, // 4
	};
	Solution solution;
	for (const auto& citations: input)
		cout << citations << " => " << solution.hIndex(citations) << endl;
	return 0;
}
