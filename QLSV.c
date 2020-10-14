#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct: kieu nguoi dung dinh nghia
struct HoTen {
	
	//khai bao bien
	//Kieu: char(kieu ki tu) ten bien[do dai truyen vao]
	char ho[30];
	char dem[30];
	char ten[30];
};

struct DiemMH {
	
	//khai bao bien 
	float toan;
	float ly;
	float hoa;
	float tbc;
};

struct SinhVien {
	
	//khai bao bien 
	char ma[10];
	
	//lay struct HoTen
	struct HoTen hoVaTen;
	
	//khai bao bien
	char lop[5];
	
	//lay struct DiemMH
	struct DiemMH diem;
};

//cai nay de nhap diem
void nhapDiem(struct DiemMH* diem) {
	printf("Toan: ");
	scanf("%f", &diem->toan);
	printf("Ly: ");
	scanf("%f", &diem->ly);
	printf("Hoa: ");
	scanf("%f", &diem->hoa);
	
	//lay trung binh cong
	diem->tbc = (diem->toan + diem->ly + diem->hoa) / 3;
}

//cai nay de nhap ho ten
void nhapHoTen(struct HoTen* ten) {
	printf("Ho: ");
	scanf("%s", ten->ho);
	printf("Ten Dem: ");
	getchar();
	gets(ten->dem);
	printf("Ten: ");
	scanf("%s", ten->ten);
}

//goi den cai struct sinhvien, ten struct nay la nhapSV
struct SinhVien nhapSV() {
	struct SinhVien sv;
	printf("Nhap ma: ");
	scanf("%s", sv.ma);
	//goi den cai nhapHoTen o phia tren
	nhapHoTen(&sv.hoVaTen);
	printf("Lop: ");
	scanf("%s", sv.lop);
	
	//goi den cai nhapDiem o phia tren
	nhapDiem(&sv.diem);
	
	//tra ve
	return sv;
}

int suattsv(char *stid) {
    FILE *fp;
    //int i = 0;
    struct SinhVien sv;
    char id[5];
    fp = fopen("sinhvien.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    hienThiTenCot();
    while (fscanf(fp, "\n Ma SV:%s", id) != EOF) {
        if (strcmp(id,stid) == 0) {
            printf("\n Nhap ma sinh vien:");
            gets(sv.ma);
            printf("\n Nhap ho sinh vien:");
            gets(sv.hoVaTen.ho);
            printf("\n Nhap ten dem sinh vien :");
            gets(sv.hoVaTen.dem);
            printf("\n Nhap ten sinh vien :");
            gets(sv.hoVaTen.ten);
            printf("\n Nhap lop sinh vien :");
            gets(sv.lop);
            printf("\n Nhap diem toan :");
            scanf("%f", &sv.diem.toan);
            printf("\n Nhap diem ly :");
            scanf("%f", &sv.diem.ly);
            printf("\n Nhap diem hoa:");
            scanf("%f", &sv.diem.hoa);
            
            fprintf(fp,"%-10s %-10s %-20s %-10s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n",
			sv.ma, sv.hoVaTen.ho, sv.hoVaTen.dem, sv.hoVaTen.ten, sv.lop,
			sv.diem.toan, sv.diem.ly, sv.diem.hoa, sv.diem.tbc);
        }
        fclose(fp);
//        else printf("\n Khong ton tai sinh vien co ma nay trong file");
    }
    fclose(fp);
}


int xoattsv(char *stid) {
    FILE *fp;
    //int i = 0;
    struct SinhVien sv;
    char id[5];
    fp = fopen("sinhvien.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
//    DeleteFile("SinhVien.txt");
    fclose(fp);
}

void hienThiTTSV(struct SinhVien sv) {
	//may cai % nay de luc f5 no can le cho minh thoi, %-10 là lay string o ben trai la(noi chung la de can le thoi)
	printf("%-10s %-10s %-20s %-10s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n",
	//goi den cac bien cua thang SinhVien
	sv.ma, sv.hoVaTen.ho, sv.hoVaTen.dem, sv.hoVaTen.ten, sv.lop,
	sv.diem.toan, sv.diem.ly, sv.diem.hoa, sv.diem.tbc);
}


void hienThiTenCot() {
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	printf("%-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s\n", 
		"Ma SV", "Ho", "Ten Dem", "Ten", "Lop", 
		"Diem Toan", "Diem Ly", "Diem Hoa", "Diem TBC");
}

void hienThiDSSV(struct SinhVien* ds, int slsv) {
	//goi den cai thang hienThiTenCot de no hien ra cai khung
	hienThiTenCot();
	
	//khai bao 1 cai bien de gan
	int i;
	//vong lap de lap cac thang sinh vien, co thang nao la no hien ra thang day
	for(i = 0; i < slsv; i++) {
		//goi den thang hienThiTTSV o phia tren vua khai bao,
		// xong cho no cai ds sinh vien theo vong lap, co bao nhieu la no hien ra het
		hienThiTTSV(ds[i]);
	}
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
}

void sapXepTheoDiemGiamDan(struct SinhVien* ds, int slsv) {
	//su dung 2 vong for long nhau
	int i, j;
	for(i = 0; i < slsv - 1; i++) {
		for(j = slsv - 1; j > i; j --) {
			//tbc cua thang dung sau lon hon thang dung truoc thi doi cho
			if(ds[j].diem.tbc > ds[j - 1].diem.tbc) {
				struct SinhVien sv = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = sv;
			}
		}
	}
}
void sapXepTheoDiemTangDan(struct SinhVien* ds, int slsv) {
	int i, j;
	for(i = 0; i < slsv - 1; i++) {
		for(j = slsv - 1; j > i; j --) {
			//tbc cua thang dung sau nho hon thang dung truoc thi doi cho
			if(ds[j].diem.tbc < ds[j - 1].diem.tbc) {
				struct SinhVien sv = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = sv;
			}
		}
	}
}

void timTheoLop(struct SinhVien* ds, int slsv) {
	//khai bao 1 cai bien de goi
	char lop[20];
	printf("Nhap lop: ");
	//nhap gia tri tu ban phim
	scanf("%s", lop);
	hienThiTenCot();
	int i, timSV = 0;
	for(i = 0; i < slsv; i++) {
		//neu strcmp bang 0 thi hien thi sinh vien ra
		if(strcmp(lop, ds[i].lop) == 0) {
			hienThiTTSV(ds[i]);
			timSV = 1;
		}
	}
	//neu van bang gia tri goc ban dau thi in ra thong bao
	if(timSV == 0) {
		printf("Khong co sinh vien %s trong danh sach!\n", lop);
	}
}

void timTheoDiem(struct SinhVien* ds, int slsv) {
	//khai bao 1 cai bien de goi
	float tbcn;
	printf("Nhap diem: ");
	//nhap gia tri tu ban phim
	scanf("%s", tbcn);
	hienThiTenCot();
	int i, timSV = 0;
	for(i = 0; i < slsv; i++) {
		//neu strcmp bang 0 thi hien thi sinh vien ra
		if ((ds[i].diem.tbc)==tbcn){
			printf("ok");
            hienThiTTSV(ds[i]);
			timSV = 1;
			}
	}
	//neu van bang gia tri goc ban dau thi in ra thong bao
	if(timSV == 0) {
		printf("Khong co sinh vien %s trong danh sach!\n", tbcn);
	}
}

//luu vao trong file txt
void ghiFile(struct SinhVien* ds, int slsv) {
	//Hàm FILE *fopen(const char *filename, const char *mode) mo file 
	FILE* fOut = fopen("sinhvien.txt", "r+");//	mo file sinhvien.txt , r+: mo file de ghi va doc
	
	//khai bao bien de gan
	int i;
	//goi vong lap for de in ra thong tin sinh vien
	for(i = 0; i < slsv; i++) {
		struct SinhVien sv = ds[i];
		fprintf(fOut, "%-10s %-10s %-20s %-10s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n",
		sv.ma, sv.hoVaTen.ho, sv.hoVaTen.dem, sv.hoVaTen.ten, sv.lop,
		sv.diem.toan, sv.diem.ly, sv.diem.hoa, sv.diem.tbc);
	}
	
	//dong cai file lai
	fclose(fOut);
}

//doc du lieu trong file txt
void docFile(struct SinhVien* ds, int* slsv) {
	FILE* fOut = fopen("sinhvien.txt", "r");
	int i = 0;
	
	//neu cai fOut mo file thanh cong thi mo 
	if(fOut) {
		//goi 1 cai vong lap vo han
		for(;;) {
			struct SinhVien sv;
			fscanf(fOut, "%10s %10s %20[^\n] %10s %10s %10f %10f %10f %10f\n",//vi du ten dem co 2 chu thi dung[^\n] de doc duoc cai khoang trang
			sv.ma, sv.hoVaTen.ho, sv.hoVaTen.dem, sv.hoVaTen.ten, sv.lop,
			&sv.diem.toan, &sv.diem.ly, &sv.diem.hoa, &sv.diem.tbc);
			
			ds[i++] = sv;
			if(feof(fOut)) { // thoat chuong trinh
				break;
			}
		}
	}
	//khong thi bo qua
	fclose(fOut);
	*slsv = i;
}

struct SinhVien;
void hienThiDSSV(struct SinhVien*, int);
void hienThiTenCot();

//ham main de su dung nhung cai code minh vua khai bao o tren
int main() {
	//lay 1 mang danh sach sinh vien
	struct SinhVien dssv[100];
	int slsv = 0;
	int chon;
	char idstudent[6];
	
	docFile(dssv, &slsv);
	printf("------------------------------------------UNG DUNG QUAN LY DIEM CUA SINH VIEN---------------------------------------\n");
	
	//hien thi dssc( luc chay len la no hien thi ra luon cho de quan sat)
	hienThiDSSV(dssv, slsv);
	int i;
				
	do {
		
		printf("====================== MENU =====================");
		printf("\n I.CAP NHAT THONG TIN SINH VIEN");
		printf("\n\t 1. Them Sinh vien vao danh sach.");
		printf("\n\t 2. Hien thi danh sach sinh vien.");
		printf("\n\t 3. Sua thong tin sinh vien.");
		printf("\n\t 4. Xoa thong tin sinh vien.");
		printf("\n\t 5. Luu thong tin sinh vien ra file txt.");
		printf("\n II. SAP XEP TIM KIEM THONG TIN SINH VIEN");
		printf("\n\t 6. Sap xep theo diem trung binh tang dan.");
		printf("\n\t 7. Sap xep theo diem trung binh giam dan.");
		printf("\n\t 8. Tim sinh vien theo lop.");
		printf("\n\t 9. Tim sinh vien theo diem trung binh cong.");
		printf("\n\t 0. Thoat chuong trinh.");
		printf("\n-------------------------");
		printf("\nLua chon cua ban la: ");
		
		scanf("%d", &chon);
		struct SinhVien sv;
		
		//cau lenh dieu kien
		switch(chon) {
			case 0:
				break;
				
			case 1:
				
				//Cai nay de goi den cai thang nhapSV o tren
				printf("\n1: Nhap thong tin sinh vien:\n");
				sv = nhapSV();
				dssv[slsv++] = sv;
				printf("\n");
				printf("\n");
				printf("\n");
				break;
				
			case 2:
				printf("\n2: Danh sach sinh vien hien co trong ung dung:\n");
				hienThiDSSV(dssv, slsv); 				
				printf("\n");
				printf("\n");
				printf("\n");
				break;
				
			case 3:
				fflush(stdin);
                printf("\n3: Ban nhap vao ma sinh vien muon sua:");
                gets(idstudent);
                suattsv(idstudent);
                break;
			
			case 4:
				fflush(stdin);
                printf("\n4: Ban nhap vao ma sinh vien muon xoa:");
                gets(idstudent);
                suattsv(idstudent);
                break;
                
            //Moi lan nhap xong thi bam vao day de no luu vao file txt
			case 5:
				ghiFile(dssv, slsv);
				printf("\n5: Luu thong tin sinh vien thanh cong!\n");
				printf("\n");
				printf("\n");
				printf("\n");
				break;
				
			case 6:
				sapXepTheoDiemTangDan(dssv, slsv);
				printf("\n6: Danh sach sinh vien sau khi sap xep theo diem trung binh tang dan:\n");
				hienThiDSSV(dssv, slsv);
				printf("\n");
				printf("\n");
				printf("\n");
				break;
			case 7:
				sapXepTheoDiemGiamDan(dssv, slsv);
				printf("\n7: Danh sach sinh vien sau khi sap xep theo diem trung binh giam dan:\n");
				hienThiDSSV(dssv, slsv);
				printf("\n");
				printf("\n");
				printf("\n");
				break;
				
			case 8:
				printf("\n8: Tim kiem thong tin theo lop:\n");
				timTheoLop(dssv, slsv);
				printf("\n");
				printf("\n");
				printf("\n");
				break;
			
			
			case 9:
				printf("\n9: Tim kiem thong tin theo diem:\n");
				timTheoDiem(dssv, slsv);
				printf("\n");
				printf("\n");
				printf("\n");
				break;
				
			default:
				printf("Ban chon sai roi, vui long chon lai!\n");
				printf("\n");
				printf("\n");
				printf("\n");
				break;
		}
		
	} while(chon);
	
	return 0;
}
