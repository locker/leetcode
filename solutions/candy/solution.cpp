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
	int candy(const vector<int>& ratings) {
		// Minimal number of candies to dispense so that
		// - each child has at least one candy;
		// - a child with a greater rating has more candies than his
		//   neighbors in the line.
		int result = 0;
		// Rating of the previous child in the line.
		int prev_rating = 0;
		// Number of candies given to the previous child.
		int prev_candies = 0;
		// Number of preceding children that have decreasing ratings.
		int decl_count = 0;
		// Number of candies initially given to the first child in
		// the sequence of children having declining ratings.
		int decl_first = 0;
		// Flag set for the first child in the line.
		bool first = true;
		for (auto rating: ratings) {
			int candies;
			if (first || rating <= prev_rating) {
				// This child isn't better than the previous
				// one. One candy will do.
				candies = 1;
			} else {
				// This child exceeds the previous one so
				// we have to give him one more candy.
				candies = prev_candies + 1;
			}
			result += candies;

			if (first || rating >= prev_rating) {
				// This child isn't worse than the previous
				// one so we don't need to give more candies
				// to preceding children. Start a new sequence.
				decl_count = 0;
				decl_first = candies;
			} else {
				// One more child in the declining sequence.
				// We need to give all children in the sequence
				// one more candy except, may be, the first
				// one: he doesn't need a candy if he already
				// has more than the sequence length.
				result += decl_count;
				++decl_count;
				if (decl_count >= decl_first)
					++result;
			}

			prev_rating = rating;
			prev_candies = candies;
			first = false;
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{5}, // [1] => 1
		{1, 1}, // [1, 1] => 2
		{2, 1}, // [2, 1] => 3
		{1, 2}, // [1, 2] => 3
		{1, 2, 2}, // [1, 2, 1] => 4
		{1, 0, 2}, // [2, 1, 2] => 5
		{1, 2, 2, 2}, // [1, 2, 1, 1] => 5
		{1, 2, 3, 4}, // [1, 2, 3, 4] => 10
		{4, 3, 2, 1}, // [4, 3, 2, 1] => 10
		{1, 3, 2, 2, 1}, // [1, 2, 1, 2, 1] => 7
		{5, 5, 4, 3, 3}, // [1, 3, 2, 1, 1] => 8
		{5, 5, 4, 3, 2}, // [1, 4, 3, 2, 1] => 11
		{1, 6, 10, 8, 7, 3, 2}, // [1, 2, 5, 4, 3, 2, 1] => 18
	};
	Solution solution;
	for (const auto& ratings: input)
		cout << ratings << " => " << solution.candy(ratings) << endl;
	return 0;
}
