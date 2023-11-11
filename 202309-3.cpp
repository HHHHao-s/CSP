#include <math.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
#include <string.h>
#include <bitset>
#include <sstream>
using namespace std;

int n,m;
constexpr long long mo = 1000000007;

long long quickmul(long long x, long long n){ // 快速幂实现pow功能
    constexpr long long MOD = 1000000007;
    if(x == 0) return 0;
    if(n==0) return 1;
    long long sum = 1;
    while(n){
        if(n&1) sum = (long long)sum * x % MOD;
        n >>= 1;
        x = (long long)x * x % MOD;
    }
    return sum;
}

struct X{
    X(){
        index_=-1;
        pw_=0;
    }
    X(long long index, long long pw){
        index_=index;
        pw_ = pw;
    }
    long long index_;
    long long pw_;
};

struct Func{
    Func(){
        
        muls.resize(n);
        for(int i=0;i<n;i++){
            muls[i]={i,0};
        }
    }
    Func(X x){
        muls.resize(n);
        for(int i=0;i<n;i++){
            muls[i]={i,0};
        }
        muls[x.index_]=x;
    }
    Func(const Func& rhs){
        changshu = rhs.changshu;
        muls = rhs.muls;
    }

    Func(Func&& rhs)noexcept{
        muls = move(rhs.muls);
        changshu = rhs.changshu;
    }

    Func& operator=(Func&& rhs)noexcept{
        muls = move(rhs.muls);
        changshu = rhs.changshu;
        return *this;
    }
    Func& operator=(const Func& rhs){
        changshu = rhs.changshu;
        muls = rhs.muls;
        return *this;
    }
    ~Func(){

    }

    string GetCode() const{
        constexpr long long carry = 50;
        long long code = 0;        
        string str(n,0);
        for(int i=0;i<n;i++){
            str[i] = muls[i].pw_;// pw_最大120
        }
        return str;
    }

    Func Mul(const Func & rhs)const{
        Func ret;
        for(int i=0;i<n;i++){
            ret.muls[i].pw_=rhs.muls[i].pw_ + muls[i].pw_;
        }
        ret.changshu = (changshu*rhs.changshu)%mo;
        return ret;
    }

    


    long long Calc(X x, const vector<long long> &changshus)const {
        long long ret = changshu;
        for(int i=0;i<n;i++){
            if(i!=x.index_){
                if(muls[i].pw_==0){
                    continue;
                }
                ret = (ret*quickmul(changshus[i], muls[i].pw_) )%mo;
            }else{
                if(muls[i].pw_==0){
                    return 0ll;
                }else if(muls[i].pw_==1){
                    continue;
                }
                ret = (ret*(muls[i].pw_)*quickmul(changshus[i], muls[i].pw_-1))%mo;
            }
        }
        return ret;
    }


    
    vector<X> muls;
    long long changshu{1};
};

struct Funcs{
    Funcs(){

    }
    Funcs(Func&& single_func)noexcept{
        funcs[single_func.GetCode()] = move(single_func);
    }

    Funcs(Funcs && rFuncs)noexcept{
        funcs= move(rFuncs.funcs);
    }

    void AddFunc(const Func &func){
        string code = func.GetCode();
        if(funcs.count(code)!=0){
            funcs[code].changshu+= func.changshu;
        }else{
            funcs[code]=func;
        }
        
    }

    void AddFunc(Func &&func) noexcept{
        string code = func.GetCode();
        if(funcs.count(code)!=0){
            funcs[code].changshu+= func.changshu;

        }else{
            funcs[code]=move(func);
        }
        func.muls.clear();  
    }
    void MulFunc(const X &rhs){
        for(auto it=funcs.begin();it!=funcs.end();it++){
            it->second.muls[rhs.index_].pw_++;
        }
    }

    void AddFuncs(const Funcs&rhs){
        for(auto it=rhs.funcs.begin();it!=rhs.funcs.end();it++){
            AddFunc(it->second);
        }
    }

    void MulFuncs(const Funcs&rhs){
        Funcs new_funcs;
        for(auto it=funcs.begin();it!=funcs.end();it++){
            const Func &func1 = it->second;
            for(auto it2 = rhs.funcs.begin();it2!=rhs.funcs.end();it2++){
                const Func &func2 = it2->second;
                Func new_func = func1.Mul(func2);
                new_funcs.AddFunc(new_func);
            }
        }
        funcs=move(new_funcs.funcs);
    }

    long long Calc(X x,const vector<long long> &changshus)const {
        long long ret=0;
        for(auto it=funcs.begin();it!=funcs.end();it++){
            ret = (ret+it->second.Calc(x, changshus))%mo;
        }
        if(ret<0){
            ret+=mo;
        }
        return ret;
    }

    void Reverse(){
        for(auto it=funcs.begin();it!=funcs.end();it++){
            it->second.changshu=-it->second.changshu;
        }
    }

    unordered_map<string, Func> funcs;

    // list<Func> func_adds;
};


int main(){

    
    
    
    scanf("%d %d\n", &n, &m);
    Funcs funcs;

    stack<Funcs> st;

    char line[1000];
    scanf("%[^\n]\n", line);
    int linesz = strlen(line);
    char buf[100];
    int p=0;
    while(sscanf(line+p, "%s ",buf)==1){
        p+=strlen(buf)+1;
        // cout << buf << endl;
        if(buf[0]=='x'){
            long long index = atoll(buf+1)-1;
            X nx = {index, 1};
            Func func{nx};
            // Funcs(func);
            st.emplace(move(func));
        }else if(buf[0]=='+'){
            Funcs fs1 = move(st.top());
            st.pop();
            Funcs fs2 = move(st.top());
            st.pop();
            fs2.AddFuncs(fs1);
            st.emplace(move(fs2));
        }else if(buf[0]=='*'){
            Funcs fs1 = move(st.top());
            st.pop();
            Funcs fs2 = move(st.top());
            st.pop();
            fs1.MulFuncs(fs2);
            st.emplace(move(fs1));
        }else if(buf[0]=='-'){        
            if(buf[1]==0){
                Funcs fs1 = move(st.top());
                st.pop();
                Funcs fs2 = move(st.top());
                st.pop();
                fs1.Reverse();
                fs2.AddFuncs(fs1);
                st.emplace(move(fs2));
            }else{
                
                Func new_f;
                long long num = atoll(buf+1);
                new_f.changshu= -num;
                st.emplace(move(new_f));
            }
        }else{                    
            Func new_f;
            long long num = atoll(buf);
            new_f.changshu= num;            
            st.emplace(move(new_f));
        }
        if(p>=linesz){
            break;
        }
    }
    const Funcs & last = st.top();
    for(int i=0;i<m;i++){
        int num;
        cin >> num;
        X x{num-1, 0};
        vector<long long >cs;

        for(int j=0;j<n;j++){
            cin>>num;
            cs.push_back(num);
        }
        cout << last.Calc(x, cs) << endl;
    }
    
}
