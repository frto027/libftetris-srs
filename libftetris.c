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
#include "libftetris.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/*0 R 2 L*/
/*[FTE_TETROMINO_*][FTE_ROT_*][4*(y from top) + (x from left)]*/
static const fte_color_t tetromino_colors[8][4][4*4] = {
    /*NONE*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*I*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_I   , FTE_COLOR_I   , FTE_COLOR_I   , FTE_COLOR_I   , 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_I   , FTE_COLOR_I   , FTE_COLOR_I   , FTE_COLOR_I   , 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_I   , FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*O*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_O   , FTE_COLOR_O   , FTE_COLOR_NONE,  
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*T*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_T   , FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_T   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*S*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, 
            FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, 
            FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_S   , FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_S   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*Z*/{
        {
            FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_Z   , FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_Z   , FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*J*/{
        {
            FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_J   , FTE_COLOR_J   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },/*L*/{
        {
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_NONE, 
            FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_NONE, 
            FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        },{
            FTE_COLOR_L   , FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_L   , FTE_COLOR_NONE, FTE_COLOR_NONE, 
            FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, FTE_COLOR_NONE, 

        }
    },
};
#define SRS_TEST_COUNT 5
//[from FTE_ROT_*][left or right][test 0 1 2 3 4][x or y]
static const signed char WallKick_TSZJL[4][2][SRS_TEST_COUNT][2] = {
    {//0
        {//0->R
            {0,0},{-1,0},{-1,1},{0,-2},{-1,-2}
        },{//0->L
            {0,0},{1,0},{1,1},{0,-2},{1,-2}
        }
    },{//R
        {//R->2
            {0,0},{1,0},{1,-1},{0,2},{1,2}
        },{//R->0
            {0,0},{1,0},{1,-1},{0,2},{1,2}
        }
    },{//2
        {//2->L
            {0,0},{1,0},{1,1},{0,-2},{1,-2}
        },{//2->R
            {0,0},{-1,0},{-1,1},{0,-2},{-1,-2}
        }
    },{//L
        {//L->0
            {0,0},{-1,0},{-1,-1},{0,2},{-1,2}
        },{//L->2
            {0,0},{-1,0},{-1,-1},{0,2},{-1,2}
        }
    }
};

static signed char WallKick_I[4][2][SRS_TEST_COUNT][2] = {
    {//0
        {//0->R
            {0,0},{-2,0},{1,0},{-2,-1},{1,2}
        },{//0->L
            {0,0},{-1,0},{2,0},{-1,2},{2,-1}
        }
    },{//R
        {//R->2
            {0,0},{-1,0},{2,0},{-1,2},{2,-1}
        },{//R->0
            {0,0},{2,0},{-1,0},{2,1},{-1,-2}
        }
    },{//2
        {//2->L
            {0,0},{2,0},{-1,0},{2,1},{-1,-2}
        },{//2->R
            {0,0},{1,0},{-2,0},{1,-2},{-2,1}
        }
    },{//L
        {//L->0
            {0,0},{1,0},{-2,0},{1,-2},{-2,1}
        },{//L->2
            {0,0},{-2,0},{1,0},{-2,-1},{1,2}
        }
    }
};

int fteTryFill(FTE_GAME * game){
    int gleft = game->tetromino_floating.left;
    int gtop = game->tetromino_floating.bottom;
    const fte_color_t * tcolors = tetromino_colors[game->tetromino_floating.type][game->tetromino_floating.rotation];
    fte_color_t (*colors)[FTE_HEIGHT] = game->colors;
    //碰撞检测
    for(int left = 0;left < 4;left++){
        for(int top = 0;top < 4;top++){
            //边界碰撞
            if(tcolors[left+top*4] != FTE_COLOR_NONE){
                //block碰撞
                int target_left = gleft+left;
                int target_top = gtop - top;
                if(target_left >= FTE_WIDTH || target_left < 0 || target_top < 0  || colors[target_left][target_top] != FTE_COLOR_NONE){
                    return FALSE;
                }
            }
        }
    }
    //填充
    for(int left = 0;left < 4;left++){
        for(int top = 0;top < 4;top++){
            if(tcolors[left+top*4] != FTE_COLOR_NONE){
                colors[gleft + left][gtop - top] = tcolors[left+top*4];
            }
        }
    }

    return TRUE;
}
void fteClean(FTE_GAME * game){
    int gleft = game->tetromino_floating.left;
    int gtop = game->tetromino_floating.bottom;
    const fte_color_t * tcolors = tetromino_colors[game->tetromino_floating.type][game->tetromino_floating.rotation];
    fte_color_t (*colors)[FTE_HEIGHT] = game->colors;
    //填充
    for(int left = 0;left < 4;left++){
        for(int top = 0;top < 4;top++){
            if(tcolors[left+top*4] != FTE_COLOR_NONE){
                colors[gleft + left][gtop - top] = FTE_COLOR_NONE;
            }
        }
    }
}
void fteFillGhost(FTE_GAME * game){
    int gleft = game->tetromino_floating.left;
    int gtop = game->tetromino_floating.bottom;
    const fte_color_t * tcolors = tetromino_colors[game->tetromino_floating.type][game->tetromino_floating.rotation];
    fte_color_t (*colors)[FTE_HEIGHT] = game->colors;
    int maxdrop = gtop;
    //碰撞测试
    for(int left = 0;left < 4;left++){
        int ttop = -1;
        //find a block in left
        for(int top = 3;top >= 0;top--){
            if(tcolors[top * 4 + left] != FTE_COLOR_NONE){
                ttop = top;
                break;
            }
        }
        if(ttop != -1){
            int float_block = gtop - ttop;
            //touch test
            for(int droptop=0;droptop<maxdrop;droptop++){
                if(float_block - droptop - 1 < 0 || colors[gleft + left][float_block - droptop - 1] != FTE_COLOR_NONE){
                    maxdrop = droptop;
                    break;
                }
            }
        }
    }
    //fill
    for(int left = 0;left < 4;left++){
        for(int top=0;top<4;top++){
            if(tcolors[left+top*4] != FTE_COLOR_NONE && colors[gleft + left][gtop-maxdrop-top] == FTE_COLOR_NONE){
                colors[gleft + left][gtop-maxdrop-top]=FTE_COLOR_GHOST;
            }
        }
    }
}
void fteCleanGhost(FTE_GAME * game){
    int gleft = game->tetromino_floating.left;
    int gtop = game->tetromino_floating.bottom;
    const fte_color_t * tcolors = tetromino_colors[game->tetromino_floating.type][game->tetromino_floating.rotation];
    fte_color_t (*colors)[FTE_HEIGHT] = game->colors;
    for(int left = 0;left < 4;left++){
        for(int top = 3;top >= 0;top--){
            if(tcolors[left+top*4] != FTE_COLOR_NONE){
                int cleartop = gtop - top;
                while(cleartop >= 0 && colors[gleft + left][cleartop] != FTE_COLOR_GHOST){
                    cleartop--;
                }
                while(cleartop >= 0 && colors[gleft + left][cleartop] == FTE_COLOR_GHOST){
                    colors[gleft + left][cleartop] = FTE_COLOR_NONE;
                    cleartop--;
                }
                break;
            }
        }
    }
}

void fteGameInit(FTE_GAME * game){
    for(int i=0;i<FTE_WIDTH;i++){
        for(int j=0;j<FTE_HEIGHT;j++){
            game->colors[i][j] = FTE_COLOR_NONE;
        }
        for(int j=0;j<FTE_GARBAGE_MAXROWS;j++){
            game->garbage_queue.garbage_buffer[i][j] = FTE_COLOR_NONE;
        }
    }
    game->garbage_queue.count = 0;

    game->tetromino_floating.type = FTE_TETROMINO_NONE;
    game->tetromino_floating.rotation = FTE_ROT_0;
    game->ghost = 0;
}

void fteGameSetGhost(FTE_GAME * game,int isShow){
    if(game->ghost != isShow){
        game->ghost = isShow;
        if(game->tetromino_floating.type != FTE_TETROMINO_NONE){
            if(isShow){
                fteFillGhost(game);
            }else{
                fteCleanGhost(game);
            }
        }
    }
}

fte_result_t fteRot(FTE_GAME * game,signed char direction){
    int old_rot = game->tetromino_floating.rotation;
    int old_left = game->tetromino_floating.left;
    int old_top = game->tetromino_floating.bottom;
    const signed char (*tests)[2] = NULL;
    //assert(direction == 1 || direction == -1)
    switch (game->tetromino_floating.type)
    {
    case FTE_TETROMINO_O:
        //O-spin
        return FTE_RESULT_MOVE_SUCCESS;
    case FTE_TETROMINO_I:
        tests = WallKick_I[old_rot][direction == 1 ? 0 : 1];
        break;
    case FTE_TETROMINO_T:
    case FTE_TETROMINO_S:
    case FTE_TETROMINO_Z:
    case FTE_TETROMINO_J:
    case FTE_TETROMINO_L:
        tests = WallKick_TSZJL[old_rot][direction == 1 ? 0 : 1];
        break;
    default:
        //None-spin??
        return FTE_RESULT_MOVE_FAILED;
    }
    //clean float block
    fteClean(game);
    if(game->ghost)
        fteCleanGhost(game);
    //try rot
    game->tetromino_floating.rotation = (old_rot + 4 + direction)%4;
    for(int testing = 0;testing < SRS_TEST_COUNT;testing++){
        game->tetromino_floating.left = old_left + tests[testing][0];
        game->tetromino_floating.bottom = old_top + tests[testing][1];
        if(fteTryFill(game)){
             if(game->ghost){
                fteFillGhost(game);
            }
            return testing == 0 ? FTE_RESULT_MOVE_SUCCESS : FTE_RESULT_MOVE_WALLKICK;
        }
    }

    //rot failed
    game->tetromino_floating.rotation = old_rot;
    game->tetromino_floating.left = old_left;
    game->tetromino_floating.bottom = old_top;
    //it must success:
    fteTryFill(game);
    return FTE_RESULT_MOVE_FAILED;
}

fte_result_t fteRotLeft(FTE_GAME * game){
    return fteRot(game,-1);
}

fte_result_t fteRotRight(FTE_GAME * game){
    return fteRot(game,1);
}

fte_result_t fteMove(FTE_GAME * game,signed char leftplus,signed char topplus){
    if(game->tetromino_floating.type == FTE_TETROMINO_NONE){
        return FTE_RESULT_MOVE_FAILED;
    }
    int old_left = game->tetromino_floating.left;
    int old_top = game->tetromino_floating.bottom;
    //clean float block
    fteClean(game);
    if(game->ghost)
        fteCleanGhost(game);
    game->tetromino_floating.left = old_left + leftplus;
    game->tetromino_floating.bottom = old_top + topplus;
    if(fteTryFill(game)){
        if(game->ghost)
            fteFillGhost(game);
        return FTE_RESULT_MOVE_SUCCESS;
    }
    game->tetromino_floating.left = old_left;
    game->tetromino_floating.bottom = old_top;
    fteTryFill(game);
    if(game->ghost)
        fteFillGhost(game);
    return FTE_RESULT_MOVE_FAILED;
}

fte_result_t fteMoveLeft(FTE_GAME * game){
    return fteMove(game,-1,0);
}
fte_result_t fteMoveRight(FTE_GAME * game){
    return fteMove(game,1,0);
}
fte_result_t fteMoveDown(FTE_GAME * game){
    return fteMove(game,0,-1);
}

int fteCleanLines(FTE_GAME * game){
    int count = 0;
    for(int line = game->tetromino_floating.bottom,i=0;line >= 0 && i < 4;i++,line--){
        int j;
        for(j = 0;j<FTE_WIDTH;j++){
            if(game->colors[j][line] == FTE_COLOR_NONE){
                break;
            }
        }
        if(j == FTE_WIDTH){
            //clean line
            for(j = 0;j<10;j++){
                for(int heightscan = line;heightscan < FTE_HEIGHT - 1;heightscan++){
                    game->colors[j][heightscan] = game->colors[j][heightscan + 1];
                }
            }
            count++;
            //what else?
        }
    }
    return count;
}
void fteFillGarbages(FTE_GAME * game){
    int garbage_count = game->garbage_queue.count;
    for(int left = 0;left < FTE_WIDTH;left++){
        //lift
        for(int tops = FTE_HEIGHT - 1;tops >= garbage_count;tops--){
            game->colors[left][tops] = game->colors[left][tops - garbage_count];
        }
    }
    //fill garbage
    for(int left = 0;left < FTE_WIDTH;left++){
        for(int top = 0;top < garbage_count;top++){
            game->colors[left][top] = game->garbage_queue.garbage_buffer[left][top];
        }
    }
    game->garbage_queue.count = 0;
}

fte_result_t fteSpawn(FTE_GAME * game,fte_tetromino_t type,int clean_current){
    if(game->tetromino_floating.type != FTE_TETROMINO_NONE){
        if(game->ghost){
            fteCleanGhost(game);
        }
        if(clean_current){
            fteClean(game);
        }
    }
    game->tetromino_floating.type = type;
    /* fixed position */
    game->tetromino_floating.left = 3;
    game->tetromino_floating.bottom = 22;
    game->tetromino_floating.rotation = FTE_ROT_0;

    if(type != FTE_TETROMINO_NONE){
        if(fteTryFill(game)){
            if(game->ghost){
                fteFillGhost(game);
            }
            return FTE_RESULT_MOVE_SUCCESS;
        }else{
            //game over
            fteClean(game);
            fteTryFill(game);
            return FTE_RESULT_MOVE_FAILED;
        }
    }
    return FTE_RESULT_MOVE_SUCCESS;
}

fte_result_t fteReplaceCurrentTetromino(FTE_GAME * game,fte_tetromino_t new_tetromino){
    return fteSpawn(game,new_tetromino,1);
}
fte_tetromino_t fteGetCurrentTetromino(FTE_GAME * game){
    return game->tetromino_floating.type;
}
fte_result_t fteSpawnNext(FTE_GAME * game,fte_tetromino_t next,int * clean_count){
    int r = fteCleanLines(game);
    if(clean_count){
        *clean_count = r;
    }
    fteFillGarbages(game);
    return fteSpawn(game,next,0);
}

void fteAddGarbage(FTE_GAME * game,fte_color_t garbage[FTE_WIDTH]){
    int count = game->garbage_queue.count;
    if(count >= FTE_GARBAGE_MAXROWS){
        //garbage is full!
        return;
    }
    game->garbage_queue.count = count + 1;
    for(int i=0;i<FTE_WIDTH;i++){
        game->garbage_queue.garbage_buffer[i][count] = garbage[i];
    }
}

fte_tetromino_t fte7BagGenItem(FTE_7BAG * bag){
    if(bag->next >= 7){
        bag->next = 0;
        fte_tetromino_t * buf = bag->bagItems;
        unsigned int seed = bag->privseed;
        //Fisher-Yates shuffle
        for(int i=0;i<5;i++){
            seed = (1103515245 * seed + 12345);
            int j = (seed % (7 - i)) + i;
            fte_tetromino_t temp = buf[i];
            buf[i] = buf[j];
            buf[j] = temp;
        }
        bag->privseed = seed;
    }
    return bag->bagItems[bag->next++];
}

void fte7BagInit(FTE_7BAG * bag,unsigned int seed){
    bag->privseed = seed;
    bag->next = 7;
    //load bag items
    for(int i=0;i<7;i++){
        bag->bagItems[i] = i+1;
    }
}