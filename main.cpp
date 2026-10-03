#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>


/*

    Text analyzer must do:
    1. Input text
    2. Analyze how much words, symbols
    3. Output longest and shortest word
    4. Save text to file, and load it from file
    5. Ability to edit the text
    6. Ability to find the word in the text

*/

class Analyzer{
    public:
    std::string text = "";

    //Function to count words in the text

    int count_words(){
        int count = 0;
        bool in_word = false;

        for (char c : text){
            if (!std::isspace(c)){
                if (!in_word){
                    count++;
                    in_word = true;
                }
            }
            else{
                in_word = false;
            }
        }

        return count;
    }

    //Function to count nonspace symbols in the text
    int count_symbols(){
        int count = 0;
        for(char c : text){
            if(!std::isspace(c)){
                ++count;
            }
        }
        return count;
    }

};


void show_texts(std::vector<Analyzer>& show_text);
void show_menu(std::vector<Analyzer>& show_menu);
void save_texts(std::vector<Analyzer>& save_texts);
void load_texts(std::vector<Analyzer>& load_texts);

/*

    Main function to launch the programm

*/
int main(){
    std::vector<Analyzer> texts;

    load_texts(texts);
    show_menu(texts);
}




//Function to load texts from the file
void load_texts(std::vector<Analyzer>& load_texts){
    Analyzer block;
    int counter = 0;
    std::ifstream fin;
    std::string text;

    
    fin.open("texts.txt");
    while (std::getline(fin, text)) {
        ++counter;
        if (text.empty()) {
            continue;
        }
        block.text = text;
        load_texts.push_back(block);
    }
    fin.close();
}

//Function to save texts to the file
void save_text(std::vector<Analyzer>& save_text) {
    Analyzer block;
    std::ofstream fout;

    fout.open("texts.txt");
    for (const auto& text_block : save_text) {
        fout << text_block.text << "\n";
    }
    fout.close();
}

// Function to show menu of the programm
void show_menu(std::vector<Analyzer>& show_menu){

}


//Function to show all the saved texts
void show_texts(std::vector<Analyzer>& show_texts){
    Analyzer block;
    int counter = 0;
    for(const auto& text_block : show_texts){
        ++counter;
        std::cout << counter << ". "<< text_block.text<<"\n";
    }
}