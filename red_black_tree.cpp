#include <iostream>
#include "red_black_tree.h"
using namespace std;

template<class key_type,class value_type>
red_black_tree_node::red_black_tree_node(key_type key,value_type value,node_color color=RED,
                                        red_black_tree_node<key_type,value_type>* parent=nullptr,
                                        red_black_tree_node<key_type,value_type>* left=nullptr,
                                        red_black_tree_node<key_type,value_type>* right=nullptr):key(key),value(value),color(color),parent(parent),left(left),right(right)
{

}



int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
