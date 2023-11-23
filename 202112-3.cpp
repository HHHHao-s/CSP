#include <bits/stdc++.h>
using namespace std;

int w,s,k;


vector<int> getgx(){
    vector<int> gx({1,-3});
    
    int cur = -9;
    for(int i=1;i<k;i++){
        auto tmp = gx;
        gx.push_back(0);
        for(int j=1;j<=tmp.size();j++){
            gx[j] = (tmp[j-1]*cur+gx[j])%929;
        }
        cur*=3;
    }
    return gx;

}

vector<int> getxkdx(const vector<int>& mayuan){
    auto xkdx = mayuan;
    for(int i=1;i<=k;i++){
        xkdx.push_back(0);
    }
    return xkdx;
}

vector<int> calc(vector<int>& dx,vector<int>& gx){
    vector<int> rx;

    for(int i =0;i<=dx.size()-gx.size();i++){
        int div = dx[i]/gx[0];
        dx[i]=0;
        for(int j=1;j<gx.size();j++){
            dx[i+j] = (dx[i+j] - div*gx[j]);
            if(i==dx.size()-gx.size()){
                rx.push_back(dx[i+j]);
            }
        }
    }
    return rx;
    
}

int main(){

    scanf("%d %d\n", &w, &s);
    if(s==-1){
        k=0;
    }
    else{
        k = (1<<(s+1));
    }

    enum {
        BIG,
        NUM,
        SMALL
    } mode;
    mode = BIG;
    char c;
    vector<int> encoded;

    while (scanf("%c", &c)!=EOF)
    {
        if(c=='\n'){
            break;
        }
        switch (mode)
        {
        case BIG:
            {
                if(c>='A' && c<='Z'){
                    encoded.push_back(c-'A');
                    
                }else if(isdigit(c)){
                    encoded.push_back(28);
                    encoded.push_back(c-'0');
                    mode=NUM;
                }else{
                    encoded.push_back(27);
                    encoded.push_back(c-'a');
                    mode=SMALL;
                }
            
                break;
            }
        case NUM:{
                if(c>='A' && c<='Z'){
                    encoded.push_back(28);
                    encoded.push_back(c-'A');
                    mode= BIG;
                }else if(isdigit(c)){
                    encoded.push_back(c-'0');

                }else{
                    encoded.push_back(27);
                    encoded.push_back(c-'a');
                    mode=SMALL;
                }
            break;
        }
            
        case SMALL:{
                if(c>='A' && c<='Z'){
                    encoded.push_back(28);
                    encoded.push_back(28);
                    encoded.push_back(c-'A');
                    mode= BIG;
                }else if(isdigit(c)){
                    encoded.push_back(28);
                    encoded.push_back(c-'0');
                    mode=NUM;
                }else{
                    
                    encoded.push_back(c-'a');
                    mode=SMALL;
                }
            break;
        }
        default:
            break;
        }
    }

    if(encoded.size()&1){
        encoded.push_back(29);
    }
    vector<int> mayuan;

    int len = ((1+encoded.size()/2+k +w-1)/w)*w;
    mayuan.push_back(len-k);
    for(int i=0;i<encoded.size();i+=2){
        mayuan.push_back(30*encoded[i]+encoded[i+1]);
    }
    while(mayuan.size()<len -k){
        mayuan.push_back(900);
    }
    for(int i=0;i<mayuan.size();i++){
        cout << mayuan[i] << endl;
    }
    vector<int> gx = getgx();
    vector<int> xkdx = getxkdx(mayuan);
    vector<int> rx = calc(xkdx, gx);
    for(int i =0;i<rx.size();i++){
        int r = rx[i];
        r%=929;
        if(r<0){
            r+=929;
        }
        cout << r << endl;
    }



    return 0;

}