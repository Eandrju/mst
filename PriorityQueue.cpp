#include "PriorityQueue.h"

bool PriorityQueue::IsEmpty() {
    std::cout << "ja pierdole\n";
    return false;
}

void PriorityQueue::DecreaseKey(int, int) {
    std::cout << "ja pierdole\n";
}

heapNode PriorityQueue::FindNode(int) {
    heapNode a;
    std::cout << "ja pierdole\n";
    return a;
}

heapNode PriorityQueue::ExtractMin() {
    heapNode a;
    std::cout << "ja pierdole\n";
    return a;
}

PriorityQueueBH::PriorityQueueBH(int n, bool verbose) {
    this->verbose_ = verbose;
    for(int i = 0; i < n; i++) {
        heapNode foo;
        foo.vertex = i;
        foo.weight = INT32_MAX;
        this->heap.push_back(foo);
        this->position.push_back(i);
    }
    this->HeapifyDown();

    if (this->verbose_) {
        std::cout << "after initalization\n";
        this->HeapValidation(0);
    }
}

PriorityQueueBH::PriorityQueueBH() {
}

bool PriorityQueueBH::IsEmpty() {
    return this->heap.size() == 0;
}

heapNode PriorityQueueBH::FindNode(int vertex) {
    int index;
    index = this->position[vertex];
    if (index == -1) {
        heapNode result = {-1 , -1};
        return result;
    }
    else {
        return this->heap[index];
    }
}


heapNode PriorityQueueBH::ExtractMin() {
    heapNode peak = this->heap[0];
    this->heap[0] = this->heap[this->heap.size() - 1];
    this->heap.pop_back();
    this->position[peak.vertex] = -1;
    this->position[this->heap[0].vertex]= 0;
    this->HeapifyDown();

    if (this->verbose_) {
        std::cout << "after extractmin\n";
        this->HeapValidation(0);
    }
    return peak;

}


void PriorityQueueBH::HeapifyDown() {
    int i = 0;
    // left, right, parent
    heapNode l, r, p;

    while (2*i + 1 < this->heap.size()) {
        p = this->heap[i]; 
        l = this->heap[2*i + 1];
        if (2*i + 2 < this->heap.size())
            r = this->heap[2*i + 2]; 
        else 
            r.weight = INT32_MAX;

        // left child is the smallest
        if (l.weight <= r.weight && l.weight <= p.weight) {
            std::swap(this->heap[i], this->heap[2*i + 1]);
            this->position[l.vertex] = i;
            this->position[p.vertex] = 2*i + 1;
            i = 2*i + 1;
        }
        // right child is the smallest
        else if (r.weight <= l.weight && r.weight <= p.weight) {
            std::swap(this->heap[i], this->heap[2*i + 2]);
            this->position[r.vertex] = i;
            this->position[p.vertex] = 2*i + 2;               
            i = 2*i + 2;
        }
        // parent is in the correct position
        else break;
    }
}

void PriorityQueueBH::DecreaseKey(int vertex, int newWeight) {
    int index = this->position[vertex];
    this->heap[index].weight = newWeight;
    this->HeapifyUp(index); 
}
    
void PriorityQueueBH::HeapifyUp(int i) {
    // child, parent
    heapNode c, p;
    c = this->heap[i];
    p = this->heap[(i-1)/2];
    if (i!= 0 && c.weight < p.weight) {
        std::swap(this->heap[i], this->heap[(i-1)/2]);
        std::swap(this->position[c.vertex], this->position[p.vertex]);
        this->HeapifyUp((i-1)/2);
    }

}
     

bool PriorityQueueBH::HeapValidation(int idx) { 
    int n;
    n = this->heap.size();
    std::string trash;
    for (int i=0; i<=(n-2)/2; i++) 
    { 
        // If left child is greater, return false 
        if (this->heap[2*i +1].weight < this->heap[i].weight) {
            std::cout << "failed at vortex: " << i<< "\n";
            std::cout << "2*i+ 1 " << 2*i + 1 << "\n";
            std::cout << this->heap[i].weight << " < " << this->heap[2*i+ 1].weight << "\n";
            std::cin >> trash;
            return false; 
        }
  
        // If right child is greater, return false 
        if (2*i+2 < n && this->heap[2*i+2].weight < this->heap[i].weight) {
            std::cout << "failed at vortex: " << i<< "\n";
            std::cout << "2*i+ 2 " << 2*i + 2 << "\n";
            std::cout << this->heap[i].weight << " < " << this->heap[2*i+ 2].weight << "\n";
            std::cin >>trash;
            return false; 
        }
    } 
    return true; 
} 


// ------------ PRIORITY QUEUE - FIBONACHI HEAP -----------------------------------
//
void checkChildren(fibNode* r) {
    fibNode* c;
    int deg, i;

    c = r->child; 
    deg = r->degree;
    i = 1;

    
    std::string trash;
    if (c == NULL)
        return;
    do {
        if (i > deg) {
            std::cout << "degree of " << r->vertex << " isn't updated, or list closed\n";
            std::cout << "degree is " << deg << " and I alredy check "<< i << " child\n";
            std::cin >> trash;
        }
        if (c->parent != r) {
            std::cout << c->vertex << " has wrong pointer for parent\n";
            std::cin >> trash;
        }
        if (c->right->left != c) {
            std::cout << c->right->vertex << " has wrong pointer for left\n";
            std::cin >> trash;
        }
        if (c->left->right != c) {
            std::cout << c->left->vertex << " has wrong pointer for right\n";
            std::cin >> trash;
        }
        checkChildren(c);
        c = c->right;
        i++;
    } while (c != r->child);
}

void checkTree(fibNode*& r) {
    fibNode* dummy;
    dummy = r;
    std::string trash;
    if (r == NULL)
        return;

    do { 
        if (dummy != dummy->right->left) {
            std::cout << dummy->vertex << " has wrong right\n";
        }
        if (dummy->parent != NULL) {
            std::cout << dummy->vertex << "parent doesnt point to NULL\n"; 
            std::cin >> trash;
        }
        //checkChildren(dummy);
        dummy = dummy->right;
        if (dummy->weight < r->weight) {
            std::cout << dummy->weight << " "<< dummy->vertex << "has lower minimal value\n";
            std::cin >> trash;
            //r = dummy;
        }
    } while (dummy != r);
}
    
    
PriorityQueueFH::PriorityQueueFH(int n, bool verbose) {
    this->verbose_ = verbose;
    this->n_decKey = 0;
    this->numberOfNodes = 0;
    this->minimum = NULL;
    this->counter = 0;
    this->verbose2 = false;
    for (int i = 0; i < n; i++)
        this->Insert(i, INT32_MAX);
    
}

heapNode PriorityQueueFH::FindNode(int vertex) {
    heapNode result;
    fibNode* node;
    node = this->vertexToNodeMap[vertex];
    if (node == NULL) {
        result.weight = -1;
        result.vertex = -1;
    }
    else {
        result.weight = node->weight;
        result.vertex = node->vertex;
    }
    return result;
}

void PriorityQueueFH::Insert(int vertex, int weight) {
    fibNode* node;
    node = new fibNode;
    node->weight = weight;
    node->parent = NULL;
    node->child = NULL;
    node->degree = 0;
    node->left = node; 
    node->right = node;
    node->marked = false;
    node->vertex = vertex;
    this->vertexToNodeMap[vertex] = node;

    // add node to rootList
    if (this->minimum != NULL) {
        this->minimum->right->left = node;
        node->right = this->minimum->right;
        node->left = this->minimum;
        this->minimum->right = node;
    }
    if (this->minimum == NULL || weight < this->minimum->weight) {
        this->minimum = node;
    }
    this->numberOfNodes += 1;
    
}

void PriorityQueueFH::FibHeapLink(fibNode* c, fibNode* p) {
    //std::cout << "fibHeapLink\n";
    //this->Visualize();
    //checking whether removed node was minimum
    if (this->minimum == c) {
        this->minimum = p;
    }
    
    c->left->right = c->right;
    c->right->left = c->left;
    

    // adding c to p's children
    if (p->child == NULL) {
        c->right = c;
        c->left = c;
        p->child = c;
    }
    else {
        //std::cout << (p->child->right->left == NULL) << "\n";
        p->child->right->left = c;
        c->right = p->child->right;
        c->left = p->child;
        p->child->right = c;
    }
    c->parent = p;
    p->degree += 1;
    c->marked = false;
    //std::cout << "after fibheaplink\n";
    //this->Visualize();
}





void PriorityQueueFH::Consolidate() {
    //std::cout << "entered consolidate\n";
    //this->Visualize();
    std::unordered_map<int, fibNode*> A;

    fibNode *x, *y, *head, *next;
    int deg;
    x = this->minimum;
    head = this->minimum;

    do { 
        deg = x->degree;
        next = x->right;
        //std::cout << "head: " << head->vertex << " x: " << x->vertex << " next: " << next->vertex << "\n";
        //this->n_decKey++;

        if (x->weight < this->minimum->weight) {
            this->minimum = x;
        }
        

        while (A.count(deg)) {
            this->n_decKey++;

            y = A[deg];

            if (x->weight > y->weight) {
                std::swap(x, y); 
            }

            if (y == head)
                head = y->right;

            if (y == next)
                next = y->right;

            this->FibHeapLink(y, x);
            A.erase(deg);
            deg += 1;
        }

        A[deg] = x;
        x = next;
    }
    while (head != x);
}
      

heapNode PriorityQueueFH::ExtractMin() {
    //std::cout << "entered extractMin\n";
    fibNode* z;
    z = this->minimum;
    if (z != NULL) {
        this->vertexToNodeMap[z->vertex] = NULL;

        // setting child->parent := NULL for every child of minimum 
        fibNode* dummy;
        dummy = z->child;
        if (dummy != NULL) {
            do {
                dummy->parent = NULL;
                dummy = dummy->right;
            } while (dummy != z->child);
        }
        
       if (z->child != NULL ) {
            if (z->right != z) {
                z->left->right = z->child->right;
                z->right->left = z->child;
                z->child->right->left = z->left;
                z->child->right = z->right;
                this->minimum = z->right; 
                this->Consolidate();
            }
            else {
                this->minimum = z->child;
                this->Consolidate();
            }
        }
        else {
            if (z->right != z) {
                this->minimum->right->left = this->minimum->left;
                this->minimum->left->right = this->minimum->right;
                this->minimum = z->right; 
                this->Consolidate();
            }
            else {
                this->minimum = NULL;
            }
        }
        this->numberOfNodes -= 1;
    }

    heapNode result;

    result.vertex = z->vertex;
    result.weight = z->weight;
 
    delete z;
    return result;
}


fibNode* PriorityQueueFH::GetNode(int vertex) {
    return this->vertexToNodeMap[vertex];
}

bool PriorityQueueFH::IsEmpty() {
    return (this->minimum == NULL);
}


void PriorityQueueFH::Cut(fibNode* c, fibNode* p) {
    this->n_cut++;
    // remove c from p's child list
    if (c->right == c) {
        p->child = NULL;
    } 
    else {
        p->child = c->right;
        c->right->left = c->left;
        c->left->right = c->right;
    }
    p->degree -= 1;

    // add c to root list
    c->parent = NULL;
    this->minimum->right->left = c;
    c->right = this->minimum->right;
    this->minimum->right = c;
    c->left = this->minimum;

    c->marked = false;
    
    //update minimum if necessery
    if (c->weight < this->minimum->weight) {
        this->minimum = c;
    }
}

void PriorityQueueFH::CascadingCut(fibNode* n) {
    this->n_cassCut++;
    fibNode *p;
    p = n->parent;
    if (p != NULL) {
        if (n->marked == false) {
            n->marked = true;
        }
        else {
            this->Cut(n, p);
            this->CascadingCut(p);
        }
    }
}

void PriorityQueueFH::DecreaseKey(int vertex, int newWeight) {
    //this->n_decKey++;

    fibNode *n, *p;
    n = this->GetNode(vertex);
        
    n->weight = newWeight;
    
    p = n->parent;
    if (p != NULL && n->weight < p->weight) {
        this->Cut(n, p);
        this->CascadingCut(p);
    }

    // updating minimum
    if (n->weight < this->minimum->weight && p == NULL)
        this->minimum = n;

    //std::cout << "decresed key of " << vertex << "\n";
    //this->Visualize();
}


void v(fibNode* node, std::string pre, int level) {
    std::string pc = "│ ";
    fibNode* x = node;

    while (true) {
        if (x->right != node) {
            std::cout << pre << "├─";
        }
        else {
            std::cout << pre << "└─";
            pc = "  ";
        }

        if (x->child == NULL) {
            std::cout << "╴ w" << x->weight << " v" << x->vertex << " d" << x->degree;
            if (x->marked) std::cout << "*";
            if (x->child == NULL) std::cout << " c";
            if (x->parent== NULL) std::cout << " r";
            std::cout << "\n";
        }
        else {
            std::cout << "┐ w" << x->weight << " v" << x->vertex << " d" << x->degree;
            if (x->marked) std::cout << "*";
            if (x->child== NULL) std::cout << " c";
            if (x->parent== NULL) std::cout << " r";
            std::cout << "\n";
            v(x->child, pre + pc, level+1);
        }

        if (x->right == node)
            break;
        x = x->right;
    }
}

void PriorityQueueFH::Visualize() {
    if (this->minimum == NULL) {
        std::cout << "<empty>\n";
    }
    else {
        std::cout << "minimum: " << this->minimum->vertex << "\n";
        v(this->minimum, "", 0);
    }
    checkTree(this->minimum);
    std::string trash;
    std::cin >> trash;
}
