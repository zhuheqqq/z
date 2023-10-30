#include<iostream>
using namespace std;

class MyLinkedList {
public:
    struct LinkedNode{
        int val;
        LinkedNode* next;
        LinkedNode(int val):val(val),next(nullptr){}
    };
    MyLinkedList() {
        dummyhead=new LinkedNode(0);
        size=0;
    }
    
    int get(int index) {
        if(index>size-1||index<0)
        {
            return -1;
        }

        LinkedNode* cur=dummyhead->next;
        while(index--)
        {
            cur=cur->next;
        }
        return cur->val;

    }
    
    void addAtHead(int val) {
        LinkedNode* firstlist=new LinkedNode(val);
        firstlist->next=dummyhead->next;
        dummyhead->next=firstlist;
        size++;

    }
    
    void addAtTail(int val){
        LinkedNode* finallist=new LinkedNode(val);
        LinkedNode*cur=dummyhead;

        while(cur->next!=nullptr)
        {
            cur=cur->next;
        }
        cur->next=finallist;
        size++;

    }
    
    void addAtIndex(int index, int val) {//如果 index 等于链表的长度，那么该节点会被追加到链表的末尾
            if(index>size||index<0)
            {
                return;
            }
            LinkedNode* prev=new LinkedNode(val);
            LinkedNode*cur=dummyhead;
            while(index--)
            {
                cur=cur->next;
            }
            prev->next=cur->next;
            cur->next=prev;
            size++;

    }
    
    void deleteAtIndex(int index) {
        if (index >= size || index < 0) {
            return;
        }
        LinkedNode* cur = dummyhead;
        while(index--) {
            cur = cur ->next;
        }
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp=nullptr;
        size--;
    }

private:
    LinkedNode* dummyhead;
    int size;
        
};



int main() {
    MyLinkedList* obj = new MyLinkedList();

    // 测试 addAtHead 方法
    obj->addAtHead(1);
    obj->addAtHead(2);

    // 测试 get 方法
    int val1 = obj->get(0); // 2
    int val2 = obj->get(1); // 1
    int val3 = obj->get(2); // -1，应该返回-1，因为索引2超出了链表范围

    // 输出结果
    std::cout << "Value at index 0: " << val1 << std::endl;
    std::cout << "Value at index 1: " << val2 << std::endl;
    std::cout << "Value at index 2: " << val3 << std::endl;

    // 测试 addAtTail 方法
    obj->addAtTail(3);
    obj->addAtTail(4);

    std::cout << "Value at index 2: " << obj->get(2)<< std::endl;
    std::cout << "Value at index 3: " << obj->get(3)<< std::endl;
    std::cout << "Value at index 4: " << obj->get(4) << std::endl;
    

    // 测试 addAtIndex 方法
    obj->addAtIndex(2, 5);
    obj->addAtIndex(0, 6);

    //输出链表内容
    for (int i = 0; i < 7; i++) {
        int val = obj->get(i);
        std::cout << "Value at index " << i << ": " << val << std::endl;
    }

    // 测试 deleteAtIndex 方法
    obj->deleteAtIndex(3);
    obj->deleteAtIndex(0);

    // 输出链表内容
    for (int i = 0; i < 5; i++) {
        int val = obj->get(i);
        std::cout << "Value at index " << i << ": " << val << std::endl;
    }

    // 释放对象
    delete obj;

    return 0;
}
