#include <bits/stdc++.h>
using namespace std;

const int kmax = 5;

enum Type{
    OR,
    XOR,
    AND,
    NOT,
    NAND,
    NOR

    
};

struct Node{
    Type type;
    bitset<kmax> cur;
    int kcur{0};
    int kin{0};
    
};

vector<Node> nodes;
vector<vector<int>> grid;
vector<vector<int>> input;
vector<bool> input_digit;
vector<bool> output; 
vector<vector<bool>> outputs;
Node createNode(string & FUNC){
    Node node;
    if(FUNC == "XOR"){
        node.type = XOR;
    }else if(FUNC == "AND"){
        node.type = AND;
    }else if(FUNC == "OR"){
        node.type = OR;
    }else if(FUNC == "NOT"){
        node.type = NOT;
    }else if(FUNC=="NAND"){
        node.type = NAND;
    }else if(FUNC == "NOR"){
        node.type = NOR;
    }
    return node;
}
int Q,M,N; // M -> input

bool calc_out(const Node &node){
    bool ret=0;
    switch (node.type)
    {
    case XOR:{
        ret=node.cur.test(0);
        for(int i=1;i<node.kin;i++){
            bool th = node.cur.test(i);
            ret ^= th;

        }

        break;
    }
        
        
    case AND:{
        ret=node.cur.test(0);
        for(int i=1;i<node.kin;i++){
            bool th = node.cur.test(i);
            ret &= th;

        }
        break;
    }
    case OR:{
        ret=node.cur.test(0);
        for(int i=1;i<node.kin;i++){
            bool th = node.cur.test(i);
            ret |= th;

        }
        break;
    }
    case NOT:{
        ret = !node.cur.test(0);
        break;
    }
    case NAND:{
        ret=node.cur.test(0);
        for(int i=1;i<node.kin;i++){
            bool th = node.cur.test(i);
            ret &= th;

        }
        ret = !ret;
        break;
    }
    case NOR:{
        ret=node.cur.test(0);
        for(int i=1;i<node.kin;i++){
            bool th = node.cur.test(i);
            ret |= th;

        }
        ret = !ret;
        break;
    }    
    default:
        break;
    }
    return ret;
}
int outs=0;
void Node_in(int node_index, bool in){

    Node & node= nodes[node_index];
    if(in){
        node.cur.set(node.kcur);
    }
    node.kcur++;
    if(node.kin==node.kcur){
        bool out=calc_out(node);
        output[node_index]=out;
        outs++;
        
        if(node.kcur==node.kin){
            for(int next_node:grid[node_index]){
                Node_in(next_node, out);
            }
        }
    }
    
    
    

}

void qidong(){

    for(int i=1;i<=M;i++){
        for(int next_node: input[i]){
            Node_in(next_node, input_digit[i]);
        }
    }

}



int main(){


    cin >> Q;
    while(Q--){
        cin >> M >> N;

        
        grid.clear();
        input.clear();
        output.clear();

        nodes.resize(1); // init

        input.resize(M+1);
        grid.resize(N+1);
        input_digit.resize(M+1);
        output.resize(N+1);
        outputs.clear();
        outs=0;
        for(int i=1;i<=N;i++){
            string FUNC ;
            int k;
            cin >> FUNC >> k;
            Node node = createNode(FUNC);
            int node_index = nodes.size();
            node.kin = k;
            for(int j=0;j<k;j++){
                
                string io;
                cin >> io;
                int input_index = atoi(&io[1]);
                if(io[0]=='I'){
                    input[input_index].push_back(node_index);
                    
                }else{
                    grid[input_index].push_back(node_index);
                }
            }
            nodes.push_back(node);
            
        }
        int S;
        cin >> S;

        bool loop=0;
        for(int j=0;j<S;j++){
            if(!loop){
                auto store = nodes;
                for(int i=1;i<=M;i++){
                    int in_tmp;
                    cin >> in_tmp;
                    input_digit[i]=(bool)in_tmp;
                }
                outs=0;
                qidong();
                nodes = move(store);
                if(outs==N){
                    outputs.emplace_back(move(output));
                    
                }else{
                    loop=1;
                    continue;
                    
                }
                
                output = vector<bool>(N+1);
            }else{
                for(int i=1;i<=M;i++){
                    int in_tmp;
                    cin >> in_tmp;
                }
            }
        }
        
        for(int i=1;i<=S;i++){

            int os=0;
            cin >> os;
            
            for(int j=0;j<os;j++){
                if(!loop){
                    int op;
                    cin >> op;

                    int can = outputs[i-1][op];
                    cout << can << ' ';
                }else{
                    int op;
                    cin >> op;
                }
                
            }
            if(!loop)
                cout << endl;
            
        }
        if(loop){
            cout << "LOOP" << endl;
        }



    }
}
/*

1
3 5
XOR 2 I1 I2
XOR 2 O1 I3
AND 2 O1 I3
AND 2 I1 I2
OR 2 O3 O4
4
0 1 1
1 0 1
1 1 1
0 0 0
2 5 2
2 5 2
2 5 2
2 5 2

1
2 6
NOR 2 O4 I2
AND 2 O4 O6
XOR 2 O5 O1
NOT 1 O6
NAND 2 O2 O2
AND 2 I1 O3
2
0 0
1 0
3 2 3 4
6 1 2 3 4 5 6

*/