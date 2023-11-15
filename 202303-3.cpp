#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <set>
#include <stack>
#include <algorithm>
#include <bitset>
using namespace std;
const size_t N = 2502;

unordered_map<int , unordered_map<int, bitset<N>>> attr_value_dn;

struct Expr_res{

bitset<N> dns;

};

 enum Type{
        LCRAVE,
        RCRAVE,
        AND,
        OR,
        BASE,
        RES
};

struct Expr{
    Type type;

    string base_expr;
    Expr_res res;

};



Expr_res parse_base(const string &base_expr){

    int pos = base_expr.find(':');
    // cout << base_expr<< endl;
    if(pos!=string::npos){
        int attr = 0;
        int val = 0;
        attr_value_dn[attr].reserve(1000);
        if(base_expr[0]=='('){
            attr = stoi(base_expr.substr(1,pos));
            val = stoi(base_expr.substr(pos+1,base_expr.size()-pos-2));
        }else{
            attr = stoi(base_expr.substr(0,pos));
            val = stoi(base_expr.substr(pos+1,base_expr.size()-pos-1));
        }
        
        return {attr_value_dn[attr][val]};
    }else{
        pos = base_expr.find('~');
        int attr = 0;
        int val = 0;
        attr_value_dn[attr].reserve(100);
        if(base_expr[0]=='('){
            attr = stoi(base_expr.substr(1,pos));
            val = stoi(base_expr.substr(pos+1,base_expr.size()-pos-2));
        }else{
            attr = stoi(base_expr.substr(0,pos));
            val = stoi(base_expr.substr(pos+1,base_expr.size()-pos-1));
        }
        bitset<N> dns;
        for(auto it=attr_value_dn[attr].begin();it!=attr_value_dn[attr].end();it++){
            dns |= it->second;

        }   

           
        return {attr_value_dn[attr][val] ^ dns};
        
    }

}

Expr parse_expr(const string &expr){
    stack<Expr> st;
    
    // cout << expr << endl;

    for(int i=0;i<expr.size();i++){
        if(expr[i]=='&'){
            st.push({AND});
        }else if(expr[i]=='('){
            st.push({LCRAVE});
        }else if(expr[i]=='|'){
            st.push({OR});
        }else if(expr[i]==')'){
            Expr er = move(st.top());
            st.pop();
            Expr em = move(st.top());
            st.pop();
            if(em.type==LCRAVE){
                if(er.type!=RES)
                    st.push({RES,"", parse_base(er.base_expr)});
                else{
                    st.emplace(move(er));
                }
            }else {
                Expr el = move(st.top());
                st.pop();
                st.pop(); // LCARVE
                if(el.type==AND){
                    
                    st.push({RES,"", (Expr_res){em.res.dns&er.res.dns} });
                    
                }else{
                    st.push({RES,"", (Expr_res){em.res.dns|er.res.dns} });
                }
                
                
                
            }
        }else{
            string n_exp;
            int pos = i;
            while(i+1<expr.size() && expr[i+1]!=')'){
                i++;
            }
            
            st.push({BASE, expr.substr(pos, i-pos+1)});
        }

    }
    Expr ret = move(st.top());
    st.pop();
    return ret;

}

int main(){

    attr_value_dn.reserve(500);

    string lines ;
	
	
    int n,m;
    cin>> n;
    std::getline(cin, lines);//\n
    unordered_map<int, int> ma;
    vector<int> re(N,-1);
    int cnt=0;
    for(int i=0;i<n;i++){
        std::getline(cin, lines);
        istringstream input(lines);
        int dn,attrs;
        input>>dn>>attrs;
        for(int j=0;j<attrs;j++){
            int attr,val;
            input>>attr>>val;
            // attr_value_dn[attr][val].insert(dn);
            if(ma.count(dn)==0){
                ma[dn] = cnt;
                re[cnt] = dn;
                cnt++;              
            }
            attr_value_dn[attr][val][ma[dn]]=1;
        }

    }
    cin >> m;
    std::getline(cin, lines);

    for(int i=0;i<m;i++){
        std::getline(cin, lines);
        string expr = "("+lines+")";
        Expr resu = parse_expr(expr);
        vector<int> tmd;
        tmd.reserve(N);
        
        for(int i=0;i<N;i++){
            if(resu.res.dns.test(i)){
                tmd.push_back(re[i]);
            }
        }
        sort(tmd.begin(),tmd.end());
        for(auto it: tmd){
            cout << it << ' ';
        }
        cout << endl;
    }
    return 0;

}