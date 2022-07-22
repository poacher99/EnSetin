
// MathLibrary.h - Contains declarations of math functions

#pragma once





#ifdef AI_EXPORTS
#define AI_API __declspec(dllexport)
#else
#define AI_API __declspec(dllimport)
#endif


//���ܵ�ǰ����״̬�ʹ���������������
extern "C" AI_API void recive_Board(char[5][5],int randon);

//����������������
extern "C" AI_API char move_PieceName();

//�����һ�����ӵ��������
extern "C" AI_API int* get_chessmove();