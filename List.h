#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <queue>
using namespace std;

class List
{
private:
      vector<vector<string> > List;
public:
      
      void Welcome();
      vector<string> Split(string str, char delimiter);	//Split Function initializing
      void LoadFile();
      void PrintList();
      int FindN(string syn);
      string Find(string word);
      void ReplacePara();
      void Analysis();
      bool BFS(string start, string end);
      vector<string> receive(string syn);
      bool findBfs(string syn, vector<string> visited);
};
