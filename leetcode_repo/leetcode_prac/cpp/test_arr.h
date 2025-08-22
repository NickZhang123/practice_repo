#pragma once
#include<vector>
#include<iostream>

// 升序，无重复
// 注意：
//      1. 左右闭区间为有效区间，边界有效，因此循环判断需带等于;
//      2. 查找到返回对应序号，查找不到退出循环返回-1;
template<class T>
int binary_search(T *arr, int arrsize, T target)
{
    int l = 0;
    int r = arrsize - 1;
    int m = -1;

    // 1， 因为范围为[l,r], l==r时是有效的，数据可能等于边界值
    while (l <= r) {
        m = l + ((r - l) >> 1);
        
        /*
        std::cout << "pos[" << l << ", " << m << ", " << r <<  "], ";
        std::cout << "val[" << arr[l] << ", " << arr[m] << ", " << arr[r] <<  "], ";
        std::cout << "target = " << target << std::endl;
        */

        // 2. 相等则直接返回
        if (arr[m] == target) {
            return m;
        }

        // 3. 缩小编辑，边界在mid的两边
        if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    std::cout << "l = " << l << ", r = " << r << std::endl;

    // 4. 循环结束说明没找到，找到通过第二步退出函数
    //return l;  // 此时l为可插入的位置
    return -1;
}

// 查找target，查找到则返回对应下标，否则返回要插入的位置
template<class T>
std::pair<bool, int> binary_search_and_insert(T *arr, int arrsize, T target)
{
    int l = 0;
    int r = arrsize - 1;
    int m = -1;

    while (l <= r) {
        m = l + ((r - l) >> 1);

        if (arr[m] == target) {
            return std::make_pair(true, m);
        }

        if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    // l对应插入位置
    return std::make_pair(false, l);
}


// 查找target，如果有重复的target，则返回第一个
// 存在目标值返回下标，否则返回-1
template<class T>
int binary_search_repeat_first(T *arr, int arrsize, T target)
{
    int l = 0;
    int r = arrsize - 1;
    int m = -1;
    bool flag = false;

    while (l <= r) {
        m = l + ((r - l) >> 1);

        // 相同时，移动右边界，最后返回左边界
        if (arr[m] == target) {
            flag = true;
            r = m - 1;  
        } else if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    // 存在目标值返回下标，否则返回-1
    if (flag) 
        return l;
    else 
        return -1;
}

// 查找target，如果有重复的target，则返回最后一个
// 存在目标值返回下标，否则返回-1
template<class T>
int binary_search_repeat_last(T *arr, int arrsize, T target)
{
    int l = 0;
    int r = arrsize - 1;
    int m = -1;
    bool flag = false;

    while (l <= r) {
        m = l + ((r - l) >> 1);
         
        /*
        std::cout << "pos[" << l << ", " << m << ", " << r <<  "], ";
        std::cout << "val[" << arr[l] << ", " << arr[m] << ", " << arr[r] <<  "], ";
        std::cout << "target = " << target << std::endl;
        */

        // 相同时，移动左边界，最后返回右边界
        if (arr[m] == target) {
            flag = true;
            l = m + 1;  
        } else if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    // 存在目标值返回下标，否则返回-1
    if (flag) 
        return r;
    else 
        return -1;
}

void test_arr();