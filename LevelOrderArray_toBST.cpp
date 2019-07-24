struct rangeNode{
    Node* node;
    int mini;
    int maxi;
    rangeNode(Node* x,int y, int z){
        node = x;
        mini=y;
        maxi=z;
    }
};

//Note : arr[] contains level order traversal of a BST

Node* constructBst(int arr[], int n){
    Node* root = new Node(arr[0]);
    queue<rangeNode*> q;
    rangeNode* rn = new rangeNode(root,INT_MIN,INT_MAX); 
    q.push(rn);
    int index=1;
    rangeNode* curr;
    while(!q.empty() && index<n){
            curr = q.front();
            q.pop();
        //cout<<curr->node->data<<","<<curr->mini<<","<<curr->maxi<<endl;
        if(curr->mini <= arr[index] && arr[index] < curr->node->data){
            if(!curr->node->left){
                curr->node->left = new Node(arr[index]);
                q.push(new rangeNode(curr->node->left,curr->mini,curr->node->data-1));
                index++;
            }
        }
        if(index<n && curr->node->data < arr[index] && arr[index] <= curr->maxi){
            if(!curr->node->right){
                curr->node->right = new Node(arr[index]);
                q.push(new rangeNode(curr->node->right,curr->node->data+1,curr->maxi));
                index++;
            }
        }
    }
    
    return root;
}
