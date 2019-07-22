#include<iostream>
using namespace std;
void SmallerOnRight(int[][2],int n);
int main(){
    int T;
    int n;
    cin>>T;
    while(T--){
        cin>>n;
        int arr[n][2];
        for(int i=0; i<n; ++i){
            cin>>arr[i][0];
            arr[i][1]=0;
        }
        SmallerOnRight(arr,n);
        cout<<endl;
    }
	return 0;
}

void Merge(int arr[][2], int l ,int m, int r){
    int s1=m-l+1,s2=r-m;
    
    int arr1[s1][2]{0};
    int arr2[s2][2]{0};
    
    for(int i=l; i<=m; i++){
        arr1[i-l][0] = arr[i][0];
        arr1[i-l][1] = arr[i][1];
    }
    for(int i=m+1; i<=r; i++){
        arr2[i-(m+1)][0]=arr[i][0];
        arr2[i-(m+1)][1]=arr[i][1];
    }
    
    int i=0,j=0;
    while(i<s1 && j<s2){
        if(arr1[i][0]<=arr2[j][0]){
            arr[l][0]=arr2[j][0];
            arr[l][1]=arr2[j][1];
            l++;j++;
        }
        else{
            arr1[i][1]+=s2-j;
            arr[l][0]=arr1[i][0];
            arr[l][1]=arr1[i][1];
            l++;i++;
        }
    }
    while(i<s1){
        arr[l][0]=arr1[i][0];
        arr[l][1]=arr1[i][1];
        l++;i++;
    }
    while(j<s2){
        arr[l][0]=arr2[j][0];
        arr[l][1]=arr2[j][1];
        l++;j++;
    }
}

void MergeSort(int arr[][2],int l,int r){
    if(l<r){
        int m=l+(r-l)/2;
        MergeSort(arr,l,m);
        MergeSort(arr,m+1,r);
        Merge(arr,l,m,r);
    }
}

void SmallerOnRight(int arr[][2], int n){
    MergeSort(arr,0,n-1);
    int max=0;
    for(int i=0; i<n; ++i){
        if(arr[i][1]>max)
            max=arr[i][1];
    }
    cout<<max;
}
