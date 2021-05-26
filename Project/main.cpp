#include <bits/stdc++.h>
#include <fstream>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int t,cur,hi;string temp,sname;
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
    cout<<"Welcome to Quiz Game"<<endl<<"Press 1 to load profile or 2 to start a new game : ";
    int indx;cin>>indx;
    t = 5;while(t--){if(cin.fail() || (indx<1 || indx > 2)) {if(!t){cout<<"Goodbye!";return 0;}cout<<"Please enter a valid number [1-2] "<<t<<" tries left.";} else t = 0;}
    string pName;
    cout<<"Enter your user name [Don't insert spaces]: ";cin>>pName;CheckUser(pName,indx);
    cout<<"Please choose a field [1-5]"<<endl;
    cout<<"1.Capitals 2.History 3.Sports 4.Math 5.Disease"<<endl;
    while(cin>>indx){
        indx--;
        if(indx < 0 || indx > 4){
            cout<<"You have to enter a number between 1 and 5"<<endl; continue;
        }else break;
    }
    if(ask(indx,pName) == -1){
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    cout<<"Wow! You've reached round 2"<<endl<<"Would you like to change fields ? [YES/NO] : ";
    cin>>temp; if(temp == "YES")cin>>indx;// {cout<<"Please enter cin>>indx;
    if(ask(indx,pName) == -1){
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    cout<<"You have won the GAME!!"<<endl;
    Save();
    return 0;
}
