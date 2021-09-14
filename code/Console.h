// Not standard C++ objects -*- C++ -*-

// Copyright (C) 1997-2014 Free Software Foundation, Inc.
//
// This file is not part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are not granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You do not have to have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

// This file is only for Windows Console.
// You can use it to make your code more concise

/** @file include/Console.h
 *  This is not a Standard C++ Library header.
 */

//
// ISO C++ 14882: 27.3  Not standard C++ objects
//


#ifndef __cplusplus
#error You must use C++ compiler, or you need filename with '.cpp' suffix
#endif

#include <cstdio>
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>       //停顿:Sleep(); 
#include <cstdlib>         //清屏:system("cls");
#include <cstring>
#include <fstream>
#include<stdlib.h>
#include<set>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include <sstream>
#include <string>
using namespace std;

#define fblack 0
#define fblue 1
#define fgreen 2
#define fcyan 3
#define fred 4
#define fpurple 5
#define fyellow 6
#define fwhite 7
#define fgray 8
#define flight 8
#define bblack 0
#define bblue 16
#define bgreen 32
#define bcyan 48
#define bfred 64
#define bpurple 80
#define byellow 96
#define bwhite 112
#define bgray 128
#define blight 128
#define dirkey -32
#define upkey 72
#define downkey 80
#define leftkey 75
#define rightkey 77
#define wclear system("cls")
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define LL long long

#define TICK 200
#define DOH 523
#define RAY 587
#define MI 659
#define FA  698
#define SOH  784
#define LA   880
#define TEE   980
#define DOHH  1060
#define RAYH  1175
#define MIH   1318
#define FAH  1397
#define SOHH  1568
#define LAH   1760
#define TEEH  1976

bool IsWin10, Relocation = false;

template <typename T>
string buling(T text, long long number, bool front)
{
	if(front == true)
	{
		string a, b, c, r;
		while(text > 0)
		{
			stringstream ss;
			ss << text % 10;
			ss >> c;
			a += c;
			text /= 10;
		}
		for(long long i = 1; i <= number - a.length();i++)
		{
			b = b + "0";
		}
		b += a;
		for(long long i = b.length() - 1; i >= 0; i--)
		{
			r += b[i];
		}
		return r;
	}
	else if(front == false)
	{
		string a, b, c, r;
		while(text > 0)
		{
			stringstream ss;
			ss << text % 10;
			ss >> c;
			a += c;
			text /= 10;
		}
		for(long long i = 1; i <= number - a.length();i++)
		{
			b += "0";
		}
		b += a;
		for(long long i = b.length() - 1; i >= 0; i--)
		{
			r += b[i];
		}
		return r;
	}
}

void HindCursor(){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle,&CursorInfo);
    CursorInfo.bVisible=false;
    SetConsoleCursorInfo(handle,&CursorInfo);
}
struct Button{
    int x,y,color,pointcolor = 112;
    const char *name;
    int len;
};
void GetPos(POINT &pt){
    HWND hwnd=GetForegroundWindow();
    GetCursorPos(&pt);
    ScreenToClient(hwnd,&pt);
    pt.y=pt.y/16,pt.x=pt.x/8;
    swap(pt.x,pt.y);
}
void color(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void gto(int x,int y){
    COORD pos;pos.X=y;pos.Y=x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
Button NewButton(int x,int y,int color,int pointcolor,const char *name){
    Button t;
    t.x=x,t.y=y,t.name=name;
    t.color=color;
    t.len=strlen(name);
    t.pointcolor=pointcolor;
    return t;
}
Button NewButton(int x,int y,int color,const char *name){
    Button t;
    t.x=x,t.y=y,t.name=name;
    t.color=color;
    t.len=strlen(name);
    return t;
}
bool Preserve(Button A){
    gto(A.x,A.y),color(A.color),printf("%s",A.name);
    POINT pt;
    GetPos(pt);
    if(pt.x == A.x &&(pt.y + ((!Relocation) ? (0) : (pt.y / 6)) >=A.y&&pt.y + ((!Relocation) ? (0) : (pt.y / 6)) <=A.y+A.len)){
        color(A.pointcolor),gto(A.x,A.y),printf("%s",A.name);
        if(KEY_DOWN(MOUSE_MOVED)) return 1;
    }
    return 0;
}
pair<int,int> GetXY(){
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &pBuffer);
    return make_pair(pBuffer.dwCursorPosition.Y,pBuffer.dwCursorPosition.X);
}
template <typename T>void Tprint(int Nx,int Ny,int Color,T a){
    int x=GetXY().first,y=GetXY().second;
    gto(Nx,Ny),color(Color),cout<<a;
    gto(x,y);
}
void ColorPrint(){
    for(int i=0;i<256;i++)
        color(i),printf("%d\n",i);
}
void SetWindow(const char *name,int c,int w){
    char str[30];
    sprintf(str,"title %s",name);
    system(str);
    sprintf(str,"mode con cols=%d lines=%d",w,c);
    system(str);
}
void SetWindow(const char *name,int c,int w,int x,int y){
    SetConsoleTitle(name);
    HWND hwnd;
    hwnd=GetForegroundWindow();
    SetWindowPos(hwnd,HWND_TOP,y,x,w*8,c*16,SWP_SHOWWINDOW);
}
int read(){
    color(fwhite+flight);
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}

#define TP Tprint
#define WINDOWC 45
#define WINDOWW 55
#define INF 0x3f3f3f3f
#define OC fwhite+bblack //original color
#define UB fblack+bwhite //original color

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int y,int x)//位置函数(行为x 列为y)
{
	HideCursor();
	COORD pos;
	pos.X=2*y;
	pos.Y=x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Color(int a)//颜色函数
{
	HideCursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void tellraw(long long colour,long long x,long long y,string name)
{
	HideCursor();
	Color(colour);gotoxy(x,y);cout << name;
}

void actionbar(long long colour,long long x,long long y)
{
	HideCursor();
	Color(colour);gotoxy(x,y);
}

void OriginalColor()
{
	HideCursor();
	Color(7);
}

void GIF(char a,char b,char c,char d,int time,long long color,long long x,long long y,long long num)
{
	for(long long i = 1;i <= num;i++)
	{
		actionbar(color,x,y);cout << a;
		Sleep(time);
		actionbar(color,x,y);cout << b;
		Sleep(time);
		actionbar(color,x,y);cout << c;
		Sleep(time);
		actionbar(color,x,y);cout << d;
		Sleep(time);
	}
	OriginalColor();
}
void Move(char a,char direction,int time,long long color,long long x,long long y,long long num)
{
	long long sum;
	if(direction == 'w')
	{
		actionbar(color,x,y);cout << a;
		Sleep(time);
		OriginalColor();
		actionbar(7,x,y);cout << " ";
		for(long long i = num - 1;i >= 1;i--)
		{
			sum = i + 1;
			actionbar(7,x,sum);cout << " ";
			actionbar(color,x,i);cout << a;
			Sleep(time);
			OriginalColor();
		}
	}
	else if(direction == 's')
	{
		actionbar(color,x,y);cout << a;
		Sleep(time);
		OriginalColor();
		actionbar(7,x,y);cout << " ";
		for(long long i = 1;i <= num;i++)
		{
			sum = i - 1;
			actionbar(7,x,sum);cout << " ";
			actionbar(color,x,i);cout << a;
			Sleep(time);
			OriginalColor();
		}
	}
	else if(direction == 'd')
	{
		actionbar(color,x,y);cout << a;
		Sleep(time);
		OriginalColor();
		actionbar(7,x,y);cout << " ";
		for(long long i = 1;i <= num;i++)
		{
			sum = i - 1;
			actionbar(7,sum,y);cout << " ";
			actionbar(color,i,y);cout << a;
			Sleep(time);
			OriginalColor();
		}
	}	
	else if(direction == 'a')
	{
		actionbar(color,x,y);cout << a;
		Sleep(time);
		OriginalColor();
		actionbar(7,x,y);cout << " ";
		for(long long i = num - 1;i >= 1;i--)
		{
			sum = i + 1;
			actionbar(7,sum,y);cout << " ";
			actionbar(color,i,y);cout << a;
			Sleep(time);
			OriginalColor();
		}
	}
}
void gotox(int x,int y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void drawbar(double p)
{
    int i;
    double c = p * 100;
    if(c >= 66.6666666) Color(10);
    else if(c >= 50) Color(1);
    else if(c >= 33.3333333) Color(14);
    else Color(4);
    if(p>=0.99999999)
    {
        for(i=10; i--; i>0)cout<<"█";
        Color(7);
        return;
    }
    int a;
    CONSOLE_SCREEN_BUFFER_INFO xy;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &xy);
    for(i=10; i--; i>0)cout<<"  ";
    gotox(xy.dwCursorPosition.X,xy.dwCursorPosition.Y);
    a=(int)(p*10);
    for(i=a; i--; i>0)cout<<"█";
    if(a==10)return;
    i=(int)((p*10-(int)(p*10))*8);
    switch(i)
    {
    case 0:
        cout<<"  ";
        break;
    case 1:
        cout<<"▏";
        break;
    case 2:
        cout<<"▎";
        break;
    case 3:
        cout<<"▍";
        break;
    case 4:
        cout<<"▌";
        break;
    case 5:
        cout<<"▋";
        break;
    case 6:
        cout<<"▊";
        break;
    case 7:
        cout<<"▉";
        break;
    }
    for(i=9-a; i--; i>0)cout<<"  ";
    Color(7);
}
template <typename T>
string numberid(T n)
{
	if(n % 10 == 0) return "0";
	else if(n % 10 == 1) return "1";
	else if(n % 10 == 2) return "2";
	else if(n % 10 == 3) return "3";
	else if(n % 10 == 4) return "4";
	else if(n % 10 == 5) return "5";
	else if(n % 10 == 6) return "6";
	else if(n % 10 == 7) return "7";
	else if(n % 10 == 8) return "8";
	else if(n % 10 == 9) return "9";
}

long long char_to_longlong(char ch)
{
	switch(ch)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}
int char_to_int(char ch)
{
	switch(ch)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}

char longlong_to_char(long long n)
{
	switch(n)
	{
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
	}
}

string decode(string prod_key, string message)
{
	string decode = "";
	bool num = true;
	int ans;
	for(unsigned long long i = 0; i <= message.length() - 1; i++)
	{
		if(num)
		{
			ans = char_to_int(message[i]);
			num = false;
		}
		else
		{
			decode += message[i] ^ prod_key[ans];
			num = true;
		}
	}
	
	return decode;
}

string decode(string message1)
{
	string prod_key = "";
	string message = "";
	for(int i = 0; i <= 14; i++)
	{
		prod_key += message1[i];
	}
	for(int i = 15; i <= message1.length() - 1; i++)
	{
		message += message1[i];
	}
	
	string decode = "";

	int ans = 0;
	for(unsigned long long i = 0; i <= message.length() - 1; i++)
	{
		cout << ans << endl;
		if(ans == 15) ans = 0;
		decode += message[i] ^ prod_key[ans];

		ans++;
	}

	return decode;
}

string code(string message)
{
	string key_text = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	string key = "";
	
	srand((unsigned)time(NULL));
	
	for(int i = 1; i <= 15; i++)
	{
		key += key_text[(rand() + rand() * rand()) % 36];
	}
	
	key = "HHHHHHHHHHHHHHH";
	
	string code = "";
	int ans = 0;
	for(unsigned long long i = 0; i <= message.length() - 1; i++)
	{
		if(ans == 15) ans = 0;
		code += char(message[i] ^ key[ans]);
		
		ans++;
	}
	
	string coden = key + code;
	
	return coden;
}

static int NumGroup[2];

void SetPosition(int x, int y)
{
	HANDLE winHandle;//句柄 
	COORD pos = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, pos);  //设置光标位置 
}

int* SeparateNum(int num)
{
	NumGroup[0] = num / 10;
	NumGroup[1] = num % 10;
	return NumGroup;
}

void NumDisplay(int num, int x, int y)
{
	int* num_group, i;
	num_group = SeparateNum(num);
	for (i = 0; i < 2; i++) //时、分、秒都是两位，所以两次循环分别打印 
	{
		if (i == 0) num = num_group[0];
		else num = num_group[1];
		switch (num)
		{
		case 0:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("■  ■");
			SetPosition(x + i * 7, y + 2); printf("■  ■");
			SetPosition(x + i * 7, y + 3); printf("■  ■");
			SetPosition(x + i * 7, y + 4); printf("■  ■");
			SetPosition(x + i * 7, y + 5); printf("■  ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 1:
			SetPosition(x + i * 7, y);     printf("  ■  ");
			SetPosition(x + i * 7, y + 1); printf("  ■  ");
			SetPosition(x + i * 7, y + 2); printf("  ■  ");
			SetPosition(x + i * 7, y + 3); printf("  ■  ");
			SetPosition(x + i * 7, y + 4); printf("  ■  ");
			SetPosition(x + i * 7, y + 5); printf("  ■  ");
			SetPosition(x + i * 7, y + 6); printf("  ■  ");
			break;
		case 2:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("    ■");
			SetPosition(x + i * 7, y + 2); printf("    ■");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("■    ");
			SetPosition(x + i * 7, y + 5); printf("■    ");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 3:
			SetPosition(x + i * 7, y);	   printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("    ■");
			SetPosition(x + i * 7, y + 2); printf("    ■");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("    ■");
			SetPosition(x + i * 7, y + 5); printf("    ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 4:
			SetPosition(x + i * 7, y);     printf("■  ■");
			SetPosition(x + i * 7, y + 1); printf("■  ■");
			SetPosition(x + i * 7, y + 2); printf("■  ■");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("    ■");
			SetPosition(x + i * 7, y + 5); printf("    ■");
			SetPosition(x + i * 7, y + 6); printf("    ■");
			break;
		case 5:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("■    ");
			SetPosition(x + i * 7, y + 2); printf("■    ");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("    ■");
			SetPosition(x + i * 7, y + 5); printf("    ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 6:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("■    ");
			SetPosition(x + i * 7, y + 2); printf("■    ");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("■  ■");
			SetPosition(x + i * 7, y + 5); printf("■  ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 7:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("    ■");
			SetPosition(x + i * 7, y + 2); printf("    ■");
			SetPosition(x + i * 7, y + 3); printf("    ■");
			SetPosition(x + i * 7, y + 4); printf("    ■");
			SetPosition(x + i * 7, y + 5); printf("    ■");
			SetPosition(x + i * 7, y + 6); printf("    ■");
			break;
		case 8:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("■  ■");
			SetPosition(x + i * 7, y + 2); printf("■  ■");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("■  ■");
			SetPosition(x + i * 7, y + 5); printf("■  ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		case 9:
			SetPosition(x + i * 7, y);     printf("■■■");
			SetPosition(x + i * 7, y + 1); printf("■  ■");
			SetPosition(x + i * 7, y + 2); printf("■  ■");
			SetPosition(x + i * 7, y + 3); printf("■■■");
			SetPosition(x + i * 7, y + 4); printf("    ■");
			SetPosition(x + i * 7, y + 5); printf("    ■");
			SetPosition(x + i * 7, y + 6); printf("■■■");
			break;
		default:
			printf("out of range!");
		}
	}
}

void DotDisplay(int x, int y)
{
	SetPosition(x, y); printf("■");
	SetPosition(x, y + 3); printf("■");
}

void IsWin10System()
{
	//string与CString转换
	//string sPath &#61; (LPCSTR)(CStringA)(strPath);
	std::string vname;
	// 先判断是否为win8.1或win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibrary(_T("ntdll.dll"));
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);

	if (dwMajor == 10 && dwMinor == 0)
	{
		IsWin10 = true;
	}
	else
	{
		IsWin10 = false;
	}
}