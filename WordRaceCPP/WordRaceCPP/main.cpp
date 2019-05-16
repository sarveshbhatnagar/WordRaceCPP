//
//  main.cpp
//  WordRaceCPP
//
//  Created by Sarvesh Bhatnagar on 16/05/19.
//

#include <iostream>
#include <vector>
#include <fstream>

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
    //Constructor calls fillWords to initialize the vector
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
};

int main(int argc, const char * argv[]) {
    WordList w;
    cout<<w.size()<<endl;
    w.printWord(4);
    
    return 0;
}
