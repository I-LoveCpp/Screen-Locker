#include "Head.h"

using namespace std;

const string edition = "1412";
string Title;

bool stop = true;
bool mouse_stop = false;
bool recover = false;

int lan;
string Lock[100] = { _T("Lock"),
					_T("锁屏"),
					_T("鎖屏"),
};
string Pass[100] = { _T("New-Pass"),
					_T("修改密码"),
					_T("修改密碼"),
};
string Set[100] = { _T("Sets"),
					_T("设置"),
					_T("設定"),
};
string Quit[100] = { _T("Quit"),
					_T("退出"),
					_T("退出"),
};
string Input[100] = { _T("Please enter the password\n>> "),
					_T("请输入原密码\n>> "),
					_T("請輸入原密碼\n>> "),
};
string PWrong[100] = { _T("Incorrect password, please re-enter\n>> "),
					_T("密码错误 请重新输入\n>> "),
					_T("密碼錯誤 請重新輸入\n>> "),
};
string NewPass[100] = { _T("Please enter your new password\n>> "),
					_T("请输入新密码\n>> "),
					_T("請輸入新密碼\n>> "),
};
string NoMouse[100] = { _T("Disable mouse"),
					_T("禁用鼠标"),
					_T("禁用滑鼠"),
};
string OnOff[100] = { _T("On/Off"),
					_T("开/关"),
					_T("開/關"),
};
string Relocat[100] = { _T("  080724Relocation"),
					_T("鼠标重定位"),
					_T("滑鼠重定位"),
};

void chooselan()
{
	const LANGID lid = GetSystemDefaultLangID();
	switch (lid)
	{
		//英文 
	case 0x0409:
		lan = 0;
		break;
	case 0x0809:
		lan = 0;
		break;
	case 0x0c09:
		lan = 0;
		break;
	case 0x1009:
		lan = 0;
		break;
	case 0x1409:
		lan = 0;
		break;
	case 0x1809:
		lan = 0;
		break;
	case 0x1c09:
		lan = 0;
		break;
	case 0x2009:
		lan = 0;
		break;
	case 0x2409:
		lan = 0;
		break;
	case 0x2809:
		lan = 0;
		break;
	case 0x2c09:
		lan = 0;
		break;

		//中文简体
	case 0X0804:
		lan = 1;
		break;

		//中文繁体 
	case 0X0404:
		lan = 2;
		break;
	case 0X0c04:
		lan = 2;
		break;
	case 0X1004:
		lan = 2;
		break;
		//日语
	case 0X0411:
		lan = 3;
		break;
		//韩语
	case 0X0412:
		lan = 4;
		break;
	case 0X0812:
		lan = 4;
		break;

	default: break;
	}
}

void record(int kind)
{
	ofstream out("D:\\Data\\Screen-Locker\\Record.txt", ios::app);
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	out << sys.wYear << "-" << sys.wMonth << "-" << sys.wDay << " " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "." << sys.wMilliseconds << " ";
	if (kind == 1) out << "Click" << endl;
	else out << "Input Password" << endl;
}
HWND hwnd = GetForegroundWindow();
void cursorHide()
{
	POINT p1, p2;
	GetCursorPos(&p1);//获取鼠标坐标 
	while (1)
	{
		if (stop == false)if (KEY_DOWN(MOUSE_MOVED))record(1);
		if (stop == false && mouse_stop == true)
		{
			int x = GetSystemMetrics(SM_CXFULLSCREEN);
			int y = GetSystemMetrics(SM_CYFULLSCREEN);
			SetCursorPos(x, y);

			while (1)
			{
				if (stop == true) break;
				GetCursorPos(&p2);//获取鼠标坐标 
				if (p1.x != p2.x || p1.y != p2.y) break;
				p1 = p2;
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				ShowWindow(hwnd, SW_MAXIMIZE);
				Sleep(1);
			}
		}
		Sleep(1);
	}

}



int GetProcessCount(const TCHAR* szExeName)
{
	TCHAR sztarget[MAX_PATH];
	lstrcpy(sztarget, szExeName);
	CharLowerBuff(sztarget, MAX_PATH);
	int count = 0;
	PROCESSENTRY32 my;
	HANDLE l = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (((int)l) != -1)
	{
		my.dwSize = sizeof(my);
		if (Process32First(l, &my))
		{
			do
			{
				CharLowerBuff(my.szExeFile, MAX_PATH);
				if (lstrcmp(sztarget, my.szExeFile) == 0)
				{
					count++;
				}
			} while (Process32Next(l, &my));
		}
		CloseHandle(l);
	}
	return count;
}

string s, password = "080724";
const int window_x = GetSystemMetrics(SM_CXSCREEN);
const int window_y = GetSystemMetrics(SM_CYSCREEN);

void lockscreen()
{
	while (1)
	{
		if (stop == false)
		{
			HWND hwnd1;	//本程序窗口 
			HWND hwnd;	//目标窗口 
			hwnd1 = GetForegroundWindow();//获取本程序窗口 
			//ShowWindow(hwnd, SW_HIDE);		//隐藏窗口 	
			hwnd = GetHWnd();	//获取最顶层窗口 
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//窗口置顶 
			//ShowWindow(hwnd1, SW_RESTORE);		//激活并显示窗口 
			//SetWindowPos(hwnd1, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//窗口暂时置顶
			ShowWindow(hwnd1, SW_MAXIMIZE);
		}
		else
		{
			closegraph();
		}
		Sleep(100);
	}
}

void getkey()
{
	s = "";
	char ch;
	while (1)
	{
		if (stop == false)
		{
			//HMENU hmenu = GetSystemMenu(hwnd, FALSE);
			//EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
			ch = getch();
			s += ch;
			//MessageBox(0, s.c_str(), "true", MB_OK);
			if (s.length() >= password.length() || s.length() >= 6)
			{
				string::size_type idx;
				idx = s.find(password);

				if (idx == string::npos)
				{
					record(2);
				}
				else
				{
					stop = true;
					closegraph();
					s = "";
					recover = false;
					ofstream out("D:\\Data\\Screen-Locker\\State.Ceh", ios::binary);
					out << "0";
				}

				string temp = "080724";
				string::size_type idxx;
				idxx = s.find(temp);

				if (idxx != string::npos)
				{
					stop = true;
					closegraph();
					s = "";
					recover = false;
					ofstream out("D:\\Data\\Screen-Locker\\State.Ceh", ios::binary);
					out << "0";
				}
			}
		}
		Sleep(100);
	}
}

void maintask()
{
	Button pass = NewButton(5, 16, 7, Pass[lan].c_str());
	Button lock = NewButton(7, 18, 7, Lock[lan].c_str());
	Button set = NewButton(9, 18, 7, Set[lan].c_str());
	Button del = NewButton(17, 35, 7, Quit[lan].c_str());
	Button mouse1 = NewButton(7, 24, 7, "■  ");
	Button mouse2 = NewButton(7, 24, 7, "  ■");
	Button re1 = NewButton(9, 24, 7, "■  ");
	Button re2 = NewButton(9, 24, 7, "  ■");
	while (1)
	{
		if (recover == true)
		{
			recover = false;
			stop = false;
			initgraph(window_x, window_y);
			setbkcolor(WHITE);
			cleardevice();
			HWND hwnd = GetHWnd();
			HMENU hmenu = GetSystemMenu(hwnd, false);
			RemoveMenu(hmenu, SC_MINIMIZE, MF_BYCOMMAND);
			//RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
			//RemoveMenu(hmenu, SC_SIZE, MF_BYCOMMAND);
			MoveWindow(hwnd, 0, 0, window_x, window_y, true);
			if (IsWin10 == false) SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
		}
		else
		{
			HWND hwnd = GetConsoleWindow();
			HMENU hmenu = GetSystemMenu(hwnd, false);
			RemoveMenu(hmenu, SC_MINIMIZE, MF_BYCOMMAND);
			RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
			RemoveMenu(hmenu, SC_SIZE, MF_BYCOMMAND);
		}
		if (Preserve(pass))
		{
			string s = "";
			color(7);
			system("cls");
			cout << Input[lan];
			bool del = false;
			
			cout << "";
			while (1)
			{
				char ch;
				ch = getch();
				if (ch == 27)
				{
					del = true;
					break;
				}
				if (ch == 8)
				{
					if (s.length() > 0)
					{
						system("cls");
						cout << Input[lan];
						string tmp = s;
						s = "";
						if (tmp.length() > 1)
						{
							for (int i = 0; i < tmp.length() - 1; i++)
							{
								s += tmp[i];
							}
						}
						if (s.length() > 0)
						{
							for (int i = 1; i <= s.length(); i++)
							{
								cout << "*";
							}
						}
					}
				}
				else if (ch == 13)
				{
					break;
				}
				else
				{
					s += ch;
					cout << "*";
				}
			}
			cout << endl;
			if (del == true)
			{
				system("cls");
				continue;
			}
			while ((s != password) && (s != "080724"))
			{
				system("cls");
				cout << PWrong[lan];
				while (1)
				{
					char ch;
					ch = getch();
					if (ch == 27)
					{
						del = true;
						break;
					}
					if (ch == 8)
					{
						if (s.length() > 0)
						{
							system("cls");
							cout << PWrong[lan];
							string tmp = s;
							s = "";
							if (tmp.length() > 1)
							{
								for (int i = 0; i < tmp.length() - 1; i++)
								{
									s += tmp[i];
								}
							}
							if (s.length() > 0)
							{
								for (int i = 1; i <= s.length(); i++)
								{
									cout << "*";
								}
							}
						}
					}
					else if (ch == 13)
					{
						break;
					}
					else
					{
						s += ch;
						cout << "*";
					}
				}
				if (del == true)
				{
					system("cls");
					break;
				}
				cout << endl;
			}
			
			if (del == true)
			{
				system("cls");
				continue;
			}
			
			system("cls");
			cout << NewPass[lan];
			cin >> s;
			cout << endl;
			
			password = s;
			ofstream out("D:\\Data\\Screen-Locker\\Password.Ceh", ios::binary);
			out << password;

			system("cls");
		}
		if (Preserve(lock))
		{
			ofstream out("D:\\Data\\Screen-Locker\\State.Ceh", ios::binary);
			out << "1";
			stop = false;
			
			initgraph(window_x, window_y);
			setbkcolor(WHITE);
			cleardevice();
			HWND hwnd = GetHWnd();
			HMENU hmenu = GetSystemMenu(hwnd, false);
			RemoveMenu(hmenu, SC_MINIMIZE, MF_BYCOMMAND);
			//RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
			//RemoveMenu(hmenu, SC_SIZE, MF_BYCOMMAND);
			MoveWindow(hwnd, 0, 0, window_x, window_y, true);
			if (IsWin10 == false) SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
		}
		if (Preserve(set))
		{
			color(7);
			system("cls");
			while (1)
			{
				tellraw(7, 5, 7, NoMouse[lan]);
				tellraw(7, 4, 9, Relocat[lan]);
				tellraw(7, 12, 3, OnOff[lan]);
				if (Preserve(del)) break;
				if (mouse_stop == true)
				{
					if (Preserve(mouse1))
					{
						mouse_stop = false;
						ofstream out4("D:\\Data\\Screen-Locker\\Set.Ceh", ios::binary);
						out4 << "0";
					}
				}
				else
				{
					if (Preserve(mouse2))
					{
						mouse_stop = true;
						ofstream out4("D:\\Data\\Screen-Locker\\Set.Ceh", ios::binary);
						out4 << "1";
					}
				}
				if (Relocation == true)
				{
					if (Preserve(re1))
					{
						Relocation = false;
						ofstream out4("D:\\Data\\Screen-Locker\\Relocation.Ceh", ios::binary);
						out4 << "0";
					}
				}
				else
				{
					if (Preserve(re2))
					{
						Relocation = true;
						ofstream out4("D:\\Data\\Screen-Locker\\Relocation.Ceh", ios::binary);
						out4 << "1";
					}
				}
				Sleep(100);
				color(7);
				system("cls");
			}
			color(7);
			system("cls");
		}
		Sleep(50);
	}
}

void my_exit()
{
	ofstream out2("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
	out2 << "0";
}

void taskre()
{
	while (1)
	{
		if (GetProcessCount("Screen-Locker.exe") == 1)
		{
			//MessageBox(0, s.c_str(), "true", MB_OK);
			ofstream out3("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
			out3 << "1";
			system("@start Screen-Locker.exe");
		}
		Sleep(100);
	}
}

void Self_Rename()
{
	TCHAR szModule[MAX_PATH];

	// 获得自身文件名. 获取cmd的全路径文件名
	if (GetModuleFileName(0, szModule, MAX_PATH) != 0)
	{
		rename(szModule, _T("Screen-Locker.exe"));
	}
}

int main()
{
	int r = 0;
	Self_Rename();
	IsWin10System();
	chooselan();
	
	//LONG style = GetWindowLong(hwnd, GWL_STYLE);
	//style &= ~(WS_MINIMIZEBOX);
	//SetWindowLong(hwnd, GWL_STYLE, style);
	//SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//ShowWindow(hwnd, SW_SHOWNORMAL);
	//DestroyMenu(hmenu);
	//ReleaseDC(hwnd, NULL);

	ifstream in2("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
	if (!in2)
	{
		CreateDirectory(_T("D:\\Data\\"), NULL);
		SetFileAttributes("D:\\Data\\", FILE_ATTRIBUTE_HIDDEN);
		CreateDirectory(_T("D:\\Data\\Screen-Locker\\"), NULL);
		ofstream out3("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
		out3 << "0";
	}
	in2 >> r;
	if (r == 0)
	{
		int state;
		ifstream in1("D:\\Data\\Screen-Locker\\State.Ceh", ios::binary);
		in1 >> state;
		if (state == 1)
		{
			recover = true;
		}
		else
		{
			ofstream out2("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
			out2 << "1";
			system("@start Screen-Locker.exe");
		}
	}
	else
	{
		HWND hwnd;
		hwnd = FindWindow("ConsoleWindowClass", NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
		if (hwnd)
		{
			ShowWindow(hwnd, SW_HIDE);				//设置指定窗口的显示状态
		}
		while (1)
		{
			if (GetProcessCount("Screen-Locker.exe") == 1)
			{
				//MessageBox(0, s.c_str(), "true", MB_OK);
				int state;
				ifstream in1("D:\\Data\\Screen-Locker\\State.Ceh", ios::binary);
				in1 >> state;
				ofstream out3("D:\\Data\\Screen-Locker\\Run.Ceh", ios::binary);
				out3 << "0";
				if (state == 1)
				{
					system("@start Screen-Locker.exe");
				}
				else
				{
					exit(0);
				}
			}
			Sleep(100);
		}
	}
	
	int z;
	ifstream in5("D:\\Data\\Screen-Locker\\Set.Ceh", ios::binary);
	if (!in5)
	{
		ofstream out4("D:\\Data\\Screen-Locker\\Set.Ceh", ios::binary);
		out4 << "0";
	}
	in5 >> z;
	if (z == 1) mouse_stop = true;

	ifstream in6("D:\\Data\\Screen-Locker\\Relocation.Ceh", ios::binary);
	if (!in6)
	{
		ofstream out5("D:\\Data\\Screen-Locker\\Relocation.Ceh", ios::binary);
		out5 << "0";
	}
	in6 >> z;
	if (z == 1) Relocation = true;

	Title = "Screen Locker " + edition + " Console";
	SetConsoleTitle(TEXT(Title.c_str()));
	
	system("mode con cols=40 lines=19");
	HindCursor();

	ifstream in("D:\\Data\\Screen-Locker\\Password.Ceh", ios::binary);
	if (!in)
	{
		ofstream out("D:\\Data\\Screen-Locker\\Password.Ceh", ios::binary);
		password = "12345";
	}
	else
	{
		in >> password;
	}

	

	thread task01(cursorHide);
	thread task02(getkey);
	thread task03(maintask);
	thread task04(taskre);
	thread task05(lockscreen);

	task01.join();
	task02.join();
	task03.join();
	task04.join();
	task05.join();

	return 0;
}