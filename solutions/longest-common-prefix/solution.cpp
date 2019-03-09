#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream& operator<< (ostream& out, const vector<string>& v) {
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

class Solution {
public:
	string longestCommonPrefix(const vector<string>& strs) {
		string result;
		if (strs.empty())
			return result;
		for (int i = 0; ; ++i) {
			char c = '\0';
			for (auto& s: strs) {
				if (i >= static_cast<int>(s.length()))
					return result;
				if (!c)
					c = s[i];
				else if (c != s[i])
					return result;
			}
			result.push_back(c);
		}
	}
};

void test(const vector<string>& strs)
{
	cout << strs << " -> \"" <<
		Solution().longestCommonPrefix(strs) << '"' << endl;
}

int main()
{
	test({"flower", "flow", "flight"});
	test({"dog", "racecar", "cat"});
	test({"fl", "fla", "flag"});
	test({"one"});
	test({});
	return 0;
}
