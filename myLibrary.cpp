#include <iostream>
using namespace std;

// Binary Tree Node
struct Node {
    string name;
    Node *left, *right;
};


/*void deleteMovieTree(MovieNode* node){
  if(node == NULL){
    return;
  }
  deleteMovieTree(node->leftChild);
  delete node;
  deleteMovieTree(node->rightChild);
return;
}*/

/*MovieNode* MovieTree::search(string title){
  if(root==NULL){
    return NULL;
  }
  MovieNode *current = root;
  while(current!=NULL){
    if(current->title == title){
      return current;
    }
    if(title < current->title){
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }
  return current;
}*/

/*MovieNode* printMovie(MovieNode *node){
  if(node!=NULL){
    printMovie(node->leftChild);
    cout<<"Movie: "<< node->title <<" "<<node->quantity<<endl;
    printMovie(node->rightChild);
  }
  return node;
}*/

void addArtist(string name){
  Node *newArtist = newNode(name);
  MovieNode *current = root;
  while(root!=NULL){
    if(name == current->name){
        return;
    } else if(name < current->name){
        if(current->leftChild == NULL){
            current->leftChild = newArtst;
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


Node* newNode(string letter){
    Node* node = new Node;
    node->letter = letter;
    node->left = node->right = NULL;
    return (node);
}

int main(){
  Node* root = newNode(M);
    // Binary Tree is:
    //       M
    //      /  \
    //
    //    / \  / \
    //   4   5 6  7
    //          \
    //           8
    /*Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->left->right = newNode(8);*/

    return 0;
}
