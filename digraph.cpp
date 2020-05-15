#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "digraph.h"
#include <cstring>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::ifstream;

/*
This function reads the number of digraphs and stores the digarphs in a vector. It also populates all the 3 maps, updating the list of digraphs having a particular frequency,stroring the frequency of each digraph and populating the list of words containing a particular digraph
*/
void read_file(std::ifstream& ifile,  vector<string> &digraph_words, map<string,int> &digraph_by_freq_only, map <int, vector<string> > &digraph_by_freq, map <string, vector<string> > &digraph_by_list) {//change name of function                                                                
  int num_of_digraphs = 0;//stores total no of digraphs                                                                     
  string word;//used to read word by word from the file

  
  ifile >> num_of_digraphs;
  for(int i = 0; i < num_of_digraphs; i++) {//filling the vector with all the digraphs                                      
    if(ifile >> word) {
      digraph_words.push_back(word);
    }
  }

  for (int c=0;c< num_of_digraphs; c++) {//initialising the lists for all digrpahs
    digraph_by_list[digraph_words[c]];
    digraph_by_freq_only[digraph_words[c]];
  
  }
  
  while (ifile >> word){//reading word by word from file
    for (int k = 0; k < num_of_digraphs; k++) {
      std::size_t found;
      found = word.find(digraph_words[k]);//checking for occurence of digraph
      if(found != std::string::npos) {

      if(word.back() == '!' || word.back() == '?' ||word.back() == '.' || word.back() == ',') {
	word.pop_back();//removing punctuation if it exists
      }
      digraph_by_list[digraph_words[k]].push_back(word);//adding to list of words containing the digraph
      (digraph_by_freq_only[digraph_words[k]])++;//updating the frequency of a particular digraph
      }
    }
  }

  for(map<string, vector<string> >::const_iterator gt = digraph_by_list.cbegin();
      gt != digraph_by_list.cend();
      gt++) {
    digraph_by_freq[(gt->second).size()].push_back(gt->first);//adding to list of digraphs with a particular frequency of occurence
  }
}

/* 
This function implements the 3rd command line argument, i.e. 'a' or 'r' or 'c'
@param ch is the command line argument character indicating the format of output/sort                                              
*/
void output_list(char ch, map <int, vector<string> > &digraph_by_freq, map <string, vector<string> > &digraph_by_list) {//change name of function                                                       

  switch(ch) {

  case 'a':
  case 'A'://in ASCII order
    for (map<string, vector<string > >::const_iterator it = digraph_by_list.cbegin();
      it != digraph_by_list.cend();
       it++) {

      cout<<it->first<<": [";
      for(vector<string>::const_iterator jt = digraph_by_list[it->first].cbegin();
	  jt != digraph_by_list[it->first].cend();
	  ++jt) {
	string curr = *jt;
	std::transform(curr.begin(), curr.end(), curr.begin(),
		       [](unsigned char c){ return std::tolower(c); });//converting to lower case
	if(jt == digraph_by_list[it->first].cbegin()) {//used to maintain proper format of output
	  cout<<curr;
	}
	else {//used to maintain proper format of output
	  cout<<", "<<curr;
	}
      }
      cout<<"]"<<endl;
    }
    
    break;

  case 'r':
  case 'R'://in reverse ASCII order
    for (map<string, vector<string > >::const_reverse_iterator it = digraph_by_list.crbegin();
      it != digraph_by_list.crend();
       it++) {

      cout<<it->first<<": [";
      for(vector<string>::const_iterator jt = digraph_by_list[it->first].cbegin();
          jt != digraph_by_list[it->first].cend();
          ++jt) {
	string curr = *jt;
	std::transform(curr.begin(), curr.end(), curr.begin(),
                       [](unsigned char c){ return std::tolower(c); });//converting to lower case
        if(jt == digraph_by_list[it->first].cbegin()) {//used to maintain proper format of output
	  cout<<curr;
	}
        else {//used to maintain proper format of output
          cout<<", "<<curr;
	}
      }

	cout<<"]"<<endl;
    }

    break;

  case 'c':
  case 'C'://in order of count form largest to smallest
    for(map <int, vector <string> >::const_reverse_iterator kt = digraph_by_freq.crbegin();//this map maps a particular frequency to all the digraphs that have that frequency
      kt != digraph_by_freq.crend();
      kt++) {
      for(vector <string>::const_iterator nt = (kt->second).cbegin();
          nt != (kt->second).cend();
          nt++) {
	cout<<*nt<<": [";
	for(vector <string>::const_iterator pt = digraph_by_list[*nt].cbegin();
            pt != digraph_by_list[*nt].cend();
            pt++) {
	  string curr = *pt;
	  std::transform(curr.begin(), curr.end(), curr.begin(),
			 [](unsigned char c){ return std::tolower(c); });//converting to lower case
          if(pt == digraph_by_list[*nt].cbegin()) {//used to maintain proper format of output
	    cout<<curr;
	  }
	  else {//used to maintain proper format of output
	    cout<<", "<<curr;
	  }
        } 
	cout<<"]"<<endl;
      }
    }
    break;

  default://check
    break;
  }
}

/*
This function is used when the user enters a number at the stage where "q?>" is printed, and it prints all the digraphs with that frequency and their corresponding words from the file that contain that digraph
@param num is the num entered by the user and the potential frequency value for which we check
 */
void search_frequency_list(int num, map <int, vector<string> > &digraph_by_freq, map <string, vector<string> > &digraph_by_list) {
  int flag = 0;//used to check if any digraph has that particular frequency
  for(map <int, vector <string> >::const_iterator kt = digraph_by_freq.cbegin();
      kt != digraph_by_freq.cend();
      kt++) {
    if((kt->first) == num) {
      flag++;//flag incremented if digraphs for a particular frequency found
      for(vector <string>::const_iterator nt = (kt->second).cbegin();
	  nt != (kt->second).cend();
	  nt++) {
	cout<<*nt<<endl;//digraph
	for(vector <string>::const_iterator pt = digraph_by_list[*nt].cbegin();
	    pt != digraph_by_list[*nt].cend();
	    pt++) {
	  string curr = *pt;
	  std::transform(curr.begin(), curr.end(), curr.begin(),
			 [](unsigned char c){ return std::tolower(c); });//converting to lowercase
	  cout<<curr<<endl;//list of words that contain the digraph
	}
      }
    }
  }

  if(flag == 0) {
    cout<<"None"<<endl;
  }

}


/*
This function used when the user enters a particular digraph after prompted to reply to "q?>" and outputs the frequency of occurence of the digraph and then lists all the words from the file that contains the digraph if the input by user matches any of the digarphs
@param value is the string entered by the user to be searched from amongst the diraphs
 */
void search_digraph_list(string value, vector<string> &digraph_words, map<string,int> &digraph_by_freq_only, map <string, vector<string> > &digraph_by_list) {
  int flag = 0;//used to check if the string entered by user matches any digraph
  std::transform(value.begin(), value.end(), value.begin(),
		 [](unsigned char c){ return std::tolower(c); });//converting to lower case
  for(size_t i=0;i < digraph_words.size(); i++) {//checking if the value entered by user matches any of the digraphs
    if(value == digraph_words[i]) {
      flag++;
    }
  }
  if(flag == 0) {
      cout<<"No such digraph"<<endl;
  }


  if(flag != 0) {
    cout<<digraph_by_freq_only[value]<<endl;//prints frequency of the digraph
    for (map<string, vector<string > >::const_iterator lt = digraph_by_list.cbegin();
	 lt != digraph_by_list.cend();
	 lt++) {
      if((lt->first)==value) {
	for(vector<string>::const_iterator mt = digraph_by_list[lt->first].cbegin();
	    mt != digraph_by_list[lt->first].cend();
	    ++mt) {
	  string curr = *mt;
	  std::transform(curr.begin(), curr.end(), curr.begin(),
			 [](unsigned char c){ return std::tolower(c); });//converting to lowercase
	  cout<<curr<<endl;//printing list of words containing the digraph
	}
      }
    }
  }
}



