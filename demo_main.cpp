#include "red_black_tree.h"
#include <iostream>
using namespace std;
extern void main_test();
int main()
{
    red_black_tree<int,int>* t = new red_black_tree<int,int>();
    for(int i=1;i<=8;i++)
    {
        t->insert(i,i);
        cout<<"after insert "<<i<<endl;
        t->print_tree();
    }
    main_test();

}