#include<iostream>
#define N 4
using namespace std;

static int count=0;

void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
        if(board[i][j])
            cout << "Q ";
        else cout<<". ";
        printf("\n");
    }
}


bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    
    for (i = 0; i < col; i++)
    {
    if (board[row][i])
    {
        ::count++;
        return false;    
    }
    ::count+=4;        
    }
        


    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
        {
            ::count+= 1;
        return false;    
        }
    
        ::count+=6;    
    
    }
        

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
    if (board[i][j])
    {
        ::count+=1;
        return false;    
    }
    ::count+=6;        
    }
        

    return true;
}


bool solveNQUtil(int board[N][N], int col)
{

    if (col >= N)
    {
        ::count++;
        return true;    
    }
    


    for (int i = 0; i < N; i++) {
    
        if (isSafe(board, i, col)) {
            
            board[i][col] = 1;
             ::count++;
              
            if (solveNQUtil(board, col + 1))
            {
            ::count++;
            return true;    
            }
                

            
            board[i][col] = 0; 
        }
    }


    return false;
}


bool solveNQ()
{
    int board[N][N] = { { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 } };

    if (solveNQUtil(board, 0) == false) {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(board);
    return true;
}


int main()
{
    solveNQ();
    cout<<"No. of required steps :"<<::count;
    return 0;
}