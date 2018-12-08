#ifndef HASHART_HPP
#define HASHART_HPP

#include <vector>
#include <iostream>
using namespace std;

struct artist{
  string name;
  string genre;
  artist*next;
};

class Hash{
private:
  int size;
  artist** table;
public:
  Hash(int size);
  ~Hash();
  void add(string name);
  void related(string name); //BFS search?
  void hahsFunction(string genre);
  void findGenre(string genre);
  void addArtist(string name, string genre);
  void display();
};
#endif
