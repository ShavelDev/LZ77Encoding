//
//  main.cpp
//  LZ77Encoding
//
//  Created by Norbert Szawloga on 18/10/2024.
//

#include <iostream>
#include <queue>
//#include <string>
using namespace std;

class JZ77Encoder{
private:
    deque<char> chars;
    int startingIndex;
    bool getTouple(){
        if (chars.empty()) return false;
        
        // we need to handle the cases where sliding window is now filled
        int las = lookAheadStart - startingIndex;
        
        char firstLetter = chars[las];
            
        //check if there is a letter in the known part
        int foundIndex = -1;

        for(int i = startingIndex; i < las; i++){
            if (chars[i] == firstLetter) {
                foundIndex = i;
            }
        }
        
        
        
        int firstSimLetterIndex = foundIndex+1;
        int comparedLetterIndex = las+1;
        if(foundIndex != -1){
            
            for (int i = las; i < size; i++) {
                
                
                if(chars[firstSimLetterIndex] == chars[comparedLetterIndex]){
                    firstSimLetterIndex++;
                    comparedLetterIndex++;
                    continue; //DELETE
                }else{
                    firstSimLetterIndex--;
                    comparedLetterIndex--;
                    break;
                }
            }
            
            cout << "(" << las - foundIndex << ", "<< firstSimLetterIndex - foundIndex << ", " << ((comparedLetterIndex != (chars.size()-1)) ? chars[comparedLetterIndex + 1] : '+') << ")" << endl;
            
            
        }else{
            cout << "(0, 0, " << firstLetter << ")" << endl;
        }
        
        int lettersToRemove = comparedLetterIndex - las;
        cout << "deleting " << lettersToRemove << endl;
        for (int i = 0; i < lettersToRemove; i++) {
            chars.pop_front();
            if (startingIndex > 0) {
                startingIndex--;
            }
            
        }
        
        cout << "new staring index: " << startingIndex << endl;
        
        
        return false;
    }
    
public:
    const int size;
    const int lookAheadStart;
    JZ77Encoder(int size, int lookAheadStart) : size(size), lookAheadStart(lookAheadStart){
        startingIndex = size - lookAheadStart;
    };
    
    void printCodes(string characters){
        for (int i = 0; i < characters.size(); i++) {
            chars.push_back(characters[i]);
        }
        
        cout << "Chars size: " << chars.size() << endl;
        cout << "Chars[0]: " << chars[0] << endl;
        
        for (int i = 0; i < characters.size(); i++) {
            getTouple();
        }
        
    };
};




int main(int argc, const char * argv[]) {
    // insert code here...
    
    string characters = "ABCDEFG";
    
    JZ77Encoder enc(4, 2);
    enc.printCodes(characters);
    

    
    return 0;
}
