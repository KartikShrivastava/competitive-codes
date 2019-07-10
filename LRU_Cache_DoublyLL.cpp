struct Node{
    int key;
    int value;
    Node* next;
    Node* prev;
    Node(int x, int y){
        key=x;
        value=y;
        next=NULL;
        prev=NULL;
    }
};

struct Dequeue{
public:
    int capacity;
    int size;
    Node* rear;
    Node* front;
    void SetCapacity(int x){
        capacity=x;
    }
};

Dequeue dq;

LRUCache::LRUCache(int N){
    dq.capacity=N;
    dq.size=0;
    dq.front=NULL;
    dq.rear=NULL;
}


/*Sets the key x with value y in the LRU cache */
void LRUCache::set(int x, int y){
    Node* curr=dq.rear;
    bool found=false;
    while(curr!=NULL){
        if(curr->key == x){
            found=true;
            break;
        }
        curr=curr->prev;
    }
    if(found){
        if(curr==dq.rear){
            dq.rear->value=y;
        }
        else if(curr==dq.front){
            dq.front=dq.front->next;
            dq.front->prev=NULL;
            dq.rear->next=curr;
            curr->prev=dq.rear;
            curr->next=NULL;
            dq.rear=curr;
            dq.rear->value=y;
        }
        else{
            Node* prev=curr->prev;
            Node* next=curr->next;
            prev->next=next;
            next->prev=prev;
            dq.rear->next=curr;
            curr->prev=dq.rear;
            curr->next=NULL;
            dq.rear=curr;
            dq.rear->value=y;
        }
    }
    else if(dq.size==dq.capacity){//remove front and insert at rear
        Node* temp = new Node(x,y);
        Node* oldFront = dq.front;
        dq.front=dq.front->next;
        if(dq.front==NULL){
            dq.front=dq.rear=temp;
        }
        else{
            dq.front->prev=NULL;
            dq.rear->next=temp;
            temp->prev=dq.rear;
            dq.rear=temp;
        }
        delete oldFront;
        //cout<<"if:"<<temp->key<<" ";
        //cout<<"s:"<<dq.size<<" ";
    }
    else{
        Node* temp = new Node(x,y);
        if(dq.front==NULL || dq.rear==NULL){
            dq.front=dq.rear=temp;
        }
        else{
            dq.rear->next=temp;
            temp->prev=dq.rear;
            dq.rear=temp;
        }
        dq.size++;
        //cout<<"i:"<<temp->key<<" ";
        //cout<<"s:"<<dq.size<<" ";
    }
}


/*Returns the value of the key x if 
present else returns -1 */
int LRUCache::get(int x){
    if(dq.size==0)
        return -1;
    Node* curr=dq.rear;
    bool found=false;
    while(curr!=NULL){
        //cout<<"g:"<<curr->key<<"";
        if(curr->key == x){
            found=true;
            break;
        }
        curr=curr->prev;
    }
    //cout<<" ";
    int ret=-1;
    if(found){
        if(curr==dq.rear){
            ret=curr->value;
        }
        else if(curr==dq.front){
            dq.front=dq.front->next;
            dq.front->prev=NULL;
            dq.rear->next=curr;
            curr->prev=dq.rear;
            curr->next=NULL;
            dq.rear=curr;
            ret=curr->value;
        }
        else{
            Node* prev=curr->prev;
            Node* next=curr->next;
            prev->next=next;
            next->prev=prev;
            dq.rear->next=curr;
            curr->prev=dq.rear;
            curr->next=NULL;
            dq.rear=curr;
            ret=curr->value;
        }
        //cout<<"("<<curr->key<<","<<curr->value<<") ";
    }
    return ret;
}
