# Program Nilai Mahasiswa

Kode ini membaca data dari sebuah file CSV yang berisi data mahasiswa, melakukan validasi input, menghitung statistik seperti rata-rata dan nilai tertinggi/terendah, dan kemudian menghasilkan laporan dalam bentuk file teks. Laporan tersebut mencakup daftar mahasiswa beserta nama, Nomor Pokok Mahasiswa (NPM), dan nilai, bersama dengan nilai rata-rata, nilai tertinggi, dan nilai terendah.

Program ini mendefinisikan fungsi-fungsi untuk memvalidasi Nomor Pokok Mahasiswa (NPM) dan nilai. Ini juga termasuk sebuah fungsi untuk memendekkan nama agar sesuai dengan panjang maksimum yang ditentukan untuk keperluan format dalam laporan.

Secara keseluruhan, ini adalah sebuah program untuk memproses data mahasiswa dan menghasilkan laporan nilai berdasarkan data tersebut.

## Fitur

- Validasi untuk input Nomor Pokok Mahasiswa (NPM) dan nilai
- Perhitungan nilai rata-rata, nilai tertinggi, dan nilai terendah
- Pembuatan laporan nilai dalam bentuk file teks

## Pemakaian

1. Pastikan `input.csv` berisi data nilai yang valid dengan format : `Nama,NPM,Nilai`
2. Jalankan program
3. Periksa `output.txt` untuk laporan yang dihasilkan

## Persyaratan

- C++ compiler

## Code Breakdown

### Libraries
- `iostream`: operasi stream pada input & output.
- `fstream`: stream pada file seperti read/write.
- `sstream`: operasi stream pada string.
- `vector`: tipe data array dinamis.
- `iomanip`: memanipulasi input/output.
- `algorithm`: menyediakan algoritma sorting.
- `string`: memanipulasi string.

### Deklarasi Fungsi

Deklarasi ulang fungsi di atas agar fungsi terbaca saat di compile
```
bool validateNPM(string str);
bool validateNilai(string str);
string shorten(string str, int maxLen);
```
- **Fungsi Validasi**: `validateNPM()`, `validateNilai()`: mengecek apakah format input NPM dan nilai sudah benar.
- **Utility Function**: `shorten()`: menyingkat nama agar muat di dalam kolom tabel.

### Struct
**Struktur Student**: Menyimpan data mahasiswa (nama, NPM, nilai).
```
struct Student {
	string nama;
	char npm[9];
	unsigned int nilai;
};
```
- NPM harus berjumlah 9 digit
- `unsigned int` menandakan tipe data bilangan bulat positif

### Output
- `setw()` : singkatan dari "set width", mengisi string agar jumlah karakter terpenuhi. Secara default, string akan diisi dengan whitespace (spasi). 
- `left` & `right` : alignment teks pada string yg memakai `setw()`
- `setprecision()` : untuk mengatur jumlah digit setelah koma pada nilai desimal

### Validasi Input
**validateNPM()**: Mengecek apakah input NPM berupa karakter angka dengan 9 digit.
```
bool validateNPM(string str) {
	bool validationResult = false;
	size_t npmLen = 9;
	char npm[npmLen];
	auto printError = [](string var) {
		cerr << "[\x1b[31mERROR\x1b[0m] : Nilai '" << var << "' tidak valid untuk NPM" << endl;
	};
	
	try {
		strncpy(npm, str.c_str(), npmLen);
		if ((sizeof(npm)/sizeof(char)) != str.length()) {
			printError(str);
		} else {
			validationResult = true;
			for (char ch : npm) {
				if (!isdigit(ch)) {
					validationResult = false;
					printError(str);
					break;
				}
			}
		}
	}
	catch(const std::exception& e) {
		printError(str);
	}
	return validationResult;
}
```
1. validasi pertama : mengecek apakah input berjumlah 9 digit
2. validasi kedua : mengecek apakah semua karakter berupa angka
3. mengembalikan nilai `true` apabila lolos semua validasi dan error jika tidak

**validateNilai()**: Mengecek apakah input nilai berupa angka bulat 0 - 100.
```
bool validateNilai(string str) {
	auto printError = [](string var) {
		cerr << "[\x1b[31mERROR\x1b[0m] : Input '" << var << "' tidak valid untuk kolom Nilai" << endl;
	};
	bool validationResult = false;
	unsigned int x;
	size_t idx;

	try {
		x = stoul(str, &idx);
		if (idx != str.length() || x > 100 || x < 0) {
			printError(str);
		} else {
			validationResult = true;
		}
	}
	catch(const std::exception& e) {
		printError(str);
	}
	return validationResult;
}
```
- validasi pertama : cek apakah input berupa angka
- validasi kedua : cek apakan input lebih dari 100 atau kurang dari 0
- mengembalikan nilai `true` apabila lolos semua validasi dan error jika tidak
### Fungsi Pembantu
**shorten()**: mempersingkat karakter string input apabila melebih limit maksimal.
```
string shorten (string str, int maxLen) {
	string nama = str.substr(0, maxLen);
	if (str.length() > maxLen) {
		size_t lastPos = nama.rfind(' ');

		if (lastPos != string::npos) {
			nama = str.substr(0, lastPos + 1);
			nama += str.substr(lastPos + 1).front();
		}
	}
	return nama;
}
```