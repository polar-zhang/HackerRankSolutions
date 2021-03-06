#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */
 
 struct Crossover{
    int otherSlotId;
    int i,j; 
 };
 
 struct Slot{
   int i, j;
   int count;
   bool horizontal;
   int wordIndex;
   vector<Crossover> crossovers;
 };

vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    vector<string> wordList;
    // Split word list.
    int begin = 0, i;
    for(i = 0;i < words.size();i ++){
        if(words[i] == ';'){
            wordList.push_back(words.substr(begin, i - begin));
            begin = i + 1;
            i ++;
        }
    }
    wordList.push_back(words.substr(begin, i - begin));
    
    vector<Slot> slots;
    for(int i = 0;i < 10;i ++){ // Build slots.
        Slot s1 {.i = i, .j = -1, .count = 0, .horizontal = true, .wordIndex = -1};// horizontal one
        Slot s2 {.i = -1, .j = i, .count = 0, .horizontal = false, .wordIndex = -1};// vertial one
        
        for(int j = 0; j < 10;j ++){
            if(crossword[i][j] == '-'){
                if(s1.j == -1){
                    s1.j = j;
                }
                
                s1.count ++;
            }
            else{
                if(s1.count > 1){
                    // cout << "Slot: i = " << s1.i << ", j = " << s1.j << ", count = " << s1.count << std::boolalpha << ", hizontal = " << s1.horizontal << endl;
                    slots.push_back(s1);
                }
                
                s1.j = -1;
                s1.count = 0;
            }
            
            // switch i, j.
            if(crossword[j][i] == '-'){
                if(s2.i == -1){
                    s2.i = j;
                }
                
                s2.count ++;
            }
            else{
                if(s2.count > 1){
                    // cout << "Slot: i = " << s2.i << ", j = " << s2.j << ", count = " << s2.count << std::boolalpha << ", hizontal = " << s2.horizontal << endl;
                    slots.push_back(s2);
                }
                
                s2.i = -1;
                s2.count = 0;
            }
        }
        
        if(s1.count > 1){
            // cout << "Slot: i = " << s1.i << ", j = " << s1.j << ", count = " << s1.count << std::boolalpha << ", hizontal = " << s1.horizontal << endl;
            slots.push_back(s1);
        }
        if(s2.count > 1){
            // cout << "Slot: i = " << s2.i << ", j = " << s2.j << ", count = " << s2.count << std::boolalpha << ", hizontal = " << s2.horizontal << endl;
            slots.push_back(s2);
        }
    } // End build slots.
    
    if(slots.size() != wordList.size()){
        cout << "Wrong size, slots : " << slots.size() << " wordList: " << wordList.size() << endl;
    }
    
    // Mark crossovers.
    for(int i = 0;i < slots.size(); i++){
        if(!slots[i].horizontal)continue;
        for(int j = 0; j < slots.size(); j++){
            if(slots[j].horizontal)continue;
            
            if(slots[i].j <= slots[j].j && slots[i].j + slots[i].count > slots[j].j && 
                slots[j].i <= slots[i].i && slots[j].i + slots[j].count > slots[i].i){
                int cross_i = slots[i].i, cross_j = slots[j].j;
                Crossover co = {.otherSlotId = j, .i = cross_i, .j = cross_j};
                slots[i].crossovers.push_back(co);
                co.otherSlotId = i;
                slots[j].crossovers.push_back(co);
                // cout << i << "-"<<j<<"," << cross_i << "-"<<cross_j<<"; ";
            }
        }
    }
    
    // Solve the problem
    // vector<vector<bool>> triedSpots(wordList.size(), vector<bool>(wordList.size(), false));
    i = 0;
    while(i < slots.size()){ // Pick slot.
        int j = slots[i].wordIndex + 1;
        for(; j < wordList.size(); ++j){ // Pick word.
            if(wordList[j].size() != slots[i].count) continue; // At least word length should be correct.

            bool correctSpot = true;
            for(int k = 0;k < slots[i].crossovers.size(); ++k){ // All the cross over letters must be correct.
                int id = slots[i].crossovers[k].otherSlotId;
                if(slots[id].wordIndex == -1)continue;

                char letterA = wordList[j][slots[i].horizontal ? slots[i].crossovers[k].j - slots[i].j : slots[i].crossovers[k].i - slots[i].i];
                char letterB = wordList[slots[id].wordIndex][slots[id].horizontal ? slots[i].crossovers[k].j - slots[id].j : slots[i].crossovers[k].i - slots[id].i];
                if(letterA != letterB){
                    correctSpot = false;
                    break;
                }
            }

            if(correctSpot){// find a slot for now.
                slots[i].wordIndex = j;
                break;
            }
        }
        
        if(j == wordList.size()){
            // no word for this slot, backtracking ...
            --i; 
        }
        else{
            // Next slot.
            ++i;
        }
    }

    // Solve the puzzle.
    for(auto s: slots){ 
        // cout << "Slot: i = " << s.i << ", j = " << s.j << ", count = " << s.count << std::boolalpha << ", horizontal = " << s.horizontal << ", word: " << wordList[s.wordIndex] << endl;
        if(s.horizontal){
            int n = s.j, m = 0;
            do{
                crossword[s.i][n ++] = wordList[s.wordIndex][m];
            } while(++ m < s.count);
        }
        else{
            int n = s.i, m = 0;
            do{
                crossword[n ++][s.j] = wordList[s.wordIndex][m];
            } while(++ m < s.count);
        }
    }
    
    return crossword;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
