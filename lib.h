#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<Windowsx.h>
#pragma comment (lib,"Winmm.lib")
#include<string>
#include<stdio.h>
#include<math.h>

#include"resource2.h"
#include"def.h"
using namespace std;

HBITMAP picture;
PAINTSTRUCT ps;
RECT clientRect;
HWND ButtonBuy[4];
HCURSOR cursorArrow;
HCURSOR cursorHand;

int spawnButtonX = 20;
int spawnButtonY = 20;

unsigned long long MainGameSum = 0;

unsigned long long Button_1_Speed = 0;
unsigned long long Button_2_Efficiency = 1;
BOOL Button_3_Sound = TRUE;

unsigned long long ButtonBuy_1_Sell_Speed = 100;
unsigned long long ButtonBuy_2_Sell_Efficiency = 20;

int index = 0;
