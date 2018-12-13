//in oublic class
int findName(string name);

void deleteArtistTree(ArtistNode* node){
  if(node == NULL){
    return;
  }
  deleteArtistTree(node->leftChild);
  //delete node;
  free(node);
  deleteArtistTree(node->rightChild);
  return;
}

void ArtistTree::deleteTree(string name){
  ArtistNode* temp = search(name);
  deleteArtistTree(temp);
  root = NULL;
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
  if(root == NULL){
    cout<<"My Library is empty. Add music to your library!"<<endl;
    //cout<<"Need some help? Display the music database again."<<endl;
  } else {
    printArtist(root);
  }
    return;
}

int Hash::findName(string name){
  for(int i = 0; i < size; i++){
    while(table[i] != NULL){
      //cout<<table[i]->genre<<endl;
      if(table[i]->name == name){
        cout<<"here"<<endl;
        return 0;
      }
      //cout<<"here"<<endl;
      table[i] = table[i]->next;
    }
  }
  return 1;
}

void ArtistTree::addArtist(string name){
  //search for string name in the hashtable. if its not there, print error code
  Hash hash= Hash();
  if(hash.findName(name) == 1){
    cout<<"Artist not in database"<<endl;
    return;
  }
  ArtistNode *newArtist = new ArtistNode;
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
