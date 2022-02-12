#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>

using namespace std;

class Solution {
private:
	class isScrambleHelper {
	private:
		class hash {
		public:
			size_t operator()(const tuple<int, int, int>& t) const {
				return get<0>(t) ^ get<1>(t) ^ get<2>(t);
			}
		};
		const string& s1;
		const string& s2;
		unordered_set<tuple<int, int, int>, hash> checked;
		bool check(int p1, int p2, int l) {
			assert(p1 + l <= static_cast<int>(s1.length()));
			assert(p2 + l <= static_cast<int>(s2.length()));
			const auto args = make_tuple(p1, p2, l);
			if (checked.count(args) > 0)
				return false;
			if (s1.compare(p1, l, s2, p2, l) == 0)
				return true;
			for (int i = 1; i < l; ++i) {
				if (check(p1, p2 + l - i, i) &&
				    check(p1 + i, p2, l - i)) {
					return true;
				}
				if (check(p1, p2, i) &&
				    check(p1 + i, p2 + i, l - i)) {
					return true;
				}
			}
			checked.insert(args);
			return false;
		}
	public:
		isScrambleHelper(const string& s1_, const string& s2_)
			: s1(s1_), s2(s2_) {}
		bool operator()() {
			assert(s1.length() == s2.length());
			return check(0, 0, s1.length());
		}
	};
public:
	bool isScramble(const string& s1, const string& s2) {
		return isScrambleHelper(s1, s2)();
	}
};

int main()
{
	tuple<string, string, bool> test_data[] = {
		{"a", "a", true},
		{"a", "b", false},
		{"xyz", "xyz", true},
		{"xyz", "xya", false},
		{"abcde", "caebd", false},
		{"great", "rgeat", true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s1, s2, expected] : test_data) {
		bool result = solution.isScramble(s1, s2);
		cout << "isScramble(\"" << s1 << "\", \"" << s2 << "\") = " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong answer" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
