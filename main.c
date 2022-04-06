//ROMAN VITVITSKY 324065184
//YAIR HENGALI 316590595
#define _CRT_SECURE_NO_WARNINGS
#include "sudoku.h"


void main()
{
    
    srand(12345);
    short numOfPlayers, numOfActivePlayers;
    PlayersListNode** pArr;
    PlayersList activePlayersList, winnersList;
    Tree playersTree;

    numOfPlayers = getInputPlayers(&activePlayersList);//creates Active players list, returns size, each player gets random board initially

    pArr = createPArrFromList(activePlayersList, numOfPlayers);

    pMergeSort(pArr, numOfPlayers);

    playersTree = buildTreeFromArray(&pArr, numOfPlayers);

    numOfActivePlayers = numOfPlayers;

    //anulls winners list.
    winnersList.head = winnersList.tail = NULL;

    while (numOfActivePlayers > 0)
    {
        numOfActivePlayers -= gameRound(&playersTree, &activePlayersList, &winnersList);//scans Tree, returns how many players finished in round
    }

    if (isEmptyList(&winnersList))
    {
        printf("There are no winners.\n");
    }
    else
    {
        printf("********************\nAnd the winners are:\n********************\n");
        printPlayersList(&winnersList);\
    }

    freeList(winnersList);
    freeTree(playersTree);
    free(pArr);
    
}

