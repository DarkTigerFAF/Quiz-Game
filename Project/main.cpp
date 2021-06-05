#include <bits/stdc++.h>
#include <fstream>
using namespace std;
// The next two lines are just to get a random number.
random_device rd;
mt19937 rng(rd());
struct Input{
    string qu,ansr;
    int ri;
};
Input ques[5][20];
map<string,pair<int,int>> mp;
int t,cur,hi,indx;string temp,sname;
// This function is just to get a random number.
int rnd(){
    uniform_int_distribution<int> uid(0,19);
    return uid(rng);
}
// This function is to make sure that the user only enters an integer and doesn't enter a character.
void clr(int &x){cin.clear();cin.ignore(100000,'\n');cin>>x;}
// This function is to check if that player's name is already registered or if he's a new player.
void CheckUser(string name,int turn){
    if(turn == 1){
        if(mp[name].second){
            cout<<"This player is already registered, would you like to reset score ? [YES/NO] : "; cin>>temp;
            if(temp == "YES") mp[name].first = 0;
        }
    }
}
// This function is to ask the player questions.
int ask(int field,string player){
    int ans,q;
    for(int i=0;i<5;i++){
        q = rnd();
        cout<<ques[field][q].qu<<endl<<ques[field][q].ansr<<endl<<"Choose an answer [1-4]: ";
        t = 5;cin>>ans;
        while(t--){
            if(!t){cout<<"Good Bye!"<<endl;return -1;}
            else if(cin.fail() || ans < 1 || ans > 4){
                cout<<"Enter a valid number [1-4] ("<<t<<" tries left) : ";clr(ans); continue;
            }else break;
        }
        if(ans == ques[field][q].ri){
            cout<<"You got it right!"<<endl;
            mp[player].first++;
            mp[player].second = max(mp[player].first,mp[player].second);
        }else {cout<<"You got it wrong!"<<endl; return -1;}
    }
    return 1;
}
// This function is to save all the scores into the Scores file.
void Save(){
    ofstream oFile;oFile.open("Scores.txt");
    for(auto it = mp.begin();it != mp.end();it++)
        oFile<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
    oFile<<"eof";
    oFile.close();
}
// This function is to display the leaderboards.
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
// This function asks which field does the user want.
void Field(int turn){
    if(turn){
        cout<<"Wow! You've reached round 2"<<endl<<"Would you like to change fields ? [YES/NO] : ";
        cin>>temp; if(temp != "YES") return;
    }
    cout<<"1.Capitals"<<endl<<"2.History"<<endl<<"3.Sports"<<endl<<"4.Math"<<endl<<"5.Disease"<<endl;
    cout<<"Enter number of the field [1-5] : ";
    t = 5;cin>>indx;
    while(t--){
        indx--;
        if(!t){cout<<"Good Bye!"<<endl;return;}
        else if(indx < 0 || indx > 4){
            cout<<"Enter a valid number [1-5] ("<<t<<" tries left) : ";clr(indx); continue;
        }else break;
    }
}
void getFile(){
    // Getting the questions from the file into the array
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
    
    //---------------------------------------------------------------------------------
    // Getting old score data
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
    cout<<"Welcome to Quiz Game"<<endl;int in = 3;
    while(in == 3){
        cout<<"1. Start a new game"<<endl<<"2. Load game"<<endl<<"3. Show leaderboards"<<endl<<"Enter number [1-3] : ";
        cin>>in;
        // This loop is to make sure that the user enters a number between [1 - 3], and the variable 't' stands for the number of tries the user got left;
        t = 5;
        while(t--){
            if(!t){cout<<"Good Bye!"<<endl;return 0;}
            else if(cin.fail() || in < 1 || in > 3){
                cout<<"Enter a valid number [1-3] ("<<t<<" tries left) : ";clr(in);
            }else break;
        }
        if(in == 3) ShowScore();
    }
    string pName; // pName is for the player's name, I'm asking the user to enter his name.
    cout<<"Enter your user name (Don't insert spaces) : ";cin>>pName;CheckUser(pName,in);
    // CheckUser is to check if that player's name is already registered or if he's a new player.
    Field(0);if(!t) return 0;
    // if function ask() returns -1 that means the player has lost and I'm closing the game for him.
    if(ask(indx,pName) == -1){
        // if 't' equals zero it means that the user didn't enter a valid answer between [1 - 4] too many times.
        if(!t) return 0;
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    
    //-----------------------------------------------------------------------------------
    // Second round of the game.
    Field(1);if(!t) return 0;
    if(ask(indx,pName) == -1){
        if(!t) return 0;
        cout<<"Game Over!!"<<endl;
        Save();
        return 0;
    }
    cout<<"You have won the GAME!!"<<endl;
    Save();
    return 0;
}
