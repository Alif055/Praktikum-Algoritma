#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct datapenduduk {
    int nk;
    char nama[44];
    char alm[44];
    char kel[2];
};

void input() {
    // make ab soalnya jika menggunakan wb akan overwrite(ditumpuk) melainkan menambahkan
    FILE *file = fopen("datapenduduk.dat", "ab");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    datapenduduk data;
    int jml;
    cout << "Jumlah data penduduk yang ingin ditambah: "; cin >> jml;

    // agak rusak di bagian ini
    for (int i = 0; i < jml; i++)
    {
        cout << "Masukkan Nomor Kependudukan: "; cin >> data.nk;
    cin.ignore();
    cout << "Masukkan Nama: "; cin.getline(data.nama, 44);
    cout << "Masukkan Alamat: "; cin.getline(data.alm, 44);
    cout << "Masukkan Jenis Kelamin (L/P): "; cin >> data.kel;
    fwrite(&data, sizeof(datapenduduk), 1, file);
    cout << "Data berhasil disimpan!" << endl;
    }
    fclose(file);
}

void liatdata() {
    FILE *file = fopen("datapenduduk.dat", "rb");
    if (file == NULL) {
        cout << "Belum ada data!" << endl;
        return;
    }
    
    datapenduduk data;
    cout << "\nData Penduduk:\n";
    while (fread(&data, sizeof(datapenduduk), 1, file)) {
        cout << "NK: " << data.nk << " | Nama: " << data.nama << " | Alamat: " << data.alm << " | Kelamin: " << data.kel << endl;
    }
    fclose(file);
}

void search() {
    FILE *file = fopen("datapenduduk.dat", "rb");
    if (file == NULL) {
        cout << "Belum ada data!" << endl;
        return;
    }
    
    int cari;
    cout << "Masukkan NK yang dicari: "; cin >> cari;
    datapenduduk data;
    bool found = false;
    while (fread(&data, sizeof(datapenduduk), 1, file)) {
        if (data.nk == cari) {
            cout << "NK: " << data.nk << " | Nama: " << data.nama << " | Alamat: " << data.alm << " | Kelamin: " << data.kel << endl;
            found = true;
            break;
        }
    }
    fclose(file);
    if (!found) cout << "Data tidak ditemukan!" << endl;
}

void edit() {
    FILE *file = fopen("datapenduduk.dat", "rb+");
    if (file == NULL) {
        cout << "Belum ada data!" << endl;
        return;
    }
    
    int cari;
    cout << "Masukkan Nomor Kependudukan yang ingin diedit: "; cin >> cari;
    datapenduduk data;
    bool found = false;
    while (fread(&data, sizeof(datapenduduk), 1, file)) {
        if (data.nk == cari) {
            cout << "Masukkan alamat baru: ";
            cin.ignore();
            cin.getline(data.alm, 44);
            // ada warning disini
            //warning: overflow in conversion from 'long long unsigned int' to 'long int' changes value from '18446744073709551520' to '-96' [-Woverflow]  
            //91|fseek(file, -sizeof(datapenduduk), SEEK_CUR);
            fseek(file, -sizeof(datapenduduk), SEEK_CUR);
            fwrite(&data, sizeof(datapenduduk), 1, file);
            found = true;
            cout << "Data berhasil diperbarui!" << endl;
            break;
        }
    }
    fclose(file);
    if (!found) cout << "Data tidak ditemukan!" << endl;
}

void hapus() {
    FILE *file = fopen("datapenduduk.dat", "rb");
    if (file == NULL) {
        cout << "Belum ada data!" << endl;
        return;
    }
    
    FILE *temp = fopen("temp.dat", "wb");
    int cari;
    cout << "Masukkan NK yang ingin dihapus: "; cin >> cari;
    datapenduduk data;
    bool found = false;
    while (fread(&data, sizeof(datapenduduk), 1, file)) {
        if (data.nk == cari) {
            found = true;
        } else {
            fwrite(&data, sizeof(datapenduduk), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove("datapenduduk.dat");
    rename("temp.dat", "datapenduduk.dat");
    if (found) cout << "Data berhasil dihapus!" << endl;
    else cout << "Data tidak ditemukan!" << endl;
}

int main() {
    int pil;
    do {
        cout << "\n|-----Menu Data Kependudukan Depok-----|\n";
        cout << "1. Input Data Penduduk\n";
        cout << "2. Menunjukkan Data Penduduk\n";
        cout << "3. Cari Data Penduduk\n";
        cout << "4. Edit Data Penduduk\n";
        cout << "5. Hapus Data Penduduk\n";
        cout << "6. Exit\n";
        cout << "Masukkan Pilihan Anda! : ";
        cin >> pil;
        cin.ignore();

        switch (pil) {
            case 1: input(); break;
            case 2: liatdata(); break;
            case 3: search(); break;
            case 4: edit(); break;
            case 5: hapus(); break;
            case 6: cout << "keluar dengan sukses" << endl; break;
            default: cout << "Pilihan tidak ada!\n";
        }
    } while (pil != 6);
}
