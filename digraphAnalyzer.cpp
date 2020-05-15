#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "digraph.h"
#include <fstream>
#include <sstream>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::ofstream;

int main(int argc, char *argv[]) {

  if(argc != 3) {//checking for inappropriate command line arguments
    cout<<"Inappropriate command line arguments"<<endl;
    exit(1);
  }

  if(argv[2][0] != 'r' && argv[2][0] != 'a' && argv[2][0] != 'c') {//checking for inappropraie option of printing list
    cout<<"Inappropriate command line arguments"<<endl;
    exit(1);
  }


  vector<string> digraph_words;//stores digraphs                                                                                                                                               
  map<string,int> digraph_by_freq_only;//stores diagraphs and their corresponding frequencies
  map <int, vector<string> > digraph_by_freq;//stores list of digraphs with a particular frequency of occurence                                                                                                              
  map <string, vector<string> > digraph_by_list;//stores digraphs with list of words that contain those digraphs                                                                                                         

  std::ifstream ifile (argv[1]);//the text file which is to be read                                                                                                                            
  if (!ifile.is_open()) {
    cout << "Invalid file" << endl;
    exit(2);
  }

  /*
 this functions reads number of digraphs, fills vector digarph_words, map digraph_by_freq_only, digraph_by_freq, and digraph_by_list
   */
  read_file(ifile,digraph_words, digraph_by_freq_only, digraph_by_freq, digraph_by_list);

  /*
    this function implements required output for 3rd command line argument
   */
  output_list(argv[2][0], digraph_by_freq, digraph_by_list);

  
  cout<<"q?>";//asks user for next input 
  int num;//stores integer if the input by user is a number
  string value;//stores input by user regardless of whether its a string or number
  cin >> value;
  while(value != "quit" && value != "Quit") {
    std::stringstream ss;//stringstream stores value so that later, if the input is a number, the number can be extracted
    ss << value;

    if(ss >> num) {//checking if its a number
      search_frequency_list(num, digraph_by_freq, digraph_by_list);
    }
    else {
      search_digraph_list(ss.str(), digraph_words, digraph_by_freq_only,  digraph_by_list);
    }
    cout<<"q?>";
    cin >> value;
  }

  return 0;
  }
