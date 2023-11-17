#include <bits/stdc++.h>

using namespace std;

unordered_map<int ,unordered_map<int, int>> grid;

int dir_x[8] = {1,1,0,-1,-1,-1,0,1};
int dir_y[8] = {0,1,1,1,0,-1,-1,-1};

int xor_all;

int n,m,p,q;

int main(){

    cin >> n >> m >> p>>q;
    for(int i=1;i<=p;i++){
        int xi,yi;
        cin >> xi >> yi;
        grid[xi][yi] = i;
        xor_all^= i*xi + yi;
    }

    for(int i=0;i<q;i++){
        int x,y,t;
        cin >> x>>y>>t;

        int mx_k=min({x-1,n-x,y-1,m-y});
        int k=1;
        bool found_k=0;
        int ori[8];
        int tmp_xor=xor_all;
        for(;k<=mx_k;k++){
            for(int j=0;j<8;j++){
                int nx = x+k*dir_x[j];
                int ny = y+k*dir_y[j];
                if(grid[nx].count(ny)){
                    found_k=1;
                    int tmp = grid[nx][ny];
                    grid[nx].erase(ny);
                    tmp_xor ^= tmp*nx + ny;
                    ori[j] = tmp;
                }else{
                    ori[j]=0;
                }
            }
            if(found_k){
                break;
            }
        }
        if(!found_k){
            cout << xor_all << endl;
        }else{
            int carry=0;
            for(int j=0;j<8;j++){
                int nx = x+k*dir_x[(j+t)%8];
                int ny = y+k*dir_y[(j+t)%8];
                if(ori[j]!=0){
                    grid[nx][ny] = ori[j];
                    tmp_xor^=grid[nx][ny]*nx + ny;
                }
                
            }
            xor_all = tmp_xor;
            
        }

    }
    cout << xor_all;
}