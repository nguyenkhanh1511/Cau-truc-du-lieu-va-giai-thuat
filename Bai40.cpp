#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien
{
    int maSV;
    char ten[50];
    char lop[20];
    float tongKet;
    char hanhKiem[20];
};

struct Node
{
    SinhVien data;
    Node *left;
    Node *right;
};

typedef Node *Tree;

void khoiTao(Tree &t)
{
    t = NULL;
}

Node *taoNode(SinhVien sv)
{
    Node *p = new Node;
    p->data = sv;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void chenNode(Tree &t, SinhVien sv)
{
    if (t == NULL)
        t = taoNode(sv);
    else if (sv.maSV < t->data.maSV)
        chenNode(t->left, sv);
    else if (sv.maSV > t->data.maSV)
        chenNode(t->right, sv);
}

Node *timKiem(Tree t, int ma)
{
    if (t == NULL || t->data.maSV == ma)
        return t;

    if (ma < t->data.maSV)
        return timKiem(t->left, ma);
    else
        return timKiem(t->right, ma);
}

void duyetCay(Tree t)
{
    if (t != NULL)
    {
        duyetCay(t->left);

        printf("\nMa SV: %d", t->data.maSV);
        printf("\nTen: %s", t->data.ten);
        printf("\nLop: %s", t->data.lop);
        printf("\nTong ket: %.2f", t->data.tongKet);
        printf("\nHanh kiem: %s\n", t->data.hanhKiem);
        printf("----------------------\n");

        duyetCay(t->right);
    }
}

int main()
{
    Tree t;
    khoiTao(t);

    int n;
    SinhVien sv;

    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        printf("\nSinh vien %d\n", i + 1);

        printf("Ma SV: ");
        scanf("%d", &sv.maSV);
        getchar();

        printf("Ten: ");
        gets(sv.ten);

        printf("Lop: ");
        gets(sv.lop);

        printf("Tong ket: ");
        scanf("%f", &sv.tongKet);
        getchar();

        printf("Hanh kiem: ");
        gets(sv.hanhKiem);

        chenNode(t, sv);
    }

    printf("\n===== DANH SACH SINH VIEN =====\n");
    duyetCay(t);

    int ma;
    printf("\nNhap ma sinh vien can tim: ");
    scanf("%d", &ma);

    Node *kq = timKiem(t, ma);

    if (kq == NULL)
        printf("Khong co sinh vien trong cay!");
    else
    {
        printf("\n===== THONG TIN SINH VIEN =====");
        printf("\nMa SV: %d", kq->data.maSV);
        printf("\nTen: %s", kq->data.ten);
        printf("\nLop: %s", kq->data.lop);
        printf("\nTong ket: %.2f", kq->data.tongKet);
        printf("\nHanh kiem: %s", kq->data.hanhKiem);
    }

    return 0;
}
