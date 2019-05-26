#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
	int compareComponent(string::const_iterator begin1,
			     string::const_iterator end1,
			     string::const_iterator begin2,
			     string::const_iterator end2) {
		while (end1 - begin1 > end2 - begin2) {
			if (*begin1++ != '0')
				return 1;
		}
		while (end2 - begin2 > end1 - begin1) {
			if (*begin2++ != '0')
				return -1;
		}
		while (begin1 != end1) {
			if (*begin1 != *begin2)
				return *begin1 > *begin2 ? 1 : -1;
			++begin1;
			++begin2;
		}
		return 0;
	}

	string::const_iterator nextComponent(const string& version,
					     string::const_iterator it) {
		while (it != version.end() && *it != '.')
			++it;
		return it;
	}
public:
	int compareVersion(const string& v1, const string& v2) {
		for (auto begin1 = v1.begin(), begin2 = v2.begin();;) {
			auto end1 = nextComponent(v1, begin1);
			auto end2 = nextComponent(v2, begin2);
			int cmp = compareComponent(begin1, end1, begin2, end2);
			if (cmp != 0)
				return cmp;
			begin1 = end1;
			begin2 = end2;
			if (begin1 == v1.end() && begin2 == v2.end())
				return 0;
			if (begin1 != v1.end())
				++begin1;
			if (begin2 != v2.end())
				++begin2;
		}
		return 0;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"0", "0"}, // 0
		{"1", "00"}, // 1
		{"01", "020"}, // -1
		{"0.1", "0.1"}, // 0
		{"1.1", "0.1"}, // 1
		{"0.1", "1.1"}, // -1
		{"1.01", "1.001"}, // 0
		{"1.0.1", "1"}, // 1
		{"7.5.2.4", "7.5.3"}, // -1
		{"1.0", "1.0.0"}, // 0
		{"124.12", "12.124"}, // 1
		{"124.00012.2", "1234.013"}, // -1
	};
	Solution solution;
	for (const auto& p: input) {
		int cmp = solution.compareVersion(p.first, p.second);
		cout << p.first << (cmp < 0 ? " < " :
				    cmp > 0 ? " > " : " = ") <<
			p.second << endl;
	}
	return 0;
}
