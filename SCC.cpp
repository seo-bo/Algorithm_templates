class SCC //https://github.com/seo-bo/Algorithm_templates/blob/main/SCC.cpp 
{
private:
	int V, cnt, ver;
	vector<vector<int>>graph, DAG_graph;
	vector<int>low, num, id, stk;
	vector<bool>in;
	void tarjan(int node)
	{
		num[node] = low[node] = ++cnt;
		stk.push_back(node);
		in[node] = true;
		for (auto& i : graph[node])
		{
			if (!num[i])
			{
				tarjan(i);
				low[node] = min(low[node], low[i]);
			}
			else if (in[i])
			{
				low[node] = min(low[node], num[i]);
			}
		}
		if (num[node] == low[node])
		{
			while (1)
			{
				int cur = stk.back();
				stk.pop_back();
				in[cur] = false;
				id[cur] = ver;
				if (cur == node)
				{
					break;
				}
			}
			ver++;
		}
	}
	vector<vector<int>>DAG()
	{
		int len = *max_element(id.begin() + 1, id.end()) + 1;
		DAG_graph.resize(len);
		for (int i = 1; i <= V; ++i)
		{
			for (auto& j : graph[i])
			{
				if (id[i] != id[j])
				{
					DAG_graph[id[i]].push_back(id[j]);
				}
			}
		}
		return DAG_graph;
	}
public:
	SCC(int vertex, vector<vector<int>>& G)
	{
		V = vertex;
		graph = G;
		low.resize(V + 1, 0);
		num.resize(V + 1, 0);
		id.resize(V + 1, -1);
		in.resize(V + 1, false);
		cnt = 0, ver = 1;
		for (int i = 1; i <= V; ++i)
		{
			if (!num[i])
			{
				tarjan(i);
			}
		}
	}
	vector<int>get_id()
	{
		return id;
	}
	vector<vector<int>>get_DAG()
	{
		return DAG();
	}
};
