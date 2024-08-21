#include<bits/stdc++.h>
#include<iostream>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, double> iPair;
vector<int>parent1(10001),parent2(10001);


const int n= 10000;
int parent[n];      //utility array for disjoint_set operation,keeps track of the parent of a component
int size1[n],size2[n];        //Keeps track of the size so that we may join our new subtree to the less sized one


//Makes each node an independent set,complexity O(1)
void make_set(int v){
    parent[v]=v;
    size1[v]=1;
}

//Find the parent of a set, path compression used for relaxed runtime in the long run O(1)
int find1(int v){
    if(parent1[v]==v) return v;
    else
        return parent1[v] = find1(parent1[v]);
}



//Join two sets together, joining them based on size so that the tree remains as less deep as possble, complexity O(1)
void Union1(int a, int b){
    a = find1(a);
    b = find1(b);

    if(a!=b){
        if(size1[a]<size1[b]){
            swap(a,b);
        }
        parent1[b] = a;
        size1[a]+= size1[b];
    }
}

int find2(int v){
    if(parent2[v]==v) return v;
    else
        return parent2[v] = find2(parent2[v]);
}


void Union2(int a, int b){
    a = find2(a);
    b = find2(b);

    if(a!=b){
        if(size2[a]<size2[b]){
            swap(a,b);
        }
        parent2[b] = a;
        size2[a]+= size2[b];
    }
}





void kruskal1(int nodes, vector<pair<int, pair<int,double>>> adj, double &total_cost1, double &total_cost11){
    sort(adj.begin(), adj.end());   //Sorting in ascending order, compleixty O(nlogn)

    for(int i=1; i<=nodes; i++){
        make_set(i);    //Make indivitual set for all of the vertices, complexity O(1)
    }

    //Storing the total cost to traverse the graph as an mst

    //cout<<"List of edges selected by Kruskal: {";
    int temp = 1;
    for(auto &v: adj){  //Since the edges are already sorted so we get the least cost edge each time and we only need to check for cycles
        int weight = v.first;
        int x = v.second.first;
        int y =  v.second.second;

        if(find1(x)==find1(y)) continue; //Having same parents,then connected components

        Union1(x,y);                 //Having different parents,thus an edge between them won't create a cycle
//        cout<<"("<<x<<","<<y<<")";
//        if(temp != nodes-1){
//            cout<<",";
//            temp++;
//        }

        if(weight==3){
            total_cost1++;
        }
        else{
            total_cost11++;
        }

    }
    //cout<<"}"<<endl;

    //cout<<setprecision(2)<< total_cost<<endl;
}


void kruskal2(int nodes, vector<pair<int, pair<int,double>>> adj, double &total_cost2, double &total_cost22){
    sort(adj.begin(), adj.end());   //Sorting in ascending order, compleixty O(nlogn)

    for(int i=1; i<=nodes; i++){
        make_set(i);    //Make indivitual set for all of the vertices, complexity O(1)
    }

    //Storing the total cost to traverse the graph as an mst

   // cout<<"List of edges selected by Kruskal: {";
    int temp = 1;
    for(auto &v: adj){  //Since the edges are already sorted so we get the least cost edge each time and we only need to check for cycles
        int weight = v.first;
        int x = v.second.first;
        int y =  v.second.second;

        if(find2(x)==find2(y)) continue; //Having same parents,then connected components

        Union2(x,y);                 //Having different parents,thus an edge between them won't create a cycle
//        cout<<"("<<x<<","<<y<<")";
//        if(temp != nodes-1){
//            cout<<",";
//            temp++;
//        }

        if(weight==3){
            total_cost2++;
        }
        else{
            total_cost22++;
        }

    }
    //cout<<"}"<<endl;

    //cout<<setprecision(2)<< total_cost<<endl;
}


int main()
{

	//stream redirection

    int nodes,edges;
	double total_cost=0,total_cost1=0,total_cost2=0,total_cost11=0,total_cost22=0;
    cin>>nodes>>edges;

	vector<pair<int, pair<int,double>>> adj1;
	vector<pair<int, pair<int,double>>> adj2; //vector for storing edges and cost

    for(int i = 0 ;i<edges ; i++){
        int x, y;
		double w;
        cin>>x>>y>>w;

        if(w==3){
            adj1.push_back({w,{x,y}});
            adj2.push_back({w,{x,y}});
        }
        if(w==2){
            adj2.push_back({w,{x,y}});
        }
        if(w==1){
            adj1.push_back({w,{x,y}});
        }

    }


	kruskal1(nodes,adj1, total_cost1,total_cost11);
	kruskal2(nodes,adj2, total_cost2,total_cost22);

	if(total_cost1+total_cost11!=nodes-1 || total_cost2+total_cost22!=nodes-1 || total_cost1!=total_cost2)
        cout<<-1<<endl;
    else {
        cout<<edges-(total_cost1+total_cost11+total_cost22)<<endl;
    }


	return 0;
}
