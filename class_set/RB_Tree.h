// RB_Tree.h
#pragma once
#ifndef RB_TREE_H
#define RB_TREE_H

#include <utility> //pair

//定义颜色枚举类型 color
enum color
{
    BLACK,
    RED
};

// RB_Tree节点类,Key,Value
template<typename K, typename V>
class RB_TreeNode
{
public:
    std::pair<K, V> data;
    RB_TreeNode<K, V>* left_child;
    RB_TreeNode<K, V>* right_child;
    RB_TreeNode<K, V>* parent;
    color _col;
    //构造函数
    RB_TreeNode(const std::pair<K, V>& _kv)
        : data(_kv),
          left_child(nullptr),
          right_child(nullptr),
          parent(nullptr),
          _col(RED)
    {
    }

    //获取key值
    K& get_key()
    {
        return data.first;
    }

    const K& get_key()const
    {
        return data.first;
    }

    //获取value值
    V& get_value()
    {
        return data.second;
    }

    const V& get_value()const
    {
        return data.second;
    }
};

template<typename K, typename V>
class RB_Tree
{
    typedef RB_TreeNode<K, V> Node;
    typedef size_t size_type;

public:
    Node* head; //首节点，head->parent指向root

protected:

    //===========================================辅助函数模块=================================
    //删除首部节点以外的所有节点并释放内存,注意，还剩下一个首部节点，相比于析构函数，该函数执行后清除红黑树可再次使用。（析构函数额外再实现首部节点内存释放）
    void release()
    {
        if (head == nullptr)
            return;
        _release(head->parent);
        //set head null
        head->parent = nullptr;
        head->left_child = nullptr;
        head->right_child = nullptr;
    }

    void _release(Node* cur)
    { // release子函数用于递归释放内存
        if (cur == nullptr) {
            return;
        }
        _release(cur->left_child);  //删除左子树
        _release(cur->right_child); //删除右子树
        delete cur;                 //删除当前节点
    }

    //二叉树插入方式
    bool _insert(Node* _root, Node* cur)
    { //传指针方式传入被插入节点指针
        K _key = cur->get_key();
        if (_root->get_key() == _key) { //无法插入情况
            return false;
        } else if (_root->get_key() > _key) { //插入节点在左边
            if (_root->left_child == nullptr) //已经找到空位
            {
                _root->left_child = cur;
                cur->parent = _root;
                return true;
            } else {
                return _insert(_root->left_child, cur);
            }
        } else {
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

    //获得节点的叔叔节点
    Node* uncle(Node* cur)
    { //应该没有空cur和空cur->parent和空cur->parent->parent的情况，暂时不考虑边界
        if (cur->parent ==
            cur->parent->parent->left_child) // cur->parent是祖父的左孩子
        {
            return cur->parent->parent->right_child; //返回祖父的右孩子:uncle
        } else { // cur->parent是祖父的右孩子
            return cur->parent->parent->left_child; //返回祖父的左孩子
        }
    }

    //获得节点的兄弟节点
    Node* brother(Node* cur)
    {
        if (cur->parent == head) { //根节点没有兄弟节点
            return nullptr;
        }
        if (cur == cur->parent->left_child) // cur是父亲节点的左孩子
        {
            return cur->parent->right_child;
        } else { // cur是父亲的右孩子
            return cur->parent->left_child;
        }
    }

    //左旋操作
    void L_Rotation(Node* cur)
    {                                // cur为原祖父节点
        Node* r1 = cur->right_child; // r1为原父亲节点
        //如果根节点改变，head重定向
        if (cur->parent == head) {
            head->parent = r1;
        }
        //祖父的父亲节点重定向
        else {
            if (cur == cur->parent->left_child) // cur是父亲节点的左孩子
            {
                cur->parent->left_child = r1;
            } else { // cur是父亲的右孩子
                cur->parent->right_child = r1;
            }
        }
        // 更新
        cur->right_child = r1->left_child;
        r1->parent = cur->parent;
        cur->parent = r1;
        r1->left_child = cur;
        if (cur->right_child)
            cur->right_child->parent = cur;
    }

    //右旋操作
    void R_Rotation(Node* cur)
    { // cur为原祖父节点
        Node* l1 = cur->left_child;
        //如果根节点改变，head重定向
        if (cur->parent == head) {
            head->parent = l1;
        }
        //祖父的父亲节点重定向
        else {
            if (cur == cur->parent->left_child) // cur是父亲节点的左孩子
            {
                cur->parent->left_child = l1;
            } else { // cur是父亲的右孩子
                cur->parent->right_child = l1;
            }
        }
        // 更新
        cur->left_child = l1->right_child;
        l1->parent = cur->parent;
        cur->parent = l1;
        l1->right_child = cur;
        if (cur->left_child)
            cur->left_child->parent = cur;
    }

    //插入后的平衡操作：旋转或染色
    void BalanceFunc(Node* cur)
    {
        if (cur->parent->_col == BLACK) { //已经平衡不需要操作
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
            L_Rotation(cur->parent); //此时cur是原父亲节点的位置
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
            //对祖父节点进行右旋
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
            if (cur->parent->parent->parent == head) { //上溢到根节点
                cur->parent->parent->_col = BLACK;
            } else {
                BalanceFunc(cur->parent->parent);
            }
        }
        // case6:上溢RR情况-》uncle(RED)<-祖父->父亲->cur
        else if (
                (uncle(cur)->_col == RED) &&
                (cur == cur->parent->right_child) &&
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
                (uncle(cur)->_col == RED) && (cur == cur->parent->left_child) &&
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

    //删除某一个节点
    bool deleteFunc(Node* cur)
    {
        if (cur->left_child != nullptr ||
            cur->right_child != nullptr) { //有子代则不删除防止内存泄漏
            return false;
        }
        // cur是根节点
        if (head->parent == cur) {
            head->parent = nullptr;
            head->left_child = nullptr;
            head->right_child = nullptr;
            delete cur;
            return true;
        }
        // cur是父亲左节点
        //注意这里需要判断cur的->parent是否还有cur孩子，可能已经链接非cur孩子了
        if (cur == cur->parent->left_child) {
            cur->parent->left_child = nullptr;
        } else if (cur == cur->parent->right_child) { // cur是父亲右节点
            cur->parent->right_child = nullptr;
        }
        delete cur;
        return true;
    }

    //_erase_case2_3_
    void _erase_case2_3_(Node* bro, Node* cur)
    { // bro是原兄弟节点，cur是原父亲节点
        // case2.3.1:兄弟节点至少有一个红色子节点
        //兄弟节点存在左子节点（两个或者单左子节点）
        if (bro->left_child != nullptr) {
            R_Rotation(cur); //右旋
            //染色
            cur->_col = cur->right_child->_col; // cur继承原父亲节点颜色
            cur->right_child->_col = BLACK;
            cur->left_child->_col = BLACK;
        }
        //兄弟节点只有一个右子节点
        else if (bro->right_child != nullptr) {
            L_Rotation(bro); //对兄弟节点进行左单旋
            R_Rotation(cur); //对原父亲节点进行右单旋
            //染色
            cur->parent->_col = cur->_col;
            cur->_col = BLACK;
            bro->_col = BLACK;
        }
        // case2.3.2:兄弟节点没有子节点
        //父亲节点为红色
        else if (cur->_col == RED) {
            cur->_col = BLACK;
            bro->_col = RED;
        }
        //父亲节点为黑色
        else {
            bro->_col = RED;
            if (cur->parent == head) //父亲节点为根节点情况
            {
                return;
            }
            _erase_case2_3_(brother(cur), cur->parent);
        }
    }

    //中序遍历递归子函数
    void _InOrder_Traversal(Node* root)
    {
        if (root == nullptr)
            return;
        _InOrder_Traversal(root->left_child);
        std::cout << root->get_key() << " ";
        _InOrder_Traversal(root->right_child);
    }

    // 辅助功能函数：主要为set和map中的一些操作实现，对应RB_Tree::public:功能函数模块

    //深拷贝子函数
    void recursion_cp(Node* _root,Node* new_root) {
        if(_root==head){//首结点情况
            if (head->parent){//存在根节点情况
                new_root->parent = new Node(head->parent->data);
                new_root->parent->parent = new_root;
                recursion_cp(_root->parent, new_root->parent);
            }
            return;//只有首结点情况
        }
        //DFS构造新树
        if(_root->left_child){
            new_root->left_child = new Node(_root->left_child->data);
            new_root->left_child->parent = new_root;
            recursion_cp(_root->left_child, new_root->left_child);
        }
        if(_root->right_child){
            new_root->right_child = new Node(_root->right_child->data);
            new_root->right_child->parent = new_root;
            recursion_cp(_root->right_child, new_root->right_child);
        }
    }

    //_size递归子函数
    size_type _size(Node* _root){
        if(!_root)
            return 0;
        return _size(_root->left_child) + _size(_root->right_child) + 1;
    }

    //节点增减后更新head中的最大最小指针
    void head_child_update(){
        if(!head->parent)//空树
            return;
        head->left_child = head->parent;
        head->right_child = head->parent;
        while (head->left_child->left_child){
            head->left_child = head->left_child->left_child;
        }
        while(head->right_child->right_child){
            head->right_child = head->right_child->right_child;
        }
    }

public:
    //构造函数
    RB_Tree()
    {
        head = new Node(std::make_pair(
                K(),
                V())); //首部节点，parent指向root根节点，left_chile指向RB树最小节点，right_child指向RB树最大节点。
        head->_col = BLACK;
    }

    //析构函数
    ~RB_Tree()
    {
        release();   //删除首部节点以外的所有节点并释放内存
        delete head; //释放首部节点
        head = nullptr;
    }

    //中序遍历
    void InOrder_Traversal()
    {
        _InOrder_Traversal(get_root());
        std::cout << std::endl;
    }

    //获得根节点的指针
    Node* get_root()
    {
        return head->parent;
    }

    //寻找key对应节点
    Node* find(const K& key)
    {
        Node* root = get_root();
        while (root != nullptr) {
            if (root->get_key() == key) {
                return root;
            } else if (root->get_key() > key) {
                root = root->left_child;
            } else {
                root = root->right_child;
            }
        }
        return nullptr;
    }

    // insert
    bool insert(const std::pair<K, V>& value)
    {
        Node* cur = new Node(value); //构造新节点
        //空树的情况
        if (head->parent == nullptr) { //插入结点为根节点
            // init head
            head->parent = cur;
            head->left_child = cur;
            head->right_child = cur;
            // init rootNode
            cur->parent = head;
            cur->_col = BLACK;

            return true;
        } else if (!_insert(head->parent, cur)) { // 先插入:二叉树的插入方式
            //存在节点key，无法插入
            delete cur;
            return false;
        }

        // 如果不是插入根节点或者无法插入的话，普通插入成功，接下来进行平衡红黑树
        BalanceFunc(cur); //判断并处理平衡
        //更新head
        head_child_update();

        return true;
    }

    // erase
    bool erase(Node* cur)
    {
        if (cur == nullptr)
            return false;
        // 找到被删除的节点
        if (cur->left_child == nullptr ||
            cur->right_child == nullptr) { // 要被删除节点是自身
        } else { // 找替代删除节点（这里是右子树的最小节点
            Node* ori_cur = cur;
            cur = cur->right_child;
            while (cur->left_child != nullptr) {
                cur = cur->left_child;
            }
            std::swap(ori_cur->data, cur->data); //被删除数据和替代删除数据交换
        }
        //删除被删除节点
        // case1:被删除节点是红色:直接删除
        if (cur->_col == RED) {
            deleteFunc(cur);
        }
        // case2:删除黑色节点
        // case2.1:删除黑色节点存在一个红色替代节点
        else if (cur->left_child != nullptr || cur->right_child != nullptr) {
            Node* child; //红色替代节点
            if (cur->left_child != nullptr) {
                child = cur->left_child;
                cur->left_child = nullptr; //断开被删除节点的子节点
            } else {
                child = cur->right_child;
                cur->right_child = nullptr; //断开被删除节点的子节点
            }

            //替代节点代替被删除节点
            if (cur->parent == head) { //根节点情况
                head->parent = child;
            } else if (cur == cur->parent->left_child) {
                cur->parent->left_child = child;
            } else {
                cur->parent->right_child = child;
            }
            child->_col = BLACK;
            child->parent = cur->parent;

            //删除被删除节点
            deleteFunc(cur);
        }
        // case2.2:删除黑色叶子节点-被删除节点为根节点
        else if (cur->parent == head) {
            deleteFunc(cur);
        }
        // case2.3:删除黑色叶子节点-被删除节点的兄弟节点为黑色(不可能没有兄弟节点，不然就不符合路径黑节点数相同了)
        else if (brother(cur)->_col == BLACK) {
            //删除节点
            Node* bro = brother(cur); //临时存放兄弟节点
            deleteFunc(cur);
            cur = bro->parent; // cur成为原父亲节点
            //修复平衡
            _erase_case2_3_(bro, cur); //封装起来用于递归修复
        }
        // case2.4:删除黑色叶子节点-被删除节点的兄弟节点为红色
        else {
            //转换为case2.3
            //染色
            cur->parent->_col = RED;
            brother(cur)->_col = BLACK;
            //被删除节点是父亲的右节点：对父亲节点右旋
            if (cur == cur->parent->right_child) {
                R_Rotation(cur->parent);
            }
            // 被删除节点是父亲的左节点：对父亲节点左旋
            else {
                L_Rotation(cur->parent);
            }
            // case2.3
            //删除节点
            Node* bro = brother(cur); //临时存放兄弟节点
            deleteFunc(cur);
            cur = bro->parent; // cur成为原父亲节点
            //修复平衡
            _erase_case2_3_(bro, cur); //封装起来用于递归修复
        }
        //更新head->left/right
        head_child_update();

        return true;
    }

    // erase根据key删除
    bool erase(const K& key)
    {
        return erase(find(key));
    }


    //==============功能函数模块===================
    //置空head首节点 小心使用
    void set_head_null(){
        head->parent = nullptr;
        head->left_child = nullptr;
        head->right_child = nullptr;
    }

    //深拷贝一整棵树，返回new_head
    Node* _cp(){
        Node* new_head = new Node(std::make_pair(
                K(),
                V())); //首部节点，parent指向root根节点，left_chile指向RB树最小节点，right_child指向RB树最大节点。
        new_head->_col = BLACK;

        recursion_cp(head,new_head);//开始拷贝

        //new_head左右节点移动到最小最大叶子节点
        new_head->left_child = new_head->parent;
        new_head->right_child = new_head->parent;
        if(new_head->parent){//存在根节点情况
            while (new_head->left_child->left_child) {
                new_head->left_child = new_head->left_child->left_child;
            }
            while (new_head->right_child->right_child) {
                new_head->right_child = new_head->right_child->right_child;
            }
        }

        return new_head;
    }

    //得到树的节点数量
    size_type size(){
        return _size(head->parent);
    }

    //找到比当前节点大的下一个节点
    static Node* get_next(Node* cur){
        if(cur->right_child){//存在右子树情况
            cur = cur->right_child;
            while(cur->left_child){
                cur = cur->left_child;
            }
        }
        else{//不存在右子树情况,向上找第一个比cur大的
            while (cur->parent->parent != cur) { // cur->parent!=head
                if(cur==cur->parent->left_child){
                    return cur;
                }
                cur = cur->parent;
            }
            //找遍了都没有比cur大的，此时cur已经最大，返回nullptr
            return nullptr;
        }
        return cur;
    }

    static const Node* get_next(const Node* cur)
    {
        if (cur->right_child) { //存在右子树情况
            cur = cur->right_child;
            while (cur->left_child) {
                cur = cur->left_child;
            }
        } else { //不存在右子树情况,向上找第一个比cur大的
            while (cur->parent->parent != cur) { // cur->parent!=head
                if (cur == cur->parent->left_child) {
                    return cur;
                }
                cur = cur->parent;
            }
            //找遍了都没有比cur大的，此时cur已经最大，返回nullptr
            return nullptr;
        }
        return cur;
    }

    //找到比当前节点小的下一个节点
    static Node* get_prev(Node* cur){
        if (cur->left_child) { //存在左子树情况
            cur = cur->left_child;
            while (cur->right_child) {
                cur = cur->right_child;
            }
        } else { //不存在左子树情况,向上找第一个比cur小的
            while (cur->parent->parent != cur) {
                if (cur == cur->parent->right_child) {
                    return cur;
                }
                cur = cur->parent;
            }
            //找遍了都没有比cur大的，此时cur已经最大，返回nullptr
            return nullptr;
        }
        return cur;
    }

    static const Node* get_prev(const Node* cur)
    {
        if (cur->left_child) { //存在左子树情况
            cur = cur->left_child;
            while (cur->right_child) {
                cur = cur->right_child;
            }
        } else { //不存在左子树情况,向上找第一个比cur小的
            while (cur->parent->parent != cur) {
                if (cur == cur->parent->right_child) {
                    return cur;
                }
                cur = cur->parent;
            }
            //找遍了都没有比cur大的，此时cur已经最大，返回nullptr
            return nullptr;
        }
        return cur;
    }
};

#endif
