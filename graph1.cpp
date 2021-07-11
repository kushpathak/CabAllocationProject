#include<bits/stdc++.h>
using namespace std;
const int maxsize = 1e2+5;

/*
    Class which provides functionalities for route calculation, 
    fare calculation and addition of new routes
*/
class Graph{
    //Creating an adjacency list
    map<string,vector<pair<string,int> > >adjlist;
    //Creating a distance map i,e dist[a,b] = w
    map<pair<string,string>,int >actual;
    int fpc;
public:
    Graph(){
        fpc = 6;
    }
    /*
        This function basically adds an edge between two nodes in a graph.
    */
    void add_edge(string u,string v,int w){
       adjlist[u].push_back({v,w});
       adjlist[v].push_back({u,w});
       actual[{u,v}]=w;
       actual[{v,u}]=w;
    }
    /*
        This function updates the weight between two nodes in the graph to a
        new value
    */
    void update_weight(string u,string v,int w){
      for(int i=0;i<adjlist[u].size();i++){

            if(adjlist[u][i].first==v)
            {
                adjlist[u][i].second+=w;
                return;
            }
      }
    }
    /*
        This function whill calculate route between 2 nodes in a graph using
        dijkstra algorithm.
    */
    void dijkstra(string src,string dest){
        map<string,int>dist;
        map<string,string>parent;
        set<pair<int,string> >st;
        for(auto i : adjlist){
            dist[i.first]=INT_MAX;
        }
        dist[src]=0;
        st.insert({0,src});
        int d=0;
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
        string prev = "";
        while(dest!=src){
            route.push_back(dest);
            d+=actual[{prev,dest}];
            prev = dest;
            dest = parent[dest];
        }
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
        calculate_fare(d);
    }
    /*  
        This function will calculate fare based on the distance travelled 
        The fare might also increase by a random amount depending on the
        traffic faced 
    */
    void calculate_fare(int total_dist){
        srand(time(NULL));
        int fare = total_dist*fpc;
        fare += rand()%50;
        cout << endl << "YOUR TOTAL FARE IS = " << fare << "\n\n                  Hope you Enjoyed travelling with us \n";
        cout << "Press 1 to rate your trip" << endl;
        int ch;
        cin >> ch;
        if(ch==1){
            int rating;
            cout << "Enter Your Rating " << endl;
            cin >> rating;
        }
         do{
        cout << "\n                       Press enter to continue....                       \n";
        }while(cin.get()!='\n');
    }
};
Graph G;
/*  
    This function will be used to create edges in a graph
*/
void start(){
    G.add_edge("Noida","Ghaziabad",10);
    G.add_edge("Noida","Indirapuram",5);
    G.add_edge("Indirapuram","Ghaziabad",4);
    G.add_edge("Noida","Sector 62",8);
    G.add_edge("Sector 62","Sector 18",4);
    G.add_edge("Sector 18","Sector 59",3);
    G.add_edge("Sector 59","Sector 19",2);
    G.add_edge("Sector 19","Sector 14",1);
    G.add_edge("Sector 14","Sector 10",8);
    G.add_edge("Sector 62","Delhi Junction",20);
    G.add_edge("Delhi Junction","Chandni Chowk",5);
    G.add_edge("Chandni Chowk","New Delhi",10);
    G.add_edge("New Delhi","Chandni Chowk",7);
    G.add_edge("Chandni Chowk","Sadar Bazaar",19);
    G.add_edge("Sadar Bazaar","Canaught Place",14);
    G.add_edge("Canaught Place","Daulat Pura",19);
    G.add_edge("Daulat Pura","Lal Quila",20);
    G.add_edge("Lal Quila","Delhi Junction",2);
}
int main(){

    start();
    G.dijkstra("Noida","Delhi Junction");

}
