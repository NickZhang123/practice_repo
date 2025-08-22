#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <cstring>

// 节点容量常量
constexpr int MAX_NODE4 = 4;
constexpr int MAX_NODE16 = 16;
constexpr int MAX_NODE48 = 48;
constexpr int MAX_NODE256 = 256;

// 基础节点类
struct Node {
    int type;        // 节点类型 (4, 16, 48, 256)，特殊值 -1 表示叶子节点
    int numChildren; // 子节点数量
    virtual ~Node() = default; // 确保派生类的正确析构
};

// Node4: 最多存储 4 个子节点
struct Node4 : public Node {
    std::array<uint8_t, MAX_NODE4> keys;                  // 存储子节点的键
    std::array<std::shared_ptr<Node>, MAX_NODE4> children; // 存储子节点指针

    Node4() {
        type = MAX_NODE4;
        numChildren = 0;
    }
};

// Node16: 最多存储 16 个子节点
struct Node16 : public Node {
    std::array<uint8_t, MAX_NODE16> keys;                  // 存储子节点的键
    std::array<std::shared_ptr<Node>, MAX_NODE16> children; // 存储子节点指针

    Node16() {
        type = MAX_NODE16;
        numChildren = 0;
    }
};

// Node48: 最多存储 48 个子节点
struct Node48 : public Node {
    std::array<int8_t, 256> childIndex;                    // 索引数组：键 -> 子节点索引
    std::array<std::shared_ptr<Node>, MAX_NODE48> children; // 存储子节点指针

    Node48() {
        type = MAX_NODE48;
        numChildren = 0;
        childIndex.fill(-1); // 初始化为无效值
    }
};

// Node256: 最多存储 256 个子节点
struct Node256 : public Node {
    std::array<std::shared_ptr<Node>, MAX_NODE256> children; // 直接存储所有子节点

    Node256() {
        type = MAX_NODE256;
        numChildren = 0;
    }
};

// 叶子节点：用于存储实际值
struct LeafNode : public Node {
    int value;

    LeafNode(int val) : value(val) {
        type = -1;
        numChildren = 0;
    }
};

// 自适应基数树类
class AdaptiveRadixTree {
private:
    std::shared_ptr<Node> root;

    // 将 Node4 扩展到 Node16
    std::shared_ptr<Node16> upgradeToNode16(const std::shared_ptr<Node4>& node4) {
        auto node16 = std::make_shared<Node16>();
        node16->numChildren = node4->numChildren;

        for (int i = 0; i < node4->numChildren; ++i) {
            node16->keys[i] = node4->keys[i];
            node16->children[i] = node4->children[i];
        }

        return node16;
    }

    // 将 Node16 扩展到 Node48
    std::shared_ptr<Node48> upgradeToNode48(const std::shared_ptr<Node16>& node16) {
        auto node48 = std::make_shared<Node48>();
        node48->numChildren = node16->numChildren;

        for (int i = 0; i < node16->numChildren; ++i) {
            node48->childIndex[node16->keys[i]] = i;
            node48->children[i] = node16->children[i];
        }

        return node48;
    }

    // 将 Node48 扩展到 Node256
    std::shared_ptr<Node256> upgradeToNode256(const std::shared_ptr<Node48>& node48) {
        auto node256 = std::make_shared<Node256>();
        node256->numChildren = node48->numChildren;

        for (int i = 0; i < 256; ++i) {
            if (node48->childIndex[i] != -1) {
                node256->children[i] = node48->children[node48->childIndex[i]];
            }
        }

        return node256;
    }

    // 插入递归函数
    std::shared_ptr<Node> insertRec(std::shared_ptr<Node> node, const uint8_t* key, int depth, int keyLen, int value) {
        if (!node) return std::make_shared<LeafNode>(value); // 空节点，创建叶子节点

        // 如果是叶子节点，替换值
        if (node->type == -1) return std::make_shared<LeafNode>(value);

        // 根据节点类型插入
        if (node->type == MAX_NODE4) {
            auto n4 = std::static_pointer_cast<Node4>(node);

            // 检查键是否已存在
            for (int i = 0; i < n4->numChildren; ++i) {
                if (n4->keys[i] == key[depth]) {
                    n4->children[i] = insertRec(n4->children[i], key, depth + 1, keyLen, value);
                    return n4;
                }
            }

            // 插入新键值对
            if (n4->numChildren < MAX_NODE4) {
                n4->keys[n4->numChildren] = key[depth];
                n4->children[n4->numChildren] = insertRec(nullptr, key, depth + 1, keyLen, value);
                n4->numChildren++;
                return n4;
            }

            // 升级到 Node16
            auto n16 = upgradeToNode16(n4);
            return insertRec(n16, key, depth, keyLen, value);
        }

        if (node->type == MAX_NODE16) {
            auto n16 = std::static_pointer_cast<Node16>(node);

            for (int i = 0; i < n16->numChildren; ++i) {
                if (n16->keys[i] == key[depth]) {
                    n16->children[i] = insertRec(n16->children[i], key, depth + 1, keyLen, value);
                    return n16;
                }
            }

            if (n16->numChildren < MAX_NODE16) {
                n16->keys[n16->numChildren] = key[depth];
                n16->children[n16->numChildren] = insertRec(nullptr, key, depth + 1, keyLen, value);
                n16->numChildren++;
                return n16;
            }

            auto n48 = upgradeToNode48(n16);
            return insertRec(n48, key, depth, keyLen, value);
        }

        if (node->type == MAX_NODE48) {
            auto n48 = std::static_pointer_cast<Node48>(node);

            if (n48->childIndex[key[depth]] != -1) {
                n48->children[n48->childIndex[key[depth]]] = insertRec(n48->children[n48->childIndex[key[depth]]], key, depth + 1, keyLen, value);
                return n48;
            }

            if (n48->numChildren < MAX_NODE48) {
                n48->childIndex[key[depth]] = n48->numChildren;
                n48->children[n48->numChildren] = insertRec(nullptr, key, depth + 1, keyLen, value);
                n48->numChildren++;
                return n48;
            }

            auto n256 = upgradeToNode256(n48);
            return insertRec(n256, key, depth, keyLen, value);
        }

        if (node->type == MAX_NODE256) {
            auto n256 = std::static_pointer_cast<Node256>(node);
            n256->children[key[depth]] = insertRec(n256->children[key[depth]], key, depth + 1, keyLen, value);
            if (!n256->children[key[depth]]) n256->numChildren++;
            return n256;
        }

        return nullptr;
    }

    // 查找递归函数
    std::shared_ptr<Node> searchRec(std::shared_ptr<Node> node, const uint8_t* key, int depth, int keyLen) const {
        if (!node) return nullptr;

        if (node->type == -1) return node;

        if (node->type == MAX_NODE4) {
            auto n4 = std::static_pointer_cast<Node4>(node);
            for (int i = 0; i < n4->numChildren; ++i) {
                if (n4->keys[i] == key[depth]) {
                    return searchRec(n4->children[i], key, depth + 1, keyLen);
                }
            }
            return nullptr;
        }

        if (node->type == MAX_NODE16) {
            auto n16 = std::static_pointer_cast<Node16>(node);
            for (int i = 0; i < n16->numChildren; ++i) {
                if (n16->keys[i] == key[depth]) {
                    return searchRec(n16->children[i], key, depth + 1, keyLen);
                }
            }
            return nullptr;
        }

        if (node->type == MAX_NODE48) {
            auto n48 = std::static_pointer_cast<Node48>(node);
            if (n48->childIndex[key[depth]] != -1) {
                return searchRec(n48->children[n48->childIndex[key[depth]]], key, depth + 1, keyLen);
            }
            return nullptr;
        }

        if (node->type == MAX_NODE256) {
            auto n256 = std::static_pointer_cast<Node256>(node);
            return searchRec(n256->children[key[depth]], key, depth + 1, keyLen);
        }

        return nullptr;
    }

public:
    AdaptiveRadixTree() : root(nullptr) {}

    void insert(const std::string& key, int value) {
        root = insertRec(root, reinterpret_cast<const uint8_t*>(key.c_str()), 0, key.length(), value);
    }

    int search(const std::string& key) const {
        auto node = searchRec(root, reinterpret_cast<const uint8_t*>(key.c_str()), 0, key.length());
        if (node && node->type == -1) {
            return std::static_pointer_cast<LeafNode>(node)->value;
        }
        return -1;
    }
};

int main2() {
    AdaptiveRadixTree art;

    art.insert("hello", 1);
    art.insert("world", 2);
    art.insert("adaptive", 3);
    art.insert("radix", 4);
    art.insert("tree", 5);

    std::cout << "Search 'hello': " << art.search("hello") << std::endl;
    std::cout << "Search 'world': " << art.search("world") << std::endl;
    std::cout << "Search 'adaptive': " << art.search("adaptive") << std::endl;
    std::cout << "Search 'radix': " << art.search("radix") << std::endl;
    std::cout << "Search 'tree': " << art.search("tree") << std::endl;
    std::cout << "Search 'missing': " << art.search("missing") << std::endl;

    return 0;
}
