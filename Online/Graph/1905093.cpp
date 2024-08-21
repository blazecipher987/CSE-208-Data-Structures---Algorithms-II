#include <bits/stdc++.h>
using namespace std;



void bfs(vector<int> adj[], vector<int> &visit, vector<int> &dist, int source, vector<int> &parents){
    visit[source] = 1;
    dist[source] =0;

    queue<int> q;

    q.push(source);

    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto j : adj[v]){
            if(visit[j]==0){
                q.push(j);
                visit[j]=1;
                if(dist[v] +1 < dist[j])
                    {
                        dist[j] = dist[v] + 1;
                        parents[j] = v;
                    }
            }


        }
    }
}

int main(){
    int n,m;
    string s;

    cin>>s;
    int sizee = s.size();
    vector<int> adj[sizee];
    vector<int> gotten(10,0);

//    for(int i =0 ; i <=sizee ;i++){
//            adj[i].push_back(i+1);
//        if(gotten[s[i]]==0){
//                string temp = s[i];
//                int backs = sizee-1;
//                while(s[backs]!=temp){
//                    backs--;
//                }
//                adj[i].push_back(backs);
//        }
//    }


    for(int i= 0 ;i<=sizee ; i++){
        adj[i].push_back(i+1);
        char temp = s[i];

        for(int j =1 ; j<=sizee; j++){
            if(s[j]==temp){
                adj[i].push_back(j);
            }
        }
    }


    int source = 0, dest=sizee-1;
    //cin>>source>>dest;


//    for(int i= 0 ;i <m ;i++){
//        int x,y;
//        cin>>x>>y;
//        adj[x].push_back(y);
//    }

    vector<int> dist(sizee+1,1000);
    vector<int> visit(sizee,0);
    vector<int> parents(sizee+1, 0);

    bfs(adj, visit, dist, source,dest);

    if(dist[dest]!=1000){
        cout<<dist[sizee-1]<<endl;
    }
    else{
        cout<<"Not Reachable"<<endl;
    }

    // for(int i = 0; i<=n ; i++){
    //     cout<<i<<" : "<<dist[i]<<endl;
    //     cout<<"Parent: "<<parents[i]<<endl;
    // }

}
