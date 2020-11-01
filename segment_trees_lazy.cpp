#include <bits/stdc++.h>
using namespace std;

class segment_tree
{
    private:
        pair<int,pair<int,int>> *st;
        int * lazy;
        int n;
        void constructST(int l,int r,pair<int,pair<int,int>> *st,int i);
        int get_3_multiples_util(int l,int r,int a,int b,int i);
        void update_util(int l,int r,int a,int b,int val,int i);
    public:
        segment_tree(int n);
        void update_range(int a,int b,int val);
        int get_3_multiples(int b,int c);
};

segment_tree::segment_tree(int n)
{
    st = new pair<int,pair<int,int>>[4*n+1];
    this->n = n;
    constructST(0,n-1,st,0);
    lazy = new int[4*n+1];
    for(int i =0;i<4*n+1;i++) lazy[i] = 0;
}

void segment_tree::constructST(int l,int r,pair<int,pair<int,int>> *st,int i)
{
    if(l == r)
    {
        st[i] = pair<int,pair<int,int>>(1,pair<int,int>(0,0));
        return;
    }
    int mid = l+ (r-l)/2;
    constructST(l,mid,st,2*i+1);
    constructST(mid+1,r,st,2*i+2);
    st[i] = pair<int,pair<int,int>>(st[2*i+1].first + st[2*i+2].first,pair<int,int>(0,0));
    return;
}

void segment_tree::update_range(int a,int b,int val)
{
    update_util(0,n-1,a,b,val,0);
}


void segment_tree::update_util(int l,int r,int a,int b,int val,int i)
{
    if(lazy[i])
    {
            int total_left = lazy[i]%3;
            lazy[i] = 0;
            
            if(total_left == 1)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.second,pair<int,int>(st[i].first,st[i].second.first));
            }
            else if(total_left == 2)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.first,pair<int,int>(st[i].second.second,st[i].first));
            }
            
            if(l!=r)
            {
                lazy[2*i+1]+=total_left;
                lazy[2*i+2]+=total_left;
            }
    }   
    if(l >=a && r<= b)
    {
            lazy[i]+=val;
            int total_left = lazy[i]%3;
            lazy[i] = 0;
            
            if(total_left == 1)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.second,pair<int,int>(st[i].first,st[i].second.first));
            }
            else if(total_left == 2)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.first,pair<int,int>(st[i].second.second,st[i].first));
            }
            
            if(l!=r)
            {
                lazy[2*i+1]+=total_left;
                lazy[2*i+2]+=total_left;
            }
            return;
    }
    else if(b<l || a>r) return;
    else
    {
        int mid = l + (r-l)/2;
        update_util(l,mid,a,b,val,2*i+1);
        update_util(mid+1,r,a,b,val,2*i+2);
        st[i] = pair<int,pair<int,int>>(st[2*i+1].first + st[2*i+2].first,pair<int,int>(st[2*i+1].second.first + st[2*i+2].second.first,st[2*i+1].second.second + st[2*i+2].second.second));
    }
    
    return;
}



int segment_tree::get_3_multiples(int a,int b)
{
    return get_3_multiples_util(0,n-1,a,b,0);
}

int segment_tree::get_3_multiples_util(int l,int r,int a,int b,int i)
{
    if(lazy[i])
        {
            int total_left = lazy[i]%3;
            lazy[i] = 0;
            
            if(total_left == 1)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.second,pair<int,int>(st[i].first,st[i].second.first));
            }
            else if(total_left == 2)
            {
                st[i] = pair<int,pair<int,int>>(st[i].second.first,pair<int,int>(st[i].second.second,st[i].first));
            }
            
            if(l!=r)
            {
                lazy[2*i+1]+=total_left;
                lazy[2*i+2]+=total_left;
            }
        }
    if(l>=a && r<=b)
    {
        return st[i].first;
    }
    else if(b<l || a>r) return 0;
    else
    {
        int mid = l + (r-l)/2;
        return get_3_multiples_util(l,mid,a,b,2*i+1) + get_3_multiples_util(mid+1,r,a,b,2*i+2);
    }
}


int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    segment_tree st(n);
    int q;cin>>q;
    for(int i = 0;i<q;i++)
    {
        int a,b,c;cin>>a>>b>>c;
        switch(a)
        {
            case 0:
                st.update_range(b,c,1);
                break;
            case 1:
                cout<<st.get_3_multiples(b,c)<<endl;
                break;
        }
    }
    return 0;
}