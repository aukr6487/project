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
