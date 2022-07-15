
// MathLibrary.h - Contains declarations of math functions

#pragma once





#ifdef AI_EXPORTS
#define AI_API __declspec(dllexport)
#else
#define AI_API __declspec(dllimport)
#endif


//授受当前棋盘状态和传入的随机数并保存
extern "C" AI_API void recive_Board(char[5][5],int randon);

//输出行棋的棋子名称
extern "C" AI_API char move_PieceName();

//输出下一步棋子的落点坐标
extern "C" AI_API int* get_chessmove();