#ifndef ARTISTS_HPP
#define ARTISTS_HPP

#include <vector>
#include <iostream>

using namespace std;
struct artist;
//the vectors are the artists and genre are the edges?
struct artGenre{
  artist *A;
  int dist; //not sure if we need a distance??
};

struct artist{
  string name;
  string genre;
  bool visited;
  vector<artGenre> edges; //this is the adjedcncy list where the similar generes are stored I think...
};

class artistsDatabase{
private:
  vector<artist>verts; //the list of vertices
public:
  artistsDatabase();
  ~artistsDatabase();
  void displayEdges();
  artist* find(string name);
  void addV(string name, string genre);
  void addE();
  void related(string name); //BFS search?
  string findGenre(string genre); //BFS  search?
  string viewLibray();
  string addArtist(string name, string genre);
  string displayLibrary();
  string addToMyLibrary(string name, string genre);
  string removeFromMyLibrary(string name);
};

struct ArtistNode
{
  std::string name;

  ArtistNode *parent;
  ArtistNode *leftChild;
  ArtistNode *rightChild;

  ArtistNode(){
    parent = leftChild = rightChild = nullptr;
  }

  ArtistNode(std::string n) {
    name = n;
    parent = leftChild = rightChild = nullptr;
  }
};

class ArtistTree{
public:
  ArtistTree();
  ~ArtistTree();
  void printArtistLibrary();
  void addArtist(std::string title);
  //void findArist(std::string title);

private:
  ArtistNode *search(std::string title);
  ArtistNode *root;
};

# endif
