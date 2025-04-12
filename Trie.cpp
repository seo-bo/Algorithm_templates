class Trie https://github.com/seo-bo/Algorithm_templates/blob/main/Trie.cpp
{
private:
	struct Node
	{
		bool fin;
		Node* child[26];
		Node()
		{
			fin = false;
			for (int i = 0; i < 26; ++i)
			{
				child[i] = nullptr;
			}
		}
	};
	Node* root;
	void destroy(Node* node)
	{
		if (node != nullptr)
		{
			for (int i = 0; i < 26; ++i)
			{
				if (node->child[i])
				{
					destroy(node->child[i]);
				}
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
				for (int i = 0; i < 26; ++i)
				{
					if (node->child[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		int idx = word[depth] - 'a';
		if (del(node->child[idx], word, depth + 1))
		{
			delete node->child[idx];
			node->child[idx] = nullptr;
			if (node->fin)
			{
				return false;
			}
			for (int i = 0; i < 26; ++i)
			{
				if (node->child[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	void add(const string& word)
	{
		Node* cur = root;
		for (int i = 0; i < (int)word.size(); ++i)
		{
			int idx = word[i] - 'a';
			if (!cur->child[idx])
			{
				cur->child[idx] = new Node();
			}
			cur = cur->child[idx];
		}
		cur->fin = true;
	}
	bool search(const string& word)
	{
		Node* cur = root;
		for (int i = 0; i < (int)word.size(); ++i)
		{
			int idx = word[i] - 'a';
			if (!cur->child[idx])
			{
				return false;
			}
			cur = cur->child[idx];
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
