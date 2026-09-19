#include <stdio.h>
#include <string.h>

struct VeMayBay {
    int maVe;
    char khoiHanh[50];
    char den[50];
    float giaVe;
};

void nhap(struct VeMayBay a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nNhap ve may bay thu %d:\n", i + 1);

        printf("Ma ve: ");
        scanf("%d", &a[i].maVe);

        getchar();
        printf("Khoi hanh: ");
        fgets(a[i].khoiHanh, sizeof(a[i].khoiHanh), stdin);
        a[i].khoiHanh[strcspn(a[i].khoiHanh, "\n")] = '\0';

        printf("Den: ");
        fgets(a[i].den, sizeof(a[i].den), stdin);
        a[i].den[strcspn(a[i].den, "\n")] = '\0';

        printf("Gia ve: ");
        scanf("%f", &a[i].giaVe);
    }
}

void xuat(struct VeMayBay a[], int n) {
    printf("\n%-10s %-20s %-20s %-15s\n",
           "Ma ve", "Khoi hanh", "Den", "Gia ve");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-20s %-15.2f\n",
               a[i].maVe,
               a[i].khoiHanh,
               a[i].den,
               a[i].giaVe);
    }
}

void swap(struct VeMayBay *a, struct VeMayBay *b) {
    struct VeMayBay temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct VeMayBay a[], int left, int right) {
    float pivot = a[right].giaVe;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (a[j].giaVe < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[right]);

    return i + 1;
}

void quickSort(struct VeMayBay a[], int left, int right) {
    if (left < right) {
        int p = partition(a, left, right);

        quickSort(a, left, p - 1);
        quickSort(a, p + 1, right);
    }
}

int binarySearch(struct VeMayBay a[], int left, int right, float x) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if (a[mid].giaVe == x) {
        return mid;
    }

    if (a[mid].giaVe < x) {
        return binarySearch(a, mid + 1, right, x);
    }

    return binarySearch(a, left, mid - 1, x);
}

void timKiem(struct VeMayBay a[], int n, float x) {
    int pos = binarySearch(a, 0, n - 1, x);

    if (pos == -1) {
        printf("\nKhong tim thay ve may bay co gia %.2f\n", x);
        return;
    }

    int left = pos;
    while (left > 0 && a[left - 1].giaVe == x) {
        left--;
    }

    int right = pos;
    while (right < n - 1 && a[right + 1].giaVe == x) {
        right++;
    }

    printf("\n===== CAC VE CO GIA %.2f =====\n", x);

    for (int i = left; i <= right; i++) {
        printf("%-10d %-20s %-20s %-15.2f\n",
               a[i].maVe,
               a[i].khoiHanh,
               a[i].den,
               a[i].giaVe);
    }
}

int main() {
    struct VeMayBay a[100];
    int n;
    float x;

    printf("Nhap so luong ve may bay n = ");
    scanf("%d", &n);

    nhap(a, n);

    printf("\n===== DANH SACH VE MAY BAY VUA NHAP =====\n");
    xuat(a, n);

    quickSort(a, 0, n - 1);

    printf("\n===== DANH SACH SAU KHI SAP XEP =====\n");
    xuat(a, n);

    printf("\nNhap gia ve X can tim: ");
    scanf("%f", &x);

    timKiem(a, n, x);

    return 0;
}
