#include <stdio.h>
#include <string.h>

struct KhachHang {
    int maKH;
    char tenKH[50];
    char soDT[15];
    float tongTien;
};

void nhap(struct KhachHang a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nNhap khach hang thu %d:\n", i + 1);

        printf("Ma khach hang: ");
        scanf("%d", &a[i].maKH);

        getchar();

        printf("Ten khach hang: ");
        fgets(a[i].tenKH, sizeof(a[i].tenKH), stdin);
        a[i].tenKH[strcspn(a[i].tenKH, "\n")] = '\0';

        printf("So dien thoai: ");
        fgets(a[i].soDT, sizeof(a[i].soDT), stdin);
        a[i].soDT[strcspn(a[i].soDT, "\n")] = '\0';

        printf("Tong tien thanh toan: ");
        scanf("%f", &a[i].tongTien);
    }
}

void xuat(struct KhachHang a[], int n) {
    printf("\n%-10s %-25s %-15s %-20s\n",
           "Ma KH", "Ten khach hang", "So dien thoai", "Tong tien");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-25s %-15s %-20.2f\n",
               a[i].maKH,
               a[i].tenKH,
               a[i].soDT,
               a[i].tongTien);
    }
}

void insertionSort(struct KhachHang a[], int n) {
    for (int i = 1; i < n; i++) {
        struct KhachHang x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j].tongTien > x.tongTien) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}

int binarySearch(struct KhachHang a[], int left, int right, float X) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if (a[mid].tongTien == X) {
        return mid;
    }

    if (a[mid].tongTien < X) {
        return binarySearch(a, mid + 1, right, X);
    }

    return binarySearch(a, left, mid - 1, X);
}

void timKiem(struct KhachHang a[], int n, float X) {
    int pos = binarySearch(a, 0, n - 1, X);

    if (pos == -1) {
        printf("\nKhong tim thay khach hang co tong tien %.2f\n", X);
        return;
    }

    int left = pos;
    while (left > 0 && a[left - 1].tongTien == X) {
        left--;
    }

    int right = pos;
    while (right < n - 1 && a[right + 1].tongTien == X) {
        right++;
    }

    printf("\n===== KHACH HANG CO TONG TIEN = %.2f =====\n", X);

    for (int i = left; i <= right; i++) {
        printf("Ma KH: %d\n", a[i].maKH);
        printf("Ten KH: %s\n", a[i].tenKH);
        printf("So dien thoai: %s\n", a[i].soDT);
        printf("Tong tien thanh toan: %.2f\n", a[i].tongTien);
        printf("-----------------------------\n");
    }
}

int main() {
    struct KhachHang a[100];
    int n;
    float X;

    printf("Nhap so luong khach hang n = ");
    scanf("%d", &n);

    nhap(a, n);

    printf("\n===== DANH SACH KHACH HANG VUA NHAP =====\n");
    xuat(a, n);

    insertionSort(a, n);

    printf("\n===== DANH SACH SAU KHI SAP XEP =====\n");
    xuat(a, n);

    printf("\nNhap tong tien X can tim: ");
    scanf("%f", &X);

    timKiem(a, n, X);

    return 0;
}
