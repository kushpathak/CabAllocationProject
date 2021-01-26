#ifndef G2_H_INCLUDED
#define G2_H_INCLUDED
#include<bits/stdc++.h>
#define pi 3.14
#define earth_radius 6371.0
using namespace std;
vector<int>ans;
double convert_to_rad(double deg)
{
    return ( deg * pi / 180);
}
double distanceEarth(double lat1d,double lon1d,double lat2d, double lon2d)
{
    double lat1, lon1, lat2, lon2,
           delta_lon, central_ang;
    lat1 = convert_to_rad(lat1d);
    lon1 = convert_to_rad(lon1d);
    lat2 = convert_to_rad(lat2d);
    lon2 = convert_to_rad(lon2d);
    delta_lon = lon2 - lon1;
    central_ang = acos ( sin(lat1) *
                  sin(lat2) + cos(lat1) *
                  cos(lat2) * cos(delta_lon) );

    return (earth_radius * central_ang);
}
double randomFloat(int LO,int HI){
    srand (static_cast <unsigned> (time(0)));
    float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    return r3;
}
void generate(){
    time_t t;
    time(&t);
    char*c = ctime(&t);
    int amt = 0;
    int ti = (c[6]-'0')*10+(c[7]-'0');
    if(ti>=9)
        amt = 50;
    else if(ti>=12)
        amt = 10;
    else if(ti>=17)
         amt = 25;
    else
         amt = 10;
    vector<pair<double,double> >cabPos;
    double px,py;
    px = randomFloat(12.5,40.5);
    py = randomFloat(14.6,46.7);
    for(int i=0;i<amt;i++){
        cabPos.push_back({randomFloat(px,px+1),randomFloat(py,py+1)});
    }
    for(int i=0;i<10;i++){
         if(distanceEarth(px,py,cabPos[i].first,cabPos[i].second)<=150){
                ans.push_back(i);
        }
    }
}

#endif // G2_H_INCLUDED
