#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "test3.h"
#include "ScopeTable.h"


using namespace std;

int main(void){
    ofstream out("output.txt");
   scopeTable table = scopeTable(4,1,out);
   
   table.SDBMHash("foo",5);


}