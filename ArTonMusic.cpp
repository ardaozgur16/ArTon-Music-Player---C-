
#include <iostream>
#include <string>
#include <windows.h> // Renkler ve bekleme komutu
#include <conio.h>   // Klavye islemleri
#include <mmsystem.h> // Ses calma

 // Ses kutuphanesini projeye dahil et
#pragma comment(lib, "winmm.lib")

using namespace std;

// Sarki dugumu (Node)
struct Sarki {
    string dosyaYolu;
    string sarkiAdi;
    Sarki* ileri; // Sonraki
    Sarki* geri;  // Onceki
};

class MuzikCalar {
private:
    Sarki* bas;    // Listenin basi
    Sarki* son;    // Listenin sonu
    Sarki* calan;  // Su an calan sarki

public:
    MuzikCalar() {
        bas = NULL;
        son = NULL;
        calan = NULL;
    }

    // Yikici fonksiyon (Program kapaninca bellegi temizle)
    ~MuzikCalar() {
        Sarki* temp = bas;
        while (temp != NULL) {
            Sarki* silinecek = temp;
            temp = temp->ileri;
            delete silinecek;
        }
    }

    // Sarki Ekleme
    void ekle(string yol, string isim) {
        Sarki* yeni = new Sarki();
        yeni->dosyaYolu = yol;
        yeni->sarkiAdi = isim;
        yeni->ileri = NULL;
        yeni->geri = NULL;

        if (bas == NULL) {
            bas = yeni;
            son = yeni;
            calan = bas;
        }
        else {
            // Once calan eski sarkiyi durdur ki karismasin
            PlaySoundA(NULL, 0, 0);

            son->ileri = yeni;
            yeni->geri = son;
            son = yeni;

            // ISARETCIYI GUNCELLE: Artik yeni eklenen sarki secili olsun
            calan = yeni;
        }
    }

    // Oynatma fonksiyonu
    void oynat() {
        if (calan == NULL) return;

        // Arka planda calmasi icin SND_ASYNC kullaniyoruz
        bool durum = PlaySoundA(calan->dosyaYolu.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

        if (!durum) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Kirmizi renk
            cout << "\n[HATA] Dosya bulunamadi!" << endl;
            cout << "Konum: " << calan->dosyaYolu << endl;
            cout << "Lutfen klasorun C:\\artonmusic\\ArTonMusic\\ oldugundan emin olun." << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Rengi duzelt
            system("pause");
        }
    }

    void durdur() {
        PlaySoundA(NULL, 0, 0);
    }

    void sonraki() {
        if (calan != NULL && calan->ileri != NULL) {
            calan = calan->ileri;
            oynat();
        }
    }

    void onceki() {
        if (calan != NULL && calan->geri != NULL) {
            calan = calan->geri;
            oynat();
        }
    }

    // Menu tasarimi
    void arayuz() {
        system("cls");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Mavi
        cout << "===============================================" << endl;
        cout << "              ARTON MUSIC PLAYER               " << endl;
        cout << "===============================================" << endl;

        Sarki* temp = bas;
        int sayac = 1;

        if (bas == NULL) cout << "\n       [LISTE BOS]\n" << endl;

        while (temp != NULL) {
            if (temp == calan) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Yesil
                cout << " -> " << sayac << ". " << temp->sarkiAdi << " [SECILI/CALIYOR]" << endl;
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); // Gri
                cout << "    " << sayac << ". " << temp->sarkiAdi << endl;
            }
            temp = temp->ileri;
            sayac++;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Beyaz
        cout << "===============================================" << endl;
        cout << "[1] Oynat   [2] Durdur" << endl;
        cout << "[3] Sonraki [4] Onceki" << endl;
        cout << "[5] Ekle    [ESC] Cikis" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");
    MuzikCalar mp;

    // Sarki eklmee
    mp.ekle("C:\\artonmusic\\ArTonMusic\\sarki1.wav", "Ace of Base - Happy Nation");
    mp.ekle("C:\\artonmusic\\ArTonMusic\\sarki2.wav", "The Weeknd - Blinding Lights");
    mp.ekle("C:\\artonmusic\\ArTonMusic\\sarki3.wav", "Eminem - Lose Yourself");


    char secim;
    while (true) {
        mp.arayuz();
        secim = _getch(); // Enter beklemeden tus okuma

        if (secim == 27) { // ESC tusu
            mp.durdur();
            break;
        }

        switch (secim) {
        case '1': mp.oynat(); break;
        case '2': mp.durdur(); break;
        case '3': mp.sonraki(); break;
        case '4': mp.onceki(); break;
        case '5': {
            system("cls");
            string dosya, ad;
            cout << "\nDosya Yolu (orn: sarki5.wav): ";
            cin >> dosya;
            cout << "Sarki Ismi: ";
            cin.ignore();
            getline(cin, ad);

            // Tam yol olusturma (Kullanici sadece sarki5.wav yazsa bile calissin diye)
            // Eger tam yol yazmazsa basina klasoru biz ekliyoruz.
            string tamYol;
            if (dosya.find(":") == string::npos) { // Icinde : yoksa kisa isimdir
                tamYol = "C:\\artonmusic\\ArTonMusic\\" + dosya;
            }
            else {
                tamYol = dosya;
            }

            mp.ekle(tamYol, ad);
            break;
        }
        }
    }
    return 0;
}