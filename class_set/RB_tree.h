//RB_tree.h
#pragma once
#ifndef RB_TREE_H
#define RB_TREE_H

#include<utility>//pair

//定义颜色枚举类型 color
enum color
{
    BLACK,
    RED
};

// RB_Tree节点类,Key,Value
template<typename K, typename V>
class RBTreeNode
{
    std::pair<K, V> data;
    RBTreeNode<K, V>* left_child;
    RBTreeNode<K, V>* right_child;
    RBTreeNode<K, V>* parent;
    color _col;
    //构造函数
    RBTreeNode(const pair<K, V>& _kv)
        : data(_kv),
          left_child(nullptr),
          right_child(nullptr),
          parent(nullptr),
          _col(RED)
    {
    }

    //获取key值
    K& get_key(){
        return data.first;
    }

    //获取value值
    V& get_value(){
        return data.second;
    }
};

template<typename K,typename V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;


protected:
    Node* head;

    //===========================================辅助函数模块=================================
    //删除首部节点以外的所有节点并释放内存,注意，还剩下一个首部节点，相比于析构函数，该函数执行后清除红黑树可再次使用。（析构函数额外再实现首部节点内存释放）
    void release(){
        if(head==nullptr)
            return;
        _release(head->parent);
    }

    void _release(Node* cur){//release子函数用于递归释放内存
        if(cur==nullptr){
            return;
        }
        _release(cur->left_child);//删除左子树
        _release(cur->right_child);//删除右子树
        delete cur;//删除当前节点
    }

    //二叉树插入方式
    bool _insert(Node* _root,node* cur){//传指针方式传入被插入节点指针
        K _key = cur->get_key();
        if(_root->get_key()==_key){//无法插入情况
            return false;
        }
        else if(_root->get_key()>_key){//插入节点在左边
            if(_root->left_child==nullptr)//已经找到空位
            {
                _root->left_child = cur;
                cur->parent = _root;
                return true;
            }
            else{
                return _insert(_root->left_child, cur);
            }
        }
        else{
            if (_root->right_child == nullptr) //已经找到空位
            {
                _root->right_child = cur;
                cur->parent = _root;
                return true;
            } else {
                return _insert(_root->right_child, cur);
            }
        }

    }

public:
    //构造函数
    RBTree(){
        head = new Node(make_pair(K(), V()));//首部节点，parent指向root根节点，left_chile指向RB树最小节点，right_child指向RB树最大节点。
    }

    //析构函数
    ~RBTree(){
        release();//删除首部节点以外的所有节点并释放内存
        delete head;//释放首部节点
        head = nullptr;
    }

    //insert
    bool insert(const std::pair<K,V>& value){
        //空树的情况
        if(head->parent==nullptr){//插入结点为根节点
            node* cur = new Node(value);
            //init head
            head->parent = cur;
            head->left_child = cur;
            head->right_child = cur;
            //init rootNode
            cur->parent = head;
            cur->_col=BLACK;

            return true;
        } else { // 先插入:二叉树的插入方式
            node* cur = new Node(value);
            if(!_insert(head->parent, cur)){
                //存在节点key，无法插入
                delete cur;
                return false;
            }
        }
        //如果不是插入根节点或者无法插入的话，普通插入成功，接下来进行平衡红黑树
        // start here+++++++++++++++++++++++++++++++++++++++++++++++++++return true;二叉树插入成功后该进行平衡了，可以测试一下二叉树的插入有没有问题
    }
};

#endif
