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
        fpc = 6;
    }
    int getsize(){
        return adjlist.size();
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
    void DFSUtil(string src,map<string,bool>&vis,int Area){
        vis[src]=1;
        area[src]=Area;
        for(auto i : adjlist[src]){
            if(vis[i.first]==0){
                DFSUtil(i.first,vis,Area);
            }
        }
    }
    void Allocate_area(){
        int compo=1;
        map<string,bool>vis;
        for(auto i : adjlist){
            if(vis[i.first]==0){
                DFSUtil(i.first,vis,compo);
                compo++;
            }
        }
    }
    bool checkArea(string a,string b){
        return area[a]==area[b];
    }
    void Dijkstra(string src,string dest,int fare){
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
        Calculate_Fare(d,fare);
    }
    void Calculate_Fare(int total_dist,int f){
        srand(time(NULL));
        int fare = total_dist*fpc + (f-20);
        fare += rand()%50;
        cout << endl << "YOUR TOTAL FARE IS = " << fare << "\nTOTAL DISTANCE TRAVELED = " << total_dist   << "\n\n                  Hope you Enjoyed travelling with us \n";
    }
    int getarea(string s){
        return area[s];
    }
    int Outstation(string src,int&cnt){
        map<string,int>dist;
        map<string,string>parent;
        set<pair<int,string> >st;
        for(auto i : adjlist){
            dist[i.first]=INT_MAX;
           // parent[i.first]="1";
        }
        dist[src]=0;
        st.insert({0,src});
        ///int d=0;
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
        ///cout << i << endl;
        while(i!=src){
            ///cout << i << endl;
            route.push_back(i);
            d+=actual[{prev,i}];
            prev = i;
            i = parent[i];
        }
        d += actual[{prev,i}];
        reverse(route.begin(),route.end());
        //int cnt = 1;
        for(auto i : route){
            cout << cnt << ' ' << i << endl;
            cnt++;
        }
        return d*50;
    }
    //("pause");
};



#endif // G1_H_INCLUDED
