#include <vector>
#include <queue>
#include <climits>


using namespace std;


bool bfs(const int v, vector<int>& level,const vector<vector<int>>& graph, int source, int sink){
    fill(level.begin(), level.end(), -1);
    vector<bool> visited(graph.size(), false);

    queue<int> q;

    level[source] = 0;
    visited[source] = true;
    q.push(source);

    while(!q.empty()){
        int current = q.front();
        q.pop();


        for(int x = 0 ; x < v ; x++){

            if(graph[current][x] > 0 && level[x] <0 && !visited[x]){
                level[x] = level[current] + 1;
                visited[x] = true;
                q.push(x);
            }
        }
    }

    return level[sink] >= 0;

    

}

int dfs(const int v, vector<int>& level ,vector<vector<int>>& residualGraph, int source, int sink, int flow){
    if (source == sink){
        return flow;
    }
    for(int i = 0 ; i< v; i++){

        if (residualGraph[source][i] > 0 && level[i] == level[source] + 1){

            int current_flow = min(residualGraph[source][i], flow);

            int bottle_neck = dfs(v, level, residualGraph, i, sink, current_flow );

            if (bottle_neck > 0){
                residualGraph[source][i] -= bottle_neck;
                residualGraph[i][source] += bottle_neck;
                return bottle_neck;

            }

        }
    }


    return 0;

}

int dinic_algorithm(const int v, const vector<vector<int>>& graph,int source, int sink){

    if (source == sink){
        return 0;
    }

    vector<vector<int>> residualGraph = graph;

    vector<int> level(v, -1);

    int max_flow = 0;

    //int flow = INT_MAX;

    

    while (bfs(v, level, residualGraph, source, sink)){

        while(true){

           int  flow = dfs(v, level, residualGraph, source, sink, INT_MAX);

           if (flow <= 0){
            break;
           }
            max_flow += flow;
        }


    }





    return max_flow;
}