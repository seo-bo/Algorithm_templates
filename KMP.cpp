class KMP
{
private:
	string base, target;
	int base_len, target_len;
	vector<int> fail_()
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
	vector<int> matching_(vector<int>pattern)
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
	}
	vector<int> fail()
	{
		return fail_();
	}
	vector<int> matching()
	{
		return matching_(fail());
	}
};
