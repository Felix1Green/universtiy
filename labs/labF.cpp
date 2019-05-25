#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    char c;
    bool isempty = false;
    int count = 0;
    if(argc != 2){
        cout << "File`s name is undefined" << endl;
        return 1;
    }
    ifstream in(argv[1]);
    if(!in){
        cout << "File is not open" << endl;
        return 2;
    }
    while(in.read(&c, sizeof(char))){
        if(c != '\n') {
            isempty = false;
            cout << c;
            count = 0;
        }else if(!isempty){
            cout << c;
            isempty = true;
        }else if(count == 0){
            cout << c;
            count++;
        }
    }
    in.close();
    return 0;
}