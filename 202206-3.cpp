#include <bits/stdc++.h>
using namespace std;
struct Operation{
    unordered_set<string> operations;
    unordered_set<string> oper_type;
    unordered_set<string> oper_name;
};

// vector<string> strs;
// unordered_map<string ,int> reverse_strs;
vector<Operation> ops;

unordered_map<string ,unordered_set<string>> fars;
unordered_map<string ,unordered_set<int>> group_operation;
unordered_map<string ,int> user_operation;
// vector<Node> operators;



bool check(int index,string& operation, string &op_type, string &op_name ){
    const Operation &op = ops[index];
    if(op.operations.count(operation) || op.operations.count("*")){
        if(op.oper_type.count(op_type) || op.oper_type.count("*")){
            if(op.oper_name.empty() || op.oper_name.count(op_name)){
                return true;
            }
        }
    }
    return false;

}

int main(){
    int n,m,q;
    cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        string name;
        int nv,no,nn;
        cin >> name;
        
        cin >> nv;
        Operation op;
        for(int j=0;j<nv;j++){
            string operation;
            cin >> operation;
            op.operations.emplace(move(operation));
        }
        cin >> no;
        for(int j=0;j<no;j++){
            string type;
            cin >>type;
            op.oper_type.emplace(move(type));
        }
        cin >> nn;
        for(int j=0;j<nn;j++){
            string opname;
            cin >> opname;
            op.oper_name.emplace(move(opname));
        }
        ops.emplace_back(move(op));
        user_operation[name] = ops.size()-1;
    }
    for(int i=0;i<m;i++){
        string name;
        cin >> name;
        int ns;
        cin >> ns;
        for(int j=0;j<ns;j++){
            string type, tname;
            cin >> type >> tname;
            if(type[0]=='g'){
                group_operation[tname].insert(user_operation[name]);

            }else{
                fars[tname].insert(name);
                fars[name].insert(tname);
            }
        }
    }
    for(int i=0;i<q;i++){
        string name;
        cin >> name;
        int ng;
        cin >> ng;
        vector<string > groups;
        for(int j=0;j<ng;j++){
            string gp;
            cin >> gp;
            groups.emplace_back(move(gp));
        }
        string op,op_type,op_name;
        cin>> op >> op_type>>op_name;
        bool found=0;
        for(auto &gp : groups){
            for(auto index : group_operation[gp]){
                if(check(index, op, op_type, op_name)){
                    cout << 1 << endl;
                    found=1;
                    break;
                }    
            }
            if(found){
                break;
            }   
        }
        if(found){
            continue;
        }
        for(auto& peer: fars[name]){
            if(check(user_operation[peer], op, op_type, op_name)){
                cout << 1 << endl;
                found=1;
                break;
            }
        }
        if(!found){
            cout << 0  << endl;
            
        }     
    }
    return 0;
}