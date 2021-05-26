#include <bits/stdc++.h>
#include <fstream>
#include <climits>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int t,cur,hi,indx;string temp,sname;
struct Input{
    string qu,ansr;
    int ri;
};
int rnd(){
    uniform_int_distribution<int> uid(0,19);
    return uid(rng);
}
Input ques[5][20];
map<string,pair<int,int>> mp;
void CheckUser(string name,int turn){
    if(turn == 2){
        if(mp[name].second){
            cout<<"This player is already registered, would you like to reset score ? [YES/NO] : "; cin>>temp;
            if(temp == "YES") mp[name].first = 0;
        }
    }
}
int ask(int field,string player){
    int ans,q;
    for(int i=0;i<5;i++){
        q = rnd();
        cout<<ques[field][q].qu<<endl<<ques[field][q].ansr<<endl<<"Choose an answer [1-4]: ";
        cin>>ans;
        if(ans == ques[field][q].ri){
            cout<<"You got it right!"<<endl;
            mp[player].first++;
            mp[player].second = max(mp[player].first,mp[player].second);
        }else {cout<<"You got it wrong!"<<endl; return -1;}
    }
    return 1;
}
void Save(){
    ofstream oFile;oFile.open("Scores.txt");
    for(auto it = mp.begin();it != mp.end();it++)
        oFile<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
    oFile<<"eof";
    oFile.close();
}
void Field(int turn){
    if(turn){
        cout<<"Wow! You've reached round 2"<<endl<<"Would you like to change fields ? [YES/NO] : ";
        cin>>temp; if(temp != "YES") return;
    }
    cout<<"1.Capitals"<<endl<<"2.History"<<endl<<"3.Sports"<<endl<<"4.Math"<<endl<<"5.Disease"<<endl;
    cout<<"Enter number of the field [1-5] : "<<endl;
    while(cin>>indx){
        indx--;
        if(indx < 0 || indx > 4){
            cout<<"Enter a valid number [1-5] : "<<endl; continue;
        }else break;
    }
}
int main()
{
    ifstream inFile;inFile.open("Input.txt");
    string a,b;int ans;
    for(int i=0;i<5;i++){
        for(int j=0;j<20;j++){
            a.clear();b.clear();ans = -1;
            getline(inFile,a,'"');getline(inFile,b,'"');inFile>>ans;
            ques[i][j].qu = a,ques[i][j].ansr = b,ques[i][j].ri = ans;
        }
    }
    inFile.close();
    ifstream Score;Score.open("Scores.txt");
    while(!Score.eof()){
        Score>>sname;
        if(sname == "eof") break;
        Score>>cur>>hi;
        mp[sname] = {cur,hi};
    }
    Score.close();
    cout<<"Welcome to Quiz Game"<<endl<<"1. Start a new game"<<endl<<"2. Load game"<<endl<<"Enter number [1-2] : ";
    int in;cin>>in;
    t = 5;
    while(t--){
        if(cin.fail() || in < 1 || in > 2){
            cout<<"Enter a valid number [1-2] ("<<t<<" tries left) : "; cin>>in;
        }else break;
    }
    string pName;
    cout<<"Enter your user name (Don't insert spaces) : ";cin>>pName;CheckUser(pName,in);
    Field(0);
    if(ask(indx,pName) == -1){
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    Field(1);
    if(ask(indx,pName) == -1){
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    cout<<"You have won the GAME!!"<<endl;
    Save();
    return 0;
}
