struct ArtistNode
{
  std::string name;

  ArtistNode *parent;
  ArtistNode *leftChild;
  ArtistNode *rightChild;

  ArtistNode(){
    parent = leftChild = rightChild = NULL;
  }

  ArtistNode(std::string n) {
    name = n;
    parent = leftChild = rightChild = NULL;
  }
};

class ArtistTree{
public:
  ArtistTree();
  ~ArtistTree();
  void printArtistLibrary();
  void addArtist(string name);
  void deleteArtist(string name);
  ArtistNode *deleteNode(string name);
  ArtistNode *minValueNode(ArtistNode* node);
  ArtistNode *root;
  //void findArist(std::string title);

private:
  ArtistNode *search(std::string title);
};





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
    string name;
  for(int i=0; i<verts.size();i++){
    //cout<<verts[i].genre;
    if(verts[i].genre==genre){
       name= verts[i].name;
    }
  }

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
}//BFS  search?

string artistsDatabase::addArtist(string name, string genre){
  artist art;
  art.name=name;
  art.genre=genre;
  verts.push_back(art);
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

void deleteArtistTree(ArtistNode* node){
  if(node == NULL){
    return;
  }
  deleteArtistTree(node->leftChild);
  delete node;
  deleteArtistTree(node->rightChild);
return;
}

ArtistTree::ArtistTree(){
    root = NULL;
}

ArtistTree::~ArtistTree(){
    deleteArtistTree(root);
}

ArtistNode* ArtistTree::search(string name){
  if(root==NULL){
    return NULL;
  }
  ArtistNode *current = root;
  while(current!=NULL){
    if(current->name == name){
      return current;
    }
    if(name < current->name){
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }
  return current;
}

ArtistNode* printArtist(ArtistNode *node){
  if(node!=NULL){
    printArtist(node->leftChild);
    cout<<"Artist: "<< node->name <<endl;
    printArtist(node->rightChild);
  }
  return node;
}

void ArtistTree::printArtistLibrary(){
    printArtist(root);
}


void ArtistTree::addArtist(string name){
  ArtistNode *newArtist = new ArtistNode(name);
  if(root == NULL){
    root = newArtist;
    return;
  }
  ArtistNode *current = root;
  while(root!=NULL){
    if(name == current->name){
        return;
    } else if(name < current->name){
        if(current->leftChild == NULL){
            current->leftChild = newArtist;
            newArtist->parent = current;
            return;
        }
        current = current->leftChild;
    } else if(name > current->name){
        if(current->rightChild == NULL){
            current->rightChild = newArtist;
            newArtist->parent = current;
            return;
        }
        current = current->leftChild;
    }
  }
}


int main(int argc, char*argv[]){
    artistsDatabase yay;
  ArtistTree yes;
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
              yes.printArtistLibrary();
            }
            if(choice2=="2"){
               cout<<"Enter Name: ";
               cin>>name2;
               yes.addArtist(name2);
               break;
            }
              /*if(choice2=="3"){
                cout<<"Enter Name of Artist to Remove: ";
                cin>>name2;
                yay.removeFromMyLibrary(name2);
              }*/
          }
          if(choice2=="4"){
             cout<<"Goodbye!";
          }
        }
    if(choice=="4"){
      cout<<"Enter Name: ";
      cin>>name;
      cout<<"Enter Genre: ";
      cin>>genre;
      yay.addArtist(name,genre);
      cout<<1;
      yay.addE();
      yay.displayEdges();
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
