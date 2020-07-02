#include <stdio.h>
#include <stdlib.h>
#include "libftetris.h"
#include <time.h>
FTE_GAME game;
FTE_7BAG bag;

fte_tetromino_t queue[6];
fte_tetromino_t hold;
int holded;
int move_next_fail_count;

unsigned long long keys['z'-'a'+1];
//按键延迟的两个控制参数，单位是毫秒
#define PRESS_DELAY 300
#define REPEAT_DELAY 30

#define CSI "\e["

unsigned long long GetCurTimeMs(){
    return clock()/ (CLOCKS_PER_SEC / 1000);
}

//IOTSZJL block color
const char tetromino_colors[][19] = {
    CSI "38;2;55;55;55m",/*none*/
    CSI "38;2;0;255;255m",/*I*/
    CSI "38;2;255;255;0m",/*O*/
    CSI "38;2;128;0;128m",/*T*/
    CSI "38;2;0;128;0m",/*S*/
    CSI "38;2;255;0;0m",/*Z*/
    CSI "38;2;0;0;255m",/*J*/
    CSI "38;2;255;165;0m",/*L*/
};
const char tetromino_colors_ghost[][19] = {
    CSI "38;2;55;55;55m",/*none*/
    CSI "38;2;0;128;128m",/*I*/
    CSI "38;2;128;128;0m",/*O*/
    CSI "38;2;64;0;64m",/*T*/
    CSI "38;2;0;64;0m",/*S*/
    CSI "38;2;128;0;0m",/*Z*/
    CSI "38;2;0;0;128m",/*J*/
    CSI "38;2;128;84;0m",/*L*/
};

const char * message = NULL;
unsigned long long message_time = 0;
void showmsg(const char * msg){
    message = msg;
    message_time = GetCurTimeMs() + 1500;
}

//cache 6 tetromino to show next
fte_tetromino_t PickItem(){
    fte_tetromino_t ret = queue[0];
    for(int i=0;i<5;i++){
        queue[i] = queue[i+1];
    }
    queue[5] = fte7BagGenItem(&bag);
    return ret;
}
int died = 0;

void MySpawnNext(){
    int count;
    died |= fteSpawnNext(&game,PickItem(),&count) == FTE_RESULT_MOVE_FAILED;
    move_next_fail_count = 0;
    holded = 0;
    if(count == 4){
        showmsg("Tetris!");
    }
}

void MyHold(){
    if(holded){
        return;
    }
    if(hold == FTE_TETROMINO_NONE){
        hold = fteGetCurrentTetromino(&game);
        fteReplaceCurrentTetromino(&game,PickItem());
    }else{
        fte_tetromino_t nhold = fteGetCurrentTetromino(&game);
        fteReplaceCurrentTetromino(&game,hold);
        hold = nhold;
    }
    holded = 1;
}

void HandleInput(char input){
    if(input == 'q'){
        exit(0);
    }
    if(died){
        return;
    }
    switch(input){
        case 'a':
            if(fteMoveLeft(&game))
                move_next_fail_count = 0;
            break;
        case 'd':
            if(fteMoveRight(&game))
                move_next_fail_count = 0;
            break;
        case 's':
            fteMoveDown(&game);
            break;
        case 'w':
            while(fteMoveDown(&game) != FTE_RESULT_MOVE_FAILED);
            MySpawnNext();
            break;
        case 'j':
            if(fteRotLeft(&game) != FTE_RESULT_MOVE_FAILED)
                move_next_fail_count = 0;
            break;
        case 'k':
            if(fteRotRight(&game) != FTE_RESULT_MOVE_FAILED)
                move_next_fail_count = 0;
            break;
        case 'i':
            MyHold(&game);
            break;
    }
}

void GameStart(unsigned int seed){
    fteGameInit(&game);
    fte7BagInit(&bag,seed);
    fteGameSetGhost(&game,1);
    for(int i=0;i<6;i++){
        queue[i] = fte7BagGenItem(&bag);
    }
    hold = FTE_TETROMINO_NONE;
    MySpawnNext();
    //hide cursor
    printf(CSI "?25l");
    //background
    printf(CSI "48;2;0;0;0m");
    printf(CSI "0;0H");
    //clean buffer
    /*
    for(int i=0;i<50000;i++){
        putchar(' ');
    }
    */
    for(int i=0;i<28;i++){
        for(int j=0;j<40;j++){
            putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}
//游戏主逻辑
void UpdateFrame(char input){
    static unsigned long long lasttime = 0;
    static int fail_count = 0;
    unsigned long long thistime = GetCurTimeMs();

    if(input){
        HandleInput(input);
    }
    //set cursor
    printf(CSI "0;0H");
    printf(CSI "37m" "q:quit\twasd:move\tjk:rot\ti:hold\n");
    printf("nexts:");
    for(int i=0;i<6;i++){
        printf(tetromino_colors[queue[i]]);
        putchar("-IOTSZJL"[queue[i]]);
    };
    printf(CSI "37m" "\t hold:");
    printf(tetromino_colors[hold]);
    putchar("-IOTSZJL"[hold]);
    printf(CSI "37m" "\tlock_remain:%d\n",3 - move_next_fail_count);

    if(GetCurTimeMs() < message_time){
        printf("message: %s",message);
    }
    putchar('\n');


    putchar(201);
    for(int i=0;i<21;i++)putchar(205);
    putchar(187);
    putchar(' ');
    putchar('\n');

    for(int i=21;i>=0;i--){
        putchar(186);
        putchar(' ');
        for(int j=0;j<FTE_WIDTH;j++){
            if(game.colors[j][i]){
                if(game.colors[j][i] == FTE_COLOR_GHOST){
                    printf(tetromino_colors_ghost[fteGetCurrentTetromino(&game)]);
                    putchar(254);
                }else{
                    printf(tetromino_colors[game.colors[j][i]]);
                    putchar(254);
                }
               
            }else{
                printf(tetromino_colors[0]);
                putchar(254);
            }
        }
        printf(CSI "37m");
        putchar(186);
        putchar(' ');
        putchar('\n');
    }

    putchar(200);
    for(int i=0;i<21;i++)putchar(205);
    putchar(188);
    putchar(' ');
    putchar('\n');


    if(died){
        showmsg("you died");
        return;
    }
    
    if(thistime - lasttime > 500){
        lasttime = thistime;
        if(fteMoveDown(&game) == FTE_RESULT_MOVE_FAILED){
            move_next_fail_count++;
        }
        if(move_next_fail_count >= 3){
            MySpawnNext();
        }
    }
}

//main函数从控制台读键盘输入、初始化终端，所以是平台相关的

#include <Windows.h>

int main(void)
{
    HANDLE hStdin,hStdout;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout =GetStdHandle(STD_OUTPUT_HANDLE);
    INPUT_RECORD inputs;
    DWORD cNumRead;
    system("cls");
    //clean screen
    if (!SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
    {
        printf("Can't set console mode.\n");
        return -1;
    }
    CONSOLE_CURSOR_INFO info;
    info.bVisible = 0;
    info.dwSize = 1;
    //windows下的控制台输入
    SetConsoleOutputCP(437);
    for(int i=0;i<sizeof(keys)/sizeof(*keys);i++){
        keys[i] = 0;
    }
    
    GameStart(time(NULL));
    /*
    for(int i=0;i<sizeof(garbages)/sizeof(*garbages);i++){
        fteAddGarbage(&game,garbages[i]);
    }*/
    while (1)
    {
        //处理一个控制台输入
        //不管你信不信，这个输入控制已经可以进行极简操作了
        char input = 0;
        if (!PeekConsoleInput(hStdin, &inputs, 1, &cNumRead))
        {
            printf("Read Failed.\n");
            return -1;
        }
        if (cNumRead)
        {
            ReadConsoleInput(hStdin, &inputs, 1, &cNumRead);
        }
        if (cNumRead)
        {
            //key event
            if(inputs.EventType == KEY_EVENT && inputs.Event.KeyEvent.uChar.AsciiChar >= 'a' && inputs.Event.KeyEvent.uChar.AsciiChar <= 'z'){
                if (inputs.Event.KeyEvent.bKeyDown)
                {
                    //key down
                    if(keys[inputs.Event.KeyEvent.uChar.AsciiChar - 'a'] == 0){
                        input = (inputs.Event.KeyEvent.uChar.AsciiChar);
                        keys[input - 'a'] = GetCurTimeMs() + PRESS_DELAY - REPEAT_DELAY;
                    }/* else key repeat, do nothing*/
                }else{
                    //key up
                    keys[inputs.Event.KeyEvent.uChar.AsciiChar - 'a'] = 0;
                }
            }
        }
        if(input == 0){
            //repeat the key by myself
            for(int i=0;i<sizeof(keys)/sizeof(*keys);i++){
                if(keys[i] && GetCurTimeMs() > keys[i] + REPEAT_DELAY){
                    input = i + 'a';
                    keys[i] = GetCurTimeMs();
                    break;
                }
            }
        }
        UpdateFrame(input);
    }
}