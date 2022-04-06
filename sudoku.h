//ROMAN VITVITSKY 324065184
//YAIR HENGALI 316590595

#ifndef __SUDOKU_H
#define __SUDOKU_H

#define _CRT_SECURE_NO_WARNINGS
#define NOT_FINISH 0
#define FINISH_SUCCESS 1
#define FILLED 1
#define FINISH_FAILURE -1
#define FAIL -1
#define MAX_NAME_SIZE 100

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;

typedef struct _Cell
{
    short row;
    short col;
} Cell;

typedef struct _Player
{
    char* name;//   MAX PLAYER NAME 100
    short** board; // BOARD 9X9
    Array*** possibilities;

} Player;

typedef struct cellListNode
{
    Cell cell;
    struct cellListNode* next;
    struct cellListNode* prev;
} CellListNode;


typedef struct cellList
{
    CellListNode* head;
    CellListNode* tail;
} CellList;


typedef struct playersListNode
{
    Player player;  
    struct playersListNode* next;
    struct playersListNode* prev;
} PlayersListNode;


typedef struct playersList
{
    PlayersListNode* head;
    PlayersListNode* tail;
} PlayersList;


typedef struct treeNode
{
    PlayersListNode** pArrPlayer;
    struct treeNode* left;
    struct treeNode* right;

}TreeNode;

typedef struct tree
{
    TreeNode* root;
}Tree;


//send array as counter for each digit from 1 to 9, if digit appears in line or squre, counter goes up,
//indexes with 0 at the end of function means that that digit did not apper in row line and square.
bool countPossibleDigForField(short** sudokuBoard, short *countArr, short rowi, short coli);

//function 1 from assignment.
Array*** PossibleDigits(short** sudokuBoard);

//creates empty array as escribed in function 1 assignment.
Array*** createEmptyArray();

//receives counter array and outputs and array of possible digits (short array!) the size if the array is "size"
short* buildArr(short countArr[], unsigned short* size);

//checks the digits in the square (counter)
void countDigInSquare(short** sudokuBoard, short countArr[], short rowi, short coli);

//checks for digits in COLUMN (counter)
void countDigInCol(short** sudokuBoard, short countArr[], short rowi, short coli);

//check for digits in line.
void countDigInLine(short** sudokuBoard, short countArr[], short rowi, short coli);

//makes counter arr all 0
void anull(short arr[]);

//free function.
void freePossibleSolutions(Array*** inp);

//function 2 from assignment.
int OneStage(short** board, Array*** possibilities, int* x, int* y);

//checks if the board is filled with unsigned numbers return treu if it is false if it is not.
bool isBoardFilled(short** board);

//checks whether there are duplicates in the board.
bool isDuplicateInBoard(short** board);

//checks for the tile with the minimum number of possibilities, returns its coordinates as X and Y and the number of possibilities.
short findMinPossibilities(short** board, Array*** possibilities, int* x, int* y);

//updates the Arrays in a line.
void updateArrsInRow(Array*** possibilities, short num, short row);

//updates the Arrays in a column.
void updateArrsinCol(Array*** possibilities, short num, short col);

//updates the Arrays in a square.
void updateArrsInSquare(Array*** possibilities, short num, short row, short col);

//updates the Arrays in a coulomn, a line and a square.
void updateArrsInField(Array*** possibilities, short num, short row, short col);

//function 3 from assignment.
int FillBoard(short** board, Array*** possibilities);

//prints the soduku board to the screen.
void sudokoPrintBoard(short** board);

//create random board
Array*** createRandomBoard(short** board);

//Checks allocation.
void checkAllocation(void* ptr);

//creates Active players list, returns size 
short getInputPlayers(PlayersList* list);

//sorts pointer array by number of filled initial cells, increasing order, if equal, sort by alphabetical order
void pMergeSort(PlayersListNode** parr, short size);

//merges 2 sorted pointer arrays to one new array sorted  by number of filled initial cells, increasing order, if equal, sort by alphabetical order
PlayersListNode** pMerge(PlayersListNode** parr1, short size1, PlayersListNode** parr2, short size2);

//return how many full tales are in a Player's board
short countFullTales(Player player);

//copy pointers to PlayersList Nodes from src array to dest array
void copyPArr(PlayersListNode** dest, PlayersListNode** src, short size);

//recieves array of pointers to list nodes, create tree with pointers to array fields
Tree buildTreeFromArray(PlayersListNode*** pArr, short size);//CHANGED TO ***

//part of buildTreeFromArray
TreeNode* buildTreeFromArrayRec(PlayersListNode** pArr, short size);

//Runs tree in LDR order, and runs oneStage function for every player:
//if oneStage returns FAILURE_FINISH deletes player from active players list.
//if oneStage returns SUCCESS_FINISH moves node from active players list to winners list.
//if oneStage returns NOT_FINISH let user fill cell and update player's board and possibilities.
//returns the number of players who are not active players anymore.
short gameRound(Tree* tree, PlayersList* activeList, PlayersList* winList);

//Recursive function of gameRound function.
short gameRoundRec(TreeNode* root, PlayersList* activeList, PlayersList* winList);

//Let the user choose a value for the tale with the minimum options and updates its board and possibilities.
void letUserChoose(short** board, Array*** possibilities, int x, int y);

//moves a listnode from one list to the end of the other.
void moveNodeFromListToList(PlayersListNode* node, PlayersList* lst1, PlayersList* lst2);

//delets a node from a PlayersList. 
void deleteNodeFromPlayersList(PlayersListNode* node, PlayersList* lst);

//createes dynamic memory list with values from 0,0 to 8,8 !FREE IN END OF PROGRAM!
CellList makeCList();

//creates dynamic memory clistnode with cell with r c values from input
CellListNode* createCListNode(short r, short c);

//rolls random num from range
short randomNumFromRange(unsigned short minimum_number, unsigned short max_number);

//creates list node with 81 nodes each node with corresponding cell value
CellList makeCList();

//creates cell list node with given values
CellListNode* createCListNode(short r, short c);

//creates 9x9 matrix of fields initialized with '-1' value
short** createInitializedBoard();

//checks if list is empty
bool isEmptyList(PlayersList* lst);

//as the name suggests
void insertNodeToEndPlayerList(PlayersList* list, PlayersListNode* node);

//creates a player node with given name and random board
PlayersListNode* createPlayerListNode(char* name);

//finds the node that is 'k' number of nodes from start 
CellListNode* findKNodeInList(CellList list, unsigned short k);

//deletes cell from the list and frees its memory
void deleteCNodeFromList(CellList* list, CellListNode* node);

//anulls list pointers
void makeEmptyCList(CellList* lst);

//creates array of pointers to list nodes
PlayersListNode** createPArrFromList(PlayersList list, short n);

//frees cell list
void freeCList(CellList clist);

//prints players from a players list - each one's name and board
void printPlayersList(PlayersList* lst);

//frees player's board
void freeBoard(short** board);

//frees players list and the player nodes themselves
void freeList(PlayersList list);

//frees tree nodes
void freeTree(Tree tree);
void freeTreeHelper(TreeNode* root);

#endif 