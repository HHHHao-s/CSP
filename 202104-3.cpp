#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct IP
{
    ll state;//0---未分配,1---待分配,2---占用,3---过期
    string occ_host;
    ll ip_out;
}ip[10005];

//N：地址池大小
//t_def:默认过期时间
//t_max、t_min:过期时间的上下限
//H：本机名称
ll N,n,t_def,t_max,t_min;
string H;
ll rec_time,ip_ads,time_out;
string send_host,rec_host,type;

ll search_ip()
{
    for(ll i=1;i<=N;i++)
    {
        if(ip[i].occ_host==send_host) return i;
    }
    for(ll i=1;i<=N;i++)
    {
        if(ip[i].state==0) return i;
    }
    for(ll i=1;i<=N;i++)
    {
        if(ip[i].state==3) return i;
    }
    return -1;
}

void check()
{
    for(ll i=1;i<=N;i++)
    {
        if(ip[i].ip_out<=rec_time)
        {
            if(ip[i].state==1)
            {
                ip[i].state = 0;
                ip[i].occ_host = "";
            }
            if(ip[i].state==2)
            {
                ip[i].state = 3;
            }
        }
    }
}

int solve()
{
        check();
        if(rec_host!=H && rec_host!="*")
        {
            if(type!="REQ") return 0;
        }
        if(type!="DIS" && type!="REQ") return 0;
        if(rec_host=="*" && type!="DIS") return 0;
        if(rec_host==H && type=="DIS") return 0;

        if(type=="DIS")
        {
            ll x_ip = search_ip();
            if(x_ip==-1) return 0;

            ip[x_ip].state = 1;
            ip[x_ip].occ_host = send_host;

            if(time_out==0) ip[x_ip].ip_out = rec_time + t_def;
            else
            {
                ll x_ot = time_out;
                x_ot = max(rec_time+t_min,x_ot);
                x_ot = min(rec_time+t_max,x_ot);
                ip[x_ip].ip_out = x_ot;
            }

            cout<<H<<" "<<send_host<<" OFR "<<x_ip<<" "<<ip[x_ip].ip_out<<endl;
        }
        else if(type=="REQ")
        {
            if(rec_host!=H)
            {
                for(ll i=1;i<=N;i++)
                {
                    if(ip[i].occ_host==send_host && ip[i].state==1)
                    {
                        ip[i].state = 0;
                        ip[i].occ_host = "";
                        ip[i].ip_out = 0;
                    }
                }
                return 0;
            }

            if(ip_ads > N || ip[ip_ads].occ_host!=send_host)
            {
                cout<<H<<" "<<send_host<<" NAK "<<ip_ads<<" 0"<<endl;
                return 0;
            }

            if(time_out==0) ip[ip_ads].ip_out = rec_time + t_def;
            else
            {
                ll x_ot = time_out;
                x_ot = max(rec_time+t_min,x_ot);
                x_ot = min(rec_time+t_max,x_ot);
                ip[ip_ads].ip_out = x_ot;
            }

            ip[ip_ads].state = 2;
            cout<<H<<" "<<send_host<<" ACK "<<ip_ads<<" "<<ip[ip_ads].ip_out<<endl;
        }
        return 0;
}

int main()
{
    cin>>N>>t_def>>t_max>>t_min>>H;
    cin>>n;

    for(int i=1;i<=N;i++)
    {
        ip[i].state = 0;
        ip[i].occ_host = "";
    }

    for(int i=0;i<n;i++)
    {
        cin>>rec_time>>send_host>>rec_host>>type>>ip_ads>>time_out;
        solve();
    }
    return 0;
}

/*

4 5 10 5 dhcp
16
1 a * DIS 0 0
2 a dhcp REQ 1 0
3 b a DIS 0 0
4 b * DIS 3 0
5 b * REQ 2 12
6 b dhcp REQ 2 12
7 c * DIS 0 11
8 c dhcp REQ 3 11
9 d * DIS 0 0
10 d dhcp REQ 4 20
11 a dhcp REQ 1 20
12 c dhcp REQ 3 20
13 e * DIS 0 0
14 e dhcp REQ 2 0
15 b dhcp REQ 2 25
16 b * DIS 0 0

4 70 100 50 dhcp
6
5 a * OFR 2 100
10 b * DIS 0 70
15 b dhcp2 REQ 4 60
20 c * DIS 0 70
70 d * DIS 0 120
75 d dhcp REQ 1 125

*/