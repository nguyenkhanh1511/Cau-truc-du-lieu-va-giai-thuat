#include <iostream>
#include <fstream>
#include <vector>

#define INF 9999999 

using namespace std;

int n; 
int A[100][100];
char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'}; 
void Nhap() {
    ifstream file("Grap.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file Grap.txt!" << endl;
        return;
    }
    file >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> A[i][j];
        }
    }
    file.close();
    cout << "Da nhap do thi thanh cong tu Grap.txt." << endl;
}
void HienThi() {
    cout << "Ma tran trong so cua do thi:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
}
void TimDuongDi(int u, int v) {
    vector<int> dist(n, INF); 
    vector<bool> visited(n, false); 
    vector<int> trace(n, -1);

    dist[u] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INF, current = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                current = j;
            }
        }

        if (current == -1) break; 
        visited[current] = true;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && A[current][j] != 0) { 
                if (dist[current] + A[current][j] < dist[j]) {
                    dist[j] = dist[current] + A[current][j];
                    trace[j] = current;
                }
            }
        }
    }
    if (dist[v] == INF) {
        cout << "Khong co duong di tu " << vertices[u] << " den " << vertices[v] << endl;
    } else {
        cout << "Khoang cach ngan nhat tu " << vertices[u] << " den " << vertices[v] << " la: " << dist[v] << endl;
        cout << "Duong di: ";
        vector<int> path;
        int current = v;
        while (current != -1) {
            path.push_back(current);
            current = trace[current];
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << vertices[path[i]];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }
}
int main() {
    Nhap();
    HienThi();
    cout << "\n--- Ket qua tim duong di ---" << endl;
    TimDuongDi(0, 4); 
    return 0;
}
