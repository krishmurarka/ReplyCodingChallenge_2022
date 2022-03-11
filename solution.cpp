/******************************
     AUTHOR KRISH MURARKA
*******************************/
#include<bits/stdc++.h>
using namespace std;
#define ll                 long long int
#define fast               ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
#define deb(x)             cout<<#x<<" "<<x<<"\n"
template<typename T,typename T1>T amax(T &a,T1 b){if(b>a)a=b;return a;} // only use in equations like sum=max(sum,x)  its equivalent ot amax(sum,x) => sums is changed automatically
template<typename T,typename T1>T amin(T &a,T1 b){if(b<a)a=b;return a;}
//----------------------------------STRESS TESTING  --------------------------------------
 #ifdef krish_murarka
    #include "debug.hpp"
#else
    #define debug(...)
    #define testcases(...)
#endif
void debugger(){
    #ifdef krish_murarka
        freopen("error/errorA.txt", "w", stderr);
    #else
    #endif
}

// --------------------------------------TO TAKE INPUT --------------------------------------
void read_input()
{
  #ifdef krish_murarka
  freopen("input/inputD.txt","r",stdin);
  freopen("output/outputD.txt","w",stdout);
  freopen("error/errorA.txt","w",stderr);
  #endif
}

// --------------------------------------CODE STARTS ------------------------------------------
struct Demon{
    ll reqStamina;
    ll turns;
    ll recoverStamina;
    ll nfragments;
    vector<double> frag;
    vector<ll> prefix;
    int id;
    Demon(int i){
        cin>>reqStamina>>turns>>recoverStamina>>nfragments;
        frag.resize(nfragments);
        prefix.resize(nfragments);
        for(int i=0;i<nfragments;i++){
            cin>>frag[i];
            prefix[i] = frag[i];
            if(i!=0){
                prefix[i]+= prefix[i-1];
            }
        }
        id = i;
    }
};

ll stamina,maxStamina,nTurns,nDemons;
vector<Demon> demons;


void printDemons(Demon d){
    
    debug(d.reqStamina);
    debug(d.turns);
    debug(d.recoverStamina);
    debug(d.nfragments);
    debug(d.frag);
}
double scoring_calculator(vector<ll> index){
    ll turn_max = nTurns;
    ll initial_stamina = stamina;
    ll curr_turn= -1;
    double score=0;
    vector<ll> stamina_gain(nTurns+1,0);
    for(auto i: index){
        Demon d = demons[i]; 
         do{
             curr_turn++;
             initial_stamina+=stamina_gain[curr_turn];
             initial_stamina= min(initial_stamina,maxStamina);
             if(curr_turn>=turn_max)break;
        }while(d.reqStamina >= initial_stamina);
        if(curr_turn>=turn_max)break;
        
        if(d.reqStamina <= initial_stamina){
            initial_stamina-= d.reqStamina;
            if(curr_turn + d.turns < nTurns){
                stamina_gain[curr_turn+d.turns]+=d.recoverStamina;
            }
            if(d.prefix.size()==0)continue;
            ll sz = d.prefix.size()-1;
            ll temp = max(0LL, min(turn_max-curr_turn-1,sz));
            score+= d.prefix[temp];
        }  
    }
    return score;
}
void solving()
{
  cin>>stamina>>maxStamina>>nTurns>>nDemons;
  for(int i=0;i<nDemons;i++){
      demons.pb(Demon(i));
  }
  vector<ll> check ;
  for(int i=0;i<nDemons;i++){
    check.pb(i);
  }
  reverse(check.begin(),check.begin() + check.size()/2);
    sort(check.begin(),check.end(),[](ll& a, ll& b){
     if(2*demons[a].reqStamina- demons[a].recoverStamina +3*demons[a].turns  < 2*demons[b].reqStamina - demons[b].recoverStamina + 3*demons[b].turns)return true;
     // if(demons[a].reqStamina == demons[b].reqStamina)return demons[a].recoverStamina > demons[b].recoverStamina;
     return false;
    // return rand() > rand();
  });
  double max_score =0;
  vector<ll> ans;
  int cnt=0;
  // unsigned seed = 1;
  while(true){
      ll curr_score = scoring_calculator(check);
      if(curr_score>= max_score){   
         max_score= curr_score;
         ans= check;
      } 
      if(cnt >= 29)break;
        cnt++;
        random_shuffle (check.begin(), check.begin()+check.size());
        // random_shuffle(check.begin()+check.size()/2+1, check.end());     
  }
  for(auto i: ans){
    cout<<i<<"\n";
  }
  debug(max_score);
}
int main()
{
    fast;
    srand(time(0));
    debugger();
    read_input();
    int t=1;
    // cin>>t; 
    for(int i=1;i<=t;i++)
    {  
     testcases("Case #",i);
    //cout<<"Case #"<<i<<": ";
     solving();
    }
    return 0;
}
