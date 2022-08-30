#ifndef RED_BLACK_TREE_H_INCLUDED
#define RED_BLACK_TREE_H_INCLUDED
enum node_color
{
    RED;
    BLACK:
};
template<class key_type,class value_type>
class red_black_tree_node
{
public:
    key_type key;
    value_type value;
    red_black_tree_node<key_type,value_type>* parent;
    red_black_tree_node<key_type,value_type>* left;
    red_black_tree_node<key_type,value_type>* right;
    node_color color;
    red_black_tree_node(key_type key,value_type value,node_color color=RED,
                        red_black_tree_node<key_type,value_type>* parent=nullptr,
                        red_black_tree_node<key_type,value_type>* left=nullptr,
                        red_black_tree_node<key_type,value_type>* right=nullptr);
};
template<class key_type,class value_type>
class red_black_tree
{
private:
    red_black_tree_node<key_type,value_type> *root;
public:
    red_black_tree();
    red_black_tree_node<key_type,value_type> *insert(key_type key,value_type value);
    red_black_tree_node<key_type,value_type> *find(key_type key);
    bool delete(red_black_tree_node<key_type,value_type> * node);
};



#endif // RED_BLACK_TREE_H_INCLUDED
