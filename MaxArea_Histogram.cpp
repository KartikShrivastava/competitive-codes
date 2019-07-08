long getMaxArea(long long arr[], int n){
    stack<int> s;
    s.push(0);
    int span;
    int res[n]{0};
    res[0]=1;
    for(int i=1; i<n; ++i){
        while(!s.empty() && arr[s.top()] >= arr[i])
            s.pop();

        if(s.empty())
            span=i+1;
        else
            span=i-s.top();
        
        s.push(i);
        res[i]=span;
    }
    
    while(!s.empty())
        s.pop();
    
    s.push(n-1);
    for(int i=n-2; i>=0; --i){
        while(!s.empty() && arr[s.top()] >= arr[i])
            s.pop();

        if(s.empty())
            span=n-1-i;
        else
            span=s.top()-i-1;
        
        s.push(i);
        res[i]+=span;
    }
    
    long maxarea=0;
    for(int i=0; i<n; ++i){
        if(res[i]>n)
            return 0;
        if(arr[i]*res[i] > maxarea)
            maxarea=(arr[i]*res[i]);
    }
    
    return maxarea;
}
