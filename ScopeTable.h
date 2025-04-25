#ifndef SCOPETABLE_H
#define SCOPETABLE_H

#include<string>
#include "SymbolInfo.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

class scopeTable{
    private:
    int uid;
    int bucketSize;
    int hashfunc;
    symbolInfo** scopetable;
    ofstream& out;


    public:
    scopeTable* parent;
    int collision;
    scopeTable(int bucketSize,int uid,ofstream& outputFile,int hashfunc):out(outputFile){
        this->bucketSize = bucketSize;
        this->uid = uid;
        this->scopetable = new symbolInfo*[bucketSize]();
        this->parent = NULL;
        out<<'\t'<<"ScopeTable# "<<this->uid<<" created"<<endl;
        this->collision = 0;
        this->hashfunc = hashfunc;
    }
    int getUid(){
        return this->uid;
    }
    unsigned int SDBMHash(string str, unsigned int num_buckets) {
         unsigned int hash = 0;
         unsigned int len = str.length();
         for (unsigned int i = 0; i < len; i++)
         {
         hash = ((str[i]) + (hash << 6) + (hash << 16)- hash) %
         num_buckets;
         }
         return hash;
    }

    unsigned int charSumHash(string str, unsigned int bucketSize) {
        unsigned int hash = 0;
        for (char c : str) {
            hash += c;
        }
        return hash % bucketSize;
    }
    unsigned int weightedCharSumHash(string str, unsigned int bucketSize) {
        unsigned int hash = 0;
        for (size_t i = 0; i < str.length(); ++i) {
            hash += (i + 1) * str[i];  // i + 1 so we don't multiply by 0
        }
        return hash % bucketSize;
    }
    bool duplicate(symbolInfo* firstSymbol,string symbolName){
        symbolInfo* point = firstSymbol;
        while(point != NULL){
            if(point->getSymbolName() == symbolName){
                return true;
            }
            point = point ->nextSymbol;
        }
        return false;
    }
    int insertAtEnd(symbolInfo* firstSymbol, symbolInfo* inputSymbol){
        symbolInfo* point = firstSymbol;
        int visitedCount = 0;
        while(point->nextSymbol != NULL){
           point = point -> nextSymbol;
           visitedCount++; 
        }

        point->nextSymbol = inputSymbol;
        return visitedCount+1;
    }
    void insert(symbolInfo* symbol){
        int position = 0;
        if(this->hashfunc == 0)
                position = SDBMHash(symbol->getSymbolName(),this->bucketSize);
         else if(this->hashfunc == 1)
                position = charSumHash(symbol->getSymbolName(),this->bucketSize);
         else if(this->hashfunc == 2)
                position = weightedCharSumHash(symbol->getSymbolName(),this->bucketSize);
         else{
            out <<'\t'<<"Incorrect Hash Function"<<endl;
         }
         int visitedCount = 0;
        if(this->scopetable[position] != NULL){
            this->collision++;
            bool isDuplicate = duplicate(this->scopetable[position],symbol->getSymbolName());
            if(!isDuplicate){ //if there is no duplicate
            visitedCount = insertAtEnd(this->scopetable[position], symbol);
                out<<'\t'<<"Inserted in ScopeTable# "<<this->uid<<" at position "<<position+1<<", "<<visitedCount+1<<endl;
            }else{  //if there are duplicates
                out<<'\t'<<"'"<<symbol->getSymbolName()<<"' already exists in the current ScopeTable"<<endl;
            }
        }else{ 
            this->scopetable[position] = symbol;
            out<<'\t'<<"Inserted in ScopeTable# "<<this->uid<<" at position "<<position+1<<", 1"<<endl;
        }
    }

    symbolInfo* lookUp(string symbolName){
        int position = SDBMHash(symbolName,this->bucketSize);
        int nodeCount = 0;
        if(this->scopetable[position] == NULL){
            return NULL;
        }else{
            symbolInfo* point = this->scopetable[position];

            while(point != NULL){
                if(point->getSymbolName() == symbolName){
                    out<<'\t'<<"'"<<point->getSymbolName()<<"' found in ScopeTable# "<<uid<<" at position "<<position+1<<", "<<nodeCount+1<<endl; 
                    return point;
                }else{
                    point = point->nextSymbol;
                }
                nodeCount++;
            }
            return NULL;
        }
    }

    bool deleteSymbol(string symbolName){
        int position = SDBMHash(symbolName,this->bucketSize);

        if(this->scopetable[position] == NULL){
            out<<'\t'<<"Not found in the current ScopeTable"<<endl;
            return false;
        }else{
            symbolInfo* currentPoint = this->scopetable[position];
            symbolInfo* prevPoint = NULL;
            int nodeCount = 0;
            while(currentPoint != NULL){
                if(currentPoint->getSymbolName() == symbolName){
                   if(prevPoint == NULL){  // first node of the table
                        if(currentPoint->nextSymbol == NULL){ // only one node
                            out <<'\t'<<"Deleted '"<<currentPoint->getSymbolName()<<"' from ScopeTable# "<<this->uid<<" at position "<<position+1<<", "<<nodeCount+1<<endl;
                            this->scopetable[position] = NULL;
                            return true;
                        }else{
                            out <<'\t'<< "Deleted '"<<currentPoint->getSymbolName()<<"' from ScopeTable# "<<this->uid<<" at position "<<position+1<<", "<<nodeCount+1<<endl;
                            this->scopetable[position] = currentPoint->nextSymbol;
                            return true;
                        }

                   }else{
                        cout<<"Deleted from third if"<<currentPoint->getSymbolName()<<endl;
                        out <<'\t'<<"Deleted '"<<currentPoint->getSymbolName()<<"' from ScopeTable# "<<this->uid<<" at position "<<position+1<<", "<<nodeCount+1<<endl;
                        prevPoint->nextSymbol = currentPoint->nextSymbol;
                        return true;
                   }
                   nodeCount++;
                }else{
                    prevPoint = currentPoint;
                    currentPoint = currentPoint->nextSymbol;
                }
            }
            out<<'\t'<<"Not found in the current ScopeTable"<<endl;
            return false;
        }
        
    }

    void printTable(string spacing){

        out<< spacing<<"ScopeTable# "<<this->uid<<endl;
        for(int i=0;i<this->bucketSize;i++){
            symbolInfo* symbol = this->scopetable[i];
            out<<spacing<<i+1<<"-->";
            while(symbol != NULL){
                out<<" ";
                stringstream ss(symbol->getSymbolType());
                string type;
                ss >> type;
                if(type == "FUNCTION"){
                    string returnType,arguments;
                    ss >> returnType;
                    out<<"<"<<symbol->getSymbolName()<<","<<type<<","<<returnType<<"<==(";
                    bool first_arg = true;
                    while(ss >> arguments){
                        if(!first_arg){
                            out<<",";
                        }else{
                            first_arg = false;
                        }
                        out<<arguments;
                    }
                    out<<")>";
                }else if(type == "UNION" || type == "STRUCT"){
                    string dataType,var;
                    out<< "<"<<symbol->getSymbolName()<<","<<type<<",{";
                    bool first_arg = true;
                    while(ss >> dataType >> var){
                        if(!first_arg){
                            out<<",";
                        }else{
                            first_arg = false;
                        }
                        out<<"("<<dataType<<","<<var<<")";
                    }
                    out<<"}>";
                }else{
                    out<<"<"<<symbol->getSymbolName()<<","<<symbol->getSymbolType()<<">"; 
                }
               symbol = symbol->nextSymbol;
            }

            out<<endl;
        }
    }

    /*void generalPrint(string func,int position, int nodeCount,bool duplicate,string duplicatedSymbol,string searchedSymbol,bool symbolNotFound,bool deleted, string deletedSymbol){
        if(func == "Insert"){
            if(duplicate){
                cout<<"        '"<<duplicatedSymbol<<"'"<<" already exists in the current ScopeTable";
            }else{
                cout<<"        Inserted in Scopetable# "<<this->uid <<" at position "<<position<<", "<<nodeCount<<endl;
            }
        }else if(func == "LookUp"){
            if(symbolNotFound){
                cout<<"'"<<searchedSymbol<<"'"<<" not fou"
            }
        }
    }*/

    ~scopeTable(){
        delete [] this->scopetable;
    }


};

#endif