#ifndef SCOPETABLE_H
#define SCOPETABLE_H

#include<string>
#include "SymbolInfo.h"
#include<string>
#include<iostream>

using namespace std;

class scopeTable{
    private:
    int uid;
    int bucketSize;
    symbolInfo** scopetable;

    public:
    scopeTable(int bucketSize,int uid){
        this->bucketSize = bucketSize;
        this->uid = uid;
        this->scopetable = new symbolInfo*[bucketSize]();
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

    void insertAtEnd(symbolInfo* firstSymbol, symbolInfo* inputSymbol){
        symbolInfo* point = firstSymbol;

        while(point->nextSymbol != NULL){
           point = point -> nextSymbol; 
        }

        point->nextSymbol = inputSymbol;
    }
    void insert(symbolInfo* symbol){
         int position = SDBMHash(symbol->getSymbolName(),this->bucketSize);

        if(this->scopetable[position] != NULL){
            insertAtEnd(this->scopetable[position], symbol);
        }else{
            this->scopetable[position] = symbol;
        }
    }

    symbolInfo* lookUp(string symbolName){
        int position = SDBMHash(symbolName,this->bucketSize);

        if(this->scopetable[position] == NULL){
            return NULL;
        }else{
            symbolInfo* point = this->scopetable[position];

            while(point->nextSymbol != NULL){
                if(point->getSymbolName() == symbolName){
                    return point;
                }else{
                    point = point->nextSymbol;
                }
            }
            return NULL;
        }
    }

    bool deleteSymbol(string symbolName){
        int position = SDBMHash(symbolName,this->bucketSize);

        if(this->scopetable[position] == NULL){
            return false;
        }else{
            symbolInfo* currentPoint = this->scopetable[position];
            symbolInfo* prevPoint = NULL;
            while(currentPoint->nextSymbol != NULL){
                if(currentPoint->getSymbolName() == symbolName){
                   if(prevPoint==NULL){  // first node of the table
                        if(currentPoint->nextSymbol == NULL){ // only one node
                            this->scopetable[position] = NULL;
                            return true;
                        }else{
                            this->scopetable[position] = currentPoint->nextSymbol;
                            return true;
                        }

                   }else{
                        prevPoint->nextSymbol = currentPoint->nextSymbol;
                        return true;
                   }
                }else{
                    prevPoint = currentPoint;
                    currentPoint = currentPoint->nextSymbol;
                }
            }
            return false;
        }
        
    }

    void print(){
        cout<< "ScopeTable# "<<this->uid<<endl;
        for(int i=0;i<this->bucketSize;i++){
            symbolInfo* symbol = this->scopetable[i];
            cout<<i+1<<"-->";
            while(symbol->nextSymbol != NULL){
               cout<<"<"<<symbol->getSymbolName()<<","<<symbol->getSymbolType()<<">"; 
            }

            cout<<endl;
        }
    }

    ~scopeTable(){
        delete [] this->scopetable;
    }


};

#endif