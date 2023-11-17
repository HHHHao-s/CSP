#include <bits/stdc++.h>
using namespace std;

const int R=1010, M=1010, N=1010;

int n;

unordered_map<int, pair<int,int> > danger_r;

struct info{
    int d,u,region;
};

deque<vector<info>> q;


int main(){
    cin >> n;


    for(int i=0;i<n;i++){
        int r, m;
        cin >> r >> m;
        for(int j=0;j<r;j++){
            int region;
            cin >> region;
            if(danger_r.count(region)==1 && (i<=danger_r[region].second && i>=danger_r[region].first)){
                danger_r[region].second = i+7;
            }else {
                danger_r[region].first = i;
                danger_r[region].second = i+7;
            }
        }
        q.push_back({});
        for(int j=0;j<m;j++){
            int d,u,region;
            cin >> d >> u >> region;
            q.back().push_back({d,u,region});
        }
        if(q.size()>7){
            q.pop_front();
        }
        set<int> se;
        cout << i;
        for(auto& each:q){
            for(auto& info: each){
                auto &pair = danger_r[info.region];
                int down = pair.first;
                int up = pair.second;
                if(down <=info.d && up >info.d){
                    if(i>=down && i<up){
                        if(info.d > i-7 && info.d<=i){
                            se.insert(info.u);
                        }
                        
                    }
                }
            }
        }
        for(auto &user: se){
            cout << ' ' <<user;
        }
        cout << endl;         
    }
}