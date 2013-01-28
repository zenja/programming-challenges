/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110108&format=html
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

//#define DEV 0

using namespace std;

void handleOneInput(void);
int who_get_most_one(const vector<vector<int> >& votes);
vector<int> getStat(const vector<vector<int> >& votes);
int who_takes_more_than_50_percent(const vector<vector<int> >& votes);
void eliminateLowestOnesAndRearrange(vector<vector<int> >& votes, vector<string>& names);
bool isAllTied(const vector<vector<int> >& votes);

int main()
{
    int numInputs;
    string tmpStr;
    cin >> numInputs;

    // getline after cin, remove newline
    getline(cin, tmpStr);

    // skip new line
    getline(cin, tmpStr);

    for (int i = 0; i < numInputs; i++) {
        handleOneInput();
    }
}

void handleOneInput(void)
{
    int numTotalCandidates;
    cin >> numTotalCandidates;

    vector<string> names(numTotalCandidates);

    // will use getline after cin, 
    // need to omit the new line char
    getline(cin, names[0]);

    for (int i = 0; i < numTotalCandidates; i++) {
        getline(cin, names[i]);
    }
    
    vector< vector<int> > votes;
    string line;
    getline(cin, line);
    while (line.size() > 0) {
        stringstream ss;
        ss << line;
        vector<int> v;
        for (int i = 0; i < numTotalCandidates; i++) {
            int a;
            ss >> a;
            v.push_back(a);
        }
        votes.push_back(v);

        getline(cin, line);
    }

//    cout << "Who has most one: " << names[who_get_most_one(votes)] << endl;
//    cout << "Who get more than 50% votes: " << who_takes_more_than_50_percent(votes) << endl;
//    cout << "Eliminating..." << endl;
//    eliminateLowestOnesAndRearrange(votes, names);
//    cout << "Who get more than 50% votes: " << who_takes_more_than_50_percent(votes) << endl;

    bool isAllTiredFlag = false;
    while (who_takes_more_than_50_percent(votes) == -1) {
        if (isAllTied(votes) == true) {
            // output all existing candidates
            for (unsigned int i = 0; i < names.size(); i++) {
                cout << names[i] << endl;
            }

            // set isAllTiredFlag
            isAllTiredFlag = true;
        } else {
            eliminateLowestOnesAndRearrange(votes, names);
        }
    }
    if (isAllTiredFlag == false) {
        cout << names[who_get_most_one(votes)] << endl;
    }


#ifdef DEV
    // show inputs
    cout << endl;
    cout << "Names of the candidates:" << endl;
    for (vector<string>::iterator it = names.begin(); it != names.end(); it++) {
        cout << *it << endl;
    }

    cout << endl;

    cout << "Vote matrix:" << endl;
    for (vector<vector<int> >::iterator i = votes.begin(); i != votes.end(); i++) {
        for (vector<int>::iterator j = i->begin(); j != i->end(); j++) {
            cout << *j;
        }
        cout << endl;
    }
#endif

}
vector<int> getStat(const vector<vector<int> >& votes)
{
    int numCurrentCandidates = votes[0].size();
    vector<int> stat(numCurrentCandidates, 0);
    for (vector<vector<int> >::const_iterator it = votes.begin(); it != votes.end(); it++) {
        for(int i = 0; i < numCurrentCandidates; i++) {
            if ((*it)[i] == 1) ++stat[i];
        }
    }

    return stat;
}

int who_takes_more_than_50_percent(const vector<vector<int> >& votes)
{
    vector<int> stat = getStat(votes);
    int numVotes = accumulate(stat.begin(), stat.end(), 0);
    int max = *max_element(stat.begin(), stat.end());
    if (max > (numVotes / 2)) return max_element(stat.begin(), stat.end()) - stat.begin();
    else return -1;
}

int who_get_most_one(const vector<vector<int> >& votes)
{
    vector<int> stat = getStat(votes);
    int maxElementIndex = max_element(stat.begin(), stat.end()) - stat.begin();
    return maxElementIndex;
}

/* should not perform on empty vector */
/* judge if there are more than one candidates and they all have the same results */
bool isAllTied(const vector<vector<int> >& votes)
{
    vector<int> stat = getStat(votes);

    if (stat.size() < 2) return false;

    int element = stat[0];
    for (unsigned int i = 1; i < stat.size(); i++) {
        if (element != stat[i]) return false;
    }

    return true;
}

/* should not perform on empty vector */
void eliminateLowestOnesAndRearrange(vector<vector<int> >& votes, vector<string>& names)
{
    vector<int> stat = getStat(votes);
    vector<int>::iterator minIt = min_element(stat.begin(), stat.end());
    int min = *minIt;
    while ((minIt != stat.end()) && (*minIt == min)) {
        int minIndex = minIt - stat.begin();
        stat.erase(minIt);
        names.erase(names.begin() + minIndex);
        for (vector<vector<int> >::iterator it = votes.begin(); it != votes.end(); it++) {
            vector<int>::iterator itToDelete = it->begin() + minIndex;
            int contentToDelete = *itToDelete;
            it->erase(itToDelete);
            
            // re-arrange the row
            for (unsigned int i = 0; i < it->size(); i++) {
                if ((*it)[i] > contentToDelete) (it->at(i))--;
            }
        }
        minIt = min_element(stat.begin(), stat.end());
    }
}

