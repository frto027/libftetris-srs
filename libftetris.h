/*
    libftetris-srs
    Copyright (C) 2020  frto027

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef LIBFTEETRIS_H
#define LIBFTEETRIS_H

//type of tetromino I O T S Z J L
typedef char fte_tetromino_t;
#define FTE_TETROMINO_NONE 0
#define FTE_TETROMINO_I 1
#define FTE_TETROMINO_O 2
#define FTE_TETROMINO_T 3
#define FTE_TETROMINO_S 4
#define FTE_TETROMINO_Z 5
#define FTE_TETROMINO_J 6
#define FTE_TETROMINO_L 7

//colors/blocks in game sence, FTE_COLOR_NONE is empty block.
typedef char fte_color_t;
#define FTE_COLOR_NONE 0
#define FTE_COLOR_I 1
#define FTE_COLOR_O 2
#define FTE_COLOR_T 3
#define FTE_COLOR_S 4
#define FTE_COLOR_Z 5
#define FTE_COLOR_J 6
#define FTE_COLOR_L 7
#define FTE_COLOR_GARBAGE 8
#define FTE_COLOR_GHOST   9

//rot direction is SRS system
//0 -> 1 -> 2 -> 3 -> 0 (right)
//0 <- 1 <- 2 <- 3 <- 0 (left)
typedef char fte_rot_t;
#define FTE_ROT_0 0
#define FTE_ROT_R 1
#define FTE_ROT_2 2
#define FTE_ROT_L 3

//game scense size
#define FTE_NEXT_SIZE   6
#define FTE_WIDTH       10
#define FTE_HEIGHT      40

#define FTE_GARBAGE_MAXROWS 20

typedef char fte_result_t;
#define FTE_RESULT_MOVE_FAILED      0
#define FTE_RESULT_MOVE_SUCCESS     1
#define FTE_RESULT_MOVE_WALLKICK    2

typedef struct FTE_GAME
{
    /* show colors to your game */
    fte_color_t colors[FTE_WIDTH][FTE_HEIGHT];
    struct{
        fte_color_t garbage_buffer[FTE_WIDTH][FTE_GARBAGE_MAXROWS];
        int count;
    }garbage_queue;
    
    struct
    {
        fte_tetromino_t type;
        fte_rot_t rotation;
        int left,bottom;
    }tetromino_floating;
    int ghost;
} FTE_GAME;

void fteGameInit(FTE_GAME * game);
void fteGameSetGhost(FTE_GAME * game,int isShow);
//SRS
fte_result_t fteRotLeft(FTE_GAME * game);
fte_result_t fteRotRight(FTE_GAME * game);
fte_result_t fteMoveLeft(FTE_GAME * game);
fte_result_t fteMoveRight(FTE_GAME * game);
fte_result_t fteMoveDown(FTE_GAME * game);
//Hold
//new_tetromino == FTE_TETROMINO_NONE is okay
fte_result_t fteReplaceCurrentTetromino(FTE_GAME * game,fte_tetromino_t new_tetromino);
fte_tetromino_t fteGetCurrentTetromino(FTE_GAME * game);

//spawn your own tetromino.
//you can also use fte7BagSpawnNext() instead of this function
//next can be FTE_TETROMINO_NONE, the game will stuck
fte_result_t fteSpawnNext(FTE_GAME * game,fte_tetromino_t next,int * clean_count /* OUTPUT parameter, line count of clean*/);

//garbage will be generated at next call of fteSpawnNext()
void fteAddGarbage(FTE_GAME * game,fte_color_t garbage[FTE_WIDTH]);

//================7-bag system=================
#define FTE_7BAG_BUFFERLEN 7
typedef struct FTE_7BAG{
    fte_tetromino_t bagItems[FTE_7BAG_BUFFERLEN];
    int next;
    unsigned int privseed;
} FTE_7BAG;

void fte7BagInit(FTE_7BAG * bag,unsigned int seed);
fte_tetromino_t fte7BagGenItem(FTE_7BAG * bag);
#endif