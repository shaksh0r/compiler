#include "SymbolInfo.h"
#include "ScopeTable.h"
#include<iostream>
using namespace std;

int main(void){
    symbolInfo symbol1 = symbolInfo("Plus","Operator");
    symbolInfo symbol2 = symbolInfo("Division","Operator");
    symbolInfo symbol3 = symbolInfo("Subtraction","Operator");
    scopeTable table = scopeTable(5,1);

    table.insert(&symbol1);

    table.print();

    table.deleteSymbol("Plus");

    table.print();

    table.insert(&symbol2);
    table.insert(&symbol3);

    table.print();

    symbolInfo* temp = table.lookUp("Division");

    cout<<temp->getSymbolName();


}