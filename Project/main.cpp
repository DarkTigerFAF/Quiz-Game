#include <bits/stdc++.h>
#include <fstream>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Input{
    string qu,ansr;
    int ri;
};

Input ques[5][20];
map<string,pair<int,int>> mp;
int t,cur,hi,indx;string temp,sname;
bool leave = false;
int rnd(){
    uniform_int_distribution<int> uid(0,19);
    return uid(rng);
}

void clr(int &x){cin.clear();cin.ignore(100000,'\n');cin>>x;}

int ErrorChecking(int& check,int l,int r,int base){
    t = 5;
    if(!base) l--,r--;
    //-------------------------------------------------
    // Error checking.
    /**/while(t--){
    /**/    if(!t){cout<<"Good Bye!"<<endl;return 0;}
    /**/    else if(cin.fail() || check < l || check > r){
    /**/        cout<<"Enter a valid number ["<<(base?l:l+1)<<"-"<<(base?r:r+1)<<"] ("<<t<<" tries left) : ";clr(check); continue;
    /**/    }else break;
    /**/}
    //--------------------------------------------------
    return 1;
}

void CheckUser(string name,int turn){
    if(turn == 1){
        if(mp[name].second){
            cout<<"This player is already registered, would you like to reset score ? [YES/NO] : "; cin>>temp;
            if(temp == "YES") mp[name].first = 0;
        }
    }else{
        if(!mp[name].second)
            cout<<"This name isn't registered, but now it's registered."<<endl;
    }
}

int ask(int field,string player){
    int ans,q;
    for(int i=0;i<5;i++){
        q = rnd();
        cout<<"_______________________________________________________"<<endl;
        cout<<ques[field][q].qu<<endl<<ques[field][q].ansr<<endl<<"Choose an answer [1-4]: ";
        t = 5;cin>>ans;
        if(!ErrorChecking(ans,1,4,1)) {leave = true;return -1;}
        if(ans == ques[field][q].ri){
            cout<<"You got it right!!"<<endl;
            mp[player].first++;
            mp[player].second = max(mp[player].first,mp[player].second);
        }else {cout<<endl<<"You got it wrong!"<<endl; return -1;}
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

void ShowScore(){
    for(auto it = mp.begin();it != mp.end();it++){
        if(it != mp.begin()){}else cout<<"Name : ";
        cout<<it->first<<"  ";
    }cout<<endl;
    for(auto it = mp.begin();it != mp.end();it++){
        if(it != mp.begin()){}else cout<<"Current Score : ";
        cout<<it->second.first<<"  ";
    }cout<<endl;
    for(auto it = mp.begin();it != mp.end();it++){
        if(it != mp.begin()){}else cout<<"Highest Score : ";
        cout<<it->second.second<<"  ";
    }cout<<endl;cout<<endl;
}

void Field(int turn){
    if(turn){
        cout<<"Wow! You've reached round 2"<<endl<<"Would you like to change fields ? [YES/NO] : ";
        cin>>temp; if(temp != "YES") return;
    }
    cout<<"1.Capitals"<<endl<<"2.History"<<endl<<"3.Sports"<<endl<<"4.Math"<<endl<<"5.Disease"<<endl;
    cout<<"Enter number of the field [1-5] : ";
    t = 5;cin>>indx;
    ErrorChecking(indx,1,5,0);
}

void getFile(){
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
}
int main()
{
    getFile();
    cout<<"<<<<<<<<<<<<<<<<<<Welcome to Quiz Game>>>>>>>>>>>>>>>>>"<<endl;int in = 3;
    while(in == 3){
        cout<<"1. Start a new game"<<endl<<"2. Load game"<<endl<<"3. Show leaderboards"<<endl<<"Enter number [1-3] : ";
        cin>>in;
        t = 5;
        if(!ErrorChecking(in,1,3,1)) return 0;
        if(in == 3) ShowScore();
    }
    string pName;
    cout<<"Enter your user name (Don't insert spaces) : ";cin>>pName;CheckUser(pName,in);
    Field(0);if(!t) return 0;
    cout<<"_______________________________________________________"<<endl;
    if(ask(indx - 1,pName) == -1){
        if(leave) {Save();return 0;}
        cout<<"_______________________________________________________"<<endl;
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    Field(1);if(!t) return 0;
    if(ask(indx - 1,pName) == -1){
        if(leave) {Save();return 0;}
        cout<<"_______________________________________________________"<<endl;
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    cout<<"_______________________________________________________"<<endl;
    cout<<"You have won the GAME!!"<<endl;
    Save();
    return 0;
}
