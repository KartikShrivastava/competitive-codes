int intersectPoint(Node* head1, Node* head2){
    if(!head1 || !head2)
        return -1;
    
    //traverse till the end
    Node* p1=head1,*p2=head2;
    while(p1->next){
        p1=p1->next;
    }
    
    //join end of list1 to its head
    p1->next=head1;
    
    //detect the position of loop
    p1=head2;
    p2=head2;
    while(1){
        p1=p1->next;
        p2=p2->next->next;
        if(p1==p2)
            break;
    }
    p1=head2;
    while(p1!=p2){
        p1=p1->next;
        p2=p2->next;
    }
    
    //return where two pointers meet i.e. node of Intersection
    return p2->data;
}
