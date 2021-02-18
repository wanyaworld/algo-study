class LRUCache {
public:
  
    list<int> lru{};
    unordered_map<int, int> kv{};
    int rem_cap{};
    
    LRUCache(int capacity) {
        rem_cap = capacity;

    }
    
    void del() {
        int key = lru.back();
        lru.pop_back();
        kv.erase(key);
    }
    int get(int key) {
        for (auto it = lru.begin() ; it != lru.end() ; it++) {
            if (*it == key) {
                lru.erase(it);
                lru.push_front(key);
                return kv[key];
            }
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (kv.find(key) != kv.end()) {
            for (auto it = lru.begin() ; it != lru.end() ; it++) {
                if (*it == key) {
                    lru.erase(it);
                    break;
                }
            }
            lru.push_front(key);
            kv[key] = value;
            return;
        }
        if (rem_cap <= 0) del();
        lru.push_front(key);
        kv[key] = value;
        rem_cap--;
        
    }
    
  
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
