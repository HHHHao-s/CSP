#include <bits/stdc++.h>
using namespace std;

int main(){

    int n,m;
    cin >> n >> m;

    vector<pair<double,double>> oper(n+1);
    oper[0] = {1.0,0.0};
    
    for(int i=1;i<=n;i++){
        int k;
        double num;
        cin >> k >> num;
        if(k==1){
            oper[i].first = oper[i-1].first*num;
            oper[i].second = oper[i-1].second;
        }else{
            oper[i].first = oper[i-1].first;
            oper[i].second  = oper[i-1].second+num;
        }
        
    }
    
    for(int i=0;i<m;i++){
        int mi, mj;
        double mx,my;
        cin >> mi >> mj >> mx >> my;
        double sk = oper[mj].first/oper[mi-1].first;
        double sr = oper[mj].second-oper[mi-1].second;

        mx = sk*mx;
        my = sk*my;

        double rx = mx*cos(sr)-my*sin(sr);
        double ry = mx*sin(sr)+my*cos(sr);
        printf("%lf %lf\n", rx, ry);
        // cout << rx << ' ' << ry << endl;
    } 

}