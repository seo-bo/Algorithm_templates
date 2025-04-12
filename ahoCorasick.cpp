class ahoCorasick
{
private:
	struct Node
	{
		Node* child[26], * fail;
		vector<int> out;
		Node()
		{
			fail = nullptr;
			for (int i = 0; i < 26; ++i)
			{
				child[i] = nullptr;
			}
		}
	};
	Node* root;
	bool builded;
	void add(const string& word, int id)
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
		cur->out.push_back(id);
	}
	void build_pattern()
	{
		queue<Node*>q;
		root->fail = root;
		for (int i = 0; i < 26; ++i)
		{
			if (root->child[i])
			{
				root->child[i]->fail = root;
				q.push(root->child[i]);
			}
			else
			{
				root->child[i] = root;
			}
		}
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			for (int i = 0; i < 26; ++i)
			{
				Node* temp = cur->child[i];
				if (temp)
				{
					Node* f = cur->fail;
					while (!f->child[i] && f != root)
					{
						f = f->fail;
					}
					temp->fail = f->child[i];
					for (auto& j : temp->fail->out)
					{
						temp->out.push_back(j);
					}
					q.push(temp);
				}
				else
				{
					cur->child[i] = cur->fail->child[i];
				}
			}
		}
	}
	vector<pair<int, int>> search(const string& word)
	{
		vector<pair<int, int>>ans;
		Node* cur = root;
		for (int i = 0; i < (int)word.size(); ++i)
		{
			int idx = word[i] - 'a';
			while (!cur->child[idx] && cur != root)
			{
				cur = cur->fail;
			}
			cur = cur->child[idx];
			if (!cur)
			{
				cur = root;
			}
			for (auto& j : cur->out)
			{
				ans.push_back(make_pair(j, i));
			}
		}
		return ans;
	}
public:
	ahoCorasick() { root = new Node(); builded = false; }
	void insert(const string& word, int id)
	{
		add(word, id);
	}
	vector<pair<int, int>> find(const string& word)
	{
		if (!builded)
		{
			build_pattern();
			builded = true;
		}
		return search(word);
	}
};
