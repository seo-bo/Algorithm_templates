class Segtree //https://github.com/seo-bo/Algorithm_templates/blob/main/Segtree.cpp
{
private:
	int n;
	long long MOD;
	vector<long long>tree;
	long long get_sum(int l, int r)
	{
		long long left = 0, right = 0;
		l += n, r += n;
		while (l < r)
		{
			if (l & 1)
			{
				left = (left + tree[l++]) % MOD;
			}
			if (r & 1)
			{
				right = (right + tree[--r]) % MOD;
			}
			l >>= 1;
			r >>= 1;
		}
		return (left + right) % MOD;
	}
	void update_tree(int index, long long delta)
	{
		index += n;
		tree[index] = delta % MOD;
		for (index >>= 1; index >= 1; index >>= 1)
		{
			tree[index] = (tree[index << 1] + tree[(index << 1) | 1]) % MOD;
		}
	}
public:
	Segtree(vector<long long>& v, long long mod = LLONG_MAX)
	{
		n = v.size();
		MOD = mod;
		tree.resize(2 * n);
		for (int i = 0; i < n; ++i)
		{
			tree[n + i] = v[i] % MOD;
		}
		for (int i = n - 1; i > 0; --i)
		{
			tree[i] = (tree[i << 1] + tree[(i << 1) | 1]) % MOD;
		}
	}
	long long query(int left, int right)
	{
		return get_sum(left - 1, right);
	}
	void update(int idx, long long value)
	{
		update_tree(idx - 1, value);
	}
};
