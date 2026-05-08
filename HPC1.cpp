// Parallel BFS & DFS using OpenMP
// Compile: g++ file.cpp -fopenmp
// Run: ./a.out

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<omp.h>
using namespace std;

vector<vector<int>> g;

// BFS Function
void bfs(int s,int n,bool parallel){
    vector<bool> vis(n,false);
    queue<int> q;
    q.push(s);
    vis[s]=true;

    double st=omp_get_wtime();

    cout<<(parallel?"\nParallel BFS: ":"\nSimple BFS: ");

    while(!q.empty()){
        int node=q.front(); q.pop();
        cout<<node<<" ";

        #pragma omp parallel for if(parallel)
        for(int i=0;i<g[node].size();i++){
            int nbr=g[node][i];

            if(!vis[nbr]){
                vis[nbr]=true;

                #pragma omp critical
                q.push(nbr);
            }
        }
    }

    cout<<"\nTime: "<<omp_get_wtime()-st<<" sec\n";
}

// DFS Function
void dfs(int s,int n,bool parallel){
    vector<bool> vis(n,false);
    stack<int> stc;
    stc.push(s);

    double st=omp_get_wtime();

    cout<<(parallel?"\nParallel DFS: ":"\nSimple DFS: ");

    while(!stc.empty()){
        int node=stc.top(); stc.pop();

        if(!vis[node]){
            vis[node]=true;
            cout<<node<<" ";

            #pragma omp parallel for if(parallel)
            for(int i=0;i<g[node].size();i++){

                int nbr=g[node][i];

                if(!vis[nbr]){

                    #pragma omp critical
                    stc.push(nbr);
                }
            }
        }
    }

    cout<<"\nTime: "<<omp_get_wtime()-st<<" sec\n";
}

int main(){
    int n,e,u,v,s;

    cout<<"Enter vertices and edges: ";
    cin>>n>>e;

    g.resize(n);

    cout<<"Enter edges:\n";
    for(int i=0;i<e;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout<<"Enter start node: ";
    cin>>s;

    bfs(s,n,false);
    bfs(s,n,true);

    dfs(s,n,false);
    dfs(s,n,true);

    return 0;
}
/*Enter vertices and edges: 5 4
Enter edges:
0 1
0 2
1 3
2 4
Enter start node: 0

Simple BFS: 0 1 2 3 4
Time: 0.000021 sec

Parallel BFS: 0 1 2 3 4
Time: 0.000010 sec

Simple DFS: 0 2 4 1 3
Time: 0.000018 sec

Parallel DFS: 0 2 4 1 3
Time: 0.000009 sec*/