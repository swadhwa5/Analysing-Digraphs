#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>

#ifndef DIGRAPH_H
#define DIGRAPH_H

void read_file(std::ifstream& ifile,  std::vector<std::string> &digraph_words, std::map<std::string,int> &digraph_by_freq_only, std::map <int, std::vector<std::string> > &digraph_by_freq, std::map <std::string, std::vector<std::string> > &digraph_by_list);
void output_list(char ch, std::map <int, std::vector<std::string> > &digraph_by_freq, std::map <std::string, std::vector<std::string> > &digraph_by_list);
void search_frequency_list(int num, std::map <int, std::vector<std::string> > &digraph_by_freq, std::map <std::string, std::vector<std::string> > &digraph_by_list);
void search_digraph_list(std::string value, std::vector<std::string> &digraph_words, std::map<std::string,int> &digraph_by_freq_only, std::map <std::string, std::vector<std::string> > &digraph_by_list);

#endif
