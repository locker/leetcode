#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
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

class Solution {
private:
	typedef uint8_t code_t;
	typedef uint32_t seq_t;

	static constexpr int seq_len = 10;
	static constexpr int bits_per_code = 2;
	static constexpr uint32_t code_bit_mask = (1 << bits_per_code) - 1;

	static constexpr code_t letterCode(char letter) {
		switch (letter) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		default:
			assert(false);
			return -1;
		}
	}

	static constexpr char codeLetter(code_t code) {
		switch (code) {
		case 0: return 'A';
		case 1: return 'C';
		case 2: return 'G';
		case 3: return 'T';
		default:
			assert(false);
			return -1;
		}
	}

	static string sequenceToString(seq_t seq) {
		string s;
		s.reserve(seq_len);
		for (int i = 0; i < seq_len; ++i) {
			code_t code = seq & code_bit_mask;
			s.push_back(codeLetter(code));
			seq >>= bits_per_code;
		}
		return s;
	}

	static seq_t rollSequence(seq_t seq, char letter) {
		code_t code = letterCode(letter);
		assert((code & ~code_bit_mask) == 0);
		seq >>= bits_per_code;
		seq |= code << ((seq_len - 1) * bits_per_code);
		return seq;
	}
public:
	vector<string> findRepeatedDnaSequences(const string& s) {
		int len = s.length();
		if (len <= seq_len)
			return {};
		unordered_set<seq_t> seen, repeated;
		seq_t seq = 0;
		for (int i = 0; i < len; ++i) {
			seq = rollSequence(seq, s[i]);
			if (i < seq_len - 1)
				continue;
			if (seen.find(seq) != seen.end())
				repeated.insert(seq);
			else
				seen.insert(seq);
		}
		vector<string> result;
		for (seq_t seq : repeated)
			result.push_back(sequenceToString(seq));
		return result;
	}
};

int main()
{
	const pair<string, vector<string>> test_data[] = {
		{
			"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
			{"AAAAACCCCC", "CCCCCAAAAA"},
		},
		{
			"AAAAACCCCCAAAAACCCCCCAAGGGTTT",
			{"AAAAACCCCC"},
		},
		{
			"AAAAAAAAAAAAA",
			{"AAAAAAAAAA"},
		},
		{
			"AAAAAACAAAAAA",
			{},
		},
		{
			"AACC",
			{},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		auto result = solution.findRepeatedDnaSequences(s);
		cout << s << " -> " << result << endl;
		if (unordered_set<string>(result.begin(), result.end()) !=
		    unordered_set<string>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
