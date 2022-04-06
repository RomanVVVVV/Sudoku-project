//ROMAN VITVITSKY 324065184
//YAIR HENGALI 316590595
#include "sudoku.h"


void pMergeSort(PlayersListNode** parr, short size)
{
    PlayersListNode** tmpArr = NULL;
    if (size <= 1)
        return;

    pMergeSort(parr, size / 2);
    pMergeSort(parr + (size / 2), size - (size / 2));
    tmpArr = pMerge(parr, size / 2, parr + (size / 2), size - (size / 2));

    if (tmpArr)
    {
        copyPArr(parr, tmpArr, size);
        free(tmpArr);
    }
    else
    {
        printf("Memory allocation failure!\n");
        exit(0);
    }

}


PlayersListNode** pMerge(PlayersListNode** parr1, short size1, PlayersListNode** parr2, short size2)
{
    short i1, i2, resI, abcCmp;
    PlayersListNode** res = (PlayersListNode**)malloc(sizeof(PlayersListNode*) * (size1 + size2));
    checkAllocation(res);

    i1 = i2 = resI = 0;

    while ((i1 < size1) && (i2 < size2))
    {
        short countP1 = countFullTales(parr1[i1]->player), countP2 = countFullTales(parr2[i2]->player);

        if (countP1 < countP2)
        {
            res[resI] = parr1[i1];
            i1++;

        }

        else if (countP1 > countP2)
        {
            res[resI] = parr2[i2];
            i2++;
        }

        else //If Equal
        {
            abcCmp = strcmp(parr1[i1]->player.name, parr2[i2]->player.name);
            if (abcCmp < 0)
            {
                res[resI] = parr1[i1];
                i1++;
            }

            else
            {
                res[resI] = parr2[i2];
                i2++;
            }
        }
        resI++;
    }

    while (i1 < size1)
    {
        res[resI] = parr1[i1];
        i1++;
        resI++;
    }

    while (i2 < size2)
    {
        res[resI] = parr2[i2];
        i2++;
        resI++;
    }


    return res;
}


short countFullTales(Player player)
{
    short row, col, count = 0;
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (player.board[row][col] != -1)
                count++;

    return count;
}


void copyPArr(PlayersListNode** dest, PlayersListNode** src, short size)
{
    short i;
    for (i = 0; i < size; i++)
        dest[i] = src[i];
}


void freePossibleSolutions(Array*** inp)
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            free(inp[r][c]->arr);
            free(inp[r][c]);
        }
        free(inp[r]);
    }
    free(inp);
}


Array*** PossibleDigits(short** sudokuBoard)
{
    Array*** outputArr;
    bool isFilledTile = false;

    short countArr[9] = { 0 };
    unsigned short size = 0;

    outputArr = createEmptyArray();

    for (short row = 0; row < 9; row++)
    {
        for (short col = 0; col < 9; col++)
        {
            isFilledTile = countPossibleDigForField(sudokuBoard, countArr, row, col);
            if (isFilledTile)
            {
                outputArr[row][col]->arr = NULL;
                outputArr[row][col]->size = 0;
            }
            else
            {
                outputArr[row][col]->arr = buildArr(countArr, &size);
                outputArr[row][col]->size = size;
            }
            anull(countArr);
        }
    }
    return outputArr;
}


void anull(short arr[])
{
    for (short i = 0; i < 9; i++)
    {
        arr[i] = 0;
    }
}


Array*** createEmptyArray()
{
    Array*** out;
    out = (Array***)malloc(9 * sizeof(Array**));
    checkAllocation(out);

    if (out == NULL)
        exit(0);

    for (short i = 0; i < 9; i++)
    {
        out[i] = (Array**)malloc(9 * sizeof(Array*));
        checkAllocation(out[i]);

        if (out[i] == NULL)
            exit(0);

        for (short j = 0; j < 9; j++)
        {
            out[i][j] = (Array*)malloc(sizeof(Array));
            checkAllocation(out[i][j]);

            if (out[i][j] == NULL)
                exit(0);
        }
    }
    return out;
}


short* buildArr(short countArr[], unsigned short* size)
{
    short k = 0;
    unsigned short n = 0;
    short* res;
    for (short i = 0; i < 9; i++)
    {
        if (countArr[i] == 0)
            n++;
    }
    *size = n;
    res = (short*)malloc(n * sizeof(short));
    checkAllocation(res);

    if (res == NULL)
        exit(0);
    for (short j = 0; j < 9; j++)
    {
        if (countArr[j] == 0)
        {
            res[k] = (short)(j + 1);
            k++;
        }
    }
    return res;
}


bool countPossibleDigForField(short** sudokuBoard, short *countArr, short rowi, short coli)
{
    if (sudokuBoard[rowi][coli] != -1)
        return true;

    countDigInSquare(sudokuBoard, countArr, rowi, coli);
    countDigInCol(sudokuBoard, countArr, rowi, coli);
    countDigInLine(sudokuBoard, countArr, rowi, coli);

    return false;
}


void countDigInSquare(short** sudokuBoard, short countArr[], short rowi, short coli)
{
    short row, col;
    for (row = (3 * (rowi / 3)); row < (3 * (rowi / 3)) + 3; row++)
    {
        for (col = (3 * (coli / 3)); col < (3 * (coli / 3)) + 3; col++)
        {
            if (sudokuBoard[row][col] > 0)
            {
                countArr[sudokuBoard[row][col] - 1]++;
            }
        }
    }
}


void countDigInCol(short** sudokuBoard, short countArr[], short rowi, short coli)
{
    short row;
    for (row = 0; row < 9; row++)
    {
        if (sudokuBoard[row][coli] > 0)
        {
            countArr[sudokuBoard[row][coli] - 1]++;
        }
    }
}


void countDigInLine(short** sudokuBoard, short countArr[], short rowi, short coli)
{
    short col;
    for (col = 0; col < 9; col++)
    {
        if (sudokuBoard[rowi][col] > 0)
        {
            countArr[sudokuBoard[rowi][col] - 1]++;
        }
    }
}


int OneStage(short** board, Array*** possibilities, int* x, int* y)
{
    short row, col;
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (possibilities[row][col]->size == 1)
            {
                board[row][col] = possibilities[row][col]->arr[0];
                free(possibilities[row][col]->arr);
                possibilities[row][col]->arr = NULL;
                possibilities[row][col]->size = 0;

                updateArrsInField(possibilities, board[row][col], row, col);
                row = -1;
                break;
            }

        }


    }

    if (isDuplicateInBoard(board))
        return FINISH_FAILURE;

    else if (isBoardFilled(board))
        return FINISH_SUCCESS;

    else if (findMinPossibilities(board, possibilities, x, y) == 0)
        return FINISH_FAILURE;
    else
        return NOT_FINISH;




}


bool isBoardFilled(short** board)
{
    short row, col;
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (board[row][col] == -1)
                return false;

    return true;
}


bool isDuplicateInBoard(short** board)
{

    short row=0, col=0, i;
    short countArr[9] = { 0 };
    for (row = 0; row < 9; row++)
    {
    countDigInLine(board, countArr, row, col);
    for (i = 0; i < 9; i++)
        if (countArr[i] > 1)
            return true;
    anull(countArr);
    }
    row = col = 0;
    for (col = 0; col < 9; col++)
    {
    countDigInCol(board, countArr, row, col);
    for (i = 0; i < 9; i++)
        if (countArr[i] > 1)
            return true;
    anull(countArr);
    }
    row = col = 0;
    for (row = 0; row < 9; row+=3)
    {
    for (col = 0; col < 9; col+=3)
    {
        countDigInSquare(board, countArr, row, col);
        for (i = 0; i < 9; i++)
            if (countArr[i] > 1)
                return true;
        anull(countArr);
    }
    }
    return false;
}


short findMinPossibilities(short** board, Array*** possibilities, int* x, int* y)
{
    short row, col;
    unsigned short min = 10;
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)

            if ((board[row][col] == -1) && (possibilities[row][col]->size < min))
            {
                min = possibilities[row][col]->size;
                *x = row;
                *y = col;
            }

    return min;
}


void updateArrsInRow(Array*** possibilities, short num, short row)
{
    unsigned short i, j, currSize;
    for (i = 0; i < 9; i++)
    {
        currSize = possibilities[row][i]->size;
        if (currSize > 0)
        {
            for (j = 0; j < currSize; j++)
            {
                if (possibilities[row][i]->arr[j] == num)
                {
                    for (; j < currSize - 1; j++)
                        possibilities[row][i]->arr[j] = possibilities[row][i]->arr[j + 1];

                    possibilities[row][i]->arr = (short*)realloc(possibilities[row][i]->arr, sizeof(short) * (currSize - 1));
                    possibilities[row][i]->size--;
                    currSize = possibilities[row][i]->size;
                }
            }

        }

    }


}


void updateArrsinCol(Array*** possibilities, short num, short col)
{
    unsigned short i, j, currSize;
    for (i = 0; i < 9; i++)
    {
        currSize = possibilities[i][col]->size;
        if (currSize > 0)
        {
            for (j = 0; j < currSize; j++)
            {
                if (possibilities[i][col]->arr[j] == num)
                {
                    for (; j < currSize - 1; j++)
                        possibilities[i][col]->arr[j] = possibilities[i][col]->arr[j + 1];

                    possibilities[i][col]->arr = (short*)realloc(possibilities[i][col]->arr, sizeof(short) * (currSize - 1));
                    possibilities[i][col]->size--;
                    currSize = possibilities[i][col]->size;
                }
            }

        }

    }

}


void updateArrsInSquare(Array*** possibilities, short num, short row, short col)
{
    unsigned short i, j, k, currSize;
    for (i = (row / 3) * 3; i < ((row / 3) * 3) + 3; i++)
        for (k = (col / 3) * 3; k < ((col / 3) * 3) + 3; k++)
        {
            currSize = possibilities[i][k]->size;
            if (currSize > 0)
            {
                for (j = 0; j < currSize; j++)
                {
                    if (possibilities[i][k]->arr[j] == num)
                    {
                        for (; j < currSize - 1; j++)
                            possibilities[i][k]->arr[j] = possibilities[i][k]->arr[j + 1];

                        possibilities[i][k]->arr = (short*)realloc(possibilities[i][k]->arr, sizeof(short) * (currSize - 1));
                        possibilities[i][k]->size--;
                        currSize = possibilities[i][k]->size;
                    }
                }
            }

        }


}


void updateArrsInField(Array*** possibilities, short num, short row, short col)
{
    updateArrsInRow(possibilities, num, row);
    updateArrsinCol(possibilities, num, col);
    updateArrsInSquare(possibilities, num, row, col);
}


int FillBoard(short** board, Array*** possibilities)
{

    int x, y, choice;
    short i;
    int status = OneStage(board, possibilities, &x, &y);
    while (status == NOT_FINISH)
    {
        sudokoPrintBoard(board);
        printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);

        for (i = 0; i < possibilities[x][y]->size; i++)
            printf("%d. %d\n", i + 1, possibilities[x][y]->arr[i]);

        scanf("%d", &choice);

        printf("Updating cell %d with value %d \n", x * 9 + y, choice);

        board[x][y] = choice;
        free(possibilities[x][y]->arr);
        possibilities[x][y]->arr = NULL;
        possibilities[x][y]->size = 0;
        updateArrsInField(possibilities, board[x][y], x, y);

        status = OneStage(board, possibilities, &x, &y);
    }

    if (status == FINISH_SUCCESS)
        return FILLED;
    else if (status == FINISH_FAILURE)
        return FAIL;

}


void sudokoPrintBoard(short** board)
{
    short i, j;
    printf("  ");
    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            printf("|");
        printf("%2d", i);
    }

    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
        {
            printf("\n");
            for (j = 0; j < 8; j++)
                printf("---");
        }
        printf("\n");
        printf("%2d", i);
        for (j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
                printf("|");
            if (board[i][j] == -1)
                printf("  ");
            else
                printf("%2d", board[i][j]);
        }

    }
    printf("\n");
    for (j = 0; j < 8; j++)
        printf("---");
    printf("\n");
}


short randomNumFromRange(unsigned short minimum_number, unsigned short max_number)
{
    return (unsigned short)(rand() % (max_number + 1 - minimum_number) + minimum_number);
}


Array*** createRandomBoard(short** board)//RECIEVES INITIALIZED BOARD WITH ALL -1
{
    Array*** possibilities;
    short value;
    unsigned short randN, randK, cListLen = 81, randI;
    Cell kNodeCell;
    CellListNode* kNode;
    CellList clist;

    possibilities = PossibleDigits(board);
    randN = randomNumFromRange(1, 20);
    clist = makeCList();//81 NODES
    for (short i = 0; i < randN; i++)
    {
        randK = randomNumFromRange(1, cListLen);
        kNode = findKNodeInList(clist, randK);
        kNodeCell = kNode->cell;
        deleteCNodeFromList(&clist, kNode);//+FREES
        randI = randomNumFromRange(0, (possibilities[kNodeCell.row][kNodeCell.col]->size) - 1);
        value = (possibilities[kNodeCell.row][kNodeCell.col]->arr)[randI];
        board[kNodeCell.row][kNodeCell.col] = value;
        free(possibilities[kNodeCell.row][kNodeCell.col]->arr);
        possibilities[kNodeCell.row][kNodeCell.col]->arr = NULL;
        possibilities[kNodeCell.row][kNodeCell.col]->size = 0;
        updateArrsInField(possibilities, value, kNodeCell.row, kNodeCell.col);
        cListLen--;
    }
    freeCList(clist);
    return possibilities;
}


void freeCList(CellList clist)
{
    CellListNode* currNode, * temp;
    currNode = clist.head;

    while (currNode != NULL)
    {
        temp = currNode->next;
        free(currNode);
        currNode = temp;
    }
}


CellListNode* findKNodeInList(CellList list, unsigned short k)
{
    CellListNode* node = list.head;
    int i = 1;
    while (i != k)
    {
        node = node->next;
        i++;
    }
    return node;
}


void deleteCNodeFromList(CellList* list, CellListNode* node)
{
    CellListNode* next;
    if (list->head == node && list->tail == node)//IF IS ONLY NODE 
    {
        free(node);
        makeEmptyCList(list);
    }
    else if (list->head == node)	//FIRST NODE NOT ONLY NODE
    {
        node->next->prev = NULL;
        list->head = node->next;
        free(node);
    }
    else if (list->tail == node)	//LAST NODE NOT ONLY NODE
    {
        node->prev->next = NULL;
        list->tail = node->prev;
        free(node);
    }
    else
    {
        next = node->next;
        node->prev->next = next;
        node->next->prev = node->prev;
        free(node);
    }
}


void makeEmptyCList(CellList* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}


short getInputPlayers(PlayersList* pList)
{
    pList->head = pList->tail = NULL;
    int intNOP;
    short numOfPlayers;
    char currPlayerName[MAX_NAME_SIZE];
    PlayersListNode* curr = NULL;
    printf("Please enter the number of players:\n");
    scanf("%d", &intNOP);
    printf("\n");
    getchar();

    printf("Enter players names:\n");
    numOfPlayers = (short)intNOP;


    for (int i = 0; i < numOfPlayers; i++)
    {
        gets(currPlayerName);
        curr = createPlayerListNode(currPlayerName);//DYNAMIC
        insertNodeToEndPlayerList(pList, curr);
    }
    return numOfPlayers;
}


PlayersListNode* createPlayerListNode(char* name)
{
    PlayersListNode* node = (PlayersListNode*)malloc(sizeof(PlayersListNode));
    checkAllocation(node);
    short** board = createInitializedBoard();
    node->next = node->prev = NULL;

    node->player.possibilities = createRandomBoard(board);
    node->player.board = board;
    node->player.name = _strdup(name);

    return node;
}


void checkAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(0);
    }
}


Tree buildTreeFromArray(PlayersListNode*** pArr, short size)
{
    Tree res;
    res.root = NULL;
    short newSize = pow(2, ceil(log2(size + 1))) - 1;
    *pArr = (PlayersListNode**)realloc((*pArr), (newSize) * sizeof(PlayersListNode*));
    checkAllocation(*pArr);

    for (int i = size; i < newSize; i++)
        (*pArr)[i] = NULL;

    res.root = buildTreeFromArrayRec(*pArr, newSize); 
    return res;
}


TreeNode* buildTreeFromArrayRec(PlayersListNode** pArr, short size)
{

    TreeNode* node;
    if ((size == 0) || (size == 1 && pArr[0] == NULL))
    {
        return NULL;
    }
    else if (size == 1)
    {
        node = (TreeNode*)malloc(sizeof(TreeNode));
        checkAllocation(node);

        node->pArrPlayer = (pArr);
        node->left = NULL;
        node->right = NULL;
    }
    else {
        node = (TreeNode*)malloc(sizeof(TreeNode));
        checkAllocation(node);

        node->pArrPlayer = (pArr + (size / 2));
        node->left = buildTreeFromArrayRec(pArr, size / 2);
        node->right = buildTreeFromArrayRec(pArr + (size / 2) + 1, size / 2);
    }
    return node;
}


short gameRound(Tree* tree, PlayersList* activeList, PlayersList* winList)
{
    return gameRoundRec(tree->root, activeList, winList);
}


short gameRoundRec(TreeNode* root, PlayersList* activeList, PlayersList* winList)
{
    if (root == NULL)
        return 0;
    else
    {
        short leftRes, rightRes, rootRes;
        leftRes = gameRoundRec(root->left, activeList, winList);

        //for every player: 
        if (*(root->pArrPlayer) != NULL)
        {
            int x, y;
            int status = OneStage((*(root->pArrPlayer))->player.board, (*(root->pArrPlayer))->player.possibilities, &x, &y);

            if (status == FINISH_FAILURE)
            {
                printf("\n\n%s has lost the game.\n\n", (*(root->pArrPlayer))->player.name);
                system("pause");
                deleteNodeFromPlayersList(*(root->pArrPlayer), activeList);
                *(root->pArrPlayer) = NULL;
                rootRes = 1; 
            }
            else if (status == FINISH_SUCCESS)
            {
                printf("\n\n%s, you won!\n\n", (*(root->pArrPlayer))->player.name);
                system("pause");
                moveNodeFromListToList(*(root->pArrPlayer), activeList, winList);
                *(root->pArrPlayer) = NULL;
                rootRes = 1; 
            }
            else if (status == NOT_FINISH)
            {
                printf("\nHi %s, it is your turn! Here is your board: \n\n", (*(root->pArrPlayer))->player.name);
                letUserChoose((*(root->pArrPlayer))->player.board, (*(root->pArrPlayer))->player.possibilities, x, y); 
                rootRes = 0;
            }
        }
        else
        {
            rootRes = 0; 
        }

        rightRes = gameRoundRec(root->right, activeList, winList);

        return leftRes + rightRes + rootRes; 
    }

}


void letUserChoose(short** board, Array*** possibilities, int x, int y)
{
    int choice;
    short i;
    sudokoPrintBoard(board);
    printf("Cell number [%d,%d] currently holds the minimum number of possible values, input one of the values listed below:\n", x, y);

    for (i = 0; i < possibilities[x][y]->size; i++)
        printf("%d. %d\n", i + 1, possibilities[x][y]->arr[i]);

    scanf("%d", &choice);
    while (choice < 1 || choice > 9)
    {
        printf("You entered an invalid number! please try again:\n");
        scanf("%d", &choice);
    }

    printf("Updating cell %d with value %d \n\n", x * 9 + y, choice);

    board[x][y] = choice;
    free(possibilities[x][y]->arr);
    possibilities[x][y]->arr = NULL;
    possibilities[x][y]->size = 0;
    updateArrsInField(possibilities, board[x][y], x, y);
}


void moveNodeFromListToList(PlayersListNode* node, PlayersList* lst1, PlayersList* lst2)
{
    if ((lst1->head == node) && (lst1->tail == node)) //if is the only node
    {
        lst1->head = lst1->tail = NULL;
    }

    else if (lst1->head == node) //if is the head
    {
        lst1->head = node->next;
        node->next->prev = NULL;
    }

    else if (lst1->tail == node) //if is the tail
    {
        lst1->tail = node->prev;
        node->prev->next = NULL;
    }

    else //if is in the middle of the list
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    insertNodeToEndPlayerList(lst2, node);
}


void deleteNodeFromPlayersList(PlayersListNode* node, PlayersList* lst)
{
    if ((lst->head == node) && (lst->tail == node)) //if is the only node
    {
        lst->head = lst->tail = NULL;
    }

    else if (lst->head == node) //if is the head
    {
        lst->head = node->next;
        node->next->prev = NULL;
    }

    else if (lst->tail == node) //if is the tail
    {
        lst->tail = node->prev;
        node->prev->next = NULL;
    }

    else //if is in the middle of the list
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node->player.name);
    freePossibleSolutions(node->player.possibilities);
    freeBoard(node->player.board);

    free(node);
}


CellList makeCList()
{
    CellList list;
    CellListNode* node = NULL, * prev = NULL;
    list.head = list.tail = NULL;
    short r, c;
    for (r = 0; r < 9; r++)
    {
        for (c = 0; c < 9; c++)
        {
            node = createCListNode(r, c);
            node->prev = prev;
            if (prev != NULL)
                prev->next = node;
            if (list.head == NULL)
                list.head = node;
            prev = node;
        }
    }
    node->next = NULL;
    list.tail = node;
    return list;
}


CellListNode* createCListNode(short r, short c)
{
    CellListNode* node = (CellListNode*)malloc(sizeof(CellListNode));
    checkAllocation(node);
    node->cell.row = r;
    node->cell.col = c;
    return node;
}


void insertNodeToEndPlayerList(PlayersList* list, PlayersListNode* node)
{
    if (isEmptyList(list) == true) {
        list->head = list->tail = node;
        node->next = node->prev = NULL;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
    }
}


bool isEmptyList(PlayersList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}


short** createInitializedBoard()
{
    short** board = (short**)malloc(sizeof(short*) * 9);
    checkAllocation(board);
    for (int i = 0; i < 9; i++)
    {
        board[i] = (short*)malloc(sizeof(short) * 9);
        checkAllocation(board[i]);
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = -1;
        }
    }
    return board;
}


PlayersListNode** createPArrFromList(PlayersList list, short n)
{
    PlayersListNode** playerArr = (PlayersListNode**)malloc(sizeof(PlayersListNode*) * n);
    checkAllocation(playerArr);
    PlayersListNode* node;
    int i = 0;
    node = list.head;
    while (node != NULL && i < n)
    {
        playerArr[i] = node;
        node = node->next;
        i++;
    }
    return playerArr;
}


void printPlayersList(PlayersList* lst)
{
    PlayersListNode* curr = lst->head;
    while (curr != NULL)
    {
        printf("%s! with his filled board: \n", curr->player.name);
        sudokoPrintBoard(curr->player.board);
        printf("\n");

        curr = curr->next;
    }
}


void freeList(PlayersList list)
{
    PlayersListNode* currNode, * temp;
    currNode = list.head;

    while (currNode != NULL)
    {
        temp = currNode->next;

        free(currNode->player.name);
        freePossibleSolutions(currNode->player.possibilities);
        freeBoard(currNode->player.board);

        free(currNode);
        currNode = temp;
    }
}


void freeBoard(short** board)
{
    for (int i = 0; i < 9; i++)
    {
        free(board[i]);
    }
    free(board);
}


void freeTree(Tree tree)
{
    if (tree.root == NULL)
        return;
    freeTreeHelper(tree.root);
    tree.root = NULL;
}


void freeTreeHelper(TreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeHelper(root->left);
        freeTreeHelper(root->right);
        free(root);
    }
}
