enum DIR { L, R };
 
template<typename T>
struct cartesian_tree {
    static cartesian_tree<T> *sentinel;
    T key = T();
    int priority = 0, size = 0, reverse = false;
    cartesian_tree *child[2];
 
    cartesian_tree() {
        child[L] = child[R] = this;
    }
 
    cartesian_tree(const T &x, int y) : key(x), priority(y) {
        size = 1;
        child[L] = child[R] = sentinel;
    }
 
    void push_down() {
        if (!reverse) return;
        reverse = 0;
        swap(child[L], child[R]);
        child[L]->doReverse();
        child[R]->doReverse();
    }
    void doReverse() {
        reverse ^= 1;
    }
 
    void push_up() {
        size = child[L]->size + child[R]->size + 1;
    }
};
 
 
template<typename T>
cartesian_tree<T> *cartesian_tree<T>::sentinel = new cartesian_tree<T>();
 
template<typename T, template<typename > class cartesian_tree>
class implicit_treap {
    //1 based
    typedef cartesian_tree<T> node;
    typedef cartesian_tree<T> *nodeptr;
#define emptyNode cartesian_tree<T>::sentinel
    nodeptr root;
 
    void split(nodeptr root, nodeptr &l, nodeptr &r, int firstXElment) {
        if (root == emptyNode) {
            l = r = emptyNode;
            return;
        }
        root->push_down();
        if (firstXElment <= root->child[L]->size) {
            split(root->child[L], l, root->child[L], firstXElment);
            r = root;
        } else {
            split(root->child[R], root->child[R], r,
                  firstXElment - root->child[L]->size - 1);
 
            l = root;
        }
        root->push_up();
    }
 
    nodeptr merge(nodeptr l, nodeptr r) {
        l->push_down();
        r->push_down();
        if (l == emptyNode || r == emptyNode)
            return (l == emptyNode ? r : l);
        if (l->priority > r->priority) {
            l->child[R] = merge(l->child[R], r);
            l->push_up();
            return l;
        }
        r->child[L] = merge(l, r->child[L]);
        r->push_up();
        return r;
    }
 
    vector<nodeptr> split_range(int s, int e) {
        // [x<s,s<=x<=e,e<x]
        nodeptr l, m, r, tmp;
        split(root, l, tmp, s - 1);
        split(tmp, m, r, e - s + 1);
        return {l, m, r};
    }
 
public:
    implicit_treap() : root(emptyNode) {
    }
 
    int size() {
        return root->size;
    }
 
 
    void insert(int pos, const T &key) {
        nodeptr tmp = new node(key, rand());
        nodeptr l, r;
        split(root, l, r, pos - 1);
        root = merge(merge(l, tmp), r);
    }
 
    void push_back(const T &value) {
        root = merge(root, new node(value, rand()));
    }
 
    T getByIndex(int pos) {
        vector<nodeptr> tmp = split_range(pos, pos);
        nodeptr l = tmp[0], m = tmp[1], r = tmp[2];
        m->push_down();
        T rt = m->key;
        root = merge(merge(l, m), r);
        return rt;
    }
 
    void erase(int pos) {
        vector<nodeptr> tmp = split_range(pos, pos);
        nodeptr l = tmp[0], m = tmp[1], r = tmp[2];
        delete m;
        root = merge(l, r);
    }
 
    void cyclic_shift(int s, int e) {
        //to the right
        vector<nodeptr> tmp = split_range(s, e);
        nodeptr l = tmp[0], m = tmp[1], r = tmp[2];
        nodeptr first, second;
        split(m, first, second, e - s);
        root = merge(merge(merge(l, second), first), r);
    }
 
    void reverse_range(int s, int e) {
        vector<nodeptr> tmp = split_range(s, e);
        nodeptr l = tmp[0], m = tmp[1], r = tmp[2];
        if (m != emptyNode) {
            m->reverse ^= 1;
        }
        root = merge(merge(l, m), r);
    }
 
    node range_query(int s, int e) {
        vector<nodeptr> tmp = split_range(s, e);
        nodeptr l = tmp[0], m = tmp[1], r = tmp[2];
        m->push_down();
        node rt = *m;
        root = merge(merge(l, m), r);
        return rt;
    }
};
 
