/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110204&format=html
 * Solution Guide: http://www.algorithmist.com/index.php/UVa_843
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

set<string> dictionary;

void decrypt(string line);
bool longer_length(const string& a, const string& b);
void addMatchingWords(map<string, vector<string> >& matchMap, string cWord);
bool isMatch(const string& a, const string& b);
bool tryMatching(vector<string>& sortedCipherWords,     // reference
                map<string, vector<string> >& matchMap, // reference
                map<char, char> alphabetMap,            // not reference!
                map<string, string>& resultMap,         // reference!
                unsigned int cipherIndex);
bool isMatchAlphabetMap(map<char, char>& alphabetMap, string cWord, string pWord);
void printAsterisk(int num);

int main()
{
    // input dictionary
    int dicSize;
    cin >> dicSize;
    string line;
    getline(cin, line); // omit the new line char
    for (int i = 0; i < dicSize; ++i) {
        getline(cin, line);
        dictionary.insert(line);
    }

    // solve lines
    while (getline(cin, line)) {
        decrypt(line);
    }
}

void decrypt(string line) {
    // retrieve cipher words
    stringstream ss(line);
    string cWord;
    vector<string> cipherWords; // according to sequences
    vector<string> sortedCipherWords; // sorted by string length
    while (ss >> cWord) {
        cipherWords.push_back(cWord);
    }
    sortedCipherWords = cipherWords;
    sort(sortedCipherWords.begin(), sortedCipherWords.end(), longer_length);

    // map for matched words list
    // <cipher_word, matched_dictionary_words>
    map<string, vector<string> > matchMap;

    // map for results
    // <cipher_word, dictionary_word>
    map<string, string> resultMap;

    /* FOR DEBUG
    for (vector<string>::const_iterator it = sortedCipherWords.begin(); it != sortedCipherWords.end(); ++it) {
        addMatchingWords(matchMap, *it);
    }

    cout << endl << "Printing matchMap: " << endl;
    for (map<string, vector<string> >::const_iterator it = matchMap.begin(); it != matchMap.end(); ++it) {
        cout << it->first << ": " << endl;
        for (vector<string>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt) {
            cout << *jt << ", ";
        }
        cout << endl;
    }

    cout << "-----------------------------" << endl;
    */

    map<char, char> alphabetMap; // cipher char -> plaintext char!
    bool isSuccess = tryMatching(sortedCipherWords, matchMap, alphabetMap, resultMap, 0);

    if (isSuccess) {
        for (unsigned int i = 0; i < cipherWords.size() - 1; ++i) {
            cout << resultMap[cipherWords[i]];
            cout << " ";
        }
        cout << resultMap[cipherWords[cipherWords.size() - 1]] << endl;
    } else {
        for (unsigned int i = 0; i < cipherWords.size() - 1; ++i) {
            printAsterisk(cipherWords[i].size());
            cout << " ";
        }
        printAsterisk(cipherWords[cipherWords.size() - 1].size());
        cout << endl;
    }
}

void printAsterisk(int num)
{
    for (int i = 0; i < num; ++i) {
        cout << '*';
    }
}

bool tryMatching(vector<string>& sortedCipherWords,         // reference
                map<string, vector<string> > & matchMap,    // reference
                map<char, char> alphabetMap,                // not reference!
                map<string, string> & resultMap,            // reference!
                unsigned int cipherIndex)
{
    // if cipherIndex out of bound, then finished
    if (cipherIndex > sortedCipherWords.size() - 1) return true;

    // the cipher word
    string cWord = sortedCipherWords[cipherIndex];

    // add matching words to cWord
    addMatchingWords(matchMap, cWord);

    // the matching words' vector's reference
    vector<string> & matchingWords = matchMap[cWord];

    // the copy of alphabetMap
    map<char, char> alphabetMapNew;

    // TODO: the copy of resultMap. Needed??
    map<string, string> resultMapNew;

    // if find an existing match to cWord, skip to next cipher word
    if (resultMap.find(cWord) != resultMap.end()) {
        // check subsequent results
        bool subResult = tryMatching(sortedCipherWords, matchMap, alphabetMapNew, resultMap, cipherIndex + 1);
        if (subResult == true) { // if find a whole match
            return true;
        }
    } else { // else try all the matching words for cWord
        for (vector<string>::const_iterator it = matchingWords.begin(); it != matchingWords.end(); ++it) {
            alphabetMapNew = alphabetMap;
            if (isMatchAlphabetMap(alphabetMapNew, cWord, *it)) { // if find a match to cWord

                // record the results
                resultMap[cWord] = *it;

                // check subsequent results
                bool subResult = tryMatching(sortedCipherWords, matchMap, alphabetMapNew, resultMap, cipherIndex + 1);
                if (subResult == true) { // if find a whole match
                    return true;
                }

                // BE CAREFUL:
                // although we just need one solution, 
                // we should not break if we find a match to cWord, 
                // because this match may be not possible for sub sequent matchings
                //break; -> should not break!!
            }
        }
    }

    //debug
    if (cipherIndex == 0 && resultMap.size() > 0) {
        for (map<string, string>::const_iterator it = resultMap.begin(); it != resultMap.end(); ++it) {
            cout << it->first << " -> " << it->second << endl;
        }
    }

    return false;
}

// this method will modify alphabetMap!
bool isMatchAlphabetMap(map<char, char>& alphabetMap, string cWord, string pWord)
{
    for (unsigned int i = 0; i < cWord.size(); ++i) {
        if (alphabetMap.find(cWord[i]) != alphabetMap.end() && 
                alphabetMap[cWord[i]] != pWord[i]) {
            return false;
        } else {
            alphabetMap[cWord[i]] = pWord[i];
        }
    }

    return true;
}

void addMatchingWords(map<string, vector<string> >& matchMap, string cWord)
{
    // exit if already exists
    if (matchMap.find(cWord) != matchMap.end()) {
        return;
    }

    unsigned int wordLen = cWord.size();
    for (set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
        if (it->size() == wordLen && isMatch(*it, cWord)) {
            matchMap[cWord].push_back(*it);
        }
    }
}

bool isMatch(const string& a, const string& b)
{
    if (a.size() != b.size()) return false;

    // initialize alphabet for matching
    char alphabet[26];
    for (int i = 0; i < 26; ++i) {
        alphabet[i] = '*';
    }

    for (unsigned int i = 0; i < a.size(); ++i) {
        if (alphabet[a[i] - 97] != '*' && alphabet[a[i] - 97] != b[i]) {
            return false;
        } else {
            alphabet[a[i] - 97] = b[i];
        }
    }

    // re-initialize alphabet for matching
    for (int i = 0; i < 26; ++i) {
        alphabet[i] = '*';
    }

    // do the same check reversily
    for (unsigned int i = 0; i < b.size(); ++i) {
        if (alphabet[b[i] - 97] != '*' && alphabet[b[i] - 97] != a[i]) {
            return false;
        } else {
            alphabet[b[i] - 97] = a[i];
        }
    }


    return true;
}

bool longer_length(const string& a, const string& b)
{
    return a.size() > b.size();
}
