class Segtree
{
private:
	int n;
	ll MOD;
	vector<ll>tree;
	ll query_(int l, int r)
	{
		ll left = 0, right = 0;
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
	void update_(int index, ll delta)
	{
		index += n;
		tree[index] = delta % MOD;
		for (index >>= 1; index >= 1; index >>= 1)
		{
			tree[index] = (tree[index << 1] + tree[(index << 1) | 1]) % MOD;
		}
	}
public:
	Segtree(vector<ll>& v, ll mod = LLONG_MAX)
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
	ll query(int left, int right)
	{
		return query_(left - 1, right);
	}
	void update(int idx, ll value)
	{
		update_(idx - 1, value);
	}
};
