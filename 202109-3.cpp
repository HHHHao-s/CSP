#include <bits/stdc++.h>
using namespace std;


static unsigned long mynext = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    mynext = mynext * 1103515245 + 12345;
    return((unsigned)(mynext/65536) % 32768);
}

int N,S,T,P;

double dt;

int cur_T=1;

struct Node{
    int index;
    double v,u,a,b,c,d,I;
    int shots;
};
struct Source{
    int r;  
};

struct Path{
    int node;
    double w;
    int D;
};

int MOD = 2023;

vector<Node> nodes;
// vector<vector<int>> time_shot;
vector<vector<double>> node_time_node;
// unordered_map<int ,vector<Path>> node_time_power;
vector<Source> sources;
vector<vector<Path>> grid;

inline void shot(int index){
    for(const auto &p:grid[index]){
        
        // node_time_power[p.D+cur_T].push_back(p);
        if(node_time_node[(p.D+cur_T)%MOD].size()==0){
            node_time_node[(p.D+cur_T)%MOD].resize(N);
        }
        node_time_node[(p.D+cur_T)%MOD][p.node]+= p.w;
    }
}

inline void calc(Node &node){
    double cI = 0;
    
    cI = node_time_node[cur_T%MOD][node.index];
    
    double v1 = node.v+dt*(0.04*node.v*node.v+5*node.v+140-node.u) + cI;
    double u1 = node.u+dt*node.a*(node.b*node.v - node.u);

    if(v1>=30){
        shot(node.index);
        node.shots++;
        v1 = node.c;
        u1 = u1+node.d;
    }
    node.v = v1;
    node.u = u1;
    node.I=0;

}


int main(){

    cin >> N >> S>>P>>T;
    cin >> dt;

    int base,R;
    cin >> R;
    base = R;
    nodes.reserve(N);
    sources.reserve(P);
    while(1){
        double v,u,a,b,c,d;
        cin >> v>>u>>a>>b>>c>>d;
        for(int j=0;j<R;j++){
            nodes.push_back({(int)nodes.size(),v,u,a,b,c,d,0,0});
        }
        
        if(base!=N){
            cin >> R;
            base +=R;
        }else{
            break;
        }
    }
    for(int i=0;i<P;i++){
        int r ;
        cin >> r;
        sources.push_back((Source){r});
    }
    grid.resize(N+P+1);
    

    for(int i=0;i<S;i++){

        int s, t;
        double w;
        int D;
        cin >> s >> t >> w >> D;
        grid[s].push_back({t, w,D});

    }
    node_time_node = vector<vector<double>>(2023, vector<double>(N, 0));
    for(;cur_T<=T;cur_T++){
        
        int index=N;
        // if(node_time_power.count(cur_T)){
        //     auto &paths = node_time_power[cur_T];
        //     for(auto &path: paths){
        //         nodes[path.node].I+= path.w;

        //     }
        //     node_time_power.erase(cur_T);
            

        // }
        for(auto source: sources){
            int random_num = myrand();
            if(source.r>random_num){
                shot(index);
            }
            index++;
        }
        
        for(auto &node: nodes){
            calc(node);
        }
        
            
        // memset(node_time_node[cur_T%MOD].data(), 0, N*sizeof(double) );
        
       

        

    }
    double minV=1000000, maxV=-1000000;
    int minShot=10000000,maxShot=0;


    for(auto &node: nodes){
        minV = min(minV, node.v);
        maxV = max(maxV, node.v);
        minShot = min(minShot ,node.shots);
        maxShot = max(maxShot ,node.shots);
    }

    printf("%.3lf %.3lf\n", minV, maxV);
    cout << minShot<< ' ' << maxShot;




}

/*
1 1 1 10
0.1
1 -70.0 -14.0 0.02 0.2 -65.0 2.0
30000
1 0 30.0 2

2 4 2 10
0.1
1 -70.0 -14.0 0.02 0.2 -65.0 2.0
1 -69.0 -13.0 0.04 0.1 -60.0 1.0
30000
20000
2 0 15.0 1
3 1 20.0 1
1 0 10.0 2
0 1 40.0 3

*/