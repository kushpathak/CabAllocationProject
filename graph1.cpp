#include<bits/stdc++.h>
using namespace std;
const int maxsize = 1e2+5;
class Graph{
    map<string,vector<pair<string,int> > >adjlist;
    map<pair<string,string>,int >actual;
    int fpc;
public:
    Graph(){
        fpc = 6;
    }
    void AddEdge(string u,string v,int w){
       adjlist[u].push_back({v,w});
       adjlist[v].push_back({u,w});
       actual[{u,v}]=w;
       actual[{v,u}]=w;
    }
    void Updateweight(string u,string v,int w){
      for(int i=0;i<adjlist[u].size();i++){

            if(adjlist[u][i].first==v)
            {
                adjlist[u][i].second+=w;
                return;
            }
      }
    }
    void Dijkstra(string src,string dest){
        map<string,int>dist;
        map<string,string>parent;
        set<pair<int,string> >st;
        for(auto i : adjlist){
            dist[i.first]=INT_MAX;
           // parent[i.first]="1";
        }
        dist[src]=0;
        st.insert({0,src});
        int d=0;
        while(!st.empty()){
            pair<int,string>p = *st.begin();
            //cout << p.second << endl;
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
        Calculate_Fare(d);
    }
    void Calculate_Fare(int total_dist){
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
    //("pause");
};
Graph G;
void start(){
     G.AddEdge("Noida","Ghaziabad",10);
    G.AddEdge("Noida","Indirapuram",5);
    G.AddEdge("Indirapuram","Ghaziabad",4);
    G.AddEdge("Noida","Sector 62",8);
    G.AddEdge("Sector 62","Sector 18",4);
    G.AddEdge("Sector 18","Sector 59",3);
    G.AddEdge("Sector 59","Sector 19",2);
    G.AddEdge("Sector 19","Sector 14",1);
    G.AddEdge("Sector 14","Sector 10",8);
    G.AddEdge("Sector 62","Delhi Junction",20);
    G.AddEdge("Delhi Junction","Chandni Chowk",5);
    G.AddEdge("Chandni Chowk","New Delhi",10);
    G.AddEdge("New Delhi","Chandni Chowk",7);
    G.AddEdge("Chandni Chowk","Sadar Bazaar",19);
    G.AddEdge("Sadar Bazaar","Canaught Place",14);
    G.AddEdge("Canaught Place","Daulat Pura",19);
    G.AddEdge("Daulat Pura","Lal Quila",20);
    G.AddEdge("Lal Quila","Delhi Junction",2);
}
int main(){

    start();
    G.Dijkstra("Noida","Delhi Junction");

}
