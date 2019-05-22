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
    //Only variable to be accessed.
    int interfaceOption(0);
    int interfaceValue(10);
    
    void run();
    
    //Prints the UI interface
    void print(){
        cout
        <<"Welcome to Word Race!"<<endl
        <<"1. Start a 20 word challenge"<<endl
        <<"2. Start a 50 word challenge"<<endl
        <<"3. Start a 100 word challenge"<<endl
        <<"4. Enter a new word to the list"<<endl
        <<"5. Exit"<<endl;
    }
    
    void addWordUI(){
        cout<<"Enter the sentence you want to add "<<endl;
        std::string w;
        w = std::cin.get();
        getline(std::cin, w);
        WordList().addWord(w);
//        w = std::cin.get();
    }
    
    void setInterfaceValue(){
        switch (interfaceOption) {
            case 1:
                interfaceValue=20;
                break;
            case 2:
                interfaceValue=50;
                break;
            case 3:
                interfaceValue=100;
                break;
            case 4:
                addWordUI();
                run();
                break;
            case 5:
                exit(0);
                break;
            default:
                interfaceValue=10;
                break;
        }
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
        if (interfaceOption < 1 || interfaceOption>5) {
            return true;
        }
        return false;
    }
    
    
    //Interface option is properly set, only function to be actually used.
    void run(){
        while (true) {
            print();
            select();
            if (checkError()) {
                error();
            }else{
                setInterfaceValue();
                break;
            }
        }
    }
}

bool compareString(std::string a, std::string b){
    if (a.compare(b) == 0) {
        return true; // they are equal
    }else{
        return false;// they are not equal
    }
}



int main(int argc, const char * argv[]) {
    
    std::string input="";
    std::string output;
    int score(0);
    wordsInterfaceHandler::run();
    int n(wordsInterfaceHandler::interfaceValue);
    char ws;
    ws = std::cin.get();
    words::timer();
    for (int i = 0; i<n; ++i) {
        output = words::getRandom();
        cout<<output<<endl;
        cout<<"Enter the above text!"<<endl;
        getline(std::cin, input);
        if (compareString(input, output)) {
            score+=1;
        }
    }
    words::timer();
    cout<<"Total time taken "<<words::timerDifference()<<" Seconds"<<endl;
    cout<<"Score is : "<<score<<endl;
    return 0;
}
