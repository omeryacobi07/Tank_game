#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
// TankGame.cpp
//
// שם הסטודנט : Omer Yacobi
// תעודת זהות : 330966151
// קורס       : שפת C
// תרגיל      : משחק טנקים
// תאריך      : 13.12.2025
//
// תיאור כללי:
// קובץ זה מכיל את פונקציית main ואת ממשק המשתמש.
//-----------------------------------------------------------------------------

#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int main()
{
    int      nBoardSize;
    int      nAction;
    int      nDirection;
    int      nSteps;
    int      nCenterLine;
    int      nCenterCol;
    int      nCurrentPlayer;
    int      nGameOver;

    char** pparrcBoard;
    Location arrlocTanks[2];

    nCurrentPlayer = 0;
    nGameOver = 0;

    srand((unsigned)time(NULL));

    printf("Enter board size (odd number): ");
    scanf("%d", &nBoardSize);

    pparrcBoard = AllocateBoard(nBoardSize);
    if (pparrcBoard == NULL)
    {
        printf("Memory allocation failed\n");
        return (1);
    }

    InitBoard(pparrcBoard,
        nBoardSize,
        arrlocTanks);

    PrintBoard(pparrcBoard,
        nBoardSize);

    while (!nGameOver)
    {
        printf("\nPlayer %d turn\n", nCurrentPlayer + 1);
		printf("Choose action:\n");
        printf("1 - Move\n");
        printf("2 - Shoot\n");
        printf("3 - Turning Shot\n");
        printf("4 - Air Bomb\n");
        printf("999 - Exit\n");

        scanf("%d", &nAction);

        if (nAction == 999)
        {
            break;
        }

        switch (nAction)
        {
        case 1:
			printf("Enter direction (1-up, 2-right, 3-down, 4-left): ");
			printf("Enter steps: ");
            scanf("%d %d", &nDirection, &nSteps);
            MoveTank(pparrcBoard,
                &arrlocTanks[nCurrentPlayer],
                nDirection,
                nSteps);
            break;

        case 2:
            printf("Enter direction (1-up, 2-right, 3-down, 4-left): ");
            scanf("%d", &nDirection);
            if (ShootStraight(pparrcBoard,
                arrlocTanks[nCurrentPlayer],
                nDirection))
            {
                printf("Player %d wins!\n", nCurrentPlayer + 1);
                nGameOver = 1;
            }
            break;

        case 3:
            printf("Enter direction (1-up, 2-right, 3-down, 4-left): ");
            scanf("%d", &nDirection);
            if (ShootTurning(pparrcBoard,
                arrlocTanks[nCurrentPlayer],
                nDirection))
            {
                printf("Player %d wins!\n", nCurrentPlayer + 1);
                nGameOver = 1;
            }
            break;

        case 4:
			printf("Enter air strike center (line and column): ");
            scanf("%d %d", &nCenterLine, &nCenterCol);
            if (AirBomb(pparrcBoard,
                nCenterLine,
                nCenterCol))
            {
                printf("Player %d wins!\n", nCurrentPlayer + 1);
                nGameOver = 1;
            }
            break;

        default:
            break;
        }

        PrintBoard(pparrcBoard,
            nBoardSize);

        if (!nGameOver &&
            CountWalls(pparrcBoard, nBoardSize) == 0)
        {
            printf("Draw! No walls left.\n");
            nGameOver = 1;
        }

        nCurrentPlayer = 1 - nCurrentPlayer;
    }

    FreeBoard(pparrcBoard,
        nBoardSize);

    return (0);
}
