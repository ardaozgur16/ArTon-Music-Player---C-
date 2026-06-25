# ArTon-Music-Player---C++-
\## Proje Hakkında

\*\*Arton Music Player\*\*, Veri Yapıları dersi kapsamında geliştirilmiş konsol tabanlı bir müzik çalar uygulamasıdır. Projenin temel amacı, şarkıların yönetimini statik diziler yerine dinamik \*\*Çift Yönlü Bağlı Liste (Doubly Linked List)\*\* yapısı ile gerçekleştirmektir.



Bu yapı sayesinde:

\* Şarkılar arasında ileri (`Next`) ve geri (`Prev`) yönlü geçişler \*\*O(1)\*\* karmaşıklığıyla yapılır.

\* Bellek yönetimi (Memory Management) manuel olarak `new` ve `delete` operatörleri ile sağlanır.



---



\##  Kurulum ve Çalıştırma



\### Önemli Uyarı: Ses Dosyaları

Programın doğru çalışabilmesi ve şarkıları çalabilmesi için `.wav` formatındaki müzik dosyalarının programın `.exe` dosyası ile \*\*aynı klasörde\*\* bulunması gerekmektedir.



Alternatif olarak, kod içerisinde varsayılan olarak tanımlı olan şu dizini oluşturup müzikleri içine atabilirsiniz:

`C:\\artonmusic\\ArTonMusic\\`



\### Derleme (Compile)

Kod, \*\*Windows\*\* işletim sistemi için yazılmıştır. `Windows.h` ve `mmsystem.h` kütüphanelerini kullanır.

\* Visual Studio veya Dev-C++ gibi derleyicilerde doğrudan açıp derleyebilirsiniz.

\* Kod içerisinde `#pragma comment(lib, "winmm.lib")` satırı bulunduğu için ek linker ayarı yapmanıza gerek yoktur.



---



\## Kullanım (Kontroller)



Uygulama açıldığında menü üzerinden klavye ile kontrol edilir:



| Tuş | İşlem | Açıklama |

| :--- | :--- | :--- |

| \*\*\[1]\*\* | \*\*Oynat\*\* | Seçili olan şarkıyı çalar. |

| \*\*\[2]\*\* | \*\*Durdur\*\* | Çalan şarkıyı durdurur. |

| \*\*\[3]\*\* | \*\*Sonraki\*\* | Listede bir sonraki şarkıya geçer. |

| \*\*\[4]\*\* | \*\*Önceki\*\* | Listede bir önceki şarkıya döner. |

| \*\*\[5]\*\* | \*\*Ekle\*\* | Listeye yeni bir .wav dosyası ekler. |

| \*\*\[ESC]\*\* | \*\*Çıkış\*\* | Programı kapatır ve belleği temizler. |



---



\## Teknik Detaylar



\### Veri Yapısı

Her şarkı bir `Düğüm (Node)` olarak tutulur:

```cpp

struct Sarki {

&nbsp;   string dosyaYolu;

&nbsp;   string sarkiAdi;

&nbsp;   Sarki\* ileri; // Next Pointer

&nbsp;   Sarki\* geri;  // Prev Pointer

};

Built a console-based audio player using C++ and the Windows Multimedia API (winmm.lib) for asynchronous .wav file playback.   Engineered a custom Doubly Linked List data structure from scratch to efficiently manage playlist operations such as adding tracks, skipping, and returning to previous songs. 
