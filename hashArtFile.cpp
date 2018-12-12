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
  //artist* head;
public:
  Hash();
  ~Hash();
  void add(string name, string genre);
  void related(string name); //BFS search?
  int hashFunction(string genre);
  void findGenre(string genre);
  string nameToGen(string name);

};

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

Hash::Hash(){
  size=100;
  table=new artist*[size];
  for (int i = 0; i < size; i++) {
       table[i] = new artist;
       table[i]->name = "";
       table[i]->next = NULL;
       //head=artist;

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
  artist* prev;

  if(head->name==""){
    head->name=name;
    head->genre=genre;
    cout<<"new item added: "<<head->genre<<" "<<head->name;
  }
  else{
    artist* art= new artist;
    art->name=name;
    art->genre=genre;
    art->next=NULL;
    while(head->next!=NULL){
        prev=head;
        head=head->next;
    }
    head->next=art;
    cout<<art->genre<<"-->"<<art->name;
  }
  cout<<endl;
  return;
}
 string Hash::nameToGen(string name){
   string gen;
   for(int i=0;i<size;i++){
     while(table[i]!=NULL){
       if(table[i]->name==name){
         gen=table[i]->genre;
         return gen;
       }
       table[i]=table[i]->next;
     }
   }
 }

void Hash::related(string name){
    string gen=nameToGen(name);
    int index=hashFunction(gen);
    artist* head=table[index];
    cout<<"Artists Recommended: ";
      while(table[index]!=NULL){
        if(table[index]->name!=name){;
          cout<<table[index]->name<<", ";
        }
        table[index]=table[index]->next;
      }
    cout<<endl;
    table[index]=head;
    return;
}

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
  int index=hashFunction(genre);
    artist* head=table[index];
  cout<<"Artists Recommended: ";
  while(table[index]!=NULL){
      cout<<table[index]->name<<", ";
    table[index]=table[index]->next;
  }
  cout<<endl;
  table[index]=head;
  return;
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
    return;
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

ArtistNode* ArtistTree::minValueNode(ArtistNode* node)
{
    ArtistNode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->leftChild != NULL)
        current = current->leftChild;

    return current;
}

ArtistNode* ArtistTree::deleteNode(string name)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (name < root->name){
      root = root->leftChild;
      root->leftChild = deleteNode(root->name);

    }

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (name > root->name){
      root = root->rightChild;
      root->rightChild = deleteNode(root->name);

    }

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->leftChild == NULL)
        {
            ArtistNode *temp = root->rightChild;
            delete root;
            //free(root);
            return temp;
        }
        else if (root->rightChild == NULL)
        {
            ArtistNode *temp = root->leftChild;
            delete root;
            //free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        ArtistNode* temp = minValueNode(root->rightChild);

        // Copy the inorder successor's content to this node
        root->name = temp->name;

        // Delete the inorder successor
        root = root->rightChild;
        root->rightChild = deleteNode(temp->name);
    }
    return root;
}


int main(){
  Hash hash= Hash();
  ArtistTree tree;
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
    //cout<<Fname<<" "<<Fgenre<<endl;
     hash.add(Fname, Fgenre);
   }

  }
  else{
    cout<<"failed to open file"<<endl;
  }
   //hash.display();
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
    cout<<"Select option: ";
    cin>>choice;
    while(choice!="5"){
        if(choice=="1"){
          string searchName;
          cout<<"Enter Artist Name: ";
          cin>>searchName;
          hash.related(searchName);
        }

        if(choice=="2"){
          string searchGenre;
          cout<<"Enter Genre: ";
          cin>>searchGenre;
          hash.findGenre(searchGenre);
        }

        if(choice=="3"){
          string choice2;
          string name2;
          string genre2;
          cout<<endl;
          cout<<"======My Library======"<<endl;
          cout<<"1. Display My Library"<<endl;
          cout<<"2. Add an Artist to My Library"<<endl;
          cout<<"3. Delete an artist from My Library"<<endl;
          cout<<"4. Exit to Main Menu"<<endl;
          cout<<"Select option: ";
          cin>>choice2;
          while(choice2!="4"){
            if(choice2=="1"){
              tree.printArtistLibrary();
              cout<<endl;
              break;
            }
            if(choice2=="2"){
              cout<<"Enter Name: ";
              cin>>name2;
              tree.addArtist(name2);
              break;
            }
           if(choice2=="3"){
             cout<<"Enter artist you want to delete: ";
             cin>>name2;
             tree.deleteNode(name2);
          //cout<<"Clearing your library..."<<endl;
          //cin>>name2;
          //yes.~ArtistTree();
          break;
           }
          }
        if(choice2=="4"){
          cout<<"Goodbye!"<<endl;
        }
      }

    if(choice=="4"){
      string newName;
      string newGenre;
      cout<<"Enter Name: ";
      cin>>newName;
      cout<<"Enter Genre: ";
      cin>>newGenre;
      hash.add(newName,newGenre);
    }
    
    cout<<endl;
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Search for Related Artists"<<endl;
    cout<<"2. Search Genre"<<endl;
    cout<<"3. View My Library"<<endl;
    cout<<"4. Add an Artist to the Database"<<endl;
    cout<<"5. Quit"<<endl;
    cout<<"Select option: ";
    cin>>choice;
    }
    if(choice=="5"){
      cout<<"Goodbye!"<<endl;
}
    return 0;
}
