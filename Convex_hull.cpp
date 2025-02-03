class Convex_hull
{
private:
	vector<pair<ll, ll>>point;
	int len;
	int ccw(pair<ll, ll>& a, pair<ll, ll>& b, pair<ll, ll>& c)
	{
		ll temp = a.first * b.second + b.first * c.second + c.first * a.second;
		temp -= a.second * b.first + b.second * c.first + c.second * a.first;
		return (temp < 0) ? -1 : (temp > 0) ? 1 : 0;
	}
	ll dist(pair<ll, ll>& a, pair<ll, ll>& b)
	{
		return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
	}
public:
	Convex_hull(vector<pair<ll, ll>>& v)
	{
		point = v;
		len = v.size();
	}
	vector<pair<ll, ll>> gethull()
	{
		if(len < 3)
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
		pair<ll, ll> pivot = point[0];
		sort(point.begin() + 1, point.end(), [&](pair<ll, ll>& a, pair<ll, ll>& b)
			{
				ll w = ccw(pivot, a, b);
				if (!w)
				{
					return dist(pivot, a) < dist(pivot, b);
				}
				return w > 0;
			});
		vector<pair<ll, ll>>hull;
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
