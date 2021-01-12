
#include <iostream>
#include <utility>
#include <cmath>
//Note x 2^(fret/12)

class Guitar{
    
private: char numberOfFrets;
private: double guitarStrings[6];

public:
    
    Guitar() {
        numberOfFrets = 21;
        guitarStrings[0] = 82.41; //low E
        guitarStrings[1] = 110; //A
        guitarStrings[2] = 146.8; //D
        guitarStrings[3] = 196; //G
        guitarStrings[4] = 246.9; //B
        guitarStrings[5] = 329.6; //high E
    }

    Guitar(const Guitar&fender) {
        numberOfFrets = fender.numberOfFrets;
        guitarStrings[0] = fender.guitarStrings[0]; //low E
        guitarStrings[1] = fender.guitarStrings[1]; //A
        guitarStrings[2] = fender.guitarStrings[2]; //D
        guitarStrings[3] = fender.guitarStrings[3]; //G
        guitarStrings[4] = fender.guitarStrings[4]; //B
        guitarStrings[5] = fender.guitarStrings[5]; //high E
    }

    // sets the corresponding private field and verifies the input is between 1 and 24
    bool setFretBoardLength(const unsigned char numFrets) {
        if (((int)numFrets >= 1) && ((int)numFrets <= 24)) {
            numberOfFrets = numFrets;
            std::cout << "The number of frets is now " << (int)numberOfFrets;
            return true;
        }
        else {
            std::cout << "Number of frets is out of bounds.";
            return false;
        }
    }

    // Returns the corresponding frequency in Hz for the given string and fret.
    // Unlike array indices, these use natural numbers, so the low E string shall be
    // string 1 and the high E string shall be 6
    double pitchAt(const unsigned char &stringNumber, const unsigned char &fret) {
        if (((int) stringNumber < 1 || (int) stringNumber > 6) || ((int) fret < 1 || (int) fret > numberOfFrets)) {
            std::cout << "not known because either your string or fret number is out of bounds.\n\n";
            return NULL;
        }
        
        double pitch = guitarStrings[(int) stringNumber - 1];
        double newPitch = pitch * (double) pow(2, ((double) fret/12));
        return newPitch;
    }

    // Given the pitch, the method shall return a std::pair object with the string/fret combination
    // that comes closest to producing that pitch. There may be multiple solutions. The function
    // shall return the first it identifies
    std::pair<unsigned char, unsigned char> getStringAndFret( double pitch ) {
        double minDifference = pitch;
        unsigned char bestString = NULL;
        unsigned char bestFret = NULL;
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j < (int)numberOfFrets; j++) {
                double tempPitch = (guitarStrings[i - 1] * (double) pow(2, ((double) j/12)));
                double difference = abs(pitch - tempPitch);
                if (difference < minDifference) {
                    minDifference = difference;
                    bestString = (char) i;
                    bestFret = (char) j;
                }
            }
        }
        if ((bestString == NULL) || (bestFret == NULL)) {
            std::cout << "A combination was not found :(\n";
        }
        else {
            std::cout << "\nThe most accurate string is " << (int) bestString << " (" << getStringLetter((int) bestString) << ") and the most accurate fret is " << (int) bestFret << ". \n\n";
        }
        return std::make_pair(bestString, bestFret);
    }

    // changes the tuning for an individual string.
    void tuneString(const unsigned char& string, const double& pitch ) {
        std::cout << "This string's frequency was at " << guitarStrings[(int)string - 1] << " and now it is at ";
        guitarStrings[(int)string - 1] = pitch;
        std::cout << guitarStrings[(int)string - 1] << ". \n\n";
    }
    
    //helper methods
    int getNumberOfFrets() {
        return (int) numberOfFrets;
    }
    
    void getFrequencies() {
        for (int i = 0; i < (sizeof(guitarStrings) / sizeof(guitarStrings[0])); i++) {
            if (i == 5) {
                std::cout << guitarStrings[i];
                break;
            }
            std::cout << guitarStrings[i] << ", ";
        }
    }
    
    std::string getStringLetter(int stringNumber) {
        if (stringNumber == 1)
            return "low E";
        else if (stringNumber == 2)
            return "A";
        else if (stringNumber == 3)
            return "D";
        else if (stringNumber == 4)
            return "G";
        else if (stringNumber == 5)
            return "B";
        else
            return "high E";
    }

};

int main(int argc, const char * argv[]) {
    
    Guitar fender = Guitar();
    Guitar gibson = Guitar(fender); //obligatory copy constructor
    int choice = NULL;
    
    std::cout << "Please type the number of the action you would like to do down below \n\n";
    while (choice != 5) {
        std::cout << "------Current Guitar Specs------\n";
        std::cout << "Number of frets: " << fender.getNumberOfFrets() << "\n";
        std::cout << "Frequencies of each string (EADGBE in order): ";
        fender.getFrequencies();
        std::cout << "\n";
        std::cout << "\n1 - Change the fret board length\n2 - Find a pitch with a given string and fret\n3 - Find the most accurate string/fret combination of a given pitch\n4 - Change the tuning for an individual string\n5 - quit\n";
        std::cout << ">>> ";
        std::cin >> choice;
        
        if (choice == 1) {
            int newFrets;
            std::cout << "\nPlease enter the number of frets you want (1 - 24): ";
            std::cin >> newFrets;
            fender.setFretBoardLength(newFrets);
            std:: cout << "\n\n";
        }
        else if (choice == 2) {
            int string;
            int fret;
            std::cout << "\nPlease enter the string you want to use (1 = low E, 2 = A, 3 = D, 4 = G, 5 = B, 6 = high E): ";
            std::cin >> string;
            std::cout << "\nPlease enter the fret you want to use (1 - " << fender.getNumberOfFrets() << "): ";
            std::cin >> fret;
            std::cout << "\nThe pitch at this string/fret combination is " << fender.pitchAt(string, fret) << " hz.\n\n";
        }
        else if (choice == 3) {
            double pitch;
            std::cout << "\nPlease enter the pitch: ";
            std::cin >> pitch;
            fender.getStringAndFret(pitch);
        }
        else if (choice == 4) {
            int string;
            double pitch;
            std::cout << "\nPlease enter the string you would like to change (1 = low E, 2 = A, 3 = D, 4 = G, 5 = B, 6 = high E): ";
            std::cin >> string;
            std::cout << "\nPlease enter the pitch you would like to set it at: ";
            std::cin >> pitch;
            fender.tuneString(string, pitch);
        }
        else if (choice == 5) {
            std::cout << "\nGoodbye.\n";
            choice = 5;
        }
        else {
            std::cout << "\nThat is not a choice.";
            choice = 5;
            std::cout << "\nGoodbye.\n";
        }
        
    }
    return 0;
}
