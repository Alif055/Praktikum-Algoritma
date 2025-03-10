#include <iostream>
#include <string>

using namespace std;
int jmldt=5;

struct droti{
    string nama;
    int kode;
    int harga;
};


droti roti[]={
    {"Roti Tawar", 114, 15000,},
    {"Roti Keju", 112, 17000,},
    {"Roti Coklat", 113, 17500,},
    {"Roti Abon", 111, 14000,},
    {"Roti Stroberi", 123, 13000,}};

 void rotirotikeren(droti *ptr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Nama  : " << (ptr + i)->nama << endl;
        cout << "Kode  : " << (ptr + i)->kode << endl;
        cout << "Harga : " << (ptr + i)->harga << endl;
        cout << "=-----------------------------=" << endl;
    }
}

void kseqsearch() {
    int src;
    cout << "Masukkan kode roti yang ingin dicari: ";
    cin >> src;
    cin.ignore();

    for (int i = 0; i < jmldt; i++) {
        if (roti[i].kode == src) {
            cout << "\nRoti ditemukan:\n";
            cout << "Nama  : " << roti[i].nama << endl;
            cout << "Kode  : " << roti[i].kode << endl;
            cout << "Harga : " << roti[i].harga << endl;
            return;
        } else
        {
            cout << "roti tersebut tidak terdapat di bakeshop ini";
        }
        
    }
}

void qs(int low, int high) {
    if (low < high) {
        int pivot = roti[high].harga;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (roti[j].harga < pivot) {
                i++;
                swap(roti[i], roti[j]);
            }
        }
        swap(roti[i + 1], roti[high]);

        int john = i + 1;
        qs(low, john - 1);
        qs(john + 1, high);
    }
}

void qsnama(int low, int high) {
    if (low < high) {
        string pivot = roti[high].nama;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (roti[j].nama < pivot) {
                i++;
                swap(roti[i], roti[j]);
            }
        }
        swap(roti[i + 1], roti[high]);

        int johnlennon = i + 1;
        qs(low, johnlennon - 1);
        qs(johnlennon + 1, high);
    }
}
void nbinsearch() {
    qsnama(0,jmldt-1);
    string src;
    cout << "Masukkan nama roti yang ingin dicari: ";
    getline(cin, src);
    int low = 0, high = jmldt - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (roti[mid].nama == src) {
            cout << "Roti ditemukan:\n";
            cout << "Nama  : " << roti[mid].nama << endl;
            cout << "Kode  : " << roti[mid].kode << endl;
            cout << "Harga : " << roti[mid].harga << endl;
            return;
        } else if (roti[mid].nama < src) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "Roti dengan nama " << src << " tidak ditemukan\n";
    exit(1);
}
void bs() {
    for (int i = 0; i < jmldt - 1; i++) {
        for (int j = 0; j < jmldt - i - 1; j++) {
            if (roti[j].harga < roti[j + 1].harga) {
                swap(roti[j], roti[j + 1]);
            }
        }
    }
    cout << "Data berhasil diurutkan menggunakan Bubble Sort!\n";
}
int main(){
    int n = sizeof(roti) / sizeof(roti[0]);

    int pilihan;
    do {
        cout << "\n++++ Pilih Menu ====\n";
        cout << "1. Tampilkan Roti\n";
        cout << "2. Cari Berdasarkan Kode\n";
        cout << "3. Cari Berdasarkan Nama\n";
        cout << "4. Sort Harga Roti (Ascending)\n";
        cout << "5. Sort Harga Roti (Descending)\n";
        cout << "6. Exir\n";
        cout << "------------------\n";
        cout << "Masukkan Pilihan Anda! : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1: rotirotikeren(roti, n);
        break;
        case 2: kseqsearch(); 
        break;
        case 3: nbinsearch(); 
        break;
        case 4: qs(0,n-1); 
        break;
        case 5: bs(); 
        break;
        case 6: cout << "Terimakasih telah mengunjungi ROTI AK";
        break;
        default: cout << "Pilihan tidak ada!\n";
        }
    } while (pilihan != 6);
    
}