#include "artists.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

//CONSTRUCTOR
artistsDatabase::artistsDatabase(){

}
//DESTRUCTOR
artistsDatabase::~artistsDatabase(){

}

//ADD VERTEX
void artistsDatabase::addV(string name, string genre){
  artist art;
  art.name=name;
  art.genre=genre;
  verts.push_back(art);
}

//ADD EDGE
void artistsDatabase::addE(){
  for(int i=0;i<verts.size();i++){
      for(int j=0;j<verts.size();j++){
        if(verts[j].genre==verts[i].genre&&j!=i){
          artGenre gen;
          gen.A=&verts[j];
          verts[i].edges.push_back(gen);
        }
      }
    }
}

//FIND VERTEX NAME
artist* artistsDatabase::find(string name){
  for(int i=0;i<verts.size();i++){
    if(verts[i].name==name){
      return &verts[i];
    }
  }
}

//FIND VERTEX GENRE
artist* artistsDatabase::findG(string genre){
  for(int i=0;i<verts.size();i++){
    if(verts[i].genre==genre){
      return &verts[i];
    }
  }
}

//FIND RELATED ARTIST
void artistsDatabase::related(string name){
  queue<artist*> que;
  artist* vert = find(name);
  vert->visited=true;
  que.push(vert);

while(!que.empty()){
  vert=que.front();
  que.pop();
  for(int i=0; i<vert->edges.size();i++){
    if(vert->edges[i].A->visited!=true){
      vert->edges[i].A->visited =true;
      que.push(vert->edges[i].A);
      cout<<vert->edges[i].A->name<<", ";
    }
  }
}
cout<<endl;
} //BFS search?

//FIND RELATED GENRE
string artistsDatabase::findGenre(string genre){
    queue<artist*> que;
    string genName;
  for(int i=0; i<verts.size();i++){
    if(verts[i].genre==genre){
       genName= verts[i].name;
    }
    break;
  }
cout<<1;
  artist* gene = find(genName);
  cout<<1;
 //gene->visited=true;
 cout<<1;
  que.push(gene);
while(!que.empty()){
  gene=que.front();
  que.pop();
  for(int i=0; i<gene->edges.size();i++){
    if(gene->edges[i].A->visited!=true){
      gene->edges[i].A->visited =true;
      que.push(gene->edges[i].A);
      cout<<gene->edges[i].A->genre<<", ";
    }
  }
}
cout<<endl;

}//BFS  search?
string artistsDatabase::viewLibray(){

}
string artistsDatabase::addArtist(string name, string genre){

}
string artistsDatabase::displayLibrary(){

}
string artistsDatabase::addToMyLibrary(string name, string genre){

}
string artistsDatabase::removeFromMyLibrary(string name){

}


void artistsDatabase::displayEdges(){
  for (int i=0;i<verts.size();i++) {
   cout<<verts[i].name<<" ->";
   for (int j = 0;j<verts[i].edges.size();j++){
     cout<<verts[i].edges[j].A->name<<"->";
   }
   cout<<endl;
 }
}


int main(int argc, char*argv[]){
    artistsDatabase yay;
   ifstream myfile("artFile.txt");
  string line;
  if(myfile.is_open()){
    while(getline(myfile,line)){
      stringstream comp;
      comp<<line;
      string Fgenre;
      string Fname;
      int count=0;
      while(getline(comp, line, ',')){
        if (count == 0) {
  				Fname =line;
  			}
  			else if (count == 1) {
  				Fgenre = line;
  			}
  			count++;
  		}
    //cout<<name<<" "<<genre;
     yay.addV(Fname, Fgenre);
   }
  }
  else{
    cout<<"failed to open file"<<endl;
  }
  yay.addE();
   yay.displayEdges();
    // MENU

    string choice;
    string name;
    string genre;
    cout<<endl;
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Search for Related Artists"<<endl;
    cout<<"2. Search Genre"<<endl;
    cout<<"3. View My Libray"<<endl;
    cout<<"4. Add an Artist to the Database"<<endl;
    cout<<"5. Quit"<<endl;
    cin>>choice;
    while(choice!="5"){
        if(choice=="1"){
          cout<<"Enter Artist Name: ";
          cin>>name;
          //for(int i=0;i<yay.verts.size();i++){
            // if(name!=yay.verts[i].name){
            //   cout<<"Name not in System, Try Again"<<endl;
            // }
            // else{
                yay.related(name);
            //}
            //break;
          //}
        }
        if(choice=="2"){
          cout<<"Enter Genre: ";
          cin>>genre;
          yay.findGenre(genre);


        }
        if(choice=="3"){
          string choice2;
          string name2;
          string genre2;
          cout<<"======My Library======"<<endl;
          cout<<"1. Dispaly My Library"<<endl;
          cout<<"2. Add an Artist to My Library"<<endl;
          cout<<"3. Remove an Artist from My Libray"<<endl;
          cout<<"4. Exit to Main Menu"<<endl;
          cin>>choice2;
          while(choice2!="4"){
              if(choice2=="1"){
                yay.displayLibrary();
              }
              if(choice2=="2"){
                cout<<"Enter Name: ";
                cin>>name2;
                cout<<"Enter Genre: ";
                cin>>genre2;
                yay.addToMyLibrary(name2, genre2);
              }
              if(choice2=="3"){
                cout<<"Enter Name of Artist to Remove: ";
                cin>>name2;
                yay.removeFromMyLibrary(name2);
              }
              if(choice2=="4"){
                cout<<"Goodbye!";
              }
            }
          }
    if(choice=="4"){
      cout<<"Enter Name: ";
      cin>>name;
      cout<<"Enter Genre";
      cin>>genre;
      yay.addArtist(name,genre);
    }
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Search for Related Artists"<<endl;
    cout<<"2. Search Genre"<<endl;
    cout<<"3. View My Libray"<<endl;
    cout<<"4. Add an Artist to the Database"<<endl;
    cout<<"5. Quit"<<endl;
    cin>>choice;
    }

    if(choice=="5"){
      cout<<"Goodbye!"<<endl;
}

    return 0;
}