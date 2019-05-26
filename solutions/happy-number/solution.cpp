#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
	bool isHappy(int n) {
		unordered_set<int> done;
		while (n != 1) {
			if (done.find(n) != done.end())
				return false;
			done.insert(n);
			int i = n;
			n = 0;
			while (i != 0) {
				n += (i % 10) * (i % 10);
				i /= 10;
			}
		}
		return true;
	}
};

int main()
{
	Solution solution;
	for (int n = 1; n <= 100; n < 10 ? ++n : n < 40 ? n += 2 : n += 5) {
		cout << n << " is ";
		if (!solution.isHappy(n))
			cout << "not ";
		cout << "happy" << endl;
	}
	return 0;
}
