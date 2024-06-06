#include <iostream>
#include <string>
#include <graphics.h> 
#include "mylib.h"
#include <fstream> 
#include <iomanip> 
using namespace std;

struct Khachhang {
    string name;
    string cccd;
    string gioitinh;
};

int SoSanh(string a, string b) {
    int lenA = a.length();
    int lenB = b.length();
    int minLen = min(lenA, lenB);
    for (int i = 0; i < minLen; i++) {
        if (a[i] > b[i]) {
            return 1;
        }
        if (a[i] < b[i]) {
            return -1;
        }
    }
    if (lenA == lenB) return 0;
    return (lenA > lenB) ? 1 : -1;
}

void set(int x, int y) {
    SetColor(x);
    SetBGColor(y);
}
int StrToInt(string a){
	int m=0;
    for (int i = 0; i < a.size(); i++) {
        m = m * 10 + (a[i] - '0');
    }
    return m; 
} 

struct maybay{
	string SoHieuMayBay;
	string LoaiMayBay;
	int SoDay;
	int SoDong; 
};
struct CacMayBay {
    maybay* n[300];
    int somaybay; 
};
void readfile(CacMayBay &a){
	fstream f;
	f.open("listmaybay.txt");
	string s;
	int dem=0;
	int i=1; 
	while(getline(f,s)){
		if(dem==0){
			a.n[i] = new maybay;
			a.n[i]->SoHieuMayBay=s; 
		}
		else if(dem==1){
			a.n[i]->LoaiMayBay=s; 
		}
		else if(dem==2){
			a.n[i]->SoDay=StrToInt(s); 
		}
		else if(dem==3){
			a.n[i]->SoDong=StrToInt(s);
			dem=-1;
			i++; 
		}
		dem++; 
	} 
} 
//-------------Chuyen bay-----------------
struct Ve {
    string maVe; 
    string soCMND; 
    Ve *next; 
};


struct ChuyenBay {
    string maCB; 
    string ngayGioKhoiHanh; 
    string sanBayDen; 
    int trangThai; 
    string soHieuMB; 
    int soCho; 
    Ve *danhSachVe; 
    ChuyenBay() {
        danhSachVe = nullptr; 
    }
    struct ChuyenBay *next=NULL; 
};
struct CacChuyenBay {
    ChuyenBay* n[300];
};
void capPhatVaThemVe(ChuyenBay &cb,CacMayBay a) {
	for(int j=1;j<=a.somaybay;j++){
		if(cb.soHieuMB==a.n[j]->SoHieuMayBay){
			cb.soCho=a.n[j]->SoDay*a.n[j]->SoDong; 
			for (int i = 1; i <= a.n[j]->SoDay; ++i) {
				for(int z = 1; z<=a.n[j]->SoDong;z++) {
			        Ve *newVe = new Ve;
			        newVe->maVe = char(64+i) +to_string(z);
			        newVe->soCMND = ""; 
			        newVe->next = nullptr;
			
			        if (cb.danhSachVe == nullptr) {
			            cb.danhSachVe = newVe;
			        } else {
			            Ve *temp = cb.danhSachVe;
			            while (temp->next != nullptr) {
			                temp = temp->next;
			            }
			            temp->next = newVe;
			        }
			    }
	    	}
	    	return; 
		} 
	} 
}


bool themHanhKhach(ChuyenBay &cb, string maVe, const string &soCMND) {
    Ve *temp = cb.danhSachVe;
    while (temp != nullptr) {
        if (temp->maVe == maVe && temp->soCMND.empty()) {
            temp->soCMND = soCMND;
            return true; 
        }
        temp = temp->next;
    }
    return false; 
}

//---------------KET THUC CHUYEN BAY--------------------
void themKhachHang(CacChuyenBay &cacChuyenBay, int somaybay) {
    string maChuyenBay, soCMND;
    string maVe;
    bool foundMaChuyenBay = false;
    bool foundSoCMND = false;
    while (!foundMaChuyenBay || !foundSoCMND) {
        foundMaChuyenBay = false;
        foundSoCMND = false;
        
        cout << "Nhap ma chuyen bay: ";
        cin >> maChuyenBay;
        for (int i = 1; i < somaybay; ++i) {
            if (cacChuyenBay.n[i]->maCB == maChuyenBay) {
                foundMaChuyenBay = true;
                break;
            }
        }
        
        if (!foundMaChuyenBay) {
            cout << "Khong tim thay chuyen bay voi ma " << maChuyenBay << ". Vui long nhap lai." << endl;
            continue;
        }
        
        cout << "Nhap so CMND: ";
        cin >> soCMND;
        foundSoCMND = true;
        for (int i = 1; i < somaybay; ++i) {
            Ve* tempVe = cacChuyenBay.n[i]->danhSachVe;
            while (tempVe != nullptr) {
                if (tempVe->soCMND == soCMND) {
                    foundSoCMND = false;
                    break;
                }
                tempVe = tempVe->next;
            }
            if (!foundSoCMND) {
                cout << "So CMND da ton tai cho mot hanh khach khac. Vui long nhap lai." << endl;
                break;
            }
        }
    }
    
    cout << "Nhap ma ve: ";
    cin >> maVe;
    
    bool found = false;
    for (int i = 1; i < somaybay; ++i) {
        if (cacChuyenBay.n[i]->maCB == maChuyenBay) {
            if (themHanhKhach(*cacChuyenBay.n[i], maVe, soCMND)) {
                cout << "Them hanh khach thanh cong!" << endl;
            } else {
                cout << "Ma ve da ton tai hoac khong hop le!" << endl;
            }
            found = true;
            break;
        }
    }
    
    char c;
    cout<<"Nhap phim enter de quay lai man hinh chinh:";
    c=getch(); 
}

void xoaKhachHang(CacChuyenBay &cacChuyenBay, int somaybay) {
    string soCMND;
    cout << "Nhap so CMND cua khach hang muon xoa: ";
    cin >> soCMND;
    bool found = false;
    for (int i = 1; i < somaybay; ++i) {
        Ve* tempVe = cacChuyenBay.n[i]->danhSachVe;
        while (tempVe != nullptr) {
            if (tempVe->soCMND == soCMND) {
                tempVe->soCMND = "";
                found = true;
            }
            tempVe = tempVe->next;
        }
    }
    if (found) {
        cout << "Xoa thanh cong khach hang co so CMND " << soCMND << endl;
    } else {
        cout << "Khong tim thay khach hang voi so CMND " << soCMND << endl;
    }
    char c;
    cout << "Nhap phim enter de quay lai man hinh chinh:";
    c = getch(); 
}


void xuatDanhSachHanhKhach(CacChuyenBay &cacChuyenBay, int somaybay) {
    for (int i = 1; i < somaybay; ++i) {
        cout << "Chuyen bay " << cacChuyenBay.n[i]->maCB << ":" << endl;
        Ve* tempVe = cacChuyenBay.n[i]->danhSachVe;
        while (tempVe != nullptr) {
            if (!tempVe->soCMND.empty()) {
                cout << "Ma ve: " << tempVe->maVe << ", So CMND: " << tempVe->soCMND << endl;
            }
            tempVe = tempVe->next;
        }
        cout << endl;
    }
    char c;
    cout << "Nhap phim enter de quay lai man hinh chinh:";
    c = getch(); 
}
void GheTrong(CacChuyenBay &cacChuyenBay, int somaybay) {
    for (int i = 1; i < somaybay; ++i) {
        cout << "Chuyen bay " << cacChuyenBay.n[i]->maCB << ":" << endl;
        Ve* tempVe = cacChuyenBay.n[i]->danhSachVe;
        while (tempVe != nullptr) {
            if (tempVe->soCMND.empty()) {
                cout << tempVe->maVe << "   ";
            } 
            else{
            	cout<<setfill(' ')<<setw(tempVe->maVe.size())<<""<<"   ";
			} 
            if (tempVe->next != nullptr && tempVe->maVe[0] != tempVe->next->maVe[0]) {
            	cout<<endl; 
            }
            tempVe = tempVe->next;
        }
        cout << endl;
    }
    char c;
    cout << "Nhap phim enter de quay lai man hinh chinh:";
    c = getch();
}
int main() {
    CacChuyenBay c;
    CacMayBay a;
	readfile(a); 
    fstream f;
    f.open("maybay.txt");
    string s;
    int somaybay = 1;
    int dem = 0;
    while (getline(f, s)) {
        if (dem == 0) {
            c.n[somaybay] = new ChuyenBay();
            c.n[somaybay]->maCB = s;
        }
        else if (dem == 1) {
            c.n[somaybay]->ngayGioKhoiHanh = s;
        }
        else if (dem == 2) {
            c.n[somaybay]->sanBayDen = s;
        }
        else if (dem == 3) {
            c.n[somaybay]->trangThai = StrToInt(s);
        }
        else if (dem == 4) {
            c.n[somaybay]->soHieuMB = s;
            capPhatVaThemVe(*c.n[somaybay],a);
            somaybay++;
            dem = -1; 
        } 
        dem++;
    }
    f.close();
    string MENU[10];
    MENU[0]="-----------------MENU----------------";
	MENU[1]="1.Them khach hang:                   ";
	MENU[2]="2.Xoa khach hang theo cccd:          ";
	MENU[3]="3.Xuat cac khach hang:               ";
	MENU[4]="4.Xuat cac ghe con trong:            ";
	MENU[5]="5.Thoat!                             ";
    set(15,8);
    int current=1; 
    while (1) {
    	while(1) {
    		for(int i=0;i<=5;i++){
    			if(i==0){
    				set(5,6); 
    				gotoxy(0,i);
    				cout<<MENU[i]; 
				} 
    			else if(i==current){
    				set(0,15);
					gotoxy(0,i);
					cout<<MENU[i]; 
				} 
				else{
					set(15,8);
					gotoxy(0,i);
					cout<<MENU[i]; 
				} 
			} 
			char c; 
			while(1){
				if(kbhit()){
					c=getch();
					if(c==72&&current>1){
						current--; 
					} 
					if(c==80&&current<5){
						current++; 
					} 
					break; 
				} 
			} 
			if(c==13){
				break; 
			} 
		}
		set(0,0);
		system("cls"); 
		gotoxy(0,0);
		set(15,0); 
        if (current == 1) {
            themKhachHang(c, somaybay);
        }
        else if (current == 2) {
            xoaKhachHang(c, somaybay);
        }
        else if (current == 3) {
            xuatDanhSachHanhKhach(c, somaybay);
        }
        else if (current == 4) {
        	GheTrong(c,somaybay); 
        }
        else if (current == 5) {
            break;
        }
        set(0,0);
		system("cls"); 
    }
    return 0;
}


