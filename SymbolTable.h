#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include<iostream>
#include<string>
#include "ScopeTable.h"
#include "SymbolInfo.h"
using namespace std;

class symbolTable{
    private:
       scopeTable* currentScope;
       scopeTable* stack;
    public:
        symbolTable(int scopeSize){
            this->stack = NULL;
            this->currentScope = NULL;
        }

        void enterScope(scopeTable* table){
            if(this->currentScope == NULL){
                this->stack = table;
                this->currentScope = table;
            }else{
                table->parent = this->currentScope;
                this->currentScope = table;
            }
        }

        void exitScope(){
            if(this->currentScope == NULL){
                return;
            }else{
                if(this->currentScope->parent == NULL){
                    this->stack = NULL;
                }else{
                    this->currentScope = this->currentScope->parent;
                }
            }
        }

        void insertAtCurrent(symbolInfo* symbol){
            this->currentScope->insert(symbol);
        }

        void removeFromCurrent(string symbolName){
            int returnCode = this->currentScope->deleteSymbol(symbolName);
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
        }

        void printCurrentScopeTable(){
            if(this->currentScope != NULL){
                this->currentScope->print();
            }
        }
};











#endif