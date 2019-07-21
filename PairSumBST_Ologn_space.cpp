bool findPair(Node* root, int sum) {
    stack<Node*> sLow,sHigh;
    Node* low,*high;
    low=root;
    high=root;
    while( (low || !sLow.empty()) && (high || !sHigh.empty()) ){
        if(low){
            sLow.push(low);
            low=low->left;
        }
        else if(high){
            sHigh.push(high);
            high=high->right;
        }
        else{
            Node* temp1=sLow.top();
            Node* temp2=sHigh.top();
            if(temp1->data!=temp2->data && temp1->data+temp2->data == sum){
                return true;
            }
            else if(temp1->data+temp2->data > sum){
                sHigh.pop();
                high=temp2->left;
            }
            else{
                sLow.pop();
                low=temp1->right;
            }
        }
    }
    return false;
}
