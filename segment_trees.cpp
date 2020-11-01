#include <bits/stdc++.h>
using namespace std;

class segment_tree
{
    private:
        int * st;
        int n;
        void constructST(int * arr,int l,int r,int *st,int i);
        int get_evens_util(int l,int r,int a,int b,int i);
        void update_util(int l,int r,int index,int val,int i);
    public:
        segment_tree(int * arr,int n);
        void update(int i,int val);
        int get_evens(int l ,int r);
};

segment_tree::segment_tree(int * arr,int n)
{
    st = new int[4*n+1];
    this->n = n;
    constructST(arr,0,n-1,st,0);
}

void segment_tree::constructST(int * arr,int l,int r,int *st,int i)
{
    if(l == r)
    {
        st[i] = 1-arr[l]%2;
        return;
    }
    int mid = l+ (r-l)/2;
    constructST(arr,l,mid,st,2*i+1);
    constructST(arr,mid+1,r,st,2*i+2);
    st[i] = st[2*i+1]+st[2*i+2];
    return;
}

int segment_tree::get_evens(int l ,int r)
{
    return get_evens_util(0,n-1,l,r,0);
}

int segment_tree::get_evens_util(int l,int r,int a,int b,int i)
{
    if(l>=a && r<=b)
    {
        return st[i];
    }
    if(l>b || r<a) return 0;

    int mid = l+(r-l)/2;

    return get_evens_util(l,mid,a,b,2*i+1)+get_evens_util(mid+1,r,a,b,2*i+2);
}

void segment_tree::update(int i,int val)
{
    update_util(0,n-1,i,val,0);
}

void segment_tree::update_util(int l,int r,int index,int val,int i)
{
    if(l == r && l == index)
    {
        st[i] = 1 - val%2;
        return; 
    }
    if(l<=index && index<=r)
    {
        int mid = l + (r-l)/2;
        update_util(l,mid,index,val,2*i+1);
        update_util(mid+1,r,index,val,2*i+2);
        st[i] = st[2*i+1]+st[2*i+2];
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    int arr[n];
    for(int i =0;i<n;i++) cin>>arr[i];

    segment_tree st(arr,n);
    int q;cin>>q;
    for(int i = 0;i<q;i++)
    {
        int a,b,c;cin>>a>>b>>c;
        b--;c--;
        switch(a)
        {
            case 0:
                st.update(b,c+1);
                break;
            case 1:
                cout<<st.get_evens(b,c)<<endl;
                break;
            case 2:
                cout<< (c-b-st.get_evens(b,c)+1)<<endl;
                break;
        }
    }
    return 0;
}