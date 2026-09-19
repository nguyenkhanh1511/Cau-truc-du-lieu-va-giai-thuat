#include <stdio.h>
#include <string.h>

struct Ngay {
    int ngay;
    int thang;
    int nam;
};

struct HangHoa {
    int ma;
    char ten[50];
    struct Ngay ngayXuat;
    float gia;
};

void nhap(struct HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nNhap hang hoa thu %d:\n", i + 1);

        printf("Ma hang hoa: ");
        scanf("%d", &a[i].ma);

        getchar();
        printf("Ten hang hoa: ");
        fgets(a[i].ten, sizeof(a[i].ten), stdin);
        a[i].ten[strcspn(a[i].ten, "\n")] = '\0';

        printf("Ngay xuat (dd/mm/yyyy): ");
        scanf("%d/%d/%d",
              &a[i].ngayXuat.ngay,
              &a[i].ngayXuat.thang,
              &a[i].ngayXuat.nam);

        printf("Gia xuat (trieu dong): ");
        scanf("%f", &a[i].gia);
    }
}

void xuat(struct HangHoa a[], int n) {
    printf("\n%-10s %-25s %-15s %-15s\n",
           "Ma", "Ten hang hoa", "Ngay xuat", "Gia");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-25s %02d/%02d/%04d      %-15.2f\n",
               a[i].ma,
               a[i].ten,
               a[i].ngayXuat.ngay,
               a[i].ngayXuat.thang,
               a[i].ngayXuat.nam,
               a[i].gia);
    }
}

void selectionSort(struct HangHoa a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j].gia < a[min].gia) {
                min = j;
            }
        }

        if (min != i) {
            struct HangHoa temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

int binarySearch(struct HangHoa a[], int left, int right, float x) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if (a[mid].gia == x) {
        return mid;
    }

    if (a[mid].gia < x) {
        return binarySearch(a, mid + 1, right, x);
    }

    return binarySearch(a, left, mid - 1, x);
}

void timHangHoa(struct HangHoa a[], int n, float x) {
    int pos = binarySearch(a, 0, n - 1, x);

    if (pos == -1) {
        printf("\nKhong tim thay hang hoa co gia %.2f trieu dong.\n", x);
        return;
    }

    printf("\nCac hang hoa co gia %.2f trieu dong:\n", x);

    int left = pos;
    while (left > 0 && a[left - 1].gia == x) {
        left--;
    }

    int right = pos;
    while (right < n - 1 && a[right + 1].gia == x) {
        right++;
    }

    for (int i = left; i <= right; i++) {
        printf("%-10d %-25s %02d/%02d/%04d      %-15.2f\n",
               a[i].ma,
               a[i].ten,
               a[i].ngayXuat.ngay,
               a[i].ngayXuat.thang,
               a[i].ngayXuat.nam,
               a[i].gia);
    }
}

int main() {
    struct HangHoa a[100];
    int n;
    float x;

    printf("Nhap so luong hang hoa n = ");
    scanf("%d", &n);

    nhap(a, n);

    printf("\n===== DANH SACH HANG HOA VUA NHAP =====\n");
    xuat(a, n);

    selectionSort(a, n);

    printf("\n===== DANH SACH SAU KHI SAP XEP =====\n");
    xuat(a, n);


    printf("\nNhap gia X can tim (trieu dong): ");
    scanf("%f", &x);

    timHangHoa(a, n, x);

    return 0;
}
