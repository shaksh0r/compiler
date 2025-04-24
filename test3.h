#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include<iostream>
#include<fstream>
using namespace std;

class testClass{
    private:
        ofstream& writeFile;
    public:
        explicit testClass(ofstream &wF):writeFile(wF){
        }

        void print(){
            writeFile << "Hello World"<<endl;
        }
};



#endif