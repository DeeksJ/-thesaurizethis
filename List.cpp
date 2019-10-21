#include "List.h"

void List::Welcome()                          //Function definition of Welcome
        {
        cout << "\t------------------------------------------\n";
        cout << "\t    Computer Science And Engineering\n";
        cout << "\t   CSCE 2110 - Computer Foundations 2\n";
        cout << "\t Jake Deeks Jad0420 JakeDeeks@my.unt.edu\n";
        cout << "\t------------------------------------------\n\n";
        }

vector<string> List::Split(string str, char delimiter)			//Function to Split up a string of a comma delimited list
{
  vector<string> List1;		//Vector of Strings to store each split of the string
  stringstream ss(str);					//Initializing Sstream
  string tok;										//String to grab each split
  
  while(getline(ss,tok,delimiter))		//while loop to get each split of the string
  {	
    List1.push_back(tok);
  }
 
  return List1;		//return the vector of strings with the splits inside
}

void List::LoadFile()
{
  ifstream inf;       //ifstream to hold the thesauris list
  char Input_file[25];    //holds input file
  vector <string> syn,Temp;//vectors of strings to hold split comma delimited and what pushs into 2d vector
  string node,syno;   //variables used in getline
  int counterN = 0, counterS = 0,position,pos2;
  bool exists =false;

  cout << "Please Input the Synonym List you would like to read from: ";	//Asking for input file
	cin >> Input_file;		//reading in input file
  
  inf.open(Input_file);	//Opening Input File
	if (inf.fail())				//If Loop to test if file works
	{
		cout << "File \"" << Input_file << "\" failed to open." << endl;
		exit(EXIT_FAILURE);
		return;
	}
 cout <<endl;
  
  while(getline(inf,node,':'))    //While loop to read and store everything in list
  {
      Temp.clear();      //Make sure temporary vvector is clear
      pos2 = FindN(node);
     
      
       Temp.push_back(node); //Push back the root word first to be in position 0 in vecotr
       getline(inf,syno,'\n'); //grab the rest of the line which is the comma delimited list
       syn = Split(syno,',');  //function to split comma delimited list
       for(int i = 0; i< syn.size(); ++i)  //for loop to push each element of comma delimited list into vector
       {
          Temp.push_back(syn.at(i));
       }   
       if(pos2 == -1)
       { 
        List.push_back(Temp);   //Push back vector of Root+Synonyms into postion on 2d vector
       }
       else if (pos2 != -1)     //THIS CONDITION IS FOR WHEN THE NODE HAS ALREADY HAD A ROOT WORD CREATED 
       {
         for(int j = 0;j<syn.size();++j)
         {
           List[pos2].push_back(syn[j]); 
         }       
       }
    
         Temp.clear();         //Clear previous data in temp vector
    
    for(int i = 0; i< syn.size();++i)  //Find if synonyms have a root for themselves and if don't make one
      {
        position = FindN(syn[i]);
        
        if(position == -1) //If Synonym doesn't have root word create new one with its synonyms 
         {
           Temp.push_back(syn[i]);
           Temp.push_back(node);
          for(int j=0;j<syn.size();++j)
          {
            if(j!=i) //condition to make new root synonyms of all previous synonyms except itself
            {
            Temp.push_back(syn[j]);
            }
          }
          List.push_back(Temp);   //Make the new root
         }
        else if (position != -1)
        {
         
         for(int j=0;j<syn.size();++j)
          {
            if(j!=i) //condition to make new root synonyms of all previous synonyms except itself
            {
            List[position].push_back(syn[j]); 
            }
          }
        }
     
        Temp.clear();
       }    
      Temp.clear(); //Clear after pushed each synonym check

     }
   
    inf.close();  //close file
}



void List::PrintList()  //function to print the list and check to see if it was made corectly 
{
  ofstream out;
  out.open("LongO.txt");
  
  for(int i = 0;i<List.size();++i)  //double for loop to print the 2d vector
  {
    for(int j = 0;j < List[i].size();++j)
    {
       if(j==0)
        {
        out << List[i][j] << ":";  //Prints Root word followed by :
        }
       else if (List[i].size() == j+1)
       {
         out << List[i][j];   //Prints end synonym
       }
      else
      {
        out << List[i][j] << ",";  //Prints synonyms with comma in between
      }
    }
      out << endl;
  }
  
  out.close();
}

int List::FindN(string syn)    //Initial find function to find is synonym has root already made
{
    for(int i = 0; i < List.size();++i)
    {
      if(List[i][0] == syn)
      {
          return i + 1;
      }
    }
  return -1;
}

string List::Find(string word)  //Second find function to replace the root word with a synonym
{
  srand (time(NULL));
    string passed;
  // CODE THAT I KNOWS WORKS FOR MILESTONE
        for(int i = 0; i < List.size();++i)
        {
        int random= rand() % List[i].size();  //get a random place in the words synonyms
        while(random ==0) //Loop to not get root word
          {
          if(random!=0)
          {
            break;
            break;
          }
          else
          {
          random = rand() % List[i].size(); //
          }
          }
        if(List[i][0] == word)
         {
         return List[i][random];
         }
        }
}


void List::ReplacePara()    //Function to read in paragraph and search each word to find synonyms to replace
{
  ifstream in;
  char paragraph[25];
  int Hops;  //
  char holder1 = ' ';   //Space holder for in between words
  char holder2;       //Punctation holder for punctation
  bool punct = false;     //boolean for if wor being tested has punctation
  bool upper = false;
  string para,word;
      
  cout << "Please Input the Paragraph you would like to read from: ";	//Asking for input file
	cin >> paragraph;		//reading in input file
  cout << endl;
  cout << "Please Enter the Number of times to randomnly swap synonyms: ";  //Asking how many times to swap the root word
  cin >> Hops;  //reading in # of swaps
  
  
  in.open(paragraph);	//Opening Input File
	if (in.fail())				//If Loop to test if file works
	{
		cout << "File \"" << paragraph << "\" failed to open." << endl;
		exit(EXIT_FAILURE);
		return;
	}
  cout <<endl;  
  
  while(in >> word)     //While Loop to look through each word in the paragraph and see if they have synonyms
  {
 
    if(ispunct(word[word.size()-1]))    //Check to see if word checked has puncation tagged on the end
    {   
      holder2 = word[word.size()-1];  //Grab Punctation and store into holder variable
     word.erase(word.size()-1,word.size()); //get rid of the puncation to compare properly  
     punct = true;  //Flag boolean value to say that there was a puncation here
    }
    else if(isupper(word[0]))
    {
      transform(word.begin(),word.end(),word.begin(), ::tolower); //Change word to be all lowercase for find function
      upper = true;
    }
    
      for(int i =0;i<Hops;++i)
      {
      if(FindN(word) != -1) //Function call to replace root word with synonyms
        {
        word = Find(word);    //Replace word with synonym
        }
      }
 
    if (upper == true)
    {
     transform(word.begin(),word.begin()+1,word.begin(), ::toupper);  //Change the first letter back into a Uppercase letter
      para.append(word);              //Add word back
      upper =false;     //reset boolean
    }
    else
    {
    para.append(word);    //add word
    }
    if(punct == true)
    {
      para.push_back(holder2);    //add punctation at end of word
      punct = false;    //reset boolean
    }
    para.push_back(holder1);    //add space into string
  }
  

 cout << para <<endl;
  in.close();
}

void List::Analysis()
{
  ifstream in1,in2;
  int i=0;
  char input1[35],input2[30];
  char holder1 = ' ';   //Space holder for in between words
  char holder2;       //Punctation holder for punctation
  bool punct = false;     //boolean for if wor being tested has punctation
  bool upper = false;
  bool similar;
  vector <string> visited;
  string para,word1,word2;
  
  cout << "Please enter the file name containing Paragraph #1: ";
  cin >> input1;
  cout << endl;
  cout << "Please enter the file name containinf Paragraph #2: ";
  cin >> input2;
  cout << endl;
  in1.open(input1);	//Opening Input File
	if (in1.fail())				//If Loop to test if file works
	{
		cout << "File \"" << input1 << "\" failed to open." << endl;
		exit(EXIT_FAILURE);
		return;
	}

  
  in2.open(input2);	//Opening Input File
	if (in2.fail())				//If Loop to test if file works
	{
		cout << "File \"" << input2 << "\" failed to open." << endl;
		exit(EXIT_FAILURE);
		return;
	}
 
  
   while(in1 >> word1 && in2 >>word2)     //While Loop to look through each word in the paragraph and see if they have synonyms
  {
     
   
    if(ispunct(word1[word1.size()-1]))    //Check to see if word checked has puncation tagged on the end
    {   
     word1.erase(word1.size()-1,word1.size()); //get rid of the puncation to compare properly  
    }
 
    if(ispunct(word2[word2.size()-1]))    //Check to see if word checked has puncation tagged on the end
    {   
     word2.erase(word2.size()-1,word2.size()); //get rid of the puncation to compare properly  
    }
    
    transform(word1.begin(),word1.end(),word1.begin(), ::tolower); //Change word to be all lowercase for find function
    transform(word2.begin(),word2.end(),word2.begin(), ::tolower); //Change word to be all lowercase for find function
    
    if(word1.compare(word2) != 0 && !ispunct(word2[word2.size()-2]))    //Check if there is word1=word2 & if there is 's
     {
       if(FindN(word1) == -1 || FindN(word2)==-1) //check if each word is in the list
       {
         cout << "Paragraphs Are Not Similar" << endl;

        return;         //NEED THIS TO HAVE THE COODE TO WORK DISABLED 
       }
       else
       {         
       similar = BFS(word1,word2);    //Call function for breadth first search and give result to boolean
       } 
       
      if(similar == false)
      {

        cout << "Paragraphs Are Not Similar" << endl; 
        return; //end function if the paragraphs are dissimilar
      }
       else if (similar == true)
       {
   
       }
     }
  }
        cout << "Paragraph Comparison Analysis Completed!" <<endl;
   if(similar==true)
   {
    cout << "Results: Paragraphs are similar!" << endl;     //if paragraphs are similar
   }
  similar = NULL;
  
  in1.close();    //close first paragraph file  
  in2.close();    //close second paragraph file
  
}

bool List::BFS(string start,string end)
{
 int hammingDist =0;
 int totalham;
  vector<string> visited;
  
  visited.push_back(start); //Start node
 
  if(start == end)  //If the words are already the same word
  {
    return true;
  }
 for(int i =0;i < visited.size();i++) //Loop to go through the queue list
 {
  for(int j =0; j<receive(visited.at(i)).size();++j)  //Loop to go through the visited node's synonyms
  { 
    if(!findBfs(receive(visited.at(i)).at(j),visited) ) //see if it was already visited
    {
      if(receive(visited[i]).at(j) == end)  //If the target is found
      {
        return true;
      }
      else
      {
        visited.push_back(receive(visited[i]).at(j)); //if not poush into visited vector
      }
    }
  }

 }
 return false;
}
  
vector<string> List::receive(string syn)  //Function to get the visited node's synonyms
{
  for(int i = 0; i<List.size();++i)
  {
    if(List[i][0] == syn)
    {
      return List[i];
    }
  }
}

bool List::findBfs(string syn, vector<string> visited)  //check if word has already been visited 
{
  for(int i = 0; i < visited.size(); ++i)
  {
    if(visited[i] == syn)
    {
      return true;
    }
  }
  return false;
}