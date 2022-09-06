#ifndef RED_BLACK_TREE_H_INCLUDED
#define RED_BLACK_TREE_H_INCLUDED
#include<iostream>
#include<queue>
using namespace std;
/* declarations of some exception begin*/
class rbtree_error{};


/* declarations of some exception end */

enum node_color
{
    RED,
    BLACK,
};
template<class key_type,class value_type>
class red_black_tree;
template<class key_type,class value_type>
class red_black_tree_node;

template<class key_type,class value_type>
class node_iterator
{
public:
    const key_type &key;
    value_type &value;
    node_iterator(key_type &_key,value_type &_value,red_black_tree_node<key_type,value_type> *node);
    node_iterator* operator->();
    value_type& operator*();
    friend red_black_tree<key_type,value_type>;
private:
    red_black_tree_node<key_type,value_type> *node;
};

template<class key_type,class value_type>
class red_black_tree_node
{
public:
    key_type key;
    value_type value;
    node_color color;
    red_black_tree_node<key_type,value_type>* parent;
    red_black_tree_node<key_type,value_type>* left;
    red_black_tree_node<key_type,value_type>* right;

    node_iterator<key_type,value_type> node_iter;
    bool nil;
    /**
    该构造函数用来构造非nil节点，如果没有传入左右子节点，会自动挂载nil节点作为子节点。
    */
    red_black_tree_node(key_type key,value_type value,node_color color=RED,
                        red_black_tree_node<key_type,value_type>* parent=nullptr,
                        red_black_tree_node<key_type,value_type>* left=nullptr,
                        red_black_tree_node<key_type,value_type>* right=nullptr);
    /**
    该构造函数用来构造nil节点。
    */
    red_black_tree_node();
    void set_left(red_black_tree_node<key_type,value_type>* node);
    void set_right(red_black_tree_node<key_type,value_type>* node);

};

template<class key_type,class value_type>
class red_black_tree
{
private:
    red_black_tree_node<key_type,value_type> *root;
    void fix_after_insert(red_black_tree_node<key_type,value_type>* node);
    void left_rotation(red_black_tree_node<key_type,value_type>* node);
    void right_rotation(red_black_tree_node<key_type,value_type>* node);
public:
    red_black_tree();
    /** insert
    * 插入一个键值对，如果待插入的键已经在树中存在，则返回该键所在节点的迭代器。
    * 你可以通过迭代器判断节点的值和待插入的值是否一样。如果一样，说明新增节点成功。如果不一样，说明
    * 待插入的键已经存在。
    */
    node_iterator<key_type,value_type> insert(key_type key,value_type value);
    node_iterator<key_type,value_type> find(key_type key);
    bool erase(node_iterator<key_type,value_type> node_iter);
    /**
    * 以二叉树的数组表示法打印树。红节点用下划线表示，_32_表示红节点，键为32。
    */
    void print_tree();
};


/**
构造节点迭代器的构造函数。
*/
template<class key_type,class value_type>
node_iterator<key_type,value_type>::node_iterator(key_type &key,value_type &value,red_black_tree_node<key_type,value_type> *node):key(key),value(value),node(node){}

/**
该构造函数用来构造非nil节点，如果没有传入左右子节点，会自动挂载nil节点作为子节点。
*/
template<class key_type,class value_type>
red_black_tree_node<key_type,value_type>::red_black_tree_node(key_type key,value_type value,node_color color,
                                        red_black_tree_node<key_type,value_type>* parent,
                                        red_black_tree_node<key_type,value_type>* left,
                                        red_black_tree_node<key_type,value_type>* right):
                                        key(key),value(value),color(color),parent(parent),left(left),right(right),node_iter(this->key,this->value,this)
{
    nil=false;
    if(left==nullptr)
    {
        set_left(new red_black_tree_node<key_type,value_type>());
        this->left->parent=this;
    }
    if(right==nullptr)
    {
        set_right(new red_black_tree_node<key_type,value_type>());
        this->right->parent=this;
    }
}
/**
该构造函数用来构造nil节点。
*/
template<class key_type,class value_type>
red_black_tree_node<key_type,value_type>::red_black_tree_node():node_iter(this->key,this->value,this)
{
    nil=true;
    color=BLACK;
    this->left=nullptr;
    this->right=nullptr;
}




template<class key_type,class value_type>
red_black_tree<key_type,value_type>::red_black_tree()
{
    root=nullptr;
}




template<class key_type,class value_type>
void red_black_tree_node<key_type,value_type>::set_left(red_black_tree_node<key_type,value_type>* node)
{
    if(left!=nullptr)
    {
        delete left;
    }
    left=node;
    left->parent=this;
}

template<class key_type,class value_type>
void red_black_tree_node<key_type,value_type>::set_right(red_black_tree_node<key_type,value_type>* node)
{
    if(right!=nullptr)
    {
        delete right;
    }
    right=node;
    right->parent=this;
}

template<class key_type,class value_type>
node_iterator<key_type,value_type> red_black_tree<key_type,value_type>::insert(key_type key,value_type value)
{
    if(root==nullptr)
    {
        root=new red_black_tree_node<key_type,value_type>(key,value,BLACK);
        return root->node_iter;
    }
    else
    {
        red_black_tree_node<key_type,value_type>* x=root;
        red_black_tree_node<key_type,value_type>* new_add_node=nullptr;

        while(1)
        {
            if(key<x->key)
            {
                if(x->left->nil)
                {
                    new_add_node=new red_black_tree_node<key_type,value_type>(key,value,RED,x);
                    x->set_left(new_add_node);
                    fix_after_insert(new_add_node);
                    return new_add_node->node_iter;
                }
                else
                {
                    x=x->left;
                }
            }
            else if(key==x->key)
            {
                return x->node_iter;
            }
            else
            {
                if(x->right->nil)
                {
                    new_add_node=new red_black_tree_node<key_type,value_type>(key,value,RED,x);
                    x->set_right(new_add_node);
                    fix_after_insert(new_add_node);
                    return new_add_node->node_iter;
                }
                else
                {
                    x=x->right;
                }
            }
        }
    }
}
template<class key_type,class value_type>
void red_black_tree<key_type,value_type>::left_rotation(red_black_tree_node<key_type,value_type>* node)
{
    red_black_tree_node<key_type,value_type>* rn=node->right;
    if(node==root)
    {
        root=node->right;
        root->parent=nullptr;
    }
    else
    {
        if(node->parent->left==node)
        {
            node->parent->left=rn;
            rn->parent=node->parent;
        }
        else
        {
            node->parent->right=rn;
            rn->parent=node->parent;
        }
    }
    node->right=rn->left;
    rn->left->parent=node;
    rn->left=node;
    node->parent=rn;
}

template<class key_type,class value_type>
void red_black_tree<key_type,value_type>::right_rotation(red_black_tree_node<key_type,value_type>* node)
{
    red_black_tree_node<key_type,value_type>* ln=node->left;
    if(node==root)
    {
        root=node->left;
        root->parent=nullptr;
    }
    else
    {
        if(node->parent->left==node)
        {
            node->parent->left=ln;
            ln->parent=node->parent;
        }
        else
        {
            node->parent->right=ln;
            ln->parent=node->parent;
        }
    }
    node->left=ln->right;
    ln->right->parent=node;
    ln->right=node;
    node->parent=ln;
}

/**
private函数，插入一个节点后，用来进行调整，使得符合红黑树约束。
*/
template<class key_type,class value_type>
void red_black_tree<key_type,value_type>::fix_after_insert(red_black_tree_node<key_type,value_type>* node)
{
    while(node!=root&&node->parent->color==RED)
    {
        red_black_tree_node<key_type,value_type>* uncle;
        if(node->parent==node->parent->parent->left) uncle=node->parent->parent->right;
        else uncle=node->parent->parent->left;
        if(uncle->color==RED)
        {
            node->parent->color=BLACK;
            uncle->color=BLACK;
            uncle->parent->color=RED;
            node=uncle->parent;
        }
        else
        {
            if(uncle==uncle->parent->right&&node==node->parent->left)  //左左情况
            {
                node->parent->color=BLACK;
                node->parent->parent->color=RED;
                right_rotation(node->parent->parent);
                break;
            }
            else if(uncle==uncle->parent->right&&node==node->parent->right) //左右情况
            {
                left_rotation(node->parent);
                node=node->left;
            }
            else if(uncle==uncle->parent->left&&node==node->parent->right) //右右情况
            {
                node->parent->color=BLACK;
                node->parent->parent->color=RED;
                left_rotation(node->parent->parent);
                break;
            }
            else
            {
                right_rotation(node->parent);
                node=node->right;
            }
        }
    }
    root->color = BLACK;
}

template<class key_type,class value_type>
void red_black_tree<key_type,value_type>::print_tree()
{
    if(root==nullptr)
    {
        cout<<endl;
    }
    queue< red_black_tree_node<key_type,value_type>* > q;
    q.push(root);
    bool all_leaf;
    while(!q.empty())
    {
        int qsize=q.size();
        bool last_all_leaf=all_leaf;
        all_leaf=true;
        for(int i=0;i<qsize;i++)
        {
            red_black_tree_node<key_type,value_type>* x=q.front();
            q.pop();
            if(x==nullptr)
            {
                if(!last_all_leaf)
                {
                    q.push(nullptr);
                    q.push(nullptr);
                    cout<<" null ";
                }
                else
                {
                    q=queue< red_black_tree_node<key_type,value_type>* > ();
                    break;
                }
            }
            else if(!x->nil)
            {
                all_leaf=false;
                q.push(x->left);
                q.push(x->right);
                if(x->color==RED)
                {
                    cout<<" _"<<x->key<<"_, ";
                }
                else
                {
                    cout<<" "<<x->key<<" ";
                }
            }
            else if(x->nil)
            {
                q.push(x->left);
                q.push(x->right);
                cout<<" nil ";
            }


        }
        cout<<endl;
    }
}


#endif // RED_BLACK_TREE_H_INCLUDED
