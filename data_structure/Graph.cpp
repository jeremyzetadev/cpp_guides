#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<stack>
#include<iostream>

using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;
    public:
        Graph(int V){
            this->V = V;
            adj = vector<vector<int>>(V, vector<int>(V,0));
        }

        void addEdge(int v, int w){
            adj[v].push_back(w);
            adj[w].push_back(v);
        }

        void DFS(int start){
            vector<bool> visited(V, false);
            DFS(start, visited);
        }

        void DFS(int start, vector<bool>& visited){
            cout << start << " ";
            visited[start] = true;
            for(int i : adj[start])
                if(visited[i] == false)
                    DFS(i, visited);
        }

        void BFS(int start){
            vector<bool> visited(adj.size(), false);
            queue<int> q;
            visited[start] = true;
            q.push(start);

            while(!q.empty()){
                int vis = q.front();
                q.pop();
                cout << vis << " ";
                for(int i :adj[vis]){
                    if(!visited[i]){
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
};

int main(void){
    int V = 7;
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Following Breath First Traversal\n";
    g.BFS(2);
    cout << endl;
    cout << "Following Depth First Traversal\n";
    g.DFS(2);
}
