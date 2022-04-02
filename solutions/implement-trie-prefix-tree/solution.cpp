#include <iostream>
#include <vector>
#include <utility>

using namespace std;

namespace {

class Trie {
private:
	static int getCommonPrefixLength(const string& s1, size_t pos1,
					 const string& s2, size_t pos2) {
		size_t i;
		for (i = 0; i + pos1 < s1.length() && i + pos2 < s2.length(); ++i) {
			if (s1[i + pos1] != s2[i + pos2])
				break;
		}
		return i;
	}

	struct Node {
		bool belongs = false;
		string prefix;
		vector<Node> children;
		Node() {}
		Node(string prefix_) : prefix(move(prefix_)) {}
	};

	Node root;

	// p_node: deepest matching node
	// p_len: length of the matching prefix in the found node
	// p_pos: length of the matching prefix in the input string
	void findNode(const string& s, Node** p_node,
		      size_t *p_len, size_t *p_pos) {
		Node* node = &root;
		size_t len = getCommonPrefixLength(s, 0, node->prefix, 0);
		size_t pos = len;
		*p_len = len;
		*p_pos = pos;
		*p_node = node;
		while (len == node->prefix.length()) {
			bool found = false;
			for (auto& child : node->children) {
				len = getCommonPrefixLength(s, pos,
							    child.prefix, 0);
				if (len != 0) {
					node = &child;
					pos += len;
					*p_node = node;
					*p_len = len;
					*p_pos = pos;
					found = true;
					break;
				}
			}
			if (!found)
				break;
		}
	}

public:
	Trie() {}

	void insert(const string& s) {
		Node *node;
		size_t len;
		size_t pos;
		findNode(s, &node, &len, &pos);
		if (len != node->prefix.length()) {
			Node new_node(node->prefix.substr(
					len, node->prefix.length() - len));
			new_node.belongs = node->belongs;
			new_node.children = move(node->children);
			node->children.push_back(move(new_node));
			node->prefix.resize(len);
			node->belongs = false;
		}
		if (pos != s.length()) {
			Node new_node(s.substr(pos, s.length() - pos));
			new_node.belongs = true;
			node->children.push_back(move(new_node));
		} else {
			node->belongs = true;
		}
	}

	bool search(const string& s) {
		Node *node;
		size_t len;
		size_t pos;
		findNode(s, &node, &len, &pos);
		return pos == s.length() && len == node->prefix.length() &&
			node->belongs;
	}

	bool startsWith(const string& prefix) {
		Node *node;
		size_t len;
		size_t pos;
		findNode(prefix, &node, &len, &pos);
		return pos == prefix.length() &&
			(node->belongs || !node->children.empty());
	}
};

bool success = true;

Trie testCreate()
{
	cout << "Trie()" << endl;
	return Trie();
}

void testInsert(Trie& t, const string& s)
{
	cout << "insert(\"" << s << "\")" << endl;
	t.insert(s);
}

void testSearch(Trie& t, const string& s, bool expected)
{
	bool result = t.search(s);
	cout << "search(\"" << s << "\") = " <<
		(result ? "true" : "false") << endl;
	if (result != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

void testStartsWith(Trie& t, const string& s, bool expected)
{
	bool result = t.startsWith(s);
	cout << "startsWith(\"" << s << "\") = " <<
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
		auto t = testCreate();
		testSearch(t, "", false);
		testStartsWith(t, "", false);
		testInsert(t, "");
		testSearch(t, "", true);
		testStartsWith(t, "", true);
	}
	{
		auto t = testCreate();
		testInsert(t, "abc");
		testInsert(t, "abd");
		testSearch(t, "ab", false);
		testSearch(t, "abc", true);
		testStartsWith(t, "", true);
		testStartsWith(t, "abc", true);
	}
	{
		auto t = testCreate();
		testInsert(t, "abc");
		testInsert(t, "abd");
		testInsert(t, "abcdefg");
		testInsert(t, "abcdefghi");
		testSearch(t, "ab", false);
		testSearch(t, "abc", true);
		testStartsWith(t, "abc", true);
		testSearch(t, "abcdef", false);
		testStartsWith(t, "abcdef", true);
		testSearch(t, "abcdefgh", false);
		testStartsWith(t, "abcdefgh", true);
		testSearch(t, "abcdefg", true);
		testSearch(t, "abcdefghi", true);
	}
	{
		auto t = testCreate();
		testInsert(t, "abc");
		testSearch(t, "", false);
		testStartsWith(t, "", true);
		testSearch(t, "ab", false);
		testStartsWith(t, "ab", true);
		testSearch(t, "abc", true);
		testStartsWith(t, "abc", true);
	}
	{
		auto t = testCreate();
		testInsert(t, "apple");
		testSearch(t, "apple", true);
		testSearch(t, "app", false);
		testStartsWith(t, "app", true);
		testInsert(t, "app");
		testSearch(t, "app", true);
	}
	return success ? 0 : 1;
}
