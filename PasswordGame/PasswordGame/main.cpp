/*
 Project by: Kavon Cacho, Gian Kyle Nicolas, and Dean Quach
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <random>
#include <algorithm>
#include <array>
#include <sstream>
#include <time.h>
#include <thread>
using namespace std;

class PasswordGenerator {

    list<string> uniqueTokens;
    std::list<string>::iterator it = uniqueTokens.begin();
    std::list<string>::iterator itCracker = uniqueTokens.begin();
    string password;
    int iterationLength;

public:
    PasswordGenerator(list<string> passwordTokens) {
        uniqueTokens = passwordTokens;
    }

    string getRandomPassword(int numWords) {
        const int numTokens = numWords;
        int randIndices[numTokens];
        int randIndicesSize = sizeof(randIndices) / sizeof(randIndices[0]);
        int randMax = uniqueTokens.size();
        srand(time(0));
        
        for (int i = 0; i < randIndicesSize; ++i) {
            int randNum = (rand() % randMax) + 1;
            for (int j = 0; j < i; ++j) {
                if (randNum == randIndices[j]) {
                    cout << "This was reached";
                    getRandomPassword(numTokens);
                }
            }
            randIndices[i] = randNum;
        }
        for (int i = 0; i < randIndicesSize; ++i) {
            int randTemp = randIndices[i];
            advance(it, randTemp);
            string word = *it;
            it = uniqueTokens.begin();
            //advance(it, -1);

            if (i == randIndicesSize - 1) {
                password = password + word;
            }
            else {
                password = password + word + " ";
            }

        }
        cout << "\nthe password is\n\n" << password << "\n\n";

        return password;
    }

    void setIterationLength(int numWords) {
        iterationLength = numWords;
        it = uniqueTokens.begin();
    }

    std::string next() {
        
        int j = 0;
        int i = 0;
        string crackedPassword;
        string pwArray[iterationLength];
        stringstream ssin(password);
        while (ssin.good() && i < iterationLength) {
            ssin >> pwArray[i];
            ++i;
        }

        uniqueTokens.begin();
        while (j < iterationLength) {
            for (itCracker = uniqueTokens.begin(); itCracker != uniqueTokens.end(); ++itCracker) {
                if (*itCracker == pwArray[j]) {
                    if (j == iterationLength - 1) {
                        crackedPassword = crackedPassword + pwArray[j];
                    }
                    else {
                        crackedPassword = crackedPassword + pwArray[j] + " ";
                    }
                    
                }
                
            }
            j++;
        }
            cout << "The cracked password is: " << crackedPassword << "\n";
        
        return crackedPassword;
    };

    bool hasNext() {
        if ((itCracker != uniqueTokens.end()) && (itCracker == --uniqueTokens.end())) {
            return false;
        }
        else {
            return true;
        }
    }
    
    int thread2Helper(int numWords, string pw) {
        while (getRandomPassword(numWords) != pw) {
            getRandomPassword(numWords);
        }
        cout<< "\n\nPassword has been cracked on thread 2.\n";
        return 0;
    };
    
};

void passwordGuesser(int numWords, list<string> passwordTokens) {
    PasswordGenerator pwg = PasswordGenerator(passwordTokens);
    int numTokens = numWords;
    string password = pwg.getRandomPassword(numTokens);
    pwg.setIterationLength(numTokens);
    pwg.next();
    
    /*
    thread first(pwg.next());
    thread second(pwg.thread2Helper(ref(numTokens),ref(password)));
    These give us errors and we don't know why
     */
    
};

list<string> getUnique(ifstream& myFile) {
    list<string> uniqueList;
    list<string>::iterator it = uniqueList.begin();
    string word;
    while (myFile >> word) {
        for (int i = 0; i < word.length(); i++) {
            if ((word.at(i) == '.') || (word.at(i) == ',')) {
                word.erase(i--, 1);
            }
        }
        for (int i = 0; i < word.length(); i++) {
            if (word.at(i) >= 65 && word.at(i) <= 92) {
                word.at(i) = word.at(i) + 32;
            }
        }
        uniqueList.insert(it, word);
    }
    uniqueList.sort();
    uniqueList.unique();
    cout << "\n\n";
    for (auto v : uniqueList)
        std::cout << v << " ";
    cout << "\n\n";
    return uniqueList;
}

int main(int argc, const char* argv[]) {

    string fString;
    ifstream myFile;
    string fileLocation;
    int numTokens;
    list<string> passwordTokens;

    cout << "Please enter the location of the file: ";
    cin >> fileLocation;
    myFile.open(fileLocation);
    if (myFile.fail()) {
        cout << "\nThe specified file does not exist here. Make sure there are no unnecessary whitespaces.\n";
        exit(0);
    }
    cout << "\nThe file has been found.";
    cout << "\nParsing now!";

    passwordTokens = getUnique(myFile);

    cout << "\nPlease enter the number of tokens you would like to generate a password with. You may use 1 to 5 tokens: ";
    cin >> numTokens;
    if (numTokens < 1 || numTokens > 5 || numTokens > passwordTokens.size()) {
        cout << "\nNumber of tokens is out of range, or it is more than the number of unique tokens in specified file.\n";
        exit(0);
    }

    passwordGuesser(numTokens, passwordTokens);

    return 0;
}

