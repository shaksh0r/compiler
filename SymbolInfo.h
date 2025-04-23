#ifndef SYMBOLINFO_H
#define SYMBOLINFO_H


#include<string>
#include<iostream>

using namespace std;
class symbolInfo{
    private:
    string symbolName;
    string symbolType;

    public:
    symbolInfo* nextSymbol;
    symbolInfo(string symbolName,string symbolType){
        this->symbolName = symbolName;
        this->symbolType = symbolType;
    }

    string getSymbolName(){
        return this->symbolName;
    }

    string getSymbolType(){
        return this->symbolType;
    }

    void setSymbolName(string symbolName){
        this->symbolName = symbolName;
    }

    void setSymbolType(string symbolType){
        this->symbolType = symbolType;
    }
};

#endif