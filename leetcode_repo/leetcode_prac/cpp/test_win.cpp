#include "test_win.h"
#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <climits>

using namespace std;


// 带负数的列表中查找大于k的最小子串
tuple<int, vector<int>> shortestSubarray(vector<int>& nums, int k) 
{
    // 1. 前缀和列表头部需要加入一个0，用于diff计算
    vector<long> vec(nums.size() + 1);
    vector<int> vec2(nums.size());
    vec[0] = 0;
    for (int i = 0; i < nums.size(); i++) {
        vec[i + 1] = nums[i] + vec[i]; 
    }

    // 2. de中保存的是idx，维持一个递增的窗口
    deque<int> de;
    int diff = INT_MAX;
    for (int i = 0; i < vec.size(); i++) {
        // 2.1 处理窗口左边界（计算满足条件的diff）
        while(!de.empty() && vec[i] - vec[de.front()] >= k) {
            //diff = min(diff, i - de.front()); // 注意内部保存的是下标
            if (diff > i - de.front()) {
                diff = i - de.front();
                for (int j = 0; j < diff; j++) {
                    vec2[j] = nums[de.front() + j];
                }
            }
            de.pop_front();
        }

        // 2.2 处理窗口右边界（使得窗口递增）
        while (!de.empty() && vec[i] <= vec[de.back()]) {
            de.pop_back();
        }

        // 将当前元素idx加入窗口
        de.push_back(i);
    }

    diff = diff == INT_MAX ? -1 : diff;
    return {diff, vec2};
}


int totalFruit(vector<int>& fruits) 
{
    // 滑动窗口
    // 右窗口向前探索，如果类型小于等于2，记录diff，如果类型大于2，则停下来，移动左窗口；
    // 左窗口每次移动后减小对应类型计数，当计数小于2后，处理右窗口
    // 代码思路：
    //      右窗口为外层循环，循环内记录kind和diff，当kind超过2类时，内部循环移动左指针
    int i = 0, j = 0; 
    map<int, int> m;
    int kinds = 0;
    int diff = -1;
    while (j < fruits.size()) {
        m[fruits[j]]++;
        // 处理j指针数据和类型
        while (m.size() > 2) {
            diff = j - i > diff ? j - i : diff;
            // 移动i，降低kinds
            m[fruits[i]]--;
            if (m[fruits[i]] == 0) {
                m.erase(fruits[i]);
            }
            i++;
        }
        j++;
    }
    return diff;
}

vector<int> findAnagrams(string s, string p) {
    if (s.length() < p.length()) {
        return {};
    }

    int tgt_len = p.length();
    vector<int> vec(26, 0);
    for (auto &c: p) {
        vec[c - 'a']++;
        
    }

    int i = 0;
    int j = 0;
    int count = 0;
    vector<int> vec2(26, 0);
    vector<int> vec3;
    int diff = 0;
    while (j < s.length()) {
        if (j - i >= tgt_len) {
            //cout << "1. " << i << j << count << endl;
            if (count == tgt_len) {
                vec3.emplace_back(i);
            }
            diff = s[i] - 'a';
            if (vec[diff] > 0 && vec2[diff] <= vec[diff])
            {
                count--;
            }
            vec2[diff]--;
            i++;
        }

        //cout << "2. " << i << j << count << endl;
        diff = s[j] - 'a';
        /*
        if (vec[diff] <= 0) {
            j++;
            i = j;
            count = 0;
            continue;
        }
        */
        
        //cout << "3. " << i << j << count << endl;
        if (vec[diff] > 0 && vec2[diff] < vec[diff]) {    
            count++;
        }
        vec2[diff]++;
        j++;
    }

    return vec3;
}

void test_win()
{
    //vector<int> vec = {1,2,3,2,2};
    //cout << totalFruit(vec) << endl;

/*
    vector<int> vec = {2,-1,2,3,6,-43,5,52,-5,-53,56,2,51};
    auto [diff, vec2] = shortestSubarray(vec, 57);
    cout << diff << endl;
    vec2.resize(diff);
    for (auto &i : vec2) {
        cout << i << " ";
    }
    cout << endl;
*/

    findAnagrams("abab", "ab");
 }