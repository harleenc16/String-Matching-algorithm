//C++ program for string matching
//This code is submitted by Harleen Chaudhary

#include <iostream>
#include <string>
#include <fstream>
#include<sstream> 
#include<vector>
using namespace std; 
#define NO_OF_CHARS 256  
vector<string> v;
string BigData;
vector<string> validBUIDs;

bool validBUID(string s)
{
    if(s.size() < 10)return false;

    if(s[0] != 'U')return false;

    for(int i =1 ; i<=8 ; i++)
    {
        if(!isdigit(s[i]))return false;
    }

    if(isdigit(s[9]))return false;

    int sum = 0;
    for(int i =1 ; i<=8 ; i++)
    {
        sum+=(s[i] - '0');
    }

    if(sum>=31 && sum<=68)return true;
    else return false;

}



void fourA()
{
	
	 fstream file;
	 file.open("TinyData.txt" , ios::in);
     while(file)
     {
         string temp;
         getline(file , temp);
         v.push_back(temp);
     }

     for(int i =0 ; i < v.size(); i++)
     {
         BigData+=v[i];
     }
	 
	 
	 
    int count = 0;

    for(int j = 0 ; j <BigData.size() ; j++)
    {
        string t = BigData.substr( j , 10);
        if(validBUID(t))
        {
            validBUIDs.push_back(t);
            count++;
        }
    }

    cout<<"The number of BU-IDs whose digits add to a number between 31 and 68 are : \n";
    cout<<count<<'\n'<<'\n';
  
    
}


void computeLPSArray(string pat, int M, int* lps); 
  

int KMPSearch(string pat, string txt) 
{ 
    int M = pat.length();
    int N = txt.length();
  
   
    int lps[M]; 
	int count=0; 
   
    computeLPSArray(pat, M, lps); 
  
    int i = 0; 
    int j = 0; 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
			count++;	
            j = lps[j - 1]; 
	
    } 
	
     else if (i < N && pat[j] != txt[i]) { 
           
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
	
	return count; 
} 

void computeLPSArray(string pat, int M, int* lps) 
{ 
   
    int len = 0; 
    lps[0] = 0; 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else 
        {   
            if (len != 0) { 
                len = lps[len - 1]; 
  
            } 
            else 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 


void fourB(){
	
	//checks for all letters (case matters)
	//duplicated counted
	//checking contigous words 
	
	ifstream input("SmallData.txt"); 
    string txt;
    if(input) {
       ostringstream ss;
       ss << input.rdbuf(); // reading data
       txt = ss.str(); //reading the whole file as one string
    }

	ifstream file("dictionary.txt");
	string pat;
	int sum=0; 
	int total=0;
	int ans; 	
	while(getline(file, pat)){

		if(pat.find("h") != 0 ){ 
			
		   ans = KMPSearch(pat, txt);
		} 
			total=total+ans;
	}
	cout<<"The number of words that appear in the file that do not begin with h: "  <<total<<endl;
	
	
}

void fourC() {
	
	//checks for all characters and spaces 
	//efficient 
	
	ifstream input("TinyData.txt"); 
    string str;
    if(input) {
       ostringstream ss;
       ss << input.rdbuf(); // reading data
       str = ss.str(); //reading the whole file as one string
    }
	
  int max_lower = 0, max_upper = 0, len = str.length(), lower = 0, upper = 0;
  
  for(int i = 0; i < len; i++) {
	  
    upper = i + 1, lower = i;
	
    for(int j = 0; j < 2; j++) {
		
      lower = i - j;
	  
      for(;lower >= 0 and upper < len and str[lower] == str[upper]
          ;upper++, lower--);
	  
      if((max_upper - max_lower) < (upper - lower - 2)) {
		  
        max_lower = lower + 1, max_upper = upper - 1;
		
      }
    }
  }
  cout<<"The longest palindrome is: " << str.substr(max_lower, max_upper - max_lower + 1)<<endl;
}


int main(){
	
	fourA(); 
	fourB();
	//alternate approach for fourB()- build a Trie from the dictionary, and use it to search the input file.
	fourC();
	
	return 0; 
}
