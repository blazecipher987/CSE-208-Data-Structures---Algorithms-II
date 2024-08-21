#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tlld tuple<ll,ll,double>

int const n = 10000;
int const inf = 1e18;


vector<tlld>E;  //{inital vertex,final vertex,cost}
vector<double>dis(1001,-inf); //for maintaining distance
vector<ll>parent(1001,-1),sol;     //FOR BACKTRACKING
//vector<bool>vis(1001,false);

bool cycle=false;
bool pathExist=true;    //tO KEEP TRACK OF REACHABLE DESTINATION

void Bellman_Ford(ll source,ll des,ll n,ll m){
    ll i,x,j,to,from;
    double w;
    dis[source]=1; //source must be 1 since we are doing multiplication

    for(i=0;i<n;i++){ //We are relaxing the edge and doing bellman ford at once
        x=-1;
        for(j=0;j<m;j++){
            int u=get<0>(E[j]); //initial vertex
            int v=get<1>(E[j]);   //ending vertex
            w=get<2>(E[j]);    //edge weight

            if(dis[u] * w > dis[v]){ //the more number the more reliable
                dis[v]=dis[u]*w;
                x=v;
                parent[v]=u; //for backtracking purpose
            }
        }
    }

    // if(x!=-1){
    //     cycle=true;

    //     for(i=0;i<n-1;i++){
    //         for(j=0;j<m;j++){
    //             from=get<0>(E[j]);
    //             to=get<1>(E[j]);        
    //             w=get<2>(E[j]);

    //             if(dis[from] + w < dis[to]){
    //                 dis[to]=dis[from]+w;
    //                 parent[to]=from;
    //                 if(mp[to]==1) pathExist=false;
    //             }
    //             if(pathExist==false) break;
    //         }
    //         if(pathExist==false) break;
    //     }
    // } 

    if(dis[des]==1e18)
        pathExist=false; //Destination not reached if it's infinite after relaxation
}

int main(){

    // freopen("in", "r", stdin);
    // freopen("out", "w", stdout);

    ll i,j,k,n,m,x,y,source,des;
    double w;

    cin>>n>>m;

    for(i=0;i<m;i++){
        cin>>x>>y>>w;
        E.pb(make_tuple(x,y,w)); //The underlying graph structure
    }

    cin>>source>>des;

    //dfs(des);
    Bellman_Ford(source,des,n,m);

    // if(cycle)
    //     cout<<"The graph contains a negative cycle"<<endl; 
    // else cout<<"The graph does not contain a negative cycle"<<endl;

    if(pathExist==true){
        
        x=des;
        while(x!=-1){ 
            sol.pb(x);
            x=parent[x];
        } 

        cout<<"Most reliable path score: "<<dis[des]<<endl;
        for(i=sol.size()-1;i>=0;i--){
            cout<<sol[i];
            if(i!=0) cout<<" -> ";
        }
    }
    else cout<<"Destinationnot reachable"<<endl;
}

