#include "2105079_SymbolInfo.h"
#include "2105079_Scopetable.h"
#include "2105079_Symboltable.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main(int argc, char* argv[]){
    if(argc<3) return 0;
    if(argv[1]=="" || argv[2]=="") return 0;

    string input_file = argv[1], output_file = argv[2];

    ofstream reportOut(output_file);
    ofstream out("temp_output.txt");
    ifstream in(input_file);

    
    string s;
    getline(in,s);
    int bucket_size = stoi(s);
    symbolTable table1 = symbolTable(out,0,bucket_size);
    symbolTable table2 = symbolTable(out,1,bucket_size);
    symbolTable table3 = symbolTable(out,2,bucket_size);
    int lineCount = 0,scopetable1Count = 1;
    while(getline(in,s)){
        //reading the first input
        out << "Cmd "<<lineCount+1 <<": "<<s<<endl;
        stringstream ss(s);
        string first;
        ss >> first;
        
        string second,third,rest;
        if(first == "I"){
            ss >> second >> third;
            if(third == "FUNCTION" || third == "UNION" || third == "STRUCT"){
                getline(ss,rest);
                string type = third + " " +rest;
                symbolInfo* symbol1 = new symbolInfo(second,type);
                symbolInfo* symbol2 = new symbolInfo(second,type);
                symbolInfo* symbol3 = new symbolInfo(second,type);
                table1.insertAtCurrent(symbol1);
                table2.insertAtCurrent(symbol2);
                table3.insertAtCurrent(symbol3);
            }else{
                getline(ss,rest);
                if(rest == "" || rest == " "){ // all ok
                    symbolInfo* symbol1 = new symbolInfo(second,third);
                    symbolInfo* symbol2 = new symbolInfo(second,third);
                    symbolInfo* symbol3 = new symbolInfo(second,third);
                    table1.insertAtCurrent(symbol1);
                    table2.insertAtCurrent(symbol2);
                    table3.insertAtCurrent(symbol3);
                }else{ // wrong input
                }
            }
        }else if(first == "L"){
            ss >> second;
            getline(ss,rest);

            if(rest == ""){ //all ok
                table1.lookUp(second);
                table2.lookUp(second);
                table3.lookUp(second);
            }else{ // wrong input
                out<<'\t'<<"Number of parameters mismatch for the command L"<<endl;
            }
        }else if(first == "D"){
            ss >> second;
            getline(ss,rest);
            if(second == ""){
                out<<'\t'<<"Number of parameters mismatch for the command D"<<endl;
            }else{
                if(rest == ""){ //all ok
                    table1.removeFromCurrent(second); 
                    table2.removeFromCurrent(second);
                    table3.removeFromCurrent(second);
                }else{ // wrong input
    
                }
            }
            
        }else if(first == "P"){
            ss >> second;
            if(second == "A" || second == "C"){ // all ok for second word
               getline(ss,rest);
            if(rest == ""){ //all ok
                if(second == "A"){
                    table1.printAllScopeTables();
                    table2.printAllScopeTables();
                    table3.printAllScopeTables();
                }else if(second == "C"){
                    table1.printCurrentScopeTable();
                    table2.printCurrentScopeTable();
                    table3.printCurrentScopeTable();
                }
            }else{ // wrong input
            }
            }else{ // wrong input
            }
        }else if(first == "S"){
            getline(ss,rest);
            if(rest == ""){ //all ok
                scopetable1Count++;
                scopeTable* scope1 = new scopeTable(bucket_size,scopetable1Count,out,0);
                scopeTable* scope2 = new scopeTable(bucket_size,scopetable1Count,out,1);
                scopeTable* scope3 = new scopeTable(bucket_size,scopetable1Count,out,2);
                table1.enterScope(scope1);
                table2.enterScope(scope2);
                table3.enterScope(scope3);
            }else{ // wrong input
            }
        }else if(first == "E"){
            getline(ss,rest);
            if(rest == ""){ //all ok
                table1.exitScope();
                table2.exitScope();
                table3.exitScope();
            }else{ // wrong input
            }
           
        }else if(first == "Q"){
            table1.removeAllScopeTable();
            table2.removeAllScopeTable();
            table3.removeAllScopeTable();
        }else{ // wrong input
        }   



        lineCount++;
    }

    int total_collision1 = table1.total_collision;
    int total_table1 = table1.scopeTableCount;

    int collision_mean1 = (total_collision1/(bucket_size*total_table1));

    int total_collision2 = table2.total_collision;
    int total_table2 = table2.scopeTableCount;

    int collision_mean2 = (total_collision2/(bucket_size*total_table2));

    int total_collision3 = table3.total_collision;
    int total_table3 = table3.scopeTableCount;

    int collision_mean3 = (total_collision3/(bucket_size*total_table3));


    reportOut<<"\t\t\t\t"<<"Hash Function"<<"\t\t\t"<<"Total Collision"<<"\t\t"<<"Collision Mean"<<"\t\t\t\t"<<endl;

    reportOut<<"\t\t\t\t"<<"_____________"<<"\t\t\t"<<"_______________"<<"\t\t"<<"______________"<<"\t\t\t\t"<<endl;


    reportOut<<"\t\t\t\t"<<"SDBM Hash"<<"\t\t\t\t\t"<<total_collision1<<"\t\t\t\t\t"<<collision_mean1<<"\t\t\t\t"<<endl;

    reportOut<<"\t\t\t\t"<<"DJB2 Hash"<<"\t\t\t\t\t"<<total_collision2<<"\t\t\t\t\t"<<collision_mean2<<"\t\t\t\t"<<endl;

    reportOut<<"\t\t\t\t"<<"FNV-1a Hash"<<"\t\t\t\t\t"<<total_collision3<<"\t\t\t\t\t"<<collision_mean3<<"\t\t\t\t"<<endl;



    
    
}