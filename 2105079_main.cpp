#include "2105079_SymbolInfo.h"
#include "2105079_SymbolTable.h"
#include "2105079_ScopeTable.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]){

    if(argc < 3) return 0;
    if(argv[1] == "" || argv[2] == "") return 0;

    string input_file = argv[1], output_file = argv[2];
    ifstream fileIn(input_file);
    ofstream fileOut(output_file);

    string s;
    getline(fileIn,s);
    int bucket_size = stoi(s);
    symbolTable table = symbolTable(fileOut,0,bucket_size);
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
                fileOut<<'\t'<<"Number of parameters mismatch for the command L"<<endl;
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
                scopeTable* scope = new scopeTable(bucket_size,scopeTableCount,fileOut,0);
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