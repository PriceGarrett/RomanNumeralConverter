#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <map>


using namespace std;

map<char, int> Values;
map<int, string> RomanNumerals;
void ScanFile(string fileName, char* argv);
void GenerateMap(map<char, int> &map);
void GenerateMap(map<int, string> &map);
int Convert(string);
int ValueOfNumeral(char);
string CorrespondingNumeral(int);
string Convert(int);
bool CheckValidity(string);

int main(int argc, char *argv[]){
    GenerateMap(Values);               
    GenerateMap(RomanNumerals);

    if(argc > 1){
        for(int i = 2; i < argc; i++){
            ScanFile(argv[i], argv[1]);
        }
    } else {
        // If no flag and file are added, numerals and numbers can be entered manually
        cout << "Manual Input Mode" << endl;
        cout << "Enter 1 Roman to Standard" << endl;
        cout << "Enter 2 for Standard to Roman" << endl;
        cout << "Enter anything else to cancel" << endl;
        int request;
        cin >> request;
        if(request == 1){
            cout << "Input numerals\n \"q\" to quit" << endl;
            string numerals;
            cin >> numerals;
            while (numerals != "q"){
                int numbers = Convert(numerals);
                if (numbers == 0){
                    cout << numerals << " => " << "INVALID" << endl;
                } else {
                    cout << numerals << " => " << numbers << endl;
                }
                cin >> numerals;
            }
            cout << "Exiting" << endl;
        } else if(request == 2){
            cout << "Input number\n \"0\" to quit" << endl;
            int numbers;
            cin >> numbers;
            while (numbers != 0){
                string numerals = Convert(numbers);
                cout << numbers << " => " << numerals << endl;
                cin >> numbers;
            }
            cout << "Exiting" << endl;
        } else {
            cout << "Exiting" << endl;
        }
    }




    return 0;
}

//Scans input file and will make a new output file with the converted data
void ScanFile(string fileName, char* flag){
    ifstream infs;
    ofstream outfs;
    infs.open(fileName);
    outfs.open("output_" + fileName);
    if(!infs.is_open()){
        cout << "Invalid File" << endl;
        outfs.close();
        return;
    }
    cout << "Reading file: " << fileName << endl;
    if(!strcmp(flag, "-s")){
        cout << "Converting " << fileName << endl;
        int standard;
        while(infs >> standard){
            string output = Convert(standard);
            outfs << standard << " => " << output << endl;
        }
    } 
    if (!strcmp(flag, "-r")){
        cout << "Converting " << fileName << endl;
        string roman;
        while(getline(infs, roman)){
            int output = Convert(roman);
            if(output <= 0){
                outfs << roman << " => " << "INVALID" << endl;
            } else {
                outfs << roman << " => " << output << endl;
            }
        }
    }
    infs.close();
    outfs.close();   
    cout << "Finished. See output files for results." << endl;
    return;
}

//Numerals and corresponding values are stored in maps to make sure only valid characters are used
void GenerateMap(map<char, int> &map){
    map.insert(pair<char, int> ('I', 1));
    map.insert(pair<char, int> ('V', 5));
    map.insert(pair<char, int> ('X', 10));
    map.insert(pair<char, int> ('L', 50));
    map.insert(pair<char, int> ('C', 100));
    map.insert(pair<char, int> ('D', 500));
    map.insert(pair<char, int> ('M', 1000));
    return;
}

void GenerateMap(map<int, string> &map){
    map.insert(pair<int, string> (1, "I"));
    map.insert(pair<int, string> (2, "II"));
    map.insert(pair<int, string> (3, "III"));
    map.insert(pair<int, string> (4, "IV"));
    map.insert(pair<int, string> (5, "V"));
    map.insert(pair<int, string> (6, "VI"));
    map.insert(pair<int, string> (7, "VII"));
    map.insert(pair<int, string> (8, "VIII"));
    map.insert(pair<int, string> (9, "IX"));
    map.insert(pair<int, string> (10, "X"));
    map.insert(pair<int, string> (20, "XX"));
    map.insert(pair<int, string> (30, "XXX"));
    map.insert(pair<int, string> (40, "XL"));
    map.insert(pair<int, string> (50, "L"));
    map.insert(pair<int, string> (60, "LX"));
    map.insert(pair<int, string> (70, "LXX"));
    map.insert(pair<int, string> (80, "LXXX"));
    map.insert(pair<int, string> (90, "XC"));
    map.insert(pair<int, string> (100, "C"));
    map.insert(pair<int, string> (200, "CC"));
    map.insert(pair<int, string> (300, "CCC"));
    map.insert(pair<int, string> (400, "CD"));
    map.insert(pair<int, string> (500, "D"));
    map.insert(pair<int, string> (600, "DC"));
    map.insert(pair<int, string> (700, "DCC"));
    map.insert(pair<int, string> (800, "DCCC"));
    map.insert(pair<int, string> (900, "CM"));
    map.insert(pair<int, string> (1000, "M"));
    map.insert(pair<int, string> (2000, "MM"));
    map.insert(pair<int, string> (3000, "MMM"));        //According to research, 3999 is the largest number you 
    return;                                             //can make with proper Roman Numeral formatting
}

//If numerals are in an invalid pattern, it will return 0
int Convert(string numerals){
    if(!CheckValidity(numerals)){
        return 0;                       
    }
    int sum = 0;
    int stringLength = numerals.size();
    for(int i = stringLength - 1; i > -1; i--){
        int currValue = ValueOfNumeral(numerals.at(i));
        if((i + 1 < stringLength) && (currValue < ValueOfNumeral(numerals.at(i + 1)))){
            sum -= currValue;
        } else {
            sum += currValue;
        }
    }
    return sum;
}

//Retrieves value from map
int ValueOfNumeral(char numeral){
    map<char, int>::iterator itr;
    for(itr = Values.begin(); itr != Values.end(); itr++){
        if(numeral == itr->first){
            return itr->second;
        }
    }
    return 0;
}

//Retrieves numeral from map
string CorrespondingNumeral(int number){
    map<int, string>::iterator itr;
    for(itr = RomanNumerals.begin(); itr != RomanNumerals.end(); itr++){
        if(number == itr->first){
            return itr->second;
        }
    }
    return "";
}

//Converts standard to Roman, will return INVALID if it is out of range of numerals
string Convert(int number){
    if(number < 1 || number > 3999){
        return "INVALID";
    }
    string numerals;
    if(number > 999){
        int currVal = number / 1000;
        currVal *= 1000;
        numerals += CorrespondingNumeral(currVal);
    } 
    if(number > 99){
        int currVal = number % 1000;
        currVal = currVal / 100;
        currVal *= 100;
        numerals += CorrespondingNumeral(currVal);
    } 
    if(number > 9){
        int currVal = number % 100;
        currVal = currVal / 10;
        currVal *= 10;
        numerals += CorrespondingNumeral(currVal);
    }
    int currVal = number % 10;
    numerals += CorrespondingNumeral(currVal);
    
    return numerals;
}

//Checks several points of numeral strings
//Will return false if a large symbol is preceeded by one that is too small, i.e. IC
//Will also return false if 4 of the same character are placed in a row
bool CheckValidity(string numerals){
    int stringLength = numerals.size();
    for(int i = 0; i < stringLength; i++){
        if(numerals.at(i) != 'I' && numerals.at(i) != 'V' && numerals.at(i) != 'X' && numerals.at(i) != 'L' &&
                numerals.at(i) != 'C' && numerals.at(i) != 'D' && numerals.at(i) != 'M'){
            return false;
        }
        if(i + 1 < stringLength){
            if(numerals.at(i) == 'I' && numerals.at(i + 1) != 'V' &&
                    numerals.at(i + 1) != 'I' && numerals.at(i + 1) != 'X'){        
                return false;
            }
            if(numerals.at(i) == 'V' && numerals.at(i + 1) != 'I'){        
                return false;
            }
            if(numerals.at(i) == 'X' && (numerals.at(i + 1) == 'D' || numerals.at(i + 1) == 'M')){        
                return false;
            }
            if(numerals.at(i) == 'L' && (numerals.at(i + 1) == 'D' || numerals.at(i + 1) == 'M')){        
                return false;
            }
            if(i + 3 < stringLength){
                if(numerals.at(i) == numerals.at(i + 1) && numerals.at(i) == numerals.at(i + 2) &&
                        numerals.at(i) == numerals.at(i + 3)){
                    return false;
                }
            }
        }
    }
    return true;
}