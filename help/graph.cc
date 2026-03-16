#include<bits/stdc++.h>
using namespace std;

int main(){
    // --------------------Graph representation
    // Max edges = VC_2 = (V*(V-1))/2 = O(V^2)
    // Min edge = 0(if not connected) and V-1(if graph is connected---called tree)

    const int V = 10;  // Vertices

    // --------------------Adjacency matrix
    int mat[V][V];  // if mat[i][j]==0 then i---j is not a edge
                    // else if mat[i][j]==1 then i---j is a edge
                    // in case of weighted graph the weight itself can be given
                    // Space = O(V^2)
                    // Time = O(1) searching if edge is present or not
                    //        O(V) for searching neighbours



    //---------------------Edge list
    vector<pair<int, int>> edg;   // Space = O(E)
    edg.push_back({1, 2});
    edg.push_back({3, 2});
    edg.push_back({5, 2});



    //---------------------Adjacency list
    map<int, vector<int>> adj;  // Commonly Used
    /* 
    adj[u].push_back(v);
    if(Undirected)
        adj[v].push_back(u);
    else
        check then push
    */
                                // Space = O(E)
                                // Time = O(nbr) for searching nbrs
    //or
    list<int> l[V];
    // or
    vector<vector<int>> adj(V);
    //or
    vector<int> adj[V];
    // or
    // Nodes are letters or string and edges are weighted then use this
    unordered_map<string, vector<pair<string, int>>> adj;



    //---------------------Implicit Graph
    // 2-D array given see 'Labyrinth' in cses for clarity !!!IMP -- See Once Worth it




    //----------------------------Graph Traversal and uses
    // Both dfs and bfs takes O(V+E) Time
    //----------------------------Breadth first search(bfs)---level order traversal
    //The traversed part always form a tree (no cycle since we are keeping a check for visited nodes)
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        // print here the node
        for(auto nbr: adj[curr]){
            if(!vis[nbr]){
                q.push(nbr);
                vis[nbr] = 1;
            }
        }
    }




    //----------------------------Single source shortest path for unweighted graph
    map<int, vector<int>> adj;
    map<int, int> dis; // make all distance equal to infinity
    map<int, int> par;  // for finding the path 
    queue<int> q;
    q.push(src);
    dis[src] = 0;
    par[src] = -1;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (auto nbr : adj[curr]) {
            if (dis[nbr]==INT_MAX) {
                q.push(nbr);
                dis[nbr] = dis[curr] + 1;
                par[nbr] = curr;
            }
        }
    }
    int temp = dest;
    while(temp!=-1){
        cout << temp << "<---";
        temp = par[temp];
    }
    cout << src;

    //----------------------------Depth first search(dfs)
    // The traversed part always form a tree (no cycle since we are keeping a check for visited nodes)
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)
    void dfs(int curr){
        vis[curr] = 1;
        // print here the node
        for(auto nbr: adj[curr]){
            if(!vis[nbr])
                dfs(nbr);
        }
    }




    //--------------------------finding Connected component
    //any traversal will work
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)
    int comp = 0;       // counts the number of component
    void dfs(int curr) {
        vis[curr] = 1;
        // print here the node
        for (auto nbr : adj[curr]) {
            if (!vis[nbr]) dfs(nbr);
        }
    }
    for(auto node: adj){
        if(!vis[node.first]){
            comp++;
            dfs(node.first);
        }
    }





    //--------------------------flood fill algorithm for implicit graphs
    // used in MS paint to fill a region with a particular color
    int mat[n][m];   // 2-d mat
    int dx[4] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    int dy[4] = {0, 0, -1, 1};
    void floodfill(int i, int j, char toReplace, char replaceWithColor){
        // base case--matrix boundary
        if(i<0 || j<0 || i>=n || j>=m ){
            return;
        }
        // base case -- figure boundary
        if(mat[i][j]!=toReplace){
            return;
        }
        // recursive call
        mat[i][j] = replaceWithColor;
        for (int k = 0; k < 4;k++){
            floodfill(i + dx[k], j + dy[k], toReplace, replaceWithColor);
        } 
    }
    // call in main
    floodfill(8, 13, '.', 'R');




    //-----------------------cycle detection in undirected graph
    // using dfs
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)
    bool dfs(int curr, int par) {
        vis[curr] = 1;
        for (auto nbr : adj[curr]) {
            if (!vis[nbr]) {
                bool cycle_mila = dfs(nbr, curr);
                if (cycle_mila) return 1;
            }else if(nbr!=par){
                return 1;
            }
        }
        return 0;
    }
    // call in main
    dfs(src, -1);  // parent of src is not defined (take -1)




    //-----------------------Bipartite check
    // 2-colorable , graph with odd length cycle is not biparite graph
    map<int, vector<int>> adj; // nodes = [1,..N]
    map<int, int> vis;     // make all vertces 0 (not visited)
                        // if vis[]==0  not visited
                        //         ==1  visited and colored with 1
                        //         ==2  visited and colored with 2
    bool oddLen = 0;       // check if odd length cycle is present or not
    void dfs(int curr, int par, int col) {
        vis[curr] = col;
        for (auto nbr : adj[curr]) {
            if (vis[nbr]==0) {
                dfs(nbr, curr, 3-col);
            } else if (nbr != par && col == vis[nbr]) {
                oddLen = 1;
            }
        }
    }
    // call in main
    dfs(src, 0 /*=UNDEFINED */, 1);
    // check if odd cycle detected 
    if(oddLen==0) cout<<"Bipartite";
    else cout << "Not Biparite";




    //TODO: 
    //-----------------------Shortest cycle in undirected graph(***Hard)
    // perform bfs at each node and find the minimum cycle 
    // takes O(n^2) time
    map<int, vector<int>> adj;
    void bfs(int src, int n, int &ans){
        vector<int> dis(n+1, INT_MAX);  // dist of all vertces infinity 
        queue<int> q;
        q.push(src);
        dis[src] = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (auto nbr : adj[curr]) {
                if (dis[nbr]==INT_MAX) {
                    q.push(nbr);
                    dis[nbr] = dis[curr] + 1;
                }else if(dis[nbr] >= dis[curr]){
                    // backedge
                    ans = min(ans, dis[nbr] + dis[curr] + 1);
                    /*
                                    dis[curr]
                                o-----------------nbr==curr
                                \                /
                                 \-------------/
                                    dis[nbr]
                                
                                dis[nbr]+dis[curr]==edge length
                                edge length + 1==no of nodes in cycle
                    */
                }
            }
        }
    }
    // call from main
    int ans=n+1;   // There is no cycle of length n+1 so if this is not updated then there was no cycle
    for (int i = 1; i <= n;i++){  // n is the number of nodes ==> 1,2,3....n
        bfs(i, n, ans);
    } 
    if(ans==n+1){cout << "No cycle";}
    else        {cout << ans;}





    //-----------------------topological sorting(usinf dfs)
    // graph should be directed and acyclic(DAG) !!!!IMP
    // for topological sorting use dfs method since bfs method is tougher
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)
    list<int> ordering;     // gives the final topological ordering
    void dfs(int curr) {
        vis[curr] = 1;
        for (auto nbr : adj[curr]) {
            if (!vis[nbr]) dfs(nbr);
        }
        ordering.push_front(curr);  ///////This is the deciding statement
        return;
    }
    // call from main
    for(auto node: adj){
        if(!vis[node.first]){
            dfs(node.first);
        }
    }
    // then print the list
    for(auto i:ordering){
        cout << i << " ";
    }




    //TODO:
    //-------------------------topological sorting(usinf bfs)--Kahn's Algo(***Hard)
    // graph should be directed and acyclic(DAG)!!!!IMP
    // find the indegrees of all nodes and add to queue if indegree is 0
    map<int, vector<int>> adj;
    map<int, bool> vis;  // make all vertces 0 (not visited)

    void topo(){
        int indeg[V]{};
        // updating the indegree by traversing the edges 
        for(auto i:adj){
            for(auto j:i.second){
                indeg[j]++;
            }
        }
        //bfs
        queue<int> q;
        // find the nodes with indeg 0
        for (int i = 0; i < V;i++){
            if(indeg[i]==0){
                q.push(i);
            }
        } 
        // start removing elements from the queue
        while (!q.empty()){
            int curr = q.front();
            // print the topological order
            cout << curr<<" ";
            q.pop();
            // iterate the nbrs of curr node and reduce their indeg by 1
            for (auto nbr : adj[curr]) {
                indeg[nbr]--;
                if (indeg[nbr]==0) {
                    q.push(nbr);
                }
            }
        }
        
    }




    //TODO:
    //---------------------------cycle detection in directed graph(***Hard)
    map<int, vector<int>> adj;
    vector<bool> vis(n + 1, false); // n is number of node 1,2,3,....n
    vector<bool> individualVis(n + 1, false);
    bool cycle(int node){
        // visit a node
        vis[node] = 1;
        individualVis[node] = 1;
        for(auto nbr:adj[node]){
            if(!vis[nbr]){
                bool cyclemila = cycle(nbr);
                if (cyclemila) return true;
            }else if(individualVis[nbr]){
                return true;
            }
        }
        // leave a node
        individualVis[node] = 0;
        return 0;
    }
    // call in main
    for(auto i:adj){
        if (!vis[i.first]) cycle(i.first);
    }



    //FIXME:
    //????????????????????????????????????    T    O    D    O     ?????????????????????????????????

    //----------------------------kosarajus algo for strongly connected component (TODO : :::: SEE CLRS)(***Hard)
    // scc are defined for directed graphs: the set of nodes in a graph is scc if every node in that scc is reachable from evry other node in that scc
    // if graph is a DAG then all scc is of size 1
    // in the order list created if x comes before y then there is path from y to x (x and y belongs in the same scc)
    // steps:
    //1. dfs : get an ordering based upon the finish time
    //2. reverse the graph
    //3. again do a dfs on the nodes from right to left in ordering list (each dfs call will give the nodes in a scc)



    //????????????????????????????????????    T    O    D    O     ?????????????????????????????????




    //----------------------------DSU- Disjoint union set or Union-Find Data structure
    // non-overlapping sets
    // two operation: union and find


    // ---------------------------DSU using array-ds (ALWAYS USE THE OPTIMIZED ONE SEE BELOW)
    //====> Takes O(n) time in worst case for both union and find
    vector<int> parent(n+1, -1);  //make parent[i]=i
    int find(int v) {
        if (v == parent[v]) return v;
        return find(parent[v]);
    }
    void union_(int ele1, int ele2){       // union is already a keyword in c/c++
        int s1=find(ele1);
        int s2=find(ele2);
        if(s1!=s2){ // i.e. they are in different sets
            parent[s1]=s2;
        }
    }

    rep(i,200'001){         //making parent[i]=i
        parent[i]=i;
    }

    //-----------------------------cycle detection in graph using dsu
    // IMP : : : : First implement find() and union_() functions
    vector<int> par(n+1); // n-> # of vertices named from 1 to n
    // //make parent[i]=i
    // Make this parent vector and graph ds as global
    // in this example graph is considered to be represented as edge list
    // make appropriate changes for other repressentations
    vector<pair<int,int>> edgLis;
    bool isCycle(){     //also use rank array for optimized  
        // initially consider each vertex is an independent set
        for(int i=1;i<=n;i++){
            par[i]=-1;
        }

        // now iterate and add edges one by one
        for(auto edge: edgLis){
            int i=edge.F;
            int j=edge.S;
            int s1 = find(i);
            int s2 = find(j);
            if(s1!=s2){
                union_(s1,s2);
            }else{
                return 1;   // cycle found since elements are in same set
            }
        }
        return 0;
    }


    //----------------------------- Path compression optimization in dsu for find func
    int find(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    //------------------------------union by rank optimization in dsu
    // Reason for improvemnet: In trivial union func the bigger set may get 
    //connected to smaller component therefore lookup for some element will be more
    //-=====> Now along with parent we have to create a rank array to store the size of the set
    vector<int> rnk(n+1,1);  // we are only interested in values at indeces that are the root parent of sets
    // rest of the values are useless
    // initialise all values to 1 in rank array since each vertex is in their own set
    void union_(int ele1, int ele2) {  // union is already a keyword in c/c++
        int s1 = find(ele1);
        int s2 = find(ele2);
        if (s1 != s2) {  // i.e. they are in different sets
        //always connect the smaller tree to the bigger one 
            if(rnk[s1]<rnk[s2]){
                parent[s1]=s2;
                rnk[s2]+=rnk[s1];
            }
            else{
                parent[s2]=s1;
                rnk[s1]+=rnk[s2];
            }
        }
    }

    // TIME COMPLEXITY FOR OPTIMIZED DSU : IMP
    // If path compression is implemented then find() becomes O(logn) on average
    // Addition to path compression if union by rank is also implemented then 
    // time complexity of find() and union() both becomes very close to O(1) almost constant


        


    //----------------------------MST
    // What is MST? : : A minimum spanning tree or minimum weight spanning tree is a
    // subset of the edges of a connected, edge-weighted undirected graph that
    // connects all the vertices together, without any cycles and with the minimum
    // possible total edge weight. That is, it is a spanning tree whose sum of edge
    // weights is as small as possible
    //---------------------------Minimum spanning tree-Kruskal's Algo
    // TIME COMPLEXITY : O(E logV) -- most expensive part is sorting 
    // its a greedy algorithm
    vector<vector<int>> edgLis(no_of_edges);
    for(int i=0;i<no_of_edges;i++){
        int x,y,wei;
        cin>>x>>y>>wei;
        edgLis[i] = {wei, x, y};
    }
    sortinc(edgLis); // Sort in increasing order and add the edges to the MST one by one 
    // before checking that adding the edge doesnt create a cycle
    // Cycle detection is done using DSU
    int kruskal(){  // Make everything global or pass by reference
        int ans=0;
        for(int i=0;i<no_of_edges;i++){
            int x= edgLis[i][1];
            int y= edgLis[i][2];
            int wei= edgLis[i][0];
            if(find(x)!=find(y)){
                union_(x,y);
                ans+=wei;
            }
        }   
        return ans;
    }

    //---------------------------Minimum spanning tree-Prim's Algo
    // TIME COMPLEXITY : O(VlogV + ElogV) = O(ElogV), making it the same as Kruskal's algorithm
    // its a greedy algo
    // Similar to dijkstra's algo
    vector<pair<int,int>> adjLis[n+1];
    vector<int> vis(n+1,0); // initially all unvisited
    // form the adjacency list
    priority_queue<pii, vpi, greater<pii>> q;
    // also set can be used
    // can start algo with any vertex
    q.push({0,1});  // {wei, vertex}
    int ans=0;  // net weight of the MST
    while(!q.empty()){
        auto best = q.top();
        q.pop();
        int wei=best.F;
        int to = best.S;
        if(vis[to])continue;
        ans+=wei;
        vis[to]=1;

        for(auto nbr:adjLis[to]){
            if(vis[nbr.F]==0){
                q.push({nbr.F, nbr.S});
            }
        }
    }
    cout<<ans;



    //--------------------------------SSSP-Dijkstra's Algo
    // works for weighted edges graph- directed and undirected 
    // This algo may give wrong answer if the edges are negative.
    // TIME COMPLEXITY: O(V^2) but with min-priority queue it drops down to O (V+E logV)
    unordered_map<int, vector<pair<int,int>>> adjLis;    // node: {nbr_node, wei},.....
    set<pair<int,int>> s;   //{min_dist, node}
    vector<int> dist(N+1, INT_MAX);   // initially all unvisited hence dist is INF
    unordered_map<int, int> path;
    // visit the source node
    dist[src]=0;
    path[src]=-1;
    s.insert({0, src});
    while(!s.empty()){
        pair<int,int> cur=*(s.begin());
        s.erase(s.begin());
        for(auto nbr: adjLis[cur.S]){
            if(cur.F + nbr.S < dist[nbr.F]){
                //in set, updation is not possible so we have to remove 
                // and then again insert the updated value
                int dest=nbr.F;
                auto isfound = s.find({dist[dest], dest});
                if(isfound!=s.end()){
                    s.erase(isfound);
                }
                // updating the new dist
                dist[dest]=cur.F + nbr.S;
                s.insert({dist[dest], dest});
                path[nbr.F]=cur.S;
            }
        }
    }

    //print the path if required
    //.....

    //------------------------------------Bellman Ford Algo(SSSP)
    // 3 algo for finding SSSP
    //  _________|_______________
    //  |         |              |
    // bfs     dijkstra    bellman ford
    // TIME COMPLEXITY : Θ(VE) V is # of vertices and E is # of edges.
    // this is Dynamic Programming algo
    // If the graph is complete, the value of E = V => Θ(V^2)
    // Even works for negative weighted edges
    // *****Relaxes 'all' edges V-1 times
    // For a graph with V nodes the shortest path will be a tree and the number of
    // edges would be V-1 Therefore after V-1 iterations bellman ford gives correct
    // ans The order of the edge list will determine how quick the answer will
    // converge But since we do not know the graph any order after V-1 iteration
    // always gives correct ans
    // *****If there are negative cycles (reachable from the source), Bellman-Ford
    // can be considered to fail.A negative cycle is one in which the overall sum of
    // the cycle becomes negative. 
    // To detect a negative cycle we will relax for V
    // times if any dist is changed from the V-1th time then this means graph has
    // neg cycle, since we know We need atmost V-1 iteration to reach the final ans
    // and if at Vth step dist reduces further then it means neg cycle is present

    vector<vector<int>> edgLis;     // {u, v, wt}
    vector<int> dist(n+1, INT_MAX);
    unordered_map<ll,ll> path;
    path[src]=-1;
    dist[src]=0;
    bool negcy=0;   // for detecting negative cycle
    // relaxing V-1 times, Vth time to detect neg cycle
    for(int i=0;i<V;i++){
        for(auto edge: edgLis){
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if(dist[u]!=INT_MAX && dist[u]+wt<dist[v]){ // if dist[u] is INF then the +wt might overflow
                dist[v]=dist[u]+wt;                     // hence kept a check fot that
                path[v]=u;
                if(i==V-1){
                    negcy=1;
                    node=v;
                }
            }
        }
    }
    if(negcy){
        // contains neg cycle
        //2 cases:
        //1) the vertex stored in 'node' is part of the neg cycle
        //2) the vertex stored in 'node' is succeding part of the neg cycle, in this cases we need to
        // traceback to reach at a vertex which is part of the neg cycle, and this can be done by 
        // retracing V-1 times using the path vector, it is guaranteed that you will end up in 
        // neg cycle after V-1 tracebacks
        vll ans;    // to print the neg cycle
        REP(i, 1, n + 1) node = path[node];
        for (ll x = node;; x = path[x]) {
            ans.pb(x);
            if (x == node && ans.si > 1) break;
        }
        reverse(all(ans));
        print(ans);
    }
    else{
        // no neg cycle
    }



    //-------------------------------------Floyd Warshall Algo(All pair shortest path)
    // Gives shortest path between every pair of vertices
    // i.e. from 1-> all other
    //      fomr 2-> all other
    //          ......
    // This algo also works with neg edges
    // This algo can also detect neg cycles, with one extra step
    // this is DP based algo
    // TIME COMPLEXITY : O(V^3)
    // Adjacency matrix is used in representing
    vector<vector<int>> adjMat; // Initialise it with the given data from input - 0based indexing
    // note adjMat[i][i]=0, and if from i--j there is no edge then adjMat[i][j]=INT_MAX
    // *******Rather than using INT_MAX use INF=1e9+5 or any big value for avoiding overflow
    vector<vector<int>> dist(adjMat);   // initially the dist matrix will start from values same as adjMat
    // Phases: in kth phase we include (1,2,...k) as intermediate vertices
    for(int k=0;k<V;k++){
        // interate over the entire 2d matrix
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                // if vertex k in included, can we minimise the dist?
                if(dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }







    //-------------------------------Network Flow
    /*
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    //TODO:
    */

    return 0;
}