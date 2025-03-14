class DSU //https://github.com/seo-bo/Algorithm_templates/blob/main/DSU.cpp
{
private:
	int n;
	vector<int>parent, rank;
	int get_path(int root)
	{
		return (parent[root] == root) ? parent[root] : parent[root] = get_path(parent[root]);
	}
	void merger(int root1, int root2)
	{
		int r1 = get_path(root1), r2 = get_path(root2);
		if (r1 != r2)
		{
			if (rank[r1] > rank[r2])
			{
				parent[r2] = r1;
			}
			else
			{
				parent[r1] = r2;
				if (rank[r1] == rank[r2])
				{
					rank[r2]++;
				}
			}
		}
	}
public:
	DSU(int ok)
	{
		n = ok;
		parent.resize(n + 1, 0);
		rank.resize(n + 1, 0);
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int root)
	{
		return get_path(root);
	}
	void merge(int root1, int root2)
	{
		merger(root1, root2);
	}
};
