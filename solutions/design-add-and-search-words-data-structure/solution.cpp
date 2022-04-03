#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

class WordDictionary {
private:
	struct Node {
		bool belongs = false;
		vector<Node> children;
	} root;

	static bool searchRecursive(const string& word, const int pos,
				    const Node* node) {
		if (pos == static_cast<int>(word.length()))
			return node->belongs;
		if (node->children.empty())
			return false;
		if (word[pos] == '.') {
			for (const auto& child : node->children) {
				if (searchRecursive(word, pos + 1, &child))
					return true;
			}
		} else {
			char c = word[pos];
			if (searchRecursive(word, pos + 1,
					    &node->children[c - 'a']))
				return true;
		}
		return false;
	}

public:
	WordDictionary() {}

	void addWord(const string& word) {
		Node *node = &root;
		for (char c : word) {
			if (node->children.empty())
				node->children.resize('z' - 'a' + 1);
			node = &node->children[c - 'a'];
		}
		node->belongs = true;
	}

	bool search(const string& word) {
		return searchRecursive(word, 0, &root);
	}
};

bool success = true;

WordDictionary testCreate()
{
	cout << "WordDictionary()" << endl;
	return WordDictionary();
}

void testAddWord(WordDictionary& dict, const string& word)
{
	cout << "addWord(\"" << word << "\")" << endl;
	dict.addWord(word);
}

void testSearch(WordDictionary& dict, const string& word, bool expected)
{
	bool result = dict.search(word);
	cout << "search(\"" << word << "\") = " <<
		(result ? "true" : "false") << endl;
	if (result != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

} // namespace

int main()
{
	{
		auto dict = testCreate();
		testAddWord(dict, "aaa");
		testAddWord(dict, "abc");
		testAddWord(dict, "abcde");
		testAddWord(dict, "abcdxyz");
		testSearch(dict, "aaa", true);
		testSearch(dict, "aba", false);
		testSearch(dict, "ab.", true);
		testSearch(dict, "b..", false);
		testSearch(dict, "a..", true);
		testSearch(dict, "a...", false);
		testSearch(dict, "a....", true);
		testSearch(dict, "a...e", true);
		testSearch(dict, "a...e..", false);
		testSearch(dict, "a...x..", true);
	}
	{
		auto dict = testCreate();
		testAddWord(dict, "kbev");
		testAddWord(dict, "kbez");
		testAddWord(dict, "kbvbk");
		testSearch(dict, "kb..k", true);
	}
	{
		auto dict = testCreate();
		testAddWord(dict, "bad");
		testAddWord(dict, "dad");
		testAddWord(dict, "mad");
		testSearch(dict, "pad", false);
		testSearch(dict, "bad", true);
		testSearch(dict, ".ad", true);
		testSearch(dict, "b..", true);
	}
	return success ? 0 : 1;
}
