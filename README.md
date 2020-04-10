# SoalShiftSISOP20_modul3_T01
Repository ini Sebagai Laporan Resmi Soal Shift Modul 2 Praktikum Sistem Operasi 2020

### Disusun oleh :
- Anis Saidatur Rochma [05311840000002] 
- Kadek Nesya Kurniadewi [05311840000009]

## Soal 4

Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan setiap batunya memiliki warna yang berbeda. Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian.

Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian.

**Batu mulia pertama.** Emerald. Batu mulia yang berwarna hijau mengkilat. Pada batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi: 1. Buatlah program C dengan nama "**4a.c**", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah **4x2**, dan matriks kedua **2x5**. Isi dari matriks didefinisikan **di dalam kodingan**. Matriks nantinya akan berisi angka 1-20 (**tidak perlu** dibuat filter angka). 2. Tampilkan matriks hasil perkalian tadi ke layar.

### Penyelesaian Soal
- kita diminta untuk mengalikan matriks dengan ukuran 4x2 dan 2x5, memiliki hasil matriks dengan ordo 4x5, dan isi dari matriks awalnya kita isi sendiri random angka 1-19
- Beri Thread
- Gunakan shared memory
- Jalankan Program

***Sorce code***  [Soal 4a](https://github.com/anissaidatur/SoalShiftSISOP20_modul3_T01/blob/master/soal4/4a.c)

**Library yang digunakan**

```c

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
```

**Deklarasi variabel pada matrix**
```c
int matA[4][2] , matB[2][5] , matC[4][5];
int row = 0; // untuk mengecek tiap baris pada matriksnya
int col = 0;
```

**Perkalian matrix**
```c
void* kali(void* arg) {
  if(col >= 5){
    col = 0;
    row++;
  }

  for (int i = 0; i < 2; i++) matC[row][col] += matA[row][i] * matB[i][col]; // Hasil kali matrix a dan b dijumlah ke matrix
col++;
}
```

**Fungsi utama pada matriks A dan matriks B**
```c
int main() {
  srand(time(NULL));
  //menampilkan matriks A
  printf("A = \n");
  ... 
  }
```
note: tanda ... merupakan kode program yang tidak ditampilkan untuk memudahkan pembacaan, untuk lebih detail dapat dilihat pada [Soal 4a.c](https://github.com/anissaidatur/SoalShiftSISOP20_modul3_T01/blob/master/soal4/4a.c)

`srand(time(NULL));` untuk memasang Seed pada rand. Random number generator yang ada di c bukanlah random, tapi pseudorandom. input angka setelah itu diproses , lalu keluar output "Bilangan Random" . Nah input angka tersebut disebut dengan Seed . Apabila seed tidak diubah, maka rand hasil output akan sama terus. 
Seed biasanya memakai nilai time atau waktu saat program dinyalakan. jadi ketika programnya dinyalakan pada tanggal dan jam berbeda hasil rand nya juga berbeeda. 
`Time(NULL)` adalah waktu saat ini. jadi `srand(time(NULL));`adalah Seed rand untuk waktu saat ini

**Melakukan Perkalian Matrix menggunakan Thread, tidak lupa untuk join agar saling menunggu**
```c
//declaring threads
  pthread_t tid[20]; // SIZE 20

  for (int i = 0; i < 20; i++) { // kalau i kurangdari 20 maka jalanin fungsi kali
    pthread_create(&(tid[i]), NULL, &kali, NULL);
  }

  for (int i = 0; i < 20; i++) { // buat wait
    pthread_join(tid[i], NULL);
  }
```
mendeklarasikan thread berjumlah 20, membentuk thread menggunakan pthread_create dengan parameter thread ke-i, NULL, fungsi jumlah, dan angka ke-i dalam array hasil. lalu meng-join-kan semua thread.Threads akan menunggu sampai threads sebelumnya benar benar selesai melakukan pekerjaannya

**ShmKey = SharedMemory Key , ShmdID = SharedMemory ID,  ShmPtr = Struct yang akan di passing**
```c
  key_t          ShmKEY;
  int            ShmID;
  struct shared  *ShmPTR;
```

**Proses shared memory**
```c
ShmKEY = ftok("key",100);
  ShmID = shmget(ShmKEY,sizeof(struct shared),IPC_CREAT|0666);
  if(ShmID < 0){
    printf("Shmget error\n");
    exit(1);
  }
```
`Shmid` → ID dari shared memory
`shmget()` System call untuk membuat suatu segmen shared memory 

**Memasukkan data yang ada di matriks ke dalam struct**
```c
ShmPTR->status = UNREADY;
int j = 0;
int k = 0;

for(int i = 0; i < 20; i++){
  if(k >= 5){
    j++;
    k = 0;
  }
  ShmPTR->data[i] = matC[j][k];
  k++;
}
```

```c
 printf("Jalanin yang B \n");
   while (ShmPTR->status != SIAP)
       sleep(1);
```
