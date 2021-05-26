#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int t;
int main()
{
    vector<vector<pair<string,pair<string,int>>>> ques;
    ifstream inFile;inFile.open("Input.txt");
    vector<pair<string,pair<string,int>>> temp;
    string a,b;int ans;
    for(int i=0;i<5;i++){
        temp.clear();
        for(int j=0;j<20;j++){
            a.clear();b.clear();ans = -1;
            getline(inFile,a,'"');getline(inFile,b,'"');inFile>>ans;
            temp.push_back({a,{b,ans}});
        }
        ques.push_back(temp);
    }
    inFile.close();
    ifstream Score;Score.open("Scores.txt");
    string name;int cur,hi;
    map<string,pair<int,int>> mp;
    while(!Score.eof()){
        Score>>name;
        if(name == "eof") break;
        Score>>cur>>hi;
        mp[name] = {cur,hi};
    }
    Score.close();
    cout<<"Welcome to Quiz Game"<<endl<<"Press 1 to load profile or 2 to start a new game : ";
    int indx;cin>>indx;
    t = 5;while(t--){if(cin.fail() || (indx<1 || indx > 2)) {if(!t){cout<<"Goodbye!";return 0;}cout<<"Please enter a valid number [1-2] "<<t<<" tries left.";} else t = 0;}
    string pName;
    cout<<"Enter your username : ";
    if(indx == 2){
        cin>>pName;
        if(mp[pName].second){
            cout<<"This player is already registered, would you like to reset score ? : ";
            string tryy;cin>>tryy;
            if(tryy == "yes") mp[name].first = 0;
        }
    }else
        cin>>pName;
    cout<<"Please choose a field [1-5]"<<endl;
    while(cin>>indx){
        indx--;
        if(indx < 0 || indx > 4){
            cout<<"You have to enter a number between 1 and 5"<<endl;
            continue;
        }else break;
    }
    bool lost = false;
    for(int i=0;i<5;i++){
        int q = rand() % 20;
        cout<<ques[indx][q].first<<endl<<ques[indx][q].second.first<<endl<<"Choose an answer [1-4]: ";
        int tryy;cin>>tryy;
        if(tryy == ques[indx][q].second.second){
            cout<<"You got it right!"<<endl<<endl;
            mp[pName].first++;
            mp[pName].second = max(mp[pName].first,mp[pName].second);
        }else {cout<<"You got it wrong!"<<endl<<endl;lost = true;break;}
    }
    if(!lost){
            for(int i=0;i<5;i++){
            int q = rand() % 20;
            cout<<ques[indx][q].first<<endl<<ques[indx][q].second.first<<endl<<"Choose an answer [1-4]: ";
            int tryy;cin>>tryy;
            if(tryy == ques[indx][q].second.second){
                cout<<"You got it right!"<<endl<<endl;
                mp[pName].first++;
                mp[pName].second = max(mp[pName].first,mp[pName].second);
            }else {cout<<"You got it wrong!"<<endl<<endl;lost = true;}
        }
    }
    cout<<"Game Over!"<<endl;
    ofstream oFile;oFile.open("Scores.txt");
    for(auto it = mp.begin();it != mp.end();it++){
      //  cout<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
        oFile<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
    }
    oFile<<"eof";
    oFile.close();
    return 0;
}
