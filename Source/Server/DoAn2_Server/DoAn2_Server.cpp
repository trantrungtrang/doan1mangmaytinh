// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include "math.h"
#include "Tokenizer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object
using namespace std;
CWinApp theApp;

struct Name
{
	string User;
	string Pass;
};
struct BoDe
{
	string STT;
	string De;
	string CauA;
	string CauB;
	string CauC;
	string CauD;
	string DapAn;
};

vector<string> Tokenizer::Split(const string& s, const char delim)
{
	vector<string> result;

	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}
string Parse(string s)
{
	vector<string> parts = Tokenizer::Split(s, '	');
	string a;
	a = parts[1];
	return a;
}

string EnglishGame(string TapTinChuaDe, string DapAnDung, string Chon)
{
	string KetQua = "Ban tra loi sai roi!";
	ifstream f;

	BoDe *a = new BoDe[10];

	if (TapTinChuaDe == "BoDe")
		f.open("BoDe.txt");
	
	for (int i = 0; i < 10; i++)
	{
		getline(f,a[i].STT);
		getline(f,a[i].DapAn);
	}
	for (int i = 0; i < 50; i++)
	{
		if (a[i].STT == Chon)
		{
			if (DapAnDung == a[i].DapAn )
				KetQua = "Chuc mung ban tra loi dung!";
		}
	}

	return KetQua;
}

int SaveUser(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[30];
	f >> n;
	for (int i = 0; i < 30; i++)
	{
		a[i].User = "";
		a[i].Pass = "";
	}
	k =-1;
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
		if (user == a[i].User)
		{
			k = 0;
			return 0;
		}
	}


	if (k == -1)
	{
		n++;
		a[n - 1].User = user;
		a[n - 1].Pass = pass;
		remove("TaiKhoan.txt"); // xoa file 
		ofstream f1;
		f1.open("TaiKhoan.txt"); // tao lai file moi cung ten
		f1 << n;
		f1 << endl;
		// ghi lai danh sach user bao gom ca user vua moi tao
		for (int i = 0; i < n; i++)
		{
			f1 << a[i].User;
			f1 << " ";
			f1 << a[i].Pass;
			f1 << endl;
		}
	}
	return 1;

}
bool SearchUSer(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[50];
	while (!f)
	{

		cout << "tep tin khong ton tai";
		return false;
	}

	f >> n;
	for (int i = 0; i < 50; i++)
	{
		a[i].User = "NULL";
	}
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
	}
	k = -1;
	for (int i = 0; i < n; i++)
	{
		if ( a[i].User==user && a[i].Pass == pass )
		{
			k = 0;
			return true;
		}
	}
	return false;
}
bool SearchTinhThanh(string TinhThanh)
{
	ifstream f;
	f.open("DanhSach.txt");
	string a[11];
	int n, k;
	string m, s;
	while (!f)
	{
		cout << "tep tin khong ton tai";
		return false;
	}
	for(int i = 0; i<11; i++)
	{
		f >> a[i];
	}
	for (int i = 0; i < 11; i++)
	{
		if ( a[i] == TinhThanh )
		{
			k = 0;
			return true;
		}
	}
	return false;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;



	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}

	else
	{
		// TODO: code your application's behavior here.
		CSocket server;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		server.Create(port);
		server.Listen(5);

		//Nhap so luong client
		printf("\n Nhap so luong Client: ");
		int num_client;
		scanf_s("%d",&num_client);
		if(num_client <=0 || num_client >=10)
		{
			cout<<"Vui long nhap dung so luong"<<endl;
			goto EXIT;

		}
		printf("\n Dang lang nghe ket noi tu Client...\n");

		//Tao mang chua cac socket client
		CSocket* sockClients = new CSocket[num_client];
		//them
		int *numbers = new int[num_client * 2];
		for(i=0 ; i<num_client; i++)
		{
			server.Accept(sockClients[i]);
			printf("Da tiep nhan client %d/%d\n",i+1,num_client);
			//Bao cho client biet minh la client thu may
			sockClients[i].Send((char*)&i,sizeof(int),0);

			int k,x;
			char* User;
			int lenU;
			char* Pass;
			int lenP;
			int j = i;
			// k là giá trị choose

			sockClients[i].Receive((char*)&k,sizeof(k),0);
			if(k == 1)
			{
				sockClients[j].Listen(5);
				// ---------------------------------------
				// my code
				// nhận User đã kiểm tra đúng

				sockClients[j].Receive(&lenU,sizeof(int),0);
				User = new char[lenU];
				sockClients[i].Receive(User,lenU,0);
				User[lenU] = '\0';
				// nhận pass
				sockClients[j].Receive(&lenP,sizeof(int),0);
				Pass = new char[lenP];
				sockClients[j].Receive(Pass,lenP,0);
				Pass[lenP] = '\0';
				int k;
				if(SaveUser(User,Pass) == 0)
				{
					x = 0;
					cout<<"   Dang ki khong thanh cong"<<endl<<"  Tai khoan da duoc dang ki"<<endl;

					sockClients[j].Send((char*)&x,sizeof(int),0);
					goto EXIT;
				}
				else
				{
					x = 1;
					k = 2;

					cout<<"   Dang ki thanh cong"<<endl;
					sockClients[j].Send((char*)&x,sizeof(int),0);
					goto DangNhap;
				}
			}
			// 2 là đăng nhập
			if( k == 2)
			{
DangNhap:
				sockClients[j].Receive(&lenU,sizeof(int),0);
				User = new char[lenU];
				sockClients[j].Receive(User,lenU,0);
				User[lenU] = '\0';

				sockClients[j].Receive(&lenP,sizeof(int),0);
				Pass = new char[lenP];
				sockClients[j].Receive(Pass,lenP,0);
				Pass[lenP] = '\0';
				// dang nhập thành công
				if(SearchUSer(User,Pass) == true)
				{
					int p = 1;
					sockClients[j].Send((char*)&p,sizeof(p),0);
					// nhận truy vấn h
					int x; // x = h

					sockClients[j].Receive((char*)&x,sizeof(x),0);
					if( x == 1) // x = h = 1
					{
						char truyvan23[] = "\0";
						int tv23 = strlen(truyvan23);
						sockClients[j].Send((char*)&tv23,sizeof(int),0);
						sockClients[j].Send(truyvan23,sizeof(truyvan23),0);
TruyVan:
						// nhận kết quả truy vấn
						int kq = 1; // kq = kqtv
						sockClients[j].Receive((char*)&kq,sizeof(kq),0);
						if(kq == 1)
						{
							char* TenTapTin;
							int len_ten;
							char* DapAnDung;
							int len_DapAnDung;
							char* Chon;
							int len_Chon;
							// nhận từ client
							sockClients[j].Receive((char*)&len_ten,sizeof(int),0);
							TenTapTin = new char[len_ten];
							sockClients[j].Receive(TenTapTin,len_ten,0);
							TenTapTin[len_ten] = '\0';


							sockClients[j].Receive((char*)&len_DapAnDung,sizeof(int),0);
							DapAnDung = new char[len_DapAnDung];
							sockClients[j].Receive(DapAnDung,len_DapAnDung,0);
							DapAnDung[len_DapAnDung] = '\0';

							sockClients[j].Receive((char*)&len_Chon,sizeof(int),0);
							Chon = new char[len_Chon];
							sockClients[j].Receive(Chon,len_Chon,0);
							Chon[len_Chon] = '\0';

							string KiemTra = EnglishGame(TenTapTin,DapAnDung,Chon);
							int len_ktra = strlen(KiemTra.c_str());
							sockClients[j].Send((char*)&len_ktra,sizeof(int),0);
							sockClients[j].Send(KiemTra.c_str(),len_ktra,0);

							goto TruyVan;
						}

					}


				}
				// đăng nhập thất bại
				else
				{
					int p = 0;
					sockClients[j].Send((char*)&p,sizeof(p),0);
					goto DangNhap;
				}
			}





			// ---------------------------------------

			// ngắt kết nối
			sockClients[i].Close();
		}
EXIT:

		cout<<"Exit..."<<endl;


		getchar();
	}

	getchar();
	return nRetCode;
}
