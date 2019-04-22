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
	bool isOneBitCharacter(const vector<int>& bits) {
		int size = bits.size();
		if (size <= 1)
			return true;
		// If the number of 1s preceding the last 0 is odd,
		// the last character must be two-bit:
		//
		//   ... 0 11 11 ... 11 10
		//
		// If it is even, the last character must be one-bit:
		//
		//   ... 0 11 11 ... 11 0
		//
		// because 10 can't be encoded with a two-bit character.
		//
		int count = 0;
		for (int i = size - 2; i >= 0; --i) {
			if (bits[i] == 0)
				break;
			++count;
		}
		return count % 2 == 0;
	}
};

int main()
{
	vector<int> input[] = {
		{0}, // true
		{0, 0}, // true
		{1, 0}, // false
		{1, 0, 0}, // true
		{1, 1, 0}, // true
		{1, 1, 1, 0}, // false
		{1, 0, 1, 0}, // false
		{1, 0, 1, 0, 0}, // true
		{1, 1, 1, 1, 0}, // true
		{0, 1, 1, 1, 0}, // false
		{1, 0, 0, 1, 1, 0}, // true
		{1, 0, 1, 1, 1, 0}, // false
	};
	Solution solution;
	for (const auto& bits: input) {
		cout << bits << " => ";
		cout << (solution.isOneBitCharacter(bits) ? "true" : "false");
		cout << endl;
	}
	return 0;
}
