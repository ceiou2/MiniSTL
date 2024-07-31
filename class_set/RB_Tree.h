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
public:
    std::pair<K, V> data;
    RBTreeNode<K, V>* left_child;
    RBTreeNode<K, V>* right_child;
    RBTreeNode<K, V>* parent;
    color _col;
    //构造函数
    RBTreeNode(const std::pair<K, V>& _kv)
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
    Node* head;//首节点，head->parent指向root

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
    bool _insert(Node* _root,Node* cur){//传指针方式传入被插入节点指针
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

    //获得节点的兄弟节点
    Node* uncle(Node* cur){//应该没有空cur和空cur->parent和空cur->parent->parent的情况，暂时不考虑边界
        if(cur->parent==cur->parent->parent->left_child)//cur->parent是祖父的左孩子
        {
            return cur->parent->parent->right_child;//返回祖父的右孩子:uncle
        }
        else{//cur->parent是祖父的右孩子
            return cur->parent->parent->left_child;//返回祖父的左孩子
        }
    }

    //左旋操作
    void L_Rotation(Node* cur){//cur为原祖父节点
        Node* r1 = cur->right_child;//r1为原父亲节点
        //如果根节点改变，head重定向
        if(cur->parent==head){
            head->parent = r1;
        }
        // 更新
        cur->right_child = r1->left_child;
        r1->parent = cur->parent;
        cur->parent = r1;
        r1->left_child = cur;
    }

    //右旋操作
    void R_Rotation(Node* cur){//cur为原祖父节点
        Node* l1 = cur->left_child;
        //如果根节点改变，head重定向
        if (cur->parent == head) {
            head->parent = l1;
        }
        // 更新
        cur->left_child = l1->right_child;
        l1->parent = cur->parent;
        cur->parent = l1;
        l1->right_child = cur;
    }

    //插入后的平衡操作：旋转或染色
    void BalanceFunc(Node* cur)
    {
        if(cur->parent->_col==BLACK){//已经平衡不需要操作
            return;
        }
        // case1:LL情况-》cur<-父亲<-祖父
        if ((uncle(cur) == nullptr || uncle(cur)->_col == BLACK) &&
            (cur == cur->parent->left_child) &&
            (cur->parent == cur->parent->parent->left_child)) {
            // 染色
            cur->parent->_col = BLACK;
            cur->parent->parent->_col = RED;
            R_Rotation(cur->parent->parent); // 对祖父节点右旋
        }
        // case2:RR情况-》祖父->父亲->cur
        else if (
                (uncle(cur) == nullptr || uncle(cur)->_col == BLACK) &&
                (cur == cur->parent->right_child) &&
                (cur->parent == cur->parent->parent->right_child)) {
            // 染色
            cur->parent->_col = BLACK;
            cur->parent->parent->_col = RED;
            L_Rotation(cur->parent->parent); //对祖父节点左旋
        }
        // case3:RL情况-》祖父->(cur<-父亲)
        else if (
                (uncle(cur) == nullptr || uncle(cur)->_col == BLACK) &&
                (cur == cur->parent->left_child) &&
                (cur->parent == cur->parent->parent->right_child)) {
            //染色
            cur->_col = BLACK;
            cur->parent->parent->_col = RED;
            //对父亲节点进行右旋
            R_Rotation(cur->parent);
            //对祖父节点进行左旋
            L_Rotation(cur->parent);//此时cur是原父亲节点的位置
        }
        // case4:LR情况-》(父亲->cur)<-祖父
        else if (
                (uncle(cur) == nullptr || uncle(cur)->_col == BLACK) &&
                (cur == cur->parent->right_child) &&
                (cur->parent == cur->parent->parent->left_child)) {
            //染色
            cur->_col = BLACK;
            cur->parent->parent->_col = RED;
            //对父亲节点进行左旋
            L_Rotation(cur->parent);
            //对祖父节点进行左旋
            R_Rotation(cur->parent); //此时cur是原父亲节点的位置
        }
        // case5:上溢LL情况-》cur<-父亲<-祖父->uncle(RED)
        else if (
                (uncle(cur)->_col == RED) && (cur == cur->parent->left_child) &&
                (cur->parent == cur->parent->parent->left_child)) {
            // 染色
            cur->parent->_col = BLACK;
            uncle(cur)->_col = BLACK;
            cur->parent->parent->_col = RED;
            if(cur->parent->parent->parent==head){//上溢到根节点
                cur->parent->parent->_col = BLACK;
            }
            else{
                BalanceFunc(cur->parent->parent);
            }
        }
        // case6:上溢RR情况-》uncle(RED)<-祖父->父亲->cur
        else if (
                (uncle(cur)->_col == RED) && (cur == cur->parent->right_child) &&
                (cur->parent == cur->parent->parent->right_child)) {
            // 染色
            cur->parent->_col = BLACK;
            uncle(cur)->_col = BLACK;
            cur->parent->parent->_col = RED;
            if (cur->parent->parent->parent == head) { //上溢到根节点
                cur->parent->parent->_col = BLACK;
            } else {
                BalanceFunc(cur->parent->parent);
            }
        }
        // case7:上溢LR情况-》(父亲->cur)<-祖父->uncle(RED)
        else if (
                (uncle(cur)->_col == RED) &&
                (cur == cur->parent->right_child) &&
                (cur->parent == cur->parent->parent->left_child)) {
            // 染色
            cur->parent->_col = BLACK;
            uncle(cur)->_col = BLACK;
            cur->parent->parent->_col = RED;
            if (cur->parent->parent->parent == head) { //上溢到根节点
                cur->parent->parent->_col = BLACK;
            } else {
                BalanceFunc(cur->parent->parent);
            }
        }
        // case8:上溢RL情况-》uncle(RED)<-祖父->(cur<-父亲)
        else if (
                (uncle(cur)->_col == RED) &&
                (cur == cur->parent->left_child) &&
                (cur->parent == cur->parent->parent->right_child)) {
            // 染色
            cur->parent->_col = BLACK;
            uncle(cur)->_col = BLACK;
            cur->parent->parent->_col = RED;
            if (cur->parent->parent->parent == head) { //上溢到根节点
                cur->parent->parent->_col = BLACK;
            } else {
                BalanceFunc(cur->parent->parent);
            }
        }
    }

public:
    //构造函数
    RBTree(){
        head = new Node(std::make_pair(K(), V()));//首部节点，parent指向root根节点，left_chile指向RB树最小节点，right_child指向RB树最大节点。
        head->_col = BLACK;
    }

    //析构函数
    ~RBTree(){
        release();//删除首部节点以外的所有节点并释放内存
        delete head;//释放首部节点
        head = nullptr;
    }

    //中序遍历
    void InOrder_Traversal(Node* root)
    {
        if (root == nullptr)
            return;
        InOrder_Traversal(root->left_child);
        std::cout << root->get_key() << " ";
        InOrder_Traversal(root->right_child);
    }

    //获得根节点的指针
    Node* get_root(){
        return head->parent;
    }

    //insert
    bool insert(const std::pair<K,V>& value){
        Node* cur = new Node(value);//构造新节点
        //空树的情况
        if(head->parent==nullptr){//插入结点为根节点
            //init head
            head->parent = cur;
            head->left_child = cur;
            head->right_child = cur;
            //init rootNode
            cur->parent = head;
            cur->_col=BLACK;

            return true;
        } else if (!_insert(head->parent, cur)) { // 先插入:二叉树的插入方式
            //存在节点key，无法插入
            delete cur;
            return false;
        }

        // 如果不是插入根节点或者无法插入的话，普通插入成功，接下来进行平衡红黑树
        BalanceFunc(cur);//判断并处理平衡
        //更新head+++不确定这里是要从根节点重新走还是从上一个节点开始走就行以及这里写成if会怎样（应该没关系，毕竟只插入一个）
        while(head->left_child->left_child!=nullptr){
            head->left_child = head->left_child->left_child;
        }
        while(head->right_child->right_child!=nullptr){
            head->right_child = head->right_child->right_child;
        }
        return true;
    }


};

#endif