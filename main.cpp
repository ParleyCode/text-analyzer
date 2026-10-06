#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<cctype>
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

void show_texts(std::vector<Analyzer>& texts);
void show_menu(std::vector<Analyzer>& texts);
void save_text(std::vector<Analyzer>& texts);
void load_texts(std::vector<Analyzer>& texts);
void create_texts(std::vector<Analyzer>& texts);
void show_information(std::vector<Analyzer>& texts);
void edit_message(std::vector<Analyzer>& texts);
void delete_message(std::vector<Analyzer>& texts);
void find_word(std::vector<Analyzer>& texts);
std::string to_lower(std::string text);

/*

    Main function to launch the programm

*/
int main(){
    std::vector<Analyzer> texts;

    load_texts(texts);
    show_menu(texts);
}




//Function to load texts from the file
void load_texts(std::vector<Analyzer>& texts){
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
        texts.push_back(block);
    }
    fin.close();
}

//Function to create new text message
void create_texts(std::vector<Analyzer> &texts)
{
    Analyzer text_block;
    std::string new_task = "";
    std::cout << "Please enter new text message: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, new_task);
    text_block.text = new_task;
    texts.push_back(text_block);
    save_text(texts);

}

//Function to show information about chosen text message
void show_information(std::vector<Analyzer> &texts)
{
}

//Function to edit existing text messages
void edit_message(std::vector<Analyzer> &texts)
{
    Analyzer text_block;
    int choise = 0;
    show_texts(texts);
    std::string edited_text = "";
    std::cout << "Please enter which text do you want to edit?: ";
    std::cin >> choise;
    std::cout << "Please enter edited text: ";
    std::cin.clear();std::cin.ignore(10000, '\n');
    std::getline(std::cin, edited_text);
    texts[choise - 1].text = edited_text;
    save_text(texts);

}

//Function to delete selected text message
void delete_message(std::vector<Analyzer> &texts)
{
    int choise = 0;
    show_texts(texts);
    if(texts.empty()){
        std::cout << "There is nothing to delete :( ";
        exit;
    }
    else{
        std::cout << "Please enter contact you want to delete: ";
        while(choise <= 0 || choise >= texts.size()){
        if(texts.empty()){
            break;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> choise;
        if(choise <= 0 && choise > texts.size()){
            std::cout << "Wanna see seg fault?";
        }

        else{
            texts.erase(texts.begin() + (choise - 1));
            save_text(texts);
        }
        }
    }
}

//Funcion to find selected word int all texts and mark it
void find_word(std::vector<Analyzer> &texts)
{
    Analyzer text_block;
    std::string finding_word = "";
    std::cout << "Please enter which word you want to found: ";
    std::cin.clear();std::cin.ignore(10000, '\n');
    std::getline(std::cin, finding_word);

    to_lower(finding_word);
    for (const auto& word : texts){
    if(to_lower(word.text).find(finding_word) != std::string::npos){
                 std::cout << "|----------------------------------------------------------------\n";
                 std::cout << word.text << "\n\n";
        }
    }
}

//Function to save texts to the file
void save_text(std::vector<Analyzer>& texts) {
    Analyzer block;
    std::ofstream fout;

    fout.open("texts.txt");
    for (const auto& text_block : texts) {
        fout << text_block.text << "\n";
    }
    fout.close();
}

// Function to show menu of the programm
void show_menu(std::vector<Analyzer>& texts){

    int choise = 0;

    while(true){
    std::cout << "======TEXT ANALYZATOR======" << "\n" << "1. Create new text message.\n" <<"2. List all masages\n"
    <<"3. Message information\n" <<  "4. Edit message\n" << "5. Delete message\n" << "6. Find the word\n" << "7. Save and quit\n"
    << "===========================\n"; 

        std::cout << "Enter what you want to do: ";

        if (!(std::cin >> choise)) {
            std::cout << "\nWrong input!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

            switch (choise)
            {
            case 1:
                create_texts(texts);
                break;
            case 2:
                show_texts(texts);
                break;
            case 3:
                show_information(texts);
                break;
            case 4:
                edit_message(texts);
                break;
            case 5:
                delete_message(texts);
                break;
            case 6:
                find_word(texts);
                break;
            case 7:
                save_text(texts);
                exit(0);
            default:
                std::cout << "\nWrong input!\n";
                break;
            }

 
    }

}


//Function to show all the saved texts
void show_texts(std::vector<Analyzer>& texts){
    Analyzer block;
    std::string spam = "";

    int counter = 0;
    for(const auto& text_block : texts){
        ++counter;
        std::cout << counter << ". "<< text_block.text<<"\n";
    }
    std::cout << "\nPress any button ENTER to continue";
    std::cin >> spam;
}

std::string to_lower(std::string text){
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    return text;
}
