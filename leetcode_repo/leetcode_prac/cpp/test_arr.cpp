#include "test_arr.h"
#include "./tools/01_link_list.h"
#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

void test_binary_search_repeat_first()
{
    int arr[10] = {1,3,5,5,5,7,9};
    for (int i = 0; i < 11; i++) {
        int idx = binary_search_repeat_first(arr, 7, i);
        if (idx >= 0) {
            cout << "存在目标元素" << i << "，第一个位置为" << idx << endl;
        } else {
            cout << "不存在目标元素" << i <<  endl;
        }
    }
}

void test_binary_search_repeat_last()
{
    int arr[10] = {1,3,5,5,5,7,9};
    for (int i = 0; i < 11; i++) {
        int idx = binary_search_repeat_last(arr, 7, i);
        if (idx >= 0) {
            cout << "存在目标元素" << i << "，最后一个位置为" << idx << endl;
        } else {
            cout << "不存在目标元素" << i <<  endl;
        }
    }
}

void test_binary_search_and_insert()
{
    int arr[10] = {1,3,5,7,9};
    std::pair<bool, int> p = binary_search_and_insert(arr, 5, 1);
    if (p.first) {
        cout << "存在目标元素，位置为" << p.second << endl;
    } else {
        cout << "不存在目标元素，插入位置为" << p.second << endl;
    }

    auto p2 = binary_search_and_insert(arr, 5, 6);
    if (p2.first) {
        cout << "存在目标元素，位置为" << p2.second << endl;
    } else {
        cout << "不存在目标元素，插入位置为" << p2.second << endl;
    }

    if (auto [success, idx] = binary_search_and_insert(arr, 5, 123); success) {
        cout << "存在目标元素，位置为" << idx << endl;
    } else {
        cout << "不存在目标元素，插入位置为" << idx << endl;
    }
}

void test_binary_search()
{
    int arr[10] = {1,3,5,7,9};
    int ret = binary_search(arr, 5, 0);
    if (ret != -1) {
        cout << ret << endl;
    } else {
        cout << "无此数据" << endl;
    }
}

// 求x的平方根，精确到10为小数
// 注意：
//  1. 精确到10位是指x的平方根精确到10位
//  2. 求的是小于x的平方根，是左边界靠近，返回左边界值
double test_sqrt_with_precision(int x) 
{
    double diff = 1e-10;                            // 小数科学技术法， 1e2表示100
    double l = 0.0, r = x, m = -1;
    cout << std::fixed << std::setprecision(10);    // 精确到10位，必须大于10位输出观察
    int cnt = 0;

    // 因为二分法小数逼近求值，这里不能使用<=，后续逻辑，l和r分别继承mid值，不用增加diff
    while (r - l > diff) {
        cnt++;                                      // 统计计算次数，次数更精确位数有关
        m = l + ((r - l) / 2.0);

        //std::cout << "pos[" << l << ", " << m << ", " << r <<  "], ";
        //std::cout << "target = " << x << std::endl;

        // 精确值在l和r上，不在x上，这里不能使用(x - m * m < diff)的逻辑来判断
        // 保证l和r在预期值左右，然后不断夹逼到r-l<diff范围
        //if (m * m > x) {
        if (x / m < m) {
            r = m;   
        }  else {
            l = m;   
        }
    }

    // cout << l << " " << r << " " << cnt << endl;
    // 返回左值，平方小于x的最接近的值
    return l;  
}

// 求最接近x平方根的整数
int test_sqrt(int x)
{
    int l = 0, r = x, m = -1;

    // 重要：l和r会逐渐向平方根趋近，因为m的求值方法为整数，l和r最小间接为1，当<=1时，二者递归结束
    // 保持l在平方根左边，r在平方根右边
    while (r - l > 1) {
        m = l + ((r - l) >> 1);
        std::cout << "pos[" << l << ", " << m << ", " << r <<  "], ";
        //if (m * m > x) {
        if (x / m < m) {
            r = m;
        } else {
            l = m;  
        }
    }

    return l;
}

bool isPerfectSquare(int num) 
{
        if (num == 1) {
            return true;
        }
        int l = 1, r = num, m = -1;
        while (l <= r) {
            m = l + ((r - l ) >> 1);
            long mm = (long)m * m;
            if (mm == num) {
                return true;
            } else if (mm < num) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return false;
    }

// 将1,6,3移动至末尾，其他元素保持不变
// 解法：双指针i,j遍历数组，j遍历到不属于163的数字后，将ij之间的数据进行冒泡处理
void test_arr_move() 
{
    vector<int> vec{2, 1, 6, 5, 3, 7, 9};
    int i = 0, j = 0;

    for (j = 0; j < vec.size(); j++) {
        // 只移动j
        if (vec[j] == 1 || vec[j] == 3 || vec[j] == 6) {
            continue;
        }

        // i，j相同，没有慢指针，continue
        if (i == j) {
            i++;
            continue;
        } 
        
        // i-j之间冒泡
        int k = j - 1;
        while (k >= i) {
            int tmp = vec[k];
            vec[k] = vec[k+1];
            vec[k+1] = tmp;
            k--;
        }
    }

    for (auto &i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

bool backspaceCompare(string s, string t) 
{
    int i = s.length() - 1, j = t.length() - 1, sCnt = 0, tCnt = 0;
    while (i >=0 || j>= 0) {
        while (i>=0) {
            if (s[i] == '#') {
                sCnt++;
                i--;
                continue;
            }

            if (s[i] != '#') {
                if (sCnt == 0) {
                    break;
                } else {
                    sCnt--;
                    i--;
                }
            }
        }

        while (j>=0) {
            if (t[j] == '#') {
                tCnt++;
                j--;
                continue;
            }

            if (t[j] != '#') {
                if (tCnt == 0) {
                    break;
                } else {
                    tCnt--;
                    j--;
                }
            }
        }
        
        if (i < 0 || j < 0) break;

        if (s[i] != t[j]) {
            return false;
        } else {
            i--;
            j--;
        }
    }

    cout << i << j << endl;
    if (i < 0 && j < 0) {
        return true;
    } else if (i < 0) {
        while (j>=0) {
            if (t[j] == '#') {
                tCnt++;
                j--;
                continue;
            }
            if (tCnt > 0) {
                tCnt--;
                j--;
            } else {
                return false;
            }
        } 
    } else if (j < 0) {
        while (i >= 0) {
            if (s[i] == '#') {
                sCnt++;
                i--;
                continue;
            }
            if (sCnt > 0) {
                sCnt--;
                i--;
            } else {
                return false;
            }
        }
    }

    return true;
}

bool backspaceCompare2(string S, string T) {
        int i = S.length() - 1, j = T.length() - 1;
        int skipS = 0, skipT = 0;

        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (S[i] == '#') {
                    skipS++, i--;
                } else if (skipS > 0) {
                    skipS--, i--;
                } else {
                    break;
                }
            }
            while (j >= 0) {
                if (T[j] == '#') {
                    skipT++, j--;
                } else if (skipT > 0) {
                    skipT--, j--;
                } else {
                    break;
                }
            }
            if (i >= 0 && j >= 0) {
                if (S[i] != T[j]) {
                    return false;
                }
            } else {
                if (i >= 0 || j >= 0) {
                    return false;
                }
            }
            i--, j--;
        }
        return true;
   }

int minSubArrayLen(int target, vector<int>& nums) {
    // 法1：暴力，固定一个点，另一个点向前探索，成功后保存路径；将固定点后移后，另一个点从固定点开始继续探索
    // 法2：前缀和+二分：将每个位置对应的前缀加起来形成一个值，则会形成一个前缀和的数组； 依次遍历数组，使用二分查找数组val = arr[i] + target的位置，这个位置-i就是从i开始的最小数组
    // 法3：双指针，滑动窗口； 快指针先去探索，探索到>=target位置停下来，记录快慢指针位置差距，然后慢指针移动，在移动过程中保存差距，直到<target后，再次移动快指针
    int i = 0, j = 0, cnt = 0, res = INT_MAX;
    while (j < nums.size()) {
        cnt += nums[j];
        while (cnt >= target) {     // 当达到target值后，处理i
            res = (res < (j - i + 1)) ? res : (j - i) + 1;
            cnt -= nums[i];
            i++;
        }
        j++;
    }
    return res == INT_MAX ? 0 : res;
}


void test_arr()
{
    cout << "============= test_arr start ==============" << endl;
    //test_binary_search();
    //test_binary_search_and_insert();
    //test_binary_search_repeat_first();
    //test_binary_search_repeat_last();
    
    /*
    cout << test_sqrt(15) << endl;
    cout << test_sqrt(16) << endl;
    cout << test_sqrt(2) << endl;
    cout << test_sqrt_with_precision(5) << endl;
    cout << test_sqrt_with_precision(8) << endl;
    cout << test_sqrt_with_precision(9) << endl;
    cout << test_sqrt_with_precision(16) << endl;
    cout << test_sqrt_with_precision(25) << endl;
    cout << test_sqrt_with_precision(64) << endl;
    cout << test_sqrt_with_precision(81) << endl;
    */
    
    //cout << isPerfectSquare(5) << endl;

    // 数组元素移动
    //test_arr_move();

    //cout << backspaceCompare("c#a#c", "c") << endl;
    //cout << backspaceCompare("abc##cc#", "acbb##") << endl;
    vector<int> vec{2,3,1,2,4,3};
    cout << minSubArrayLen(7, vec) << endl;
    cout << "============= test_arr end ==============" << endl;
}