#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
// Functions.h
//
// שם הסטודנט : Omer Yacobi
// תעודת זהות : 330966151
// קורס       : שפת C
// תרגיל      : משחק טנקים
// תאריך      : 13.12.2025
//
// תיאור כללי:
// קובץ זה מכיל הגדרות, טיפוסים והצהרות לפונקציות
// של משחק הטנקים.
//-----------------------------------------------------------------------------

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//-----------------------------------------------------------------------------
// Define section
//-----------------------------------------------------------------------------

#define WALL    'X'
#define TANK    'O'
#define EMPTY   ' '

#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4

//-----------------------------------------------------------------------------
// Typedef section
//-----------------------------------------------------------------------------

typedef struct
{
    int nLine;
    int nCol;
} Location;

//-----------------------------------------------------------------------------
// Global const section
//-----------------------------------------------------------------------------

extern const Location g_arrlocDirections[5];

//-----------------------------------------------------------------------------
// Prototype section
//-----------------------------------------------------------------------------

char** AllocateBoard(int inBoardSize);

void FreeBoard(char** pparrcBoard,
    int   inBoardSize);

void InitBoard(char** pparrcBoard,
    int      inBoardSize,
    Location arrlocTanks[2]);

void PrintBoard(char** pparrcBoard,
    int   inBoardSize);

void MoveTank(char** pparrcBoard,
    Location* plocTank,
    int        inDirection,
    int        inSteps);

int ShootStraight(char** pparrcBoard,
    Location locTank,
    int      inDirection);

int ShootTurning(char** pparrcBoard,
    Location locTank,
    int      inDirection);

int AirBomb(char** pparrcBoard,
    int    inCenterLine,
    int    inCenterCol);

int CountWalls(char** pparrcBoard,
    int   inBoardSize);

#endif
