#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
// Functions.cpp
//
// שם הסטודנט : Omer Yacobi
// תעודת זהות : 330966151
// קורס       : שפת C
// תרגיל      : משחק טנקים
// תאריך      : 13.12.2025
//
// תיאור כללי:
// קובץ זה מכיל את כל מימושי הפונקציות הלוגיות
// של משחק הטנקים.
//-----------------------------------------------------------------------------

#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//-----------------------------------------------------------------------------
// וקטור כיוונים גלובלי
//-----------------------------------------------------------------------------

const Location g_arrlocDirections[5] =
{
    { 0,  0 },
    { -1, 0 },
    { 0,  1 },
    { 1,  0 },
    { 0, -1 }
};

//-----------------------------------------------------------------------------
// AllocateBoard
//-----------------------------------------------------------------------------
// תיאור:
// מקצה לוח משחק דינמי כולל קיר ביטחון.
//
// קלט:
// inBoardSize – גודל הלוח.
//
// פלט:
// מצביע ללוח או NULL.
//-----------------------------------------------------------------------------

char** AllocateBoard(int inBoardSize)
{
    char** pparrcBoard;
    int    nRow;

    pparrcBoard =
        (char**)malloc((inBoardSize + 2) * sizeof(char*));
    if (pparrcBoard == NULL)
    {
        return (NULL);
    }

    for (nRow = 0; nRow < inBoardSize + 2; nRow++)
    {
        pparrcBoard[nRow] =
            (char*)malloc((inBoardSize + 2) * sizeof(char));

        if (pparrcBoard[nRow] == NULL)
        {
            return (NULL);
        }
    }

    return (pparrcBoard);
}

//-----------------------------------------------------------------------------
// FreeBoard
//-----------------------------------------------------------------------------

void FreeBoard(char** pparrcBoard,
    int   inBoardSize)
{
    int nRow;

    for (nRow = 0; nRow < inBoardSize + 2; nRow++)
    {
        free(pparrcBoard[nRow]);
    }

    free(pparrcBoard);
}

//-----------------------------------------------------------------------------
// InitBoard
//-----------------------------------------------------------------------------

void InitBoard(char** pparrcBoard,
    int      inBoardSize,
    Location arrlocTanks[2])
{
    int nRow;
    int nCol;

    for (nRow = 0; nRow < inBoardSize + 2; nRow++)
    {
        for (nCol = 0; nCol < inBoardSize + 2; nCol++)
        {
            if (nRow == 0 || nCol == 0 ||
                nRow == inBoardSize + 1 ||
                nCol == inBoardSize + 1)
            {
                pparrcBoard[nRow][nCol] = WALL;
            }
            else if (nRow % 2 == 1 && nCol % 2 == 1)
            {
                pparrcBoard[nRow][nCol] = WALL;
            }
            else
            {
                pparrcBoard[nRow][nCol] = EMPTY;
            }
        }
    }

    arrlocTanks[0].nLine = inBoardSize / 2 + 1;
    arrlocTanks[0].nCol = 1;

    arrlocTanks[1].nLine = inBoardSize / 2 + 1;
    arrlocTanks[1].nCol = inBoardSize;

    pparrcBoard[arrlocTanks[0].nLine][arrlocTanks[0].nCol] = TANK;
    pparrcBoard[arrlocTanks[1].nLine][arrlocTanks[1].nCol] = TANK;
}

//-----------------------------------------------------------------------------
// PrintBoard
//-----------------------------------------------------------------------------

void PrintBoard(char** pparrcBoard,
    int   inBoardSize)
{
    int nRow;
    int nCol;

    for (nRow = 1; nRow <= inBoardSize; nRow++)
    {
        for (nCol = 1; nCol <= inBoardSize; nCol++)
        {
            printf("%c ", pparrcBoard[nRow][nCol]);
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------
// MoveTank
//-----------------------------------------------------------------------------

void MoveTank(char** pparrcBoard,
    Location* plocTank,
    int        inDirection,
    int        inSteps)
{
    int      nStep;
    Location locDelta;

    locDelta = g_arrlocDirections[inDirection];

    pparrcBoard[plocTank->nLine][plocTank->nCol] = EMPTY;

    for (nStep = 0; nStep < inSteps; nStep++)
    {
        if (pparrcBoard[plocTank->nLine + locDelta.nLine]
            [plocTank->nCol + locDelta.nCol] != EMPTY)
        {
            break;
        }

        plocTank->nLine += locDelta.nLine;
        plocTank->nCol += locDelta.nCol;
    }

    pparrcBoard[plocTank->nLine][plocTank->nCol] = TANK;
}

//-----------------------------------------------------------------------------
// ShootStraight
//-----------------------------------------------------------------------------

int ShootStraight(char** pparrcBoard,
    Location locTank,
    int      inDirection)
{
    Location locDelta;

    locDelta = g_arrlocDirections[inDirection];

    locTank.nLine += locDelta.nLine;
    locTank.nCol += locDelta.nCol;

    while (1)
    {
        if (pparrcBoard[locTank.nLine][locTank.nCol] == WALL)
        {
            pparrcBoard[locTank.nLine][locTank.nCol] = EMPTY;
            return (0);
        }

        if (pparrcBoard[locTank.nLine][locTank.nCol] == TANK)
        {
            return (1);
        }

        locTank.nLine += locDelta.nLine;
        locTank.nCol += locDelta.nCol;
    }
}

//-----------------------------------------------------------------------------
// ShootTurning
//-----------------------------------------------------------------------------

int ShootTurning(char** pparrcBoard,
    Location locTank,
    int      inDirection)
{
    int      nTurnsCounter;
    Location locDelta;

    nTurnsCounter = 0;

    while (nTurnsCounter < 5)
    {
        locDelta = g_arrlocDirections[inDirection];

        locTank.nLine += locDelta.nLine;
        locTank.nCol += locDelta.nCol;

        if (pparrcBoard[locTank.nLine][locTank.nCol] == WALL)
        {
            inDirection = (inDirection % 4) + 1;
            nTurnsCounter++;
            continue;
        }

        if (pparrcBoard[locTank.nLine][locTank.nCol] == TANK)
        {
            return (1);
        }
    }

    return (0);
}

//-----------------------------------------------------------------------------
// AirStrike
//-----------------------------------------------------------------------------

int AirBomb(char** pparrcBoard,
    int    inCenterLine,
    int    inCenterCol)
{
    int nRowOffset;
    int nColOffset;

    for (nRowOffset = -1; nRowOffset <= 1; nRowOffset++)
    {
        for (nColOffset = -1; nColOffset <= 1; nColOffset++)
        {
            if ((rand() % 2) == 1)
            {
                if (pparrcBoard[inCenterLine + nRowOffset]
                    [inCenterCol + nColOffset] == TANK)
                {
                    return (1);
                }

                if (pparrcBoard[inCenterLine + nRowOffset]
                    [inCenterCol + nColOffset] == WALL)
                {
                    pparrcBoard[inCenterLine + nRowOffset]
                        [inCenterCol + nColOffset] = EMPTY;
                }
            }
        }
    }

    return (0);
}

//-----------------------------------------------------------------------------
// CountWalls
//-----------------------------------------------------------------------------

int CountWalls(char** pparrcBoard,
    int   inBoardSize)
{
    int nRow;
    int nCol;
    int nCounter;

    nCounter = 0;

    for (nRow = 1; nRow <= inBoardSize; nRow++)
    {
        for (nCol = 1; nCol <= inBoardSize; nCol++)
        {
            if (pparrcBoard[nRow][nCol] == WALL)
            {
                nCounter++;
            }
        }
    }

    return (nCounter);
}
