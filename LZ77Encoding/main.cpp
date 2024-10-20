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
    
    void printSlidingWindow(){
        for (int i = 0; i < startingIndex; i++) {
            cout << "_";
        }
    }
    
    bool getTouple(){
        if (chars.empty()) return false;
        
        // we need to handle the cases where sliding window is now filled
        int las = lookAheadStart - startingIndex - 1;
        
        char firstLetter = chars[las];
            
        //check if there is a letter in the known part
        int foundIndex = -1;

        
        cout << "las: " << las << " startingIndex: " << startingIndex << endl;
        for(int i = las; i > 0; i--){
            cout << "looging at: " << chars[i-1] << " at index " << i - 1<< endl;
            if (chars[i-1] == firstLetter) {
                foundIndex = i-1;
            }
        }
        
        
        
        int firstSimLetterIndex = foundIndex+1;
        int comparedLetterIndex = las+1;
        if(foundIndex != -1){
            
            //cout << "look ahead buffer size: " << size - lookAheadStart << endl;
            for (int i = lookAheadStart; i < size; i++) {
                
                
                if(chars[firstSimLetterIndex] == chars[comparedLetterIndex]){
                    //cout << "another letter found" << endl;
                    firstSimLetterIndex++;
                    comparedLetterIndex++;
                    continue; //DELETE
                }else{
                    firstSimLetterIndex--;
                    //comparedLetterIndex--;
                    break;
                }
            }
            
            cout << "(" << las - foundIndex << ", "<< firstSimLetterIndex - foundIndex + 1<< ", " << ((comparedLetterIndex != (chars.size())) ? chars[comparedLetterIndex] : '+') << ")" << endl;
            //cout << "(" << las - foundIndex << ", "<< firstSimLetterIndex - foundIndex + 1<< ")" << endl;
            
            
        }else{
            cout << "(0, 0, " << firstLetter << ")" << endl;
        }
        

        
        int lettersToRemove = comparedLetterIndex - las;
        //cout << "letters to remove: " << lettersToRemove << endl;
        for (int i = 0; i < lettersToRemove; i++) {
            if (startingIndex == 0) {
               // cout << "deleting " << lettersToRemove << endl;
                chars.pop_front();
            }
            
            if (startingIndex > 0) {
                startingIndex--;
            }
            
        }
        
        //cout << "new staring index: " << startingIndex << endl << endl;
        
        
        
        
        
        return false;
    }
    
public:
    const int size;
    const int lookAheadStart;
    JZ77Encoder(int searchBufferSize, int lookAheadBufferSize): size(searchBufferSize+lookAheadBufferSize), lookAheadStart(searchBufferSize+1){
        startingIndex = searchBufferSize;
        
        cout<< "startingIndex: " << startingIndex << endl;
        cout<< "lookAheadStart: " << lookAheadStart << endl;
        cout<< "size: " << size << endl << endl;
    };
    
    
    void printCodes(string characters){
        for (int i = 0; i < characters.size(); i++) {
            chars.push_back(characters[i]);
        }
        
//        cout << "Chars size: " << chars.size() << endl;
//        cout << "Chars[0]: " << chars[0] << endl;
        
        for(int i = 0; i < 10; i++) {
            
            
            getTouple();
            cout << chars.size() << " " << size << endl;
        }
        
    };
};




int main(int argc, const char * argv[]) {
    // insert code here...
    
    string characters = "abcdefab";
    
    JZ77Encoder enc(8,4);
    enc.printCodes(characters);
    

    
    return 0;
}
