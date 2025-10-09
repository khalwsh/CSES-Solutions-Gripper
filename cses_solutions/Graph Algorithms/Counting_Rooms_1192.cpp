#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m)
{
    return i>=0&&j<m&&i<n&&j>=0;
}
void dfs(int row,int col,int n,int m,vector<vector<char>>&grid,vector<vector<bool>>&vis)
{
    vis[row][col]=true;
    int dx[]{1,-1,0,0};
    int dy[]{0,0,1,-1};
    for(int i=0;i<4;i++)
    {
        int cur_row=row+dx[i];
        int cur_col=col+dy[i];
        if(valid(cur_row,cur_col,n,m)&&!vis[cur_row][cur_col]&&grid[cur_row][cur_col]!='#')
            dfs(cur_row,cur_col,n,m,grid,vis);
    }
}
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<vector<char>>grid(n,vector<char>(m));
    for(auto &val:grid)for(auto &i:val)cin>>i;
    vector<vector<bool>>vis(n,vector<bool>(m));
    int counter=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(!vis[i][j]&&grid[i][j]!='#')
                dfs(i,j,n,m,grid,vis),counter++;
        }
    }
    cout<<counter<<line;
 
}