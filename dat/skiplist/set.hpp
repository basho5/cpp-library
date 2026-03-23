// ========================================================
// ■ SkipListSet : ソート済集合（重複を許さず、キー順に管理）
// contains(element) は内部ハッシュテーブルにより O(1) で実現、その他の操作は O(logN)
template<typename T>
struct SkipListSet {
    static const int MAX_LEVEL = 20;
    
    // 内部ノード（ネストした struct）
    struct Node {
        T value;
        int level;
        array<Node*, MAX_LEVEL> next;
        array<int, MAX_LEVEL> span;
        Node(const T &val, int lvl) : value(val), level(lvl) {
            for (int i = 0; i < MAX_LEVEL; i++) {
                next[i] = nullptr;
                span[i] = 0;
            }
        }
    };
    
    Node* head;
    int len;
    mt19937 rngs;
    uniform_real_distribution<double> dist;
    unordered_set<T> hashSet;  // 補助：要素の存在判定を O(1) にする
     
    SkipListSet() : len(0), rngs(random_device{}()), dist(0.0, 1.0) {
        head = new Node(T(), MAX_LEVEL);
        for (int i = 0; i < MAX_LEVEL; i++) {
            head->span[i] = 1;
        }
    }
    ~SkipListSet() {
        clear();
        delete head;
    }
    void clear() {
        Node* cur = head->next[0];
        while (cur) {
            Node* nxt = cur->next[0];
            delete cur;
            cur = nxt;
        }
        for (int i = 0; i < MAX_LEVEL; i++) {
            head->next[i] = nullptr;
            head->span[i] = 1;
        }
        len = 0;
        hashSet.clear();
    }
    int size() const { return len; }
    int randomLevel() {
        int lvl = 1;
        while (dist(rngs) < 0.5 && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }
    
    // --- lower_bound(element) --- 挿入すべき位置（0-indexed）を返す (O(logN))
    int lower_bound(const T &element) const {
        int index = 0;
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (cur->next[i] && cur->next[i]->value < element) {
                index += cur->span[i];
                cur = cur->next[i];
            }
        }
        return index;
    }
    
    // --- indexOf(element) --- 要素の位置（存在しなければ -1） (O(logN) 期待)
    int indexOf(const T &element) const {
        int idx = lower_bound(element);
        Node* cur = head;
        for (int i = 0; i < idx; i++) {
            cur = cur->next[0];
        }
        if (cur->next[0] && cur->next[0]->value == element)
            return idx;
        return -1;
    }
    
    // --- contains(element) --- 内部ハッシュにより O(1)
    bool contains(const T &element) const {
        return hashSet.find(element) != hashSet.end();
    }
    
    // --- get(index) --- 0-indexed で index 番目の要素を返す (O(logN))
    T get(int index) const {
        if (index < 0 || index >= len)
            throw out_of_range("SkipListSet::get index out of bounds");
        int pos = index + 1;
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (cur->next[i] && cur->span[i] <= pos) {
                pos -= cur->span[i];
                cur = cur->next[i];
            }
        }
        return cur->value;
    }
    
    // --- add(element) --- ソート済集合へ要素を追加（既にあれば何もしない） (O(logN))
    bool add(const T &element) {
        if (contains(element))
            return false;
        int index = lower_bound(element);
        len++;
        int newLevel = randomLevel();
        Node* newNode = new Node(element, newLevel);
        
        Node* update[MAX_LEVEL];
        int rank[MAX_LEVEL];
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            if (i == MAX_LEVEL - 1)
                rank[i] = 0;
            else
                rank[i] = rank[i+1];
            while (cur->next[i] && (rank[i] + cur->span[i] <= index)) {
                rank[i] += cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        for (int i = 0; i < MAX_LEVEL; i++) {
            if (i < newLevel) {
                newNode->next[i] = update[i]->next[i];
                update[i]->next[i] = newNode;
                newNode->span[i] = update[i]->span[i] - (index - rank[i]);
                update[i]->span[i] = (index - rank[i]) + 1;
            } else {
                update[i]->span[i]++;
            }
        }
        hashSet.insert(element);
        return true;
    }
    
    // --- remove(element) --- 指定した要素を削除（存在しなければ false） (O(logN))
    bool remove(const T &element) {
        if (!contains(element))
            return false;
        int index = lower_bound(element);
        Node* update[MAX_LEVEL];
        Node* cur = head;
        int pos = index + 1;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (cur->next[i] && cur->span[i] < pos) {
                pos -= cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        Node* target = update[0]->next[0];
        if (!target || !(target->value == element))
            return false;
        for (int i = 0; i < MAX_LEVEL; i++) {
            if (update[i]->next[i] == target) {
                update[i]->span[i] += target->span[i] - 1;
                update[i]->next[i] = target->next[i];
            } else {
                update[i]->span[i]--;
            }
        }
        delete target;
        len--;
        hashSet.erase(element);
        return true;
    }
    
    // --- remove(index) --- 0-indexed で index 番目の要素を削除し、その値を返す (O(logN))
    T removeAt(int index) {
        if (index < 0 || index >= len)
            throw out_of_range("SkipListSet::removeAt index out of bounds");
        Node* update[MAX_LEVEL];
        Node* cur = head;
        int pos = index + 1;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (cur->next[i] && cur->span[i] < pos) {
                pos -= cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        Node* target = update[0]->next[0];
        T removed = target->value;
        for (int i = 0; i < MAX_LEVEL; i++) {
            if (update[i]->next[i] == target) {
                update[i]->span[i] += target->span[i] - 1;
                update[i]->next[i] = target->next[i];
            } else {
                update[i]->span[i]--;
            }
        }
        delete target;
        len--;
        hashSet.erase(removed);
        return removed;
    }
    
    // --- set(index, element) --- （更新後はソート順が変わる可能性があるため通常は使わない）  
    // ここでは、index 番目の要素を削除してから add(element) する実装です。
    bool set(int index, const T &element) {
        if (index < 0 || index >= len)
            throw out_of_range("SkipListSet::set index out of bounds");
        T old = get(index);
        if (old == element)
            return true;
        remove(old);
        return add(element);
    }
    
    // --- iterator ---
    struct iterator {
        Node* node;
        iterator(Node* n) : node(n) {}
        T& operator*() { return node->value; }
        iterator& operator++() {
            node = node->next[0];
            return *this;
        }
        bool operator!=(const iterator &other) const {
            return node != other.node;
        }
    };
    iterator begin() { return iterator(head->next[0]); }
    iterator end() { return iterator(nullptr); }
};
