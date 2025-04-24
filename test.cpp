#include "SymbolInfo.h"
#include "SymbolTable.h"
#include "ScopeTable.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main(void){


    ifstream fileIn("sample_input.txt");
    ofstream fileOut("output.txt");

    symbolTable table = symbolTable(fileOut);
    string s;
    getline(fileIn,s);
    int lineCount = 0,scopeTableCount = 1;
    while(getline(fileIn,s)){
        //reading the first input
        fileOut << "Cmd "<<lineCount+1 <<": "<<s<<endl;
        stringstream ss(s);
        string first;
        ss >> first;
        
        string second,third,rest;
        if(first == "I"){
            ss >> second >> third;
            if(third == "FUNCTION" || third == "UNION" || third == "STRUCT"){
                getline(ss,rest);
                string type = third + " " +rest;
                symbolInfo* symbol = new symbolInfo(second,type);
                table.insertAtCurrent(symbol);
            }else{
                getline(ss,rest);
                if(rest == "" || rest == " "){ // all ok
                    symbolInfo* symbol = new symbolInfo(second,third);
                    table.insertAtCurrent(symbol);
                }else{ // wrong input
                }
            }
        }else if(first == "L"){
            ss >> second;
            getline(ss,rest);

            if(rest == ""){ //all ok
                symbolInfo* result = table.lookUp(second);
            }else{ // wrong input
                fileOut<<"        Number of parameters mismatch for the command L"<<endl;
            }
        }else if(first == "D"){
            ss >> second;
            getline(ss,rest);
            if(second == ""){
                fileOut<<'\t'<<"Number of parameters mismatch for the command D"<<endl;
            }else{
                if(rest == ""){ //all ok
                    bool deleteConfirmation = table.removeFromCurrent(second); 
                }else{ // wrong input
    
                }
            }
            
        }else if(first == "P"){
            ss >> second;
            if(second == "A" || second == "C"){ // all ok for second word
               getline(ss,rest);
            if(rest == ""){ //all ok
                if(second == "A"){
                    table.printAllScopeTables();
                }else if(second == "C"){
                    table.printCurrentScopeTable();
                }
            }else{ // wrong input
            }
            }else{ // wrong input
            }
        }else if(first == "S"){
            getline(ss,rest);
            if(rest == ""){ //all ok
                scopeTableCount++;
                scopeTable* scope = new scopeTable(7,scopeTableCount,fileOut);
                table.enterScope(scope);
            }else{ // wrong input
            }
        }else if(first == "E"){
            getline(ss,rest);
            if(rest == ""){ //all ok
                table.exitScope();
            }else{ // wrong input
            }
           
        }else if(first == "Q"){
            table.removeAllScopeTable();
        }else{ // wrong input
        }

        lineCount++;
    }

}