class ahoCorasick //https ://github.com/seo-bo/Algorithm_templates/blob/main/ahoCorasick.cpp
{
private:
	struct Node
	{
		map<char, Node*>child;
		Node* fail;
		vector<int> out;
		Node() { fail = nullptr; }
	};
	Node* root;
	bool built;
	void add(const string& word, int id)
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
		cur->out.push_back(id);
	}
	void build_pattern()
	{
		queue<Node*>q;
		root->fail = root;
		for (auto& [a, b] : root->child)
		{
			b->fail = root;
			q.push(b);
		}
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			for (auto& [a, b] : cur->child)
			{
				Node* f = cur->fail;
				while (f != root && f->child.find(a) == f->child.end())
				{
					f = f->fail;
				}
				if (f->child.find(a) == f->child.end())
				{
					b->fail = root;
				}
				else
				{
					b->fail = f->child[a];
				}
				b->out.insert(b->out.end(), b->fail->out.begin(), b->fail->out.end());
				q.push(b);
			}
		}
	}
	vector<pair<int, int>> search(const string& word)
	{
		vector<pair<int, int>>ans;
		Node* cur = root;
		for (int i = 0; i < (int)word.size(); ++i)
		{
			char ok = word[i];
			while (cur != root && cur->child.find(ok) == cur->child.end())
			{
				cur = cur->fail;
			}
			if (cur->child.find(ok) != cur->child.end())
			{
				cur = cur->child[ok];
			}
			for (auto& j : cur->out)
			{
				ans.push_back(make_pair(j, i));
			}
		}
		return ans;
	}
public:
	ahoCorasick() { root = new Node(); built = false; }
	void insert(const string& word, int id)
	{
		add(word, id);
	}
	vector<pair<int, int>> find(const string& word)
	{
		if (!built)
		{
			build_pattern();
			built = true;
		}
		return search(word);
	}
};
