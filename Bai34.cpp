#include <stdio.h>
#include <string.h>

struct Ngay {
    int ngay;
    int thang;
    int nam;
};

struct NhanVien {
    int maNV;
    char hoTen[50];
    struct Ngay ngaySinh;
    float luong;
};

void nhap(struct NhanVien a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n===== NHAP NHAN VIEN THU %d =====\n", i + 1);

        printf("Ma nhan vien: ");
        scanf("%d", &a[i].maNV);

        getchar();
        printf("Ho ten: ");
        fgets(a[i].hoTen, sizeof(a[i].hoTen), stdin);
        a[i].hoTen[strcspn(a[i].hoTen, "\n")] = '\0';

        printf("Ngay sinh (dd/mm/yyyy): ");
        scanf("%d/%d/%d",
              &a[i].ngaySinh.ngay,
              &a[i].ngaySinh.thang,
              &a[i].ngaySinh.nam);

        printf("Luong (trieu dong): ");
        scanf("%f", &a[i].luong);
    }
}

void xuat(struct NhanVien a[], int n) {
    printf("\n%-10s %-25s %-15s %-15s\n",
           "Ma NV", "Ho ten", "Ngay sinh", "Luong");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-25s %02d/%02d/%04d   %-15.2f\n",
               a[i].maNV,
               a[i].hoTen,
               a[i].ngaySinh.ngay,
               a[i].ngaySinh.thang,
               a[i].ngaySinh.nam,
               a[i].luong);
    }
}

void bubbleSort(struct NhanVien a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j].luong > a[j + 1].luong) {
                struct NhanVien temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int binarySearch(struct NhanVien a[], int left, int right, float X) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if (a[mid].luong == X) {
        return mid;
    }

    if (a[mid].luong < X) {
        return binarySearch(a, mid + 1, right, X);
    }

    return binarySearch(a, left, mid - 1, X);
}

void timKiem(struct NhanVien a[], int n, float X) {
    int pos = binarySearch(a, 0, n - 1, X);

    if (pos == -1) {
        printf("\nKhong tim thay nhan vien co luong %.2f trieu dong.\n", X);
        return;
    }

    int left = pos;
    while (left > 0 && a[left - 1].luong == X) {
        left--;
    }

    int right = pos;
    while (right < n - 1 && a[right + 1].luong == X) {
        right++;
    }

    printf("\n===== NHAN VIEN CO LUONG = %.2f =====\n", X);

    for (int i = left; i <= right; i++) {
        printf("Ma NV: %d\n", a[i].maNV);
        printf("Ho ten: %s\n", a[i].hoTen);
        printf("Ngay sinh: %02d/%02d/%04d\n",
               a[i].ngaySinh.ngay,
               a[i].ngaySinh.thang,
               a[i].ngaySinh.nam);
        printf("Luong: %.2f trieu dong\n", a[i].luong);
        printf("-----------------------------\n");
    }
}

int main() {
    struct NhanVien a[100];
    int n;
    float X;

    printf("Nhap so luong nhan vien n = ");
    scanf("%d", &n);

    nhap(a, n);

    printf("\n===== DANH SACH NHAN VIEN VUA NHAP =====\n");
    xuat(a, n);

    bubbleSort(a, n);

    printf("\n===== DANH SACH SAU KHI SAP XEP =====\n");
    xuat(a, n);

    printf("\nNhap muc luong X can tim: ");
    scanf("%f", &X);

    timKiem(a, n, X);

    return 0;
}
