/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;


#include<iostream>

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    
    vector<string>out;
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            out.push_back(word);
        }
    }
    
    vector<string> words = out;
    for(int i = 0; i < (int)words.size(); i++)
    {
        string sorted = words[i];
        std::sort(sorted.begin(), sorted.end());
        
        auto lookup = dict.find(sorted);
        if(lookup == dict.end()){
            dict[sorted].push_back(words[i]);
        }
        else{
            auto lookup2 = find(dict[sorted].begin(), dict[sorted].end(), words[i]);
            if(lookup2 == dict[sorted].end()) dict[sorted].push_back(words[i]);
        }
    }
    
     
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    
    for(int i = 0; i < (int)words.size(); i++)
    {
        string sorted = words[i];
        std::sort(sorted.begin(), sorted.end());
        
        auto lookup = dict.find(sorted);
        if(lookup == dict.end()){
            dict[sorted].push_back(words[i]);
        }
        else{
            auto lookup2 = find(dict[sorted].begin(), dict[sorted].end(), words[i]);
            if(lookup2 == dict[sorted].end()) dict[sorted].push_back(words[i]);
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string>result;
    string sorted = word;
    std::sort(sorted.begin(), sorted.end());
    for(auto & it : dict){
        if(it.first == sorted) return it.second;
    }
    return result;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>>result;
    for(auto & it : dict)
    {
        if(it.second.size() >= 2)
            result.push_back(it.second);
    }
    return result;
}


