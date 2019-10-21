#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cctype> //investigate
#include "List.h"
using namespace std;
 
//Test As you go

int main()
{
  
  system("clear");
  //Vector of Vector strings
  int choice;
  
  List graph;
  
  graph.Welcome();
  graph.LoadFile();
  
  graph.PrintList();
 
 
  cout << "Welcome to !thesaurizethis, What would you like to do?"<<endl;
  cout << "1)Random Synonym Replacement\n2)Paragraph Similarity Analysis\n3)Quit" <<endl;
  cin >> choice;
  switch(choice)
  {
    case 1:
      {
    
      graph.ReplacePara();
      break;
      }
    case 2:
      {
      graph.Analysis();
      break;
      }
    case 3:
      {
      cout << "Quiting program....." << endl;
      break;
      }
  }
 
  return 0;
  
}
