//
//  main.cpp
//  WordRaceCPP
//
//  Created by Sarvesh Bhatnagar on 16/05/19.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>

#define cout std::cout
#define endl std::endl


//class for managing words in the text file wordlist.txt
class WordList{
    std::vector<std::string> words;
public:
    //fillWords fetches the words from wordlist.txt and places them in the vector words.
    void fillWords(){
        std::fstream fs;
        char a[500];
        fs.open("wordlist.txt");
        while(fs.getline(a, 500)){
            words.push_back(a);
        }
        fs.close();
    }
//    Constructor calls fillWords to initialize the vector
    WordList(){
        fillWords();
    }
    //Destructor refills the wordlist.txt along with any additional new word if any.
    ~WordList(){
        std::fstream fs;
        fs.open("wordlist.txt",std::fstream::out);
        if (!fs) {
            cout<<"Unable to open wordlist "<<endl;
            exit(9);
        }
        for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
            std::string st = *it;
            fs<<st;
            fs<<'\n';
        }
    }
    //Used to add a word in the vector, indirectly which adds up in the wordlist.txt
    void addWord(std::string w){
        words.push_back(w);
    }
    //returns size of the vector words
    unsigned long size(){
        return words.size();
    }
    //prints word at a specific location n.
    void printWord(int n){
        try {
            cout<<words.at(n)<<endl;
        } catch (std::exception e) {
            cout<<"Index out of range"<<endl;
        }
    }
    
    //returns a word from the list
    std::string fetchWord(int n){
        return words.at(n);
    }
};

//Namespace for interacting with the class wordlist
namespace words {
    time_t start(NULL),stop(NULL);
    bool timeflag(true);
    
    //returns a random word
    std::string getRandom(){
        std::random_device rd;
        return WordList().fetchWord(rd()%WordList().size());
    }
    
    //function to access size of words.
    unsigned long size(){
        return WordList().size();
    }
    
    //auxillary function for timer to set a start point
    void startTimer(){
        time(&start);
    }
    
    //auxillary function for timer to set a stop point
    void stopTimer(){
        time(&stop);
    }
    
    //Alternatively sets start and stop time when called.
    void timer(){
        if (timeflag) {
            startTimer();
            timeflag=false;
        }else{
            stopTimer();
            timeflag=true;
        }
    }
    
    double timerDifference(){
        return difftime(stop, start);
    }
    
}

namespace wordsInterfaceHandler {
    int interfaceOption(0);
    
    //Prints the UI interface
    void print(){
        cout
        <<"Welcome to Word Race!"<<endl
        <<"1. Start a 20 word challenge"<<endl
        <<"2. Start a 50 word challenge"<<endl
        <<"3. Start a 100 word challenge"<<endl
        <<"4. Start complete word list challenge"<<endl;
    }
    
    //changes the interface option variable, according to the print statement.
    void select(){
        std::cin>>interfaceOption;
    }
    
    //Error message made using switch for reusing the code if required in future.
    void error(int n=1){
        switch (n) {
            case 1:
                cout<<endl<<endl<<"Please select one of the options listed below!"<<endl;
                break;
            default:
                cout<<"Some error occured!"<<endl;
                break;
        }
    }
    
    
    //Currently checks basic error related to interface option selection.
    bool checkError(){
        if (interfaceOption < 1 || interfaceOption>4) {
            return true;
        }
        return false;
    }
    
    
    //Interface option is properly set.
    void run(){
        while (true) {
            print();
            select();
            if (checkError()) {
                error();
            }else{
                break;
            }
        }
        cout<<"Done!"<<endl;
    }
}

int main(int argc, const char * argv[]) {
    int a;
    words::timer();
    cout<<words::getRandom()<<endl;
    cout<<"Enter something "<<endl;
    std::cin>>a;
    words::timer();
    cout<<"Time taken "<<words::timerDifference()<<" Seconds"<<endl;
//    wordsInterfaceHandler::run();
    return 0;
}
