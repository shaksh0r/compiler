#include "SymbolInfo.h"
#include<iostream>
using namespace std;

int main(void){
    symbolInfo symbol = symbolInfo("Plus","Operator");

    cout<<symbol.getSymbolName();


}