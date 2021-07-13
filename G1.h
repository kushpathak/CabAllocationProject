#ifndef G1_H_INCLUDED
#define G1_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;
const int maxsize = 1e2+5;
class Graph{
    map<string,vector<pair<string,int> > >adjlist;
    map<pair<string,string>,int >actual;
    map<string,int>area;
    int fpc;
public:
    Graph(){
        /* Initialise the graph datastructure with fare per km = 6*/

        fpc = 6;
    }

    int getsize(){
        /* Function to get the size of the adjacency list */
        return adjlist.size();
    }
    void add_edge(string u,string v,int w){
        
       /*   
            Function that adds a new edge from source to destination with a weight of w
       */
       adjlist[u].push_back({v,w});
       adjlist[v].push_back({u,w});
       actual[{u,v}]=w;
       actual[{v,u}]=w;
    }
    void update_weight(string u,string v,int w){
      /*
        Function that updates the weight of edge u - v to w
      */
      for(int i=0;i<adjlist[u].size();i++){

            if(adjlist[u][i].first==v)
            {
                adjlist[u][i].second += w;
                return;
            }
      }
    }

    void dfs_util(string src,map<string,bool>&vis,int Area){
        /*
            Utility Function to assign area/locality to every node in a graph
            Every connected component will belong to an area/locality  
        */
        vis[src]=1;
        area[src]=Area;
        for(auto i : adjlist[src]){
            if(vis[i.first]==0){
                dfs_util(i.first,vis,Area);
            }
        }
    }
    void allocate_area(){
        /*
            Main Function to allocate area to every node in the graph
        */
        int compo=1;
        map<string,bool>vis;
        for(auto i : adjlist){
            if(vis[i.first]==0){
                dfs_util(i.first,vis,compo);
                compo++;
            }
        }
    }
    bool check_area(string a,string b){
        /*
            Function to check whether locations a and b belong to the same area 
            or not
        */
        return area[a]==area[b];
    }
    void dijkstra(string src,string dest,int fare){
        /*
            Function to calculate shortest path between
            src and dest using dijkstra's algo
        */
        map<string,int>dist;
        map<string,string>parent;
        set<pair<int,string> >st;
        for(auto i : adjlist){
            //Initially every node in the graph is unreachable
            dist[i.first]=INT_MAX;
           
        }
        //Since the source node is having distance 0 from itself
        dist[src]=0;
        st.insert({0,src});
        int d=0;
        while(!st.empty()){
            
            // Pick a node having minimum cost uptill now

            pair<int,string>p = *st.begin();
            
            // We are now fixing its cost as final cost 

            st.erase(p);
            string s = p.second;
            int nodedist = p.first;

            // Iterate over all of its neighbours

            for(auto neighbours : adjlist[s]){

                // Check if dist[neighbour] > dist[cur] + edge_w(cur,neighbour)
                // If this is the case then update the neighbour's weight in the graph

                if(nodedist+neighbours.second<dist[neighbours.first]){
                    auto f = st.find({dist[neighbours.first],""});
                    if(f!=st.end())
                      st.erase(f);
                    st.insert(make_pair(nodedist+neighbours.second,neighbours.first));
                    dist[neighbours.first]=nodedist+neighbours.second;

                    // We are also mantaining track of parent of each node so 
                    // as to backtrack while finding the required path
                    
                    parent[neighbours.first]=s;
                }
            }
        }
        vector<string>route;
        string prev = "";
        while(dest!=src){
            
            // backtracking from the destination node untill we reach the source node

            route.push_back(dest);
            d+=actual[{prev,dest}];
            prev = dest;
            dest = parent[dest];
        }

        // Printing the path

        d+=actual[{prev,dest}];
        cout << "                ---------------    ---   HERE IS YOUR ROUTE  ---   --------------------\n";
        int cur = 1;
        cout << "\n" << cur << " " << src << "\n";
        cur++;
        reverse(route.begin(),route.end());
        for(auto i : route){
            cout << cur << " " << i << "\n";
            cur++;
        }
        cout << endl << endl;
        calculate_fare(d,fare);
    }
    void calculate_fare(int total_dist,int f){

        /*
            Function to calculate fare for the given distance
        */
        srand(time(NULL));
        int fare = total_dist*fpc + f;
        cout << endl << "YOUR TOTAL FARE IS = " << fare << "\nTOTAL DISTANCE TRAVELED = " << total_dist   << "\n\n                  Hope you Enjoyed travelling with us \n";
    }
    int get_area(string s){
        /*
            Function to return which area does the given
            location belongs to
        */
        return area[s];
    }
    int out_station(string src,int&cnt){

        /*
            Function to calculate 
        */
        map<string,int>dist;
        map<string,string>parent;
        set<pair<int,string> >st;
        for(auto i : adjlist){
            dist[i.first]=INT_MAX;
        
        }
        dist[src]=0;
        st.insert({0,src});
        
        while(!st.empty()){
            pair<int,string>p = *st.begin();
            
            st.erase(p);
            string s = p.second;
            int nodedist = p.first;
            for(auto neighbours : adjlist[s]){
                if(nodedist+neighbours.second<dist[neighbours.first]){
                    auto f = st.find({dist[neighbours.first],""});
                    if(f!=st.end())
                      st.erase(f);
                    st.insert(make_pair(nodedist+neighbours.second,neighbours.first));
                    dist[neighbours.first]=nodedist+neighbours.second;
                    parent[neighbours.first]=s;
                }
            }
        }
        vector<string>route;
        int minDist = INT_MAX;
        string req;
        for(auto i : adjlist){
            if(dist[i.first]<minDist && i.first!=src && area[i.first]==area[src]){
                minDist = dist[i.first];
                req = i.first;
            }
        }
        string prev = "";
        int d = 0;
        string i = req;
        while(i!=src){

            route.push_back(i);
            d+=actual[{prev,i}];
            prev = i;
            i = parent[i];
        }
        d += actual[{prev,i}];
        reverse(route.begin(),route.end());
    
        for(auto i : route){
            cout << cnt << ' ' << i << endl;
            cnt++;
        }
        return d*50;
    }
    
};



#endif // G1_H_INCLUDED
