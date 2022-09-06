#include"red_black_tree.h"
using namespace std;
void main_test()
{
    red_black_tree<int,int> temp;
    for(int i=9;i<9+8;i++)
    {
        temp.insert(i,i);
        temp.print_tree();
    }
}