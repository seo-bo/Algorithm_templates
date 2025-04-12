class Trie //https ://github.com/seo-bo/Algorithm_templates/blob/main/Trie.cpp
{
private:
	struct Node
	{
		bool fin;
		map<char, Node*>child;
		Node() { fin = false; }
	};
	Node* root;
	void destroy(Node* node)
	{
		if (node)
		{
			for (auto& [_, a] : node->child)
			{
				destroy(a);
			}
			delete node;
		}
	}
	bool del(Node* node, const string& word, int depth)
	{
		if (!node)
		{
			return false;
		}
		if (depth == word.size())
		{
			if (node->fin)
			{
				node->fin = false;
				return node->child.empty();
			}
			return false;
		}
		char pivot = word[depth];
		if (del(node->child[pivot], word, depth + 1))
		{
			delete node->child[pivot];
			node->child.erase(pivot);
			return (!node->fin && node->child.empty());
		}
		return false;
	}
	void add(const string& word)
	{
		Node* cur = root;
		for (auto& i : word)
		{
			if (cur->child.find(i) == cur->child.end())
			{
				cur->child[i] = new Node();
			}
			cur = cur->child[i];
		}
		cur->fin = true;
	}
	bool search(const string& word)
	{
		Node* cur = root;
		for (auto& i : word)
		{
			if (cur->child.find(i) == cur->child.end())
			{
				return false;
			}
			cur = cur->child[i];
		}
		return (cur && cur->fin);
	}
public:
	Trie() { root = new Node(); }
	void finish()
	{
		destroy(root);
	}
	void insert(const string& word)
	{
		add(word);
	}
	bool pop(const string& word)
	{
		return del(root, word, 0);
	}
	bool find(const string& word)
	{
		return search(word);
	}
};
