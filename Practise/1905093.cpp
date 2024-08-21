#include<bits/stdc++.h>
using namespace std;

vector<int> E[100000];
vector<bool> visited[10000];
vector<int> times[100000];
vector<int> timef[100000];


struct Graph
{
	int V, E;
	vector< pair<int, iPair> > edges;

	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({w, {u, v}});
	}
};



void dfs(long long int k)
{
    times[k]=timer;
    timer = timer++;
    visited[k] = true;
    for(auto v: E[k]){
        if(visited[v]==false){
            dfs(v);
            parent[v]=u;
        }
    }

    timef[k]=timer;
}

int main()
{
	int n;
	cin>>n;
	int s;
	cin>>s;
	for(int i=0;i<s;i++)
    {
    int x,y;
    cin>>x>>y;
    E[x].push_back(y);
    }

	return 0;
}



















