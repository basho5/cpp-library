// ========================================================
// ■ SkipList : 順序付きリスト（ArrayList 的なインタフェース）
// 各操作は基本 O(logN)（ただし、contains, remove(element), indexOf は最悪 O(N)）
template<typename T>
struct SkipList {
    static const int MAX_LEVEL = 20; // 最大レベル

    // 内部ノード（ネストした struct）
    struct Node {
        T value;                         // 格納する値
        int level;                       // このノードのレベル（1～MAX_LEVEL）
        array<Node*, MAX_LEVEL> next;    // 各レベルの次のノードへのポインタ
        array<int, MAX_LEVEL> span;      // 各レベルの「飛ばす」要素数（距離）
        Node(const T &val, int lvl) : value(val), level(lvl) {
            for (int i = 0; i < MAX_LEVEL; i++) {
                next[i] = nullptr;
                span[i] = 0;
            }
        }
    };

    // メンバ変数
    Node* head;                          // ダミーヘッド（常に MAX_LEVEL のレベルを持つ）
    int len;                             // 要素数
    mt19937 rngs;                         // 乱数生成器（ランダムレベル決定用）
    uniform_real_distribution<double> dist; // 一様分布 [0,1)
    
    SkipList() : len(0), rngs(random_device{}()), dist(0.0, 1.0) {
        head = new Node(T(), MAX_LEVEL);
        for (int i = 0; i < MAX_LEVEL; i++) {
            head->span[i] = 1;
        }
    }
    ~SkipList() {
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
    }
    int size() const { return len; }
    
    int randomLevel() {
        int lvl = 1;
        while (dist(rngs) < 0.5 && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }
    
    // --- get(index) --- 0-indexed で index 番目の要素を返す (O(logN))
    T get(int index) const {
        if (index < 0 || index >= len)
            throw out_of_range("SkipList::get index out of bounds");
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
    
    // --- set(index, element) --- 0-indexed で index 番目の要素を書き換える (O(logN))
    void set(int index, const T &element) {
        if (index < 0 || index >= len)
            throw out_of_range("SkipList::set index out of bounds");
        int pos = index + 1;
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (cur->next[i] && cur->span[i] <= pos) {
                pos -= cur->span[i];
                cur = cur->next[i];
            }
        }
        cur->value = element;
    }
    
    // --- add(index, element) --- 0-indexed で index 番目の位置に要素を挿入 (O(logN))
    void add(int index, const T &element) {
        if (index < 0 || index > len)
            throw out_of_range("SkipList::add index out of bounds");
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
                rank[i] = rank[i + 1];
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
    }
    
    // --- add(element) --- 末尾に追加 (O(logN))
    void add(const T &element) {
        add(len, element);
    }
    
    // --- remove(index) --- 0-indexed で index 番目の要素を削除し、その値を返す (O(logN))
    T erase(int index) {
        if (index < 0 || index >= len)
            throw out_of_range("SkipList::removeAt index out of bounds");
        len--;
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
        return removed;
    }
    
    // --- remove(element) --- 指定した要素（最初に見つかったもの）を削除 (見つからなければ false) ※最悪 O(n)
    bool remove(const T &element) {
        int idx = indexOf(element);
        if (idx == -1)
            return false;
        erase(idx);
        return true;
    }
    
    // --- indexOf(element) --- 要素の最初の出現位置（見つからなければ -1） ※最悪 O(n)
    int indexOf(const T &element) const {
        int index = 0;
        Node* cur = head->next[0];
        while (cur) {
            if (cur->value == element)
                return index;
            index++;
            cur = cur->next[0];
        }
        return -1;
    }
    
    // --- contains(element) --- 要素が含まれているか ※最悪 O(n)
    bool contains(const T &element) const {
        return indexOf(element) != -1;
    }
    
    // --- iterator (level0 を辿る) ---
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

     // --- operator[] オーバーロード ---
    // 非const版
    T& operator[](int index) {
        if (index < 0 || index >= len)
            throw std::out_of_range("SkipList::operator[] index out of bounds");
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

    // const版
    const T& operator[](int index) const {
        if (index < 0 || index >= len)
            throw std::out_of_range("SkipList::operator[] index out of bounds");
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


};
