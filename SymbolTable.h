#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include<iostream>
#include<string>
#include<fstream>
#include "ScopeTable.h"
#include "SymbolInfo.h"
using namespace std;

class symbolTable{
    private:
       scopeTable* currentScope;
       scopeTable* stack;
       ofstream& out;
       int bucketSize;
    public:
        int total_collision;
        int scopeTableCount;
        symbolTable(ofstream& outputFile,int hashFunction,int bucketSize):out(outputFile){
            this->bucketSize = bucketSize;
            stack = new scopeTable(bucketSize,1,outputFile,hashFunction);
            this->currentScope = stack;
            this->scopeTableCount = 1;
            this->total_collision = 0;
        }

        void enterScope(scopeTable* table){
            this->scopeTableCount++;
            if(this->currentScope == NULL){
                this->stack = table;
                this->currentScope = table;
            }else{
                table->parent = this->currentScope;
                this->currentScope = table;
            }
        }

        void exitScope(){
            this->total_collision+= this->currentScope->collision;
            if(this->currentScope == NULL){
                return;
            }else{
                int uid = currentScope->getUid();
                if(this->currentScope->parent == NULL){
                    this->stack = NULL;
                }else{
                    this->currentScope = this->currentScope->parent;
                }
            
                out<<'\t'<<"ScopeTable# "<<uid<<" removed"<<endl;
            }
        }

        void insertAtCurrent(symbolInfo* symbol){
            this->currentScope->insert(symbol);
        }

        bool removeFromCurrent(string symbolName){
            bool returnCode = this->currentScope->deleteSymbol(symbolName);
            return returnCode;
        }

        symbolInfo* lookUp(string symbolName){
            scopeTable* point = this->currentScope;
            symbolInfo* temp = NULL;
            while(point != NULL){
                temp = point->lookUp(symbolName);
                if(temp != NULL){
                    return temp;
                }

                point = point ->parent;
            }
            out <<'\t'<< "'"<<symbolName<<"' not found in any of the ScopeTables"<<endl;
            return NULL;
        }

        void printCurrentScopeTable(){
            if(this->currentScope != NULL){
                this->currentScope->printTable("        ");
            }
        }

        void printAllScopeTables(){
            string spacing = "", eightSpaces = "        ";
            scopeTable* point = currentScope;
            while(point != NULL){
                spacing = spacing + eightSpaces;
                point->printTable(spacing);
                point = point -> parent;
            }
        }

        void removeAllScopeTable(){
            scopeTable* point = currentScope;
            while(point != NULL && point->parent != NULL){
                exitScope();
                point = currentScope;
            }
            currentScope = NULL;
            out<<'\t'<<"ScopeTable# "<<1<<" removed"<<endl;
        }

        ~symbolTable(){
            delete stack;
        }
};











#endif