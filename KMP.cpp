class KMP
{
private:
	string base, target;
	int base_len, target_len;
	vector<int>pattern;
	vector<int> get_fail()
	{
		vector<int>pattern(target_len, 0);
		int left = 0;
		for (int right = 1; right < target_len; ++right)
		{
			while (left > 0 && target[left] != target[right])
			{
				left = pattern[left - 1];
			}
			if (target[left] == target[right])
			{
				pattern[right] = ++left;
			}
		}
		return pattern;
	}
	vector<int> matching()
	{
		vector<int>count;
		int left = 0;
		for (int right = 0; right < base_len; ++right)
		{
			while (left > 0 && base[right] != target[left])
			{
				left = pattern[left - 1];
			}
			if (base[right] == target[left])
			{
				if (++left == target_len)
				{
					count.push_back(right - target_len + 2);
					left = pattern[left - 1];
				}
			}
		}
		return count;
	}
public:
	KMP(const string& s1, const string& s2) : base(s1), target(s2)
	{
		base_len = s1.size();
		target_len = s2.size();
		pattern.resize(target_len,0);
		get_fail();
	}
	vector<int> fail()
	{
		return pattern;
	}
	vector<int> match()
	{
		return matching();
	}
};
