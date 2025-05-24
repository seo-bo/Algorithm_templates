class CCW //https://github.com/seo-bo/Algorithm_templates/blob/main/CCW.cpp
{
private:
	vector<pair<long long, long long>>pos1;
	vector<pair<long long, long long>>pos2;
	int ccw(pair<long long, long long>&a, pair<long long, long long>&b, pair<long long, long long>&c)
	{
		long long temp = a.first * b.second + b.first * c.second + c.first * a.second;
		temp -= a.second * b.first + b.second * c.first + c.second * a.first;
		return (temp < 0) ? -1 : (temp > 0) ? 1 : 0;
	}
	int solve()
	{
		long long xy = ccw(pos1[0], pos1[1], pos2[0]) * ccw(pos1[0], pos1[1], pos2[1]);
		long long yx = ccw(pos2[0], pos2[1], pos1[0]) * ccw(pos2[0], pos2[1], pos1[1]);
		if (xy == 0 && yx == 0)
		{
			if (pos1[0] > pos1[1])
			{
				swap(pos1[0], pos1[1]);
			}
			if (pos2[0] > pos2[1])
			{
				swap(pos2[0], pos2[1]);
			}
			return (pos1[0] <= pos2[1] && pos2[0] <= pos1[1]);
		}
		return (xy <= 0 && yx <= 0);
	}
public:
	CCW(vector<long long>& pos)
	{
		pos1 = { make_pair(pos[0],pos[1]),make_pair(pos[2],pos[3]) };
		pos2 = { make_pair(pos[4],pos[5]), make_pair(pos[6],pos[7]) };
	}
	int get_ccw()
	{
		return solve();
	}
};
