#include<bits/stdc++.h>
using namespace std;


vector<vector<int>> network(101,vector<int>(101,0)), capacity(101,vector<int>(101,0)), games(101,vector<int>(101,0));
vector<int>win(100), loss(100), matchLeft(100);
map<int, string> names; //For team number to team name correspondence
const int inf=1e9;
int parentsList[100];
vector<bool> visited(100,false);
vector<int> mAge(51), mHeight(51), mDivorced(51),fAge(51), fHeight(51), fDivorced(51);



int bfs(int source, int sink){
    //Initialize all nodes parents to -1 so that we can keep track of who was visited with parents help
    memset(parentsList, -1, sizeof(parentsList)); 

    queue<pair<int,int>> q;
    q.push({source,inf});   //push source to queue
    parentsList[source] = -3;

    while(!q.empty()){
        int currNode = q.front().first;
        int forwardFlow = q.front().second;
        q.pop();


        for(auto x :  network[currNode]){
            if(parentsList[x]==-1 && capacity[currNode][x]!=0){
                parentsList[x] = currNode;
                int p = capacity[currNode][x];
                int temp = min(forwardFlow, p);

                if(x==sink){    //Destination reached so return
                    return temp;
                }

                q.push({x,temp});
            }
        }
    }

    return 0;

}

int edmond_carp(int source, int sink){

    int maxflow=0;
    int temp;

    while(true){
        temp  = bfs(source, sink);

        if(temp==0){    //this means zero flow is possible now from the source to the sink, thus we terminate the algorithm
            break;
        }

        maxflow +=  temp;

        int currNode = sink;

        while(currNode!=source){    //Backtracking
            int prevNode = parentsList[currNode];
            capacity[currNode][prevNode]  += temp;
            capacity[prevNode][currNode]  -= temp;
            currNode = prevNode;
        }

    }

    return maxflow;

}


int check(string s){
    if(s=="XXL"){
        return 1;
    }
    if(s=="XL"){
        return 2;
    }
    if(s=="L"){
        return 3;
    }

    if(s=="M"){
        return 4;
    }

    if(s=="S"){
        return 5;
    }

    if(s=="XS"){
        return 6;
    }
}


int main(){

    int source =0, sink =1000;

    int t=1;
    //cin>>t;
    while(t>0){
        int n,m;
        cin>>n>>m;
        string s1, s2;

        for(int i=1; i<=m; i++){
            cin>>s1>>s2;

            //size1 to person
            network[check(s1)].push_back(i+10);
            network[i+10].push_back(check(s1));

            //size2 to person
            network[check(s2)].push_back(i+10);
            network[i+10].push_back(check(s2));

            //destination to person
            network[i+10].push_back(sink);
            network[sink].push_back(i+10);

            //C size to persons
            capacity[check(s1)][i+10]=1;
            capacity[i+10][sink] =inf;
            //capacity[sink][i+10] = inf;

            // network[source].push_back(check(s1));
            // network[check(s1)].push_back(source);
            // network[source].push_back(check(s2));
            // network[check(s2)].push_back(source);

        }

        for(int i=1; i<=6; i++){
            //source to sizes
            network[source].push_back(i);
            network[i].push_back(source);
            //C source to sizes
            capacity[source][i] = n;
        }

        int flow  = edmond_carp(source, sink);

        if(flow<n){
            cout<<"No"<<endl;
        }
        else
            cout<<"Yes"<<endl;
            
        cout<<flow<<endl;


        t--;
    }
}