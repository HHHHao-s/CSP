#include <bits/stdc++.h>
using namespace std;
const int N = 1024;
// struct Task{
//     int mission;
//     int app;
// };

struct Node{
    int id;
    int fa;
    int count;
};

vector<bitset<N>> usable;
bitset<N> node_all;

unordered_map<int, bitset<N>> app_usable;
unordered_map<int, bitset<N>> app_Node;
vector<Node> node_fa;

int n,m;
int main(){
    cin >> n >> m;
    usable.resize(m+1);
    node_fa.resize(n+1);
    for(int i=1;i<=n;i++){
        int l ;
        cin >> l;
        usable[l].set(i);
        node_fa[i]={i,l, 0};
        node_all.set(i);
    }
    int g;
    cin >> g;
    for(int i=0;i<g;i++){
        int f, a, na, pa, paa, paar;
        cin >> f >> a >> na >> pa >> paa >> paar;
        for(int j=0;j<f;j++){
            bitset<N> can; // 节点
            if(na !=0){
                can = usable[na];
            }else{
                can = node_all;
            }
            if(!can.any()){
                cout << 0 << ' ';
                continue;
            }
            if(pa!=0){
                can &= app_usable[pa];
            }
            if(!can.any()){
                cout << 0 << ' ';
                continue;
            }
            if(paa!=0){
                auto tmp_can = can;
                can &= ~(app_Node[paa]);
                if(!can.any() && paar==0){
                    can = tmp_can;
                }
            }
            if(!can.any()){
                cout << 0 << ' ';
                continue;
            }else{
                auto f=[](const Node &a,const Node &b)->bool{
                    if(a.count>b.count){
                        return true;
                    }else if(a.count==b.count){
                        return a.id>b.id;
                    }else {
                        return false;
                    }
                };
                priority_queue<Node, vector<Node> , decltype(f)> pq(f);
                for(int bit=0;bit<n+1;bit++){
                    if(can.test(bit)){
                        pq.push(node_fa[bit]);
                    }
                
                }
                int bit = pq.top().id;
                cout << bit << ' ';
                app_usable[a] |= usable[node_fa[bit].fa];
                app_Node[a].set(bit);
                node_fa[bit].count++;

            }           
        }
        cout << endl;
    }



    return 0;
}