#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>
#include <istream>
#include <assert.h> 
#include <sstream>
using namespace std;

bool MatchingQuotes(char a, char b);
bool MatchingDoubleQuotes(char a, char b);
bool MatchingParens(char a, char b);
bool MatchingBlocks(char a, char b, char c, istream& file);


void printFile(istream& dictfile) 
{
    int LineNumber = 1;
    string buffer;
    
    while (getline(dictfile, buffer)) {
        
        cout << LineNumber << " " << left << setw(3) << buffer << endl;
        LineNumber++;
    }
    dictfile.clear();
   dictfile.seekg(0, dictfile.beg);
}


bool balanceFile(istream& dictfile)
{ 
    stack<int>I;
    stack <char> S;
    char c, d, p;
    bool match = true;
    int LineNumber = 1;

    //the dictfile.clear and seekg are super important
    //if I don't put this before the while loop it is going to return false I think, It's going to not work.
    dictfile.clear();
    dictfile.seekg(0, dictfile.beg);
    while (dictfile.get(c)) {
       
       //Cpp file 
       //1 ( )
        
        //   if(c == '\n'){
        //     LineNumber++;
        // }
    
      if(c == '/' && dictfile.peek() == '/'){
                LineNumber++;
                //I.push(LineNumber);
               string bufferLine;//Obviously didn't know I can use a getline!
               //way simpler than the other one!
               getline(dictfile, bufferLine);
        //   while(c != '\n'){
        //       dictfile.get(c);
        //       //cout << c << endl;
              
        //   }
        //   LineNumber++;
      }

      //The logic from the block comments looks funky but it worked, I tested it multiple times 
      //and it took a while to fix
      
     //this is the block comment that does everything
      //if it sees a block comment
     if(c == '/' && dictfile.peek() == '*'){
         
         dictfile.get(c);//why not get both of them 
         dictfile.get(c);
         I.push(LineNumber);//Push the line number in the stack so it won't mess up when it wants to print out a missing pair
         if(c == '\n'){
             //if it sees a new line when it gets those two characters lets increment it!
             LineNumber++;
         }
         //after incrementing let's also double check if it satisfies the while loop and see if it sees a new line again
         //if it doesn't let's skip this!
         //I.push(LineNumber);
         while((c != '*' || dictfile.peek() != '/') && dictfile.peek() != EOF){
             dictfile.get(c);
             if(c == '\n'){
                 LineNumber++;
             }
         }
         //if it is at the end of file let's print it!! Meaning if it doesn't match!
         // else lets print that they match and get those two characters and pop it.
        if(dictfile.peek() == EOF){
            match = false;
            cout << "unmatched /* symbol on line " << I.top() << endl;
            break;
        }
        cout << "Pair matching /* and */ " << endl;
        dictfile.get(c);
        dictfile.get(c);
        I.pop();
        //LineNumber++;
      /* if(c == '\n'){
        
        }*/
     }

    
   //Pretty much the if statement where it is specifically for the block comment
     //is redundant I'll just leave it there because originally from the pseudocode that you gave out
     //I though this strategy would work for every /* '' "" character but it won't I had to approach it differently
     //especially when it comes to ignoring characters in-between so you can skip this
        
    //peek checks the next character after the first
 
     if(c == '/' && dictfile.peek() == '*'){
        
        
        
        
        S.push(c);
        dictfile.get(c);
        S.push(c);
        
        
        while(c != '*' && dictfile.peek() != '/'){
            
            dictfile.get(c);
            
        }
        
        //cout << dictfile.peek() << endl;
        if(dictfile.peek(),dictfile.eof()){
        
            match = false;
            cout << " unmatched /* symbol on line " << LineNumber << endl;
            break;
         }
         
         
    }
    else if(c == '*' && dictfile.peek() == '/'){
        
        
         if (S.empty())
            {
                cout << "unmatched */ symbol on line " << LineNumber << endl;
                match = false;
                break;
            }
            
            d = S.top();
          
            S.pop();  
         
            p = S.top();
            
            S.pop();  
            
          if (MatchingBlocks(d,c,p,dictfile)) {
                
               cout << "Pair matching /* and */" << endl;
                match = true;
          }
            if (!MatchingBlocks(d,c,p,dictfile)) {
                match = false;
                cout << "unmatched */ symbol on line " << LineNumber << endl;
                break;
            }
        
        
    }
        
        if (c == '(' || c == '{' || c == '['){


                S.push(c);
                I.push(LineNumber);
        }   
        else if (c == ')' || c == '}' || c == ']')
        {
        
            if (S.empty())
            {
                cout << "unmatched " << c << "symbol on line " << LineNumber << endl;
                match = false;
                break;
            }
            
            d = S.top();
            
            S.pop();  
            I.pop();
         
          if (MatchingParens(d,c)) {
                
                cout << "Pair Matching " << d << " and "  << c  << endl;
                match = true;
          }
            if (!MatchingParens(d,c)) {
                match = false;
                cout << "unmatched " << d << " symbol on line " << LineNumber << endl;
                break;
            }
            
        }     
        //Pretty much to reduce some redundancy
        //If it sees any quote, I'll push it into the stack, push the line number (specifically for when it is at the end of file)
        //then it goes to the do while loop and for a do while loop it is nice to get the execution first then later
        //if it doesn't get a character automatically let this print out unmatch!
        //and let it return match automatically
        //and if it does get a character lets go to the while loop, while c is not a quote
        //check the top and pop
        //same strategy after the while loop just like an else if from the braces
        //if its unmatched print unmatch
        //if its matched print match, same thing for double quote after it
         if (c == '\"'){
                S.push(c);
                I.push(LineNumber);
           // dictfile.get(c);
            do{
                if(!dictfile.get(c)){
                    cout << "unmatched " << '"' << " on line " << LineNumber << endl;
                    match = false;
                    return match;
                }
                
            }
            
            while(c != '\"');
           
            d = S.top();
            
            S.pop();  
            I.pop();
            
          if (MatchingDoubleQuotes(d,c)) {
                
                cout << "Pair Matching " << d << " and "  << c  << endl;
                match = true;
          }
            if (!MatchingDoubleQuotes(d,c)) {
                match = false;
                cout << "unmatched " << d << " symbol on line " << LineNumber << endl;
                break;
            }
            
        }
        
        if (c == '\''){
                S.push(c);
                I.push(LineNumber);
           // dictfile.get(c);
            do{
                if(!dictfile.get(c)){
                    cout << "unmatched \' on line " << LineNumber << endl;
                    match = false;
                    return match;
                }
                
            }
            
            while(c != '\'');
           
            d = S.top();
            
            S.pop();  
            I.pop();
            
          if (MatchingQuotes(d,c)) {
                
                cout << "Pair Matching " << d << " and "  << c  << endl;
                match = true;
          }
            if (!MatchingQuotes(d,c)) {
                match = false;
                cout << "unmatched " << d << " symbol on line " << LineNumber << endl;
                break;
            }
            
        }
        
        
        //if it sees a new line lets increment it
        if(c == '\n'){
            LineNumber++;
        }



       
        
    }//While Loop Closing Brace
    
    
    //if its empty and match is true
    //unmatch and prints out s.top and i.top 
    //there is a reason why we push....
    if (!S.empty() && match == true) {
        cout << "unmatched " << S.top() << " symbol on line " << I.top() << endl;
        match = false;
    }

    return match;
}
 
  
//This is the function that logically makes sense and I created  functions that are similiar to this
bool MatchingParens(char a,char b) {
    return (a == '(' && b == ')')||
           (a == '{' && b == '}')||
           (a == '[' && b == ']');
    
}


bool MatchingQuotes(char a, char b){
    //'\'mean single quote
    return (a == '\'' && b == '\'');
}

bool MatchingDoubleQuotes(char a, char b){
    
    return(a == '\"' && b == '\"');
}
//this may look confusing since it has an istream& file being passed
//but the reason why I included that is because 
//I was just testing it out to clear but this is redundant
bool MatchingBlocks(char a, char b, char c, istream& file) {    
   return (a == '*' && b == '*' && c == '/' && file.peek() == '/');
    }




int main()
{


    ifstream infile;
    string filename;

    cout << "Please enter filename for C++ code: ";
    cin >> filename;
    infile.open(filename.c_str());
    
    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }
 
    printFile(infile);
    if (balanceFile(infile))
        cout << "balance ok" << endl;
    else
        cout << "Balance is not ok" << endl;
    
    
    // // //Test cases not sure if they supposed to print out because some of them don;t
    //      istringstream a("{}");
    //     assert(balanceFile(a));

    //     istringstream b("()");
    //     assert(balanceFile(b));
        
    //     istringstream c("[]");
    //     assert(balanceFile(c));
        
    //     istringstream d("//(");
    //     assert(balanceFile(d));

    //     istringstream e("/*(*/");
    //     assert(balanceFile(e));

    //     istringstream f("/*[\n*/");
    //     assert(balanceFile(f));

    //     istringstream g("""");
    //     assert(balanceFile(g));

    //     istringstream h("' '");
    //     assert(balanceFile(h));

    //     istringstream i("\"(\""); 
    //     assert(balanceFile(i));

    //     istringstream j("( \n )");
    //     assert(balanceFile(j));
       
        
}