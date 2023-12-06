#include <bits/stdc++.h>
using namespace std;

enum Type{
    DIR,
    FILE_
};

struct Node{
    Type type{DIR};
    string name;
    map<string ,Node*>sons;

    Node*far{nullptr};
    long long size{0};
    long long LD{0}, LR{0},LD_C{0}, LR_C{0};

};

Node *root;
const char *ROOT_NAME = "ROOT_";

void delete_node(Node *node){
    
    for(auto it: node->sons){
        delete_node(it.second);
    }
    delete node;
}

vector<string> split(string path){
    vector<string> ret;
    int last = 0;
    ret.push_back(ROOT_NAME);
    if(path=="/"){
        
        return ret;
    }
    for(int i=1;i<path.size();i++){
        if(path[i]=='/'){
            ret.emplace_back(path.substr(last+1,i-last-1));
            last= i;
        }
    }
    ret.emplace_back(path.substr(last+1,path.size()-last-1));
    return ret;

}

enum RetType {
    
    DIR_EXISTS,
    FILE_EXISTS,
    FILE_AS_DIR,
    NOT_ENOUGH,
    ONLY_FILE_NOT_ENOUGH

};

RetType detect(string &path, vector<Node*>& nodes, vector<string>& node_names, Node** file_node){

    node_names = split(path);
    Node *node=root;
    RetType ret = DIR_EXISTS;

    for(auto node_name: node_names){
        Node *next = nullptr;
        if(node_name!=node_names.back()){
            if(node->sons.count(node_name)){
                next = node->sons[node_name];
                if(next->type!=DIR){
                    nodes.clear();
                    return FILE_AS_DIR;
                }
                nodes.push_back(next);
                node=next;
            }else{
                
                return NOT_ENOUGH;
            }
        }else{
            if(node->sons.count(node_name)){
                next = node->sons[node_name];
                if(next->type==DIR){
                    nodes.push_back(next);
                    return DIR_EXISTS;
                }else{
                    *file_node = next;
                    return FILE_EXISTS;
                }
                
            }else{
                ret = ONLY_FILE_NOT_ENOUGH;
            }
        }
        
    }


    return ret;
}

Node *create_node(Type type,const string& name,Node*far,long long size){
    Node *ret = new Node;
    ret->type = type;
    ret->name = name;
    ret->far = far;
    ret->size =size;
    return ret;
}

char opC(){

    string path;
    long long size;
    cin >> path >> size;
    vector<Node*> nodes;
    vector<string> node_names;
    Node* file_node;
    RetType status = detect(path ,nodes, node_names, &file_node);
    if(status==DIR_EXISTS || status==FILE_AS_DIR){
        return 'N';
    }else if(status==NOT_ENOUGH || status==ONLY_FILE_NOT_ENOUGH){
        bool success = true;
        for(auto node: nodes){
            if(node->LR!=0 && node->LR_C+size>node->LR){
                success=false;
                break;
            }
        }
        if(!success){
            return 'N';
        }
        if(status==ONLY_FILE_NOT_ENOUGH){
            Node *last = nodes.back();
            if(last->LD!=0 && last->LD_C+size>last->LD){
                success=false;
            }else{
                last->sons[node_names.back()] = create_node(FILE_, node_names.back(), last, size);
                last->LD_C+=size;

            }
            for(auto node: nodes){
                node->LR_C+=size;
            }
        }else{
            Node *node = nodes.back();
            int i = nodes.size();
            for(;i<node_names.size()-1;i++){
                Node*next = create_node(DIR, node_names[i], node, 0);
                nodes.push_back(next);
                node->sons[node_names[i]]= next;
                node = next;
            }
            node->sons[node_names.back()] = create_node(FILE_, node_names.back(), node, size);
            node->LD_C+=size;
            for(auto node2: nodes){
                node2->LR_C+=size;
            }


        }
        if(!success){
            return 'N';
        }else{
            return 'Y';
        }
    }else if(status==FILE_EXISTS){
        Node* last = nodes.back();

        long long ori_file_size = file_node->size;
        long long diff = size-file_node->size;
        bool success = true;
        for(auto node: nodes){
            if(node->LR!=0 && node->LR_C+diff>node->LR){
                success=false;
                break;
            }
        }
        
        if(!success){
            return 'N';
        }
        if(last->LD!=0 &&last->LD_C+diff>last->LD){
            success=false;
            return 'N';
        }
        last->LD_C+=diff;
        
        file_node->size = size;

        
        for(auto node: nodes){
           
            node->LR_C+=diff;
        }

    }
    return 'Y';


}

char opR(){
    string path;

    cin >> path;
    vector<Node*> nodes;
    vector<string> node_names;
    Node* file_node;
    RetType status = detect(path ,nodes, node_names, &file_node);
    if(status == FILE_AS_DIR || status== NOT_ENOUGH || status==ONLY_FILE_NOT_ENOUGH){
        return 'Y';
    }else if(status==FILE_EXISTS){
        long long size = file_node->size;
        for(auto node: nodes){
           
            node->LR_C-=size;
        }
        nodes.back()->sons.erase(file_node->name);
        nodes.back()->LD_C-=size;
        delete file_node;
    }else if(status==DIR_EXISTS){
        Node* last = nodes.back();
        long long size = last->LR_C;
        nodes.pop_back();
        for(auto node: nodes){
           
            node->LR_C-=size;
        }
        nodes.back()->sons.erase(last->name);
        delete_node(last);
        

    }
    return 'Y';
}


int main(){


    root = new Node;
    root->sons["ROOT_"] = new Node;
    root->sons["ROOT_"]->name = "ROOT_";
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        string type ;
        cin >> type;

        if(type[0]=='C'){
            cout << opC() << endl;
        }else if(type[0]=='R'){
            cout << opR() << endl;
        }else{
            
            
        }
    }

}
/*

9
C /A/B/1 1024
C /A/B/2 1024
C /A/B/1/3 1024
C /A 1024
R /A/B/1
C /A/B/2 1024
C /A/B 555
R /A/B
C /A/B/C/D/E 666

10
C /A/B/1 1024
C /A/B/2 1024
C /A/B/1/3 1024
C /A 1024
R /A/B/1/3
Q / 0 1500
C /A/B/1 100
Q / 0 1500
R /A/B
Q / 0 1

9
Q /A/B 1030 2060
C /A/B/1 1024
C /A/C/1 1024
Q /A/B 1024 0
Q /A/C 0 1024
C /A/B/3 1024
C /A/B/D/3 1024
C /A/C/4 1024
C /A/C/D/4 1024


*/
