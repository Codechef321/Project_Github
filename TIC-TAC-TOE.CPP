#include<bits\stdc++.h>
using namespace std;
 
 #define COMPUTER 1
 #define HUMAN 2
 #define SIDE 3
 #define COMPUTERMOVE 'O'
 #define HUMANMOVE 'X'

void showBoard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c\n",board[0][0],board[0][1],board[0][2]);
    printf("\t\t\t--------\n");
    printf("\t\t\t %c | %c | %c\n",board[1][0],board[1][1],board[1][2]);
    printf("\t\t\t--------\n");
    printf("\t\t\t %c | %c | %c\n",board[2][0],board[2][1],board[2][2]);
}
 void showInstructions()
 {
    printf("\nchoose a cell number from 0 to 9\n\n");
    printf("\t\t\t 1|2|3\n");
    printf("\t\t\t---------\n");
    printf("\t\t\t 4|5|6\n");
    printf("\t\t\t---------\n");
    printf("\t\t\t 7|8|9\n\n");
 }
 void Initialise(char board[][SIDE])
 {
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {   board[i][j]='*';
        }    
    }
 }
 void declareWinner(int whoseTurn)
 {
    if(whoseTurn==COMPUTER)
    cout<<("Computer has won\n");
    else
    cout<<("Human has won \n");
 }
 bool gameOver(char board[][SIDE])
 {
    for (int i = 0; i < SIDE; i++)
    {
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2] &&board[i][0]!='*')
        return true;
        else if(board[0][i]==board[1][i] && board[0][i]==board[2][i] &&board[0][i]!='*')
        return true;
    }
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2] &&board[0][0]!='*')
    return true;
    else if(board[0][2]==board[1][1] && board[0][2]==board[0][2] &&board[0][2]!='*')
    return true;
    return false;
 }
 int MiniMax(char board[][SIDE],int depth,bool isAI)
 {
    int score=0,bestScore=0;
    if(gameOver(board)==true)
    {
        if(isAI==true)
        return -10;
        else return 10;
    }
    else
    {   if(depth<9)
        {   if(isAI==true)
            {   bestScore=-99;
                for (int i = 0; i < SIDE; i++)
                {   for (int j = 0; j < SIDE; j++)
                    {   if(board[i][j]=='*')
                        {   board[i][j]=COMPUTERMOVE;
                            score=MiniMax(board,depth + 1,false);
                            board[i][j]='*';
                            if(score > bestScore){
                                bestScore = score;
                            }    
                        }
                    }
                }
                return bestScore;
            }        
            else{
                bestScore=99;
                for (int i = 0; i < SIDE; i++)
                {   for (int j = 0; j < SIDE; j++)
                    {   if(board[i][j]=='*')
                        {    board[i][j]=HUMANMOVE;
                            score=MiniMax(board,depth + 1,true);
                            board[i][j]='*';
                            if(score < bestScore){
                                bestScore = score;
                            }    
                        }
                    }
                }
            return bestScore;
            }
        }
    else
    return 0;
    }
}
int bestMove(char board[][SIDE],int moveIndex)
{   int x=-1 , y=-1;
    int score=0 ,bestScore =-999;
    for (int i = 0; i < SIDE; i++)
    {   for (int j = 0; j < SIDE; j++)
        {   if (board[i][j]=='*')
            {   board[i][j]=COMPUTERMOVE;
                score=MiniMax(board,moveIndex +1,false);
                board[i][j]='*';
                if(score>bestScore)
                {   bestScore=score;
                    x=i;
                    y=j;                   
                }
            }
        }
    }
    return x*3 +y;
}
void playTICTACTOE(int whoseTurn)
{   char board[SIDE][SIDE];
    int moveIndex=0 ,x=0 ,y=0;

    Initialise(board);
    showInstructions();

    while(gameOver(board)==false && moveIndex!=SIDE*SIDE)
    {   int n;
        if(whoseTurn==COMPUTER)
        {   n=bestMove(board,moveIndex);
            x=n/SIDE;
            y=n%SIDE;
            board[x][y]=COMPUTERMOVE;
            cout<<"Computer has put a " <<COMPUTERMOVE<<" in cell\t"<< n+1 <<"\n\n";
            showBoard(board);
            moveIndex++;
            whoseTurn=HUMAN;
        }
        else if(whoseTurn==HUMAN)
        {   cout<<"You can insert in the following positions : ";
            for (int i = 0; i < SIDE; i++)
               for (int j = 0; j < SIDE; j++)
                    {   if (board[i][j]=='*')
                        cout<<(i*3+j+1)<<" ";
                    }
                    cout<<"\n\n Enter the position = ";
                    cin >> n;
                    n--;
                    x=n/SIDE;
                    y=n%SIDE;
                    if(board[x][y] == '*' && n<9 && n>=0)
                    {   board[x][y]=HUMANMOVE;
                        printf("\n\nHuman has put a %c in cell %d\n\n",HUMANMOVE,n+1);
                        showBoard(board);
                        moveIndex++;
                        whoseTurn = COMPUTER ;
                    }
                    else if(board[x][y]!='*' || n<9 || n>=0)
                    cout<<"Position is occupied , select any one available space\n";
                    else if(n<0||n>8)
                    cout<<"Invalid position\n";
                
            
        }
    }
    if (gameOver(board)==false && moveIndex==SIDE*SIDE)
        cout<<"It is a draw\n";
    else
    {   if(whoseTurn==COMPUTER)
            whoseTurn=HUMAN;
        else if(whoseTurn==HUMAN)
            whoseTurn=COMPUTER;
        declareWinner(whoseTurn);
    }
}

int main()
{   
    cout<<"\n------------------------------------------------\n\n";
    cout<<"\t\tTIC-TAC-TOE\n";
    cout<<"\n------------------------------------------------\n\n";
    char cont = 'y';
    do{
        char choice;
        cout<<"Do you want to start first?(Y/N):";
        cin>>&choice;

        if (choice=='N'||choice=='n')
            playTICTACTOE(COMPUTER);
        else if(choice=='Y'|| choice=='y')
            playTICTACTOE(HUMAN);
        else cout<<"Invalid choice\n";

        cout<<"Do you want to quit (Y/N) : ";
        cin>>&cont;
    }while(cont =='N'||cont=='n');
    return 0;
}