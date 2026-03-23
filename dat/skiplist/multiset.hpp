// ========================================================
// ■ SkipListMultiSet : 重複を許すソート済集合（MultiSet）で、
//    インデックスアクセス（get(index) など）や lower_bound/upper_bound、
//    count、insert、remove(element)、removeAt(index) などの操作が可能です。
// 各操作は基本 O(logN)（ただし、indexOf や remove(element) は最悪 O(n)）
// ========================================================
template<typename T>
struct SkipListMultiSet {
    static const int MAX_LEVEL = 20;
    
    // 内部ノード（ネストした struct）
    struct Node {
        T value;
        int level;
        array<Node*, MAX_LEVEL> next;
        array<int, MAX_LEVEL> span;  // 各レベルにおいて、このノードから次のノードまでに「飛ばす」要素数
        Node(const T &val, int lvl) : value(val), level(lvl) {
            for (int i = 0; i < MAX_LEVEL; i++){
                next[i] = nullptr;
                span[i] = 0;
            }
        }
    };
    
    Node* head;   // ダミーヘッド。実際のデータは head->next[0] 以降に格納
    int len;      // 要素数
    mt19937 rngs;
    uniform_real_distribution<double> dist;
    
    // コンストラクタ／デストラクタ
    SkipListMultiSet() : len(0), rngs(random_device{}()), dist(0.0, 1.0) {
        head = new Node(T(), MAX_LEVEL);
        for (int i = 0; i < MAX_LEVEL; i++){
            head->span[i] = 1;
        }
    }
    ~SkipListMultiSet(){
        clear();
        delete head;
    }
    void clear(){
        Node* cur = head->next[0];
        while(cur){
            Node* nxt = cur->next[0];
            delete cur;
            cur = nxt;
        }
        for (int i = 0; i < MAX_LEVEL; i++){
            head->next[i] = nullptr;
            head->span[i] = 1;
        }
        len = 0;
    }
    int size() const { return len; }
    
    // 乱数によりレベルを決定（50% の確率で上昇）
    int randomLevel(){
        int lvl = 1;
        while(dist(rngs) < 0.5 && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }
    
    // --- lower_bound(element) ---
    // ソート順で、element 以上となる最初の要素の位置（0-indexed）を返す
    int lower_bound(const T &element) const {
        int index = 0;
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && cur->next[i]->value < element){
                index += cur->span[i];
                cur = cur->next[i];
            }
        }
        return index;
    }
    
    // --- upper_bound(element) ---
    // ソート順で、element より大きい最初の要素の位置（0-indexed）を返す
    int upper_bound(const T &element) const {
        int index = 0;
        Node* cur = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && !(element < cur->next[i]->value)){ // while (cur->next[i]->value <= element)
                index += cur->span[i];
                cur = cur->next[i];
            }
        }
        return index;
    }
    
    // --- count(element) --- 要素 element の出現回数を返す (O(logN))
    int count(const T &element) const {
        return upper_bound(element) - lower_bound(element);
    }
    
    // --- get(index) --- 0-indexed で index 番目の要素を返す (O(logN))
    T get(int index) const {
        if(index < 0 || index >= len)
            throw out_of_range("SkipListMultiSet::get index out of bounds");
        int pos = index + 1;  // ダミーノード補正
        Node* cur = head;
        for(int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && cur->span[i] <= pos){
                pos -= cur->span[i];
                cur = cur->next[i];
            }
        }
        return cur->value;
    }
    
    // --- insert(element) --- 要素をソート済集合に追加（重複を許す）
    // 挿入位置は upper_bound(element) を用いる（既存の同値要素の後ろに挿入）
    void insert(const T &element) {
        int index = upper_bound(element);
        len++;
        int newLevel = randomLevel();
        Node* newNode = new Node(element, newLevel);
        
        Node* update[MAX_LEVEL];
        int rank[MAX_LEVEL];
        Node* cur = head;
        for(int i = MAX_LEVEL - 1; i >= 0; i--){
            if(i == MAX_LEVEL - 1)
                rank[i] = 0;
            else
                rank[i] = rank[i+1];
            while(cur->next[i] && (rank[i] + cur->span[i] <= index)){
                rank[i] += cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        for(int i = 0; i < MAX_LEVEL; i++){
            if(i < newLevel){
                newNode->next[i] = update[i]->next[i];
                update[i]->next[i] = newNode;
                newNode->span[i] = update[i]->span[i] - (index - rank[i]);
                update[i]->span[i] = (index - rank[i]) + 1;
            } else {
                update[i]->span[i]++;
            }
        }
    }
    
    // --- remove(element) --- 指定した要素（最初に見つかったもの）を削除する。
    // 削除に成功すれば true、存在しなければ false を返す。（O(logN) 期待）
    bool remove(const T &element) {
        int idx = lower_bound(element);
        // まず、位置 idx にある要素が element であるかを確認
        Node* cur = head;
        int pos = idx + 1;
        for (int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && cur->span[i] < pos){
                pos -= cur->span[i];
                cur = cur->next[i];
            }
        }
        if (!cur->next[0] || !(cur->next[0]->value == element))
            return false;
        // 以下、削除処理
        Node* update[MAX_LEVEL];
        cur = head;
        pos = idx + 1;
        for (int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && cur->span[i] < pos){
                pos -= cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        Node* target = update[0]->next[0];
        for (int i = 0; i < MAX_LEVEL; i++){
            if (update[i]->next[i] == target){
                update[i]->span[i] += target->span[i] - 1;
                update[i]->next[i] = target->next[i];
            } else {
                update[i]->span[i]--;
            }
        }
        delete target;
        len--;
        return true;
    }
    
    // --- removeAt(index) --- 0-indexed で index 番目の要素を削除し、その値を返す (O(logN))
    T removeAt(int index) {
        if(index < 0 || index >= len)
            throw out_of_range("SkipListMultiSet::removeAt index out of bounds");
        Node* update[MAX_LEVEL];
        Node* cur = head;
        int pos = index + 1;
        for (int i = MAX_LEVEL - 1; i >= 0; i--){
            while(cur->next[i] && cur->span[i] < pos){
                pos -= cur->span[i];
                cur = cur->next[i];
            }
            update[i] = cur;
        }
        Node* target = update[0]->next[0];
        T removed = target->value;
        for (int i = 0; i < MAX_LEVEL; i++){
            if(update[i]->next[i] == target){
                update[i]->span[i] += target->span[i] - 1;
                update[i]->next[i] = target->next[i];
            } else {
                update[i]->span[i]--;
            }
        }
        delete target;
        len--;
        return removed;
    }
    
    // --- indexOf(element) --- 最初に現れる element の位置（なければ -1） (最悪 O(n))
    int indexOf(const T &element) const {
        int idx = lower_bound(element);
        Node* cur = head;
        for (int i = 0; i < idx; i++){
            cur = cur->next[0];
        }
        if(cur->next[0] && cur->next[0]->value == element)
            return idx;
        return -1;
    }
    
    // --- set(index, element) --- （更新後はソート順が変わる可能性があるため、通常はあまり使わない）
    // ここでは、index 番目の要素を削除してから新たに insert(element) する実装です。
    void set(int index, const T &element) {
        T old = get(index);
        // 削除後、再挿入するとソート順は再計算される
        removeAt(index);
        insert(element);
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
};

