/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/rules.h"
#include "../include/player.h"

using namespace std;

void algorithm_A(Board board, Player player, int index[])
{
    
    class TreeNode
    {
    private:
        Board boardState;
        TreeNode *nextfirstNode;
        TreeNode *nextsecondNode;
        TreeNode *nextthirdNode;
        TreeNode *nextfourthNode;

        int index[2]; 
    public:
        TreeNode();
        TreeNode(Board board)
        {
            this->boardState = board;
            nextfirstNode = NULL;
            nextsecondNode = NULL;
            nextthirdNode = NULL;
            nextfourthNode = NULL;
            index[0] = 0;
            index[1] = 0;
        };
        TreeNode(Board board, int x, int y)
        {
            this->boardState = board;
            nextfirstNode = NULL;
            nextsecondNode = NULL;
            nextthirdNode = NULL;
            nextfourthNode = NULL;
            this->index[0] = x;
            this->index[1] = y;
        };
        void setNextfirstNode(TreeNode *Node)
        {
            this->nextfirstNode = Node;
        };
        void setNextsecondNode(TreeNode *Node)
        {
            this->nextsecondNode = Node;
        };
        void setNextthirdNode(TreeNode *Node)
        {
            this->nextthirdNode = Node;
        };
        void setNextfourthNode(TreeNode *Node)
        {
            this->nextfourthNode = Node;
        };
        TreeNode *getNextfirstNode()
        {
            return this->nextfirstNode;
        };
        TreeNode *getNextsecondNode()
        {
            return this->nextsecondNode;
        };
        TreeNode *getNextthirdNode()
        {
            return this->nextthirdNode;
        };
        TreeNode *getNextfourthNode()
        {
            return this->nextfourthNode;
        };
        TreeNode *getfirstTail()
        {
            TreeNode *temp = NULL;
            TreeNode *tempNext = this;
            while (tempNext != NULL)
            {
                temp = tempNext;
                tempNext = tempNext->getNextfirstNode();
            }
            return temp;
        };
        TreeNode *getsecondTail()
        {
            TreeNode *temp = NULL;
            TreeNode *tempNext = this;
            while (tempNext != NULL)
            {
                temp = tempNext;
                tempNext = tempNext->getNextsecondNode();
            }
            return temp;
        };
        TreeNode *getthirdTail()
        {
            TreeNode *temp = NULL;
            TreeNode *tempNext = this;
            while (tempNext != NULL)
            {
                temp = tempNext;
                tempNext = tempNext->getNextthirdNode();
            }
            return temp;
        };
        TreeNode *getfourthTail()
        {
            TreeNode *temp = NULL;
            TreeNode *tempNext = this;
            while (tempNext != NULL)
            {
                temp = tempNext;
                tempNext = tempNext->getNextfourthNode();
            }
            return temp;
        };
        Board getBoardState()
        {
            return this->boardState;
        };
        int getX()
        {
            return this->index[0];
        };
        int getY()
        {
            return this->index[1];
        };
    };

    class game
    {
    private:
        TreeNode *root;
        Player *player;
        Player *opponent;

    public:
        game(Board board, Player *player)
        {
            this->root = new TreeNode(board);       //傳入的board
            this->player = player;                  //傳入的player
            char colorPlayer = player->get_color(); //player顏色代號
            char colorOpponent = 'v';               
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (board.get_cell_color(i, j) != 'w' && board.get_cell_color(i, j) != colorPlayer)
                        colorOpponent = board.get_cell_color(i, j); //都設成對手!
                }
            }
            this->opponent = new Player(colorOpponent);
        };
        TreeNode *select()
        {
            this->firstPlayer(this->root);
            char color = player->get_color();
            char opocolor = this->opponent->get_color();

            TreeNode *bestNode = this->root->getNextfirstNode();       
            float best =this->point(bestNode);
            float Score;
          
            int r, c;
            Board firstboard = bestNode->getBoardState();

            TreeNode *current = bestNode;
            while (current->getNextfirstNode()!= NULL)
            {

                Score = this->point(current); 
               
               this->secondOpponent(current);
                TreeNode *secondcurrent = current->getNextsecondNode(); 
                 
                while (secondcurrent->getNextsecondNode()!= NULL)
                {
               
                    Score += 0.8 * this->point(secondcurrent);

                    this->thirdPlayer(secondcurrent);
                    TreeNode* thirdcurrent = secondcurrent->getNextthirdNode();
                    
                    while(thirdcurrent->getNextthirdNode()!=NULL){
                        
                        
                        Score += 0.7 * this->point(thirdcurrent);

                      thirdcurrent=thirdcurrent->getNextthirdNode();
                    
                    }
                    secondcurrent = secondcurrent->getNextsecondNode();
                }
                c = current->getX();
                r = current->getY();
                if (Score > best)
                {
                   
                    if (firstboard.get_cell_color(c, r) == opocolor)
                    {
                        Score = 0;
                    }
                    else
                    {
                        best = Score;
                        bestNode = current;
                    }
                }

                current = current->getNextfirstNode();
            }
           
            return bestNode;
        
        };
        void firstPlayer(TreeNode *Node)
        { 
             char color = this->player->get_color(); 
           
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (Node->getBoardState().get_cell_color(i, j) == color || Node->getBoardState().get_cell_color(i, j) == 'w')
                    {
                        Board boardState = Node->getBoardState();              
                        boardState.place_orb(i, j, this->player);//錯在這
                        TreeNode *newNode = new TreeNode(boardState, i, j);
                        TreeNode *tail = Node->getfirstTail(); 
                        tail->setNextfirstNode(newNode);   
                        newNode->setNextfirstNode(NULL);
                       
                    }
                }
            }
          
        };
        void secondOpponent(TreeNode *Node)
        { 
            char oppocolor = this->opponent->get_color(); 

            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (Node->getBoardState().get_cell_color(i, j) == oppocolor || Node->getBoardState().get_cell_color(i, j) == 'w')
                    {
                        Board boardState = Node->getBoardState();           
                        boardState.place_orb(i, j,this->opponent);//錯在這
                        TreeNode *newNode = new TreeNode(boardState, i, j);
                        TreeNode *tail = Node->getsecondTail(); 
                        tail->setNextsecondNode(newNode);   
                        newNode->setNextsecondNode(NULL);
                      
                    }
                }
            }
        };
        void thirdPlayer(TreeNode *Node)
        { 
             char color = this->player->get_color(); 
           
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (Node->getBoardState().get_cell_color(i, j) == color || Node->getBoardState().get_cell_color(i, j) == 'w')
                    {
                        Board boardState = Node->getBoardState();              
                        boardState.place_orb(i, j, this->player);//錯在這
                        TreeNode *newNode = new TreeNode(boardState, i, j);
                        TreeNode *tail = Node->getthirdTail(); 
                        tail->setNextthirdNode(newNode);   
                        newNode->setNextthirdNode(NULL);
                       
                    }
                }
            }
          
        };
         void fourthOpponent(TreeNode *Node)
        { 
            char oppocolor = this->opponent->get_color(); 
           
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (Node->getBoardState().get_cell_color(i, j) == oppocolor || Node->getBoardState().get_cell_color(i, j) == 'w')
                    {
                        Board boardState = Node->getBoardState();           
                        boardState.place_orb(i, j,this->opponent);//錯在這
                        TreeNode *newNode = new TreeNode(boardState, i, j);
                        TreeNode *tail = Node->getfourthTail(); 
                        tail->setNextfourthNode(newNode);   
                        newNode->setNextfourthNode(NULL);
                      
                    }
                }
            }
        };


        float point(TreeNode *Node)
        {
            Board board = Node->getBoardState();
            char color = player->get_color();     //player的顏色!
            char oppocolor = opponent->get_color(); //對手的顏色!
            float playernum = 0, opponentnum = 0;
            float num = 0;
            int x = Node->getX();
            int y = Node->getY();
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (board.get_cell_color(i, j) == color)
                    {
                        playernum += board.get_orbs_num(i, j);
                    }
                    else if (board.get_cell_color(i, j) == oppocolor)
                    {
                        opponentnum += board.get_orbs_num(i, j);
                    }
                }
            }
            num = playernum - opponentnum; 
            return num;
        }
    };

    game newgame(board, &player);

    TreeNode *outcome = newgame.select();
    index[0] = outcome->getX();
    index[1] = outcome->getY();
}

