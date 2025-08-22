#pragma once

// 链表节点定义
struct ListNode {
    int val;        // 当前节点值
    ListNode *p_next; // 下一个节点   

    ListNode() : val(0), p_next(nullptr) {}
    ListNode(int x) : val(x), p_next(nullptr) {}
    ListNode(int x, ListNode *p_next) : val(x), p_next(p_next) {}
};

void func_test();


