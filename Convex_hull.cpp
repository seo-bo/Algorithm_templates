class Convex_hull //https://github.com/seo-bo/Algorithm_templates/blob/main/Convex_hull
{
private:
	vector<pair<long long, long long>>point;
	int len;
	int ccw(pair<long long, long long>& a, pair<long long, long long>& b, pair<long long, long long>& c)
	{
		long long temp = a.first * b.second + b.first * c.second + c.first * a.second;
		temp -= a.second * b.first + b.second * c.first + c.second * a.first;
		return (temp < 0) ? -1 : (temp > 0) ? 1 : 0;
	}
	long long dist(pair<long long, long long>& a, pair<long long, long long>& b)
	{
		return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
	}
public:
	Convex_hull(vector<pair<long long, long long>>& v)
	{
		point = v;
		len = v.size();
	}
	vector<pair<long long, long long>>gethull()
	{
		if (len < 3)
		{
			return point;
		}
		int idx = 0;
		for (int i = 1; i < len; ++i)
		{
			if (point[i].second < point[idx].second || (point[i].second == point[idx].second && point[i].first < point[idx].first))
			{
				idx = i;
			}
		}
		swap(point[0], point[idx]);
		pair<long long, long long> pivot = point[0];
		sort(point.begin() + 1, point.end(), [&](pair<long long, long long>& a, pair<long long, long long>& b)
			{
				long long w = ccw(pivot, a, b);
				if (!w)
				{
					return dist(pivot, a) < dist(pivot, b);
				}
				return w > 0;
			});
		vector<pair<long long, long long>>hull;
		hull.push_back(point[0]);
		hull.push_back(point[1]);
		for (int i = 2; i < len; ++i)
		{
			while (hull.size() >= 2 && ccw(hull[(int)hull.size() - 2], hull[(int)hull.size() - 1], point[i]) <= 0)
			{
				hull.pop_back();
			}
			hull.push_back(point[i]);
		}
		return hull;
	}
};