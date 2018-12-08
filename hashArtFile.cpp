// #include "hashArt.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

struct artist{
  string name;
  string genre;
  artist*next;
};

class Hash{
  int size;
  artist** table;
public:
  Hash();
  ~Hash();
  void add(string name, string genre);
  void related(string name); //BFS search?
  int hashFunction(string genre);
  void findGenre(string genre);
  void addArtist(string name, string genre);
  void display();
};


Hash::Hash(){
  size=5;
  table=new artist*[size];
  for (int i = 0; i < size; i++) {
       table[i] = new artist;
       table[i]->name = "";
       table[i]->next = NULL;
   }
}
Hash::~Hash(){
  for(int i=0; i<size; i++){
  artist* head=table[i];
  while(head!=NULL){
        artist*temp=head->next;
        delete head;
        head=temp;
      }
      table[i]=NULL;
    }
}
void Hash::add(string name, string genre){
  int index=hashFunction(genre);
  artist* head=table[index];

  if(table[index]==NULL){
    artist* art=new artist;
    art->name=name;
    art->genre=genre;
    art->next=NULL;
    table[index]=art;
  }
  else{
    artist* prev;
      while(head!=NULL){
          prev=head;
          head=head->next;
      }
      if(head==NULL){
          artist* temp = new artist;
          temp->name=name;
          temp->genre=genre;
          temp->next=NULL;
          prev->next=temp;
      }
    }
}

void Hash::related(string name){
  for(int i;i<size;i++){
    if(table[i]->name==name){
      string gen = table[i]->genre;
      int index=hashFunction(gen);
      while(table[index]->next!=NULL){
        if(table[index]->next->genre==gen){
          cout<<table[index]->next->genre<<",";
        }
        table[index]->next=table[index]->next->next;
      }
    }
  }
} //BFS search?
int Hash::hashFunction(string word){
   unsigned long hash = 5381;
    int c;
    for(int i=0; i<word.length(); i++){
      c = (int) word[i];
      hash = hash*33 + c;
      }
  hash = hash % size;
  if(hash < 0)
      hash+=size;

  return hash;
  }
void Hash::findGenre(string genre){

}
void Hash::addArtist(string name, string genre){

}
void Hash::display(){
  for (int i = 0; i < 5; i++){
    while(table[i]->next!=NULL){
      cout<<table[i]->name<<", "<<table[i]->genre<<"->";
      cout<<table[i]->next->name<<", "<<table[i]->next->genre;
      cout<<endl;
      table[i]->next=table[i]->next->next;

    }
    cout<<table[i]->name<<", "<<table[i]->genre<<"->";
    cout<<endl;
}

}

int main(){
  Hash hash= Hash();
cout<<1;
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
    cout<<Fname<<" "<<Fgenre;
     hash.add(Fname, Fgenre);
   }
   cout<<endl;
  }
  else{
    cout<<"failed to open file"<<endl;
  }
   hash.display();
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
                hash.related(name);
            //}
            //break;
          //}
        }
        if(choice=="2"){
          cout<<"Enter Genre: ";
          cin>>genre;
          hash.findGenre(genre);


        }
        if(choice=="3"){
          // string choice2;
          // string name2;
          // string genre2;
          // cout<<"======My Library======"<<endl;
          // cout<<"1. Dispaly My Library"<<endl;
          // cout<<"2. Add an Artist to My Library"<<endl;
          // cout<<"3. Remove an Artist from My Libray"<<endl;
          // cout<<"4. Exit to Main Menu"<<endl;
          // cin>>choice2;
          // while(choice2!="4"){
          //     if(choice2=="1"){
          //       yay.displayLibrary();
          //     }
          //     if(choice2=="2"){
          //       cout<<"Enter Name: ";
          //       cin>>name2;
          //       cout<<"Enter Genre: ";
          //       cin>>genre2;
          //       yay.addToMyLibrary(name2, genre2);
          //     }
          //     if(choice2=="3"){
          //       cout<<"Enter Name of Artist to Remove: ";
          //       cin>>name2;
          //       yay.removeFromMyLibrary(name2);
          //     }
          //     if(choice2=="4"){
          //       cout<<"Goodbye!";
          //     }
          //   }
          }
    if(choice=="4"){
      cout<<"Enter Name: ";
      cin>>name;
      cout<<"Enter Genre: ";
      cin>>genre;
      hash.add(name,genre);
      hash.display();
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
