#include "SymbolInfo.h"
#include<iostream>
#include<string>
using namespace std;

int main(void){


    symbolInfo symbol = symbolInfo("Hello","Hi");
    symbolInfo** arr = new symbolInfo*[2];

    arr[0] = &symbol;

    
}