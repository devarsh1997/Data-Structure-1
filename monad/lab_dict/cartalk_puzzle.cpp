/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;


#include <iostream>
/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> result;
    vector<string> temp;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
       while (getline(wordsFile, word)) {
            temp.push_back(word);
        }
    }
    
   
    
    for(unsigned long i = 0; i < temp.size(); i++){
        if(temp[i].size() == 5){
           string w1 = temp[i].substr(1, temp[i].size() - 1);
           string first = temp[i].substr(0, 1);
           string second = temp[i].substr(2, temp[i].size() - 2);
           string w2 = first + second;
        
           if(d.homophones(w1, w2) == true){
               result.push_back(make_tuple(temp[i], w1, w2));
           }
        }
    }
    
    
    return result;
}
