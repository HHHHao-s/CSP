#include <bits/stdc++.h>

using namespace std;

long long Q[8][8];
long long M[8][8];
long long M_[8][8];
long long M__[8][8];
double COSM[8][8];
double res[8][8];

int main(){

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            cin >> Q[i][j];
        }
    }
    int n;
    cin >> n;
    int T;
    cin >> T;
    int mi=0,mj=1,mr=2;
    int flag = 1;
    memset(M, 0, 64*sizeof(int));
 
    
    cin >> M[0][0];
    for(int i=1;i<n;i++){
        int x;
        cin >> x;
        M[mi][mj] = x;
        if(flag==1 && (mj==0||mi==7)){
            if(mi==7){//ld
                mj++;
            }else{
                mi++;
            }
            flag=-flag;
        }else if(flag==-1 && (mi==0 || mj==7)){
            if(mj==7){
                mi++;
            }else{
                mj++;
            }
            flag = -flag;
        }else{
            mi+=flag;
            mj-=flag;
        }
    
    }
    if(T==0){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                cout << M[i][j] << ' ';
            }
            cout << endl;
        }
    }else if(T==1){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                M_[i][j] = M[i][j]*Q[i][j];
                
            }
        }
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                cout << M_[i][j] << ' ';
            }
            cout << endl;
        }
    }else{
        const double PI = acos(-1);
        const double au = sqrt(0.5);

        double tmp;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                M_[i][j] = M[i][j]*Q[i][j];
                
            }
        }
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                COSM[i][j] = cos((PI/8)*(i+0.5)*j);
            }
        }
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                double tmp=0;
                for(int u=0;u<8;u++){
                    for(int v=0;v<8;v++){
                        double un=u==0?au:1;
                        double vn=v==0?au:1;
                        tmp += un*vn*M_[u][v]*COSM[i][u]*COSM[j][v];
                    }
                }
                tmp/=4;
                res[i][j]=tmp;
                tmp += 128.0;
                if(tmp-floor(tmp)>=0.5){
                    M__[i][j]=((long long )tmp) + 1;
                   
                }else{
                    M__[i][j]=(long long )tmp;
                }
                if(M__[i][j]<0){
                    M__[i][j]=0;
                }else if(M__[i][j]>255){
                    M__[i][j]=255;
                }

            }
        }
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                cout << M__[i][j] << ' ';
            }
            cout << endl;
        }

    }




}