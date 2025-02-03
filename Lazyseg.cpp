class Lazyseg
{
private:
	int n;
	ll MOD;
	vector<ll>tree, lazy;
	void build(vector<ll>& v, int start, int end, int node)
	{
		if (start == end)
		{
			tree[node] = v[start];
			return;
		}
		int mid = (start + end) / 2;
		build(v, start, mid, node * 2);
		build(v, mid + 1, end, node * 2 + 1);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
	}
	void lazy_update(int start, int end, int node)
	{
		if (lazy[node])
		{
			tree[node] = (tree[node] + (end - start + 1) * lazy[node]) % MOD;
			if (start != end)
			{
				lazy[node * 2] = (lazy[node * 2] + lazy[node]) % MOD;
				lazy[node * 2 + 1] = (lazy[node * 2 + 1] + lazy[node]) % MOD;
			}
			lazy[node] = 0;
		}
	}
	void update_tree(int start, int end, int node, int left, int right, ll value)
	{
		lazy_update(start, end, node);
		if (start > right || end < left)
		{
			return;
		}
		if (left <= start && end <= right)
		{
			tree[node] = (tree[node] + (end - start + 1) * value) % MOD;;
			if (start != end)
			{
				lazy[node * 2] = (lazy[node * 2] + value) % MOD;
				lazy[node * 2 + 1] = (lazy[node * 2 + 1] + value) % MOD;
			}
			return;
		}
		int mid = (start + end) / 2;
		update_(start, mid, node * 2, left, right, value);
		update_(mid + 1, end, node * 2 + 1, left, right, value);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
	}
	ll get_sum(int start, int end, int node, int left, int right)
	{
		lazy_update(start, end, node);
		if (start > right || end < left)
		{
			return 0LL;
		}
		if (left <= start && end <= right)
		{
			return tree[node];
		}
		int mid = (start + end) / 2;
		return (query_(start, mid, node * 2, left, right) + query_(mid + 1, end, node * 2 + 1, left, right)) % MOD;
	}
public:
	Lazyseg(vector<ll>& v, ll mod = LLONG_MAX)
	{
		n = v.size();
		MOD = mod;
		tree.resize(4 * n + 3, 0);
		lazy.resize(4 * n + 3, 0);
		build(v, 0, n - 1, 1);
	}
	void update(int left, int right, ll value)
	{
		if (left > right)
		{
			swap(left, right);
		}
		update_tree(0, n - 1, 1, left, right, value);
	}
	ll query(int left, int right)
	{
		if (left > right)
		{
			swap(left, right);
		}
		return get_sum(0, n - 1, 1, left, right);
	}
};
