class Manacher //https://github.com/seo-bo/Algorithm_templates/blob/main/Manacher.cpp
{
private:
	string base;
	long long MOD;
	int len;
	vector<int> solve()
	{
		vector<int>R(len, 0);
		int r = 0, p = 0;
		for (int i = 0; i < len; ++i)
		{
			if (i <= r)
			{
				R[i] = min(R[2 * p - i], r - i);
			}
			while (0 <= i - R[i] - 1 && i + R[i] + 1 < len && base[i - R[i] - 1] == base[i + R[i] + 1])
			{
				R[i]++;
			}
			if (r < i + R[i])
			{
				r = i + R[i];
				p = i;
			}
		}
		return R;
	}
public:
	Manacher(string str)
	{
		base = "?";
		for (auto& i : str)
		{
			base += i;
			base += '?';
		}
		len = base.size();
		MOD = LLONG_MAX;
	}
	Manacher(string str, long long mod) : Manacher(str)
	{
		MOD = mod;
	}
	long long palin()
	{
		vector<int>R = getR();
		long long count = 0;
		for (int i = 0; i < len; ++i)
		{
			count = (count + (R[i] + 1LL) / 2) % MOD;
		}
		return count;
	}
	vector<int> getR()
	{
		return solve();
	}
};