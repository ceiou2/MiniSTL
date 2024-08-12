// HashTable.h
/*
后期可以优化的地方：用户自定义或者传入hash函数，end（）不仅仅返回nullptr的iterator
目前只能接受可以强制转换为int的关键字
*/
#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <utility>
#include "MiniVector.h" //hash表底层以vector实现

//表项，使用链表节点
template<typename T>
class HashNode
{
public:
    T data;
    HashNode* next;
    // 构造函数
    HashNode() {}
    HashNode(T d): data(d) {}
};

//使用开散列，vector+链表的方式
template<typename K, typename T, typename KeyOfT>
class HashTable
{
private:
    typedef HashNode<T> Node;
    typedef size_t size_type;
    typedef K key_type;
    typedef T value_type;

    vector<Node*> table;
    size_type size;
    KeyOfT kot; //仿函数，用于获取T data中的K key
    //=================辅助功能函数模块=====================
    // 清空所有vector上的链表（清空桶
    void release()
    {
        for (size_type i = 0; i < table.size(); ++i) {
            if (table[i]) {
                release_list(table[i]);
                table[i] = nullptr;
            }
        }
        size = 0;
    }
    //清空一个桶（链表
    void release_list(Node* cur)
    {
        if (!cur)
            return;
        release_list(cur->next);
        delete (cur);
    }

    //按照hash方式插入节点，可以一次输入一个链表，从cur>>-->>nullptr,根据链表特性，从尾部到头部插入
    //调用该函数前需确保key不重复
    void hash_in(Node* cur)
    {
        if (!cur)
            return;
        hash_in(cur->next);
        // 找到hash位置并插入（头插
        size_type index = hash(cur);
        cur->next = table[index];
        table[index] = cur;
    }

    //获得节点的key对应的hash值
    size_type hash(const Node* cur) const
    {
        key_type key = kot(cur->data);
        return (int)key % table.size();
    }

    size_type hash(const key_type& key) const
    {
        return (int)key % table.size();
    }

    //深拷贝链表，返回新链表头
    Node* _copy_list(const Node* ori_cur) const
    {
        Node* res = new Node(); //哑节点
        Node* head = res;       //新链表的头节点的前一个哑节点
        while (ori_cur) {
            res->next = new Node(ori_cur->data);
            ori_cur = ori_cur->next;
            res = res->next;
        }
        res = head->next; //新链表的头节点
        delete head;
        return res;
    }

public:
    //构造函数
    HashTable(): size(0)
    {
        table.resize(10, nullptr);
    }

    //析构函数
    ~HashTable()
    {
        release(); //清空所有桶
    }

    // 插入函数 成功返回插入节点的指针;失败返回nullptr
    /*
    本函数中的swap用vector的非成员函数方式调用会报错
    swap(ori_table,table)//here
    */
    Node* insert(T data)
    {
        //检测是否需要扩容：装载因子==1时扩容（size==table.size()）
        if (size == table.size()) {
            //扩容
            size_type new_size = 2 * size;
            vector<Node*> ori_table(new_size); //开辟新空间
            ori_table.swap(
                    table); // ori_table存放原hastableable，table存放新hastableable
            // 将hastableable里的所有节点按照data的hash转移到newhastableable上
            for (size_type i = 0; i < ori_table.size(); ++i) {
                if (ori_table[i]) {
                    hash_in(ori_table[i]);
                }
            }
        }
        if (find(kot(data))) { // data已经存在
            return nullptr;
        }
        ++size;
        Node* s = new Node(data);
        hash_in(s);
        return s;
    }

    //查找函数
    Node* find(const key_type& key)
    {
        //计算hash
        Node* cur = table[hash(key)];
        while (cur) {
            if (kot(cur->data) == key)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    const Node* find(const key_type& key) const
    {
        //计算hash
        Node* cur = table[hash(key)];
        while (cur) {
            if (kot(cur->data) == key)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    //删除函数
    bool erase(const K key)
    {
        //找到data所在节点
        Node* cur = find(key);
        if (!cur) // data不存在
            return false;
        //找到节点所在位置
        size_type index = hash(cur); //找到cur的hash
        if (table[index] == cur) {   //桶里第一个就是cur的情况
            table[index] = cur->next;

        } else { // cur不是第一个节点
            Node* pre = table[index];
            while (pre->next != cur) { //找到cur的前一个节点
                pre = pre->next;
            }
            pre->next = cur->next;
        }
        delete cur;
        --size;
        return true;
    }

    //======功能函数模块======
    size_type get_size() const
    {
        return size;
    }

    void clear()
    { //清空所有桶
        release();
    }

    //获得第一个节点
    Node* begin()
    {
        for (size_type i = 0; i < table.size(); ++i) {
            if (table[i]) { //第一个非空位置
                return table[i];
            }
        }
        return nullptr; //空hashtable
    }

    const Node* begin() const
    {
        for (size_type i = 0; i < table.size(); ++i) {
            if (table[i]) { //第一个非空位置
                return table[i];
            }
        }
        return nullptr; //空hashtable
    }

    //获得最后一个节点
    Node* end()
    {
        return nullptr;
    }

    //找到当前节点的下一个节点（仅桶内
    Node* get_next_in_bucket(Node* cur)
    {
        return cur->next;
    }

    //找到当前节点的下一个节点（可跨桶
    Node* get_next(Node* cur)
    {
        if (cur->next)
            return cur->next;
        for (size_type i = hash(cur) + 1; i < table.size(); ++i) {
            if (table[i])
                return table[i];
        }
        return nullptr; //后面没元素了
    }

    const Node* get_next(const Node* cur) const
    {
        if (cur->next)
            return cur->next;
        for (size_type i = hash(cur) + 1; i < table.size(); ++i) {
            if (table[i])
                return table[i];
        }
        return nullptr; //后面没元素了
    }

    //深拷贝一个副本,副本存放在other中
    void _cp(HashTable& other) const
    {
        other.clear();
        //控制桶数量相同
        other.table.resize(table.size());
        //深拷贝链表
        for (size_type i = 0; i < table.size(); ++i) {
            if (table[i]) {
                other.table[i] = _copy_list(table[i]);
            }
        }
        other.size = size;
    }

    //移动table中的所有链表到新的table中
    void move_to(HashTable& other)
    {
        other.clear();
        //这里直接交换两个table
        swap(other);

        //此后被移动HashTable析构能够自动销毁目的地HashTable的原始数据
        //还不会删除被移动HashTable的原始数据，可谓一举两得
    }

    void swap(HashTable& other)
    {
        table.swap(other.table);
        std::swap(other.size, size);
    }
};

#endif
