#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// define fungsi2 validasi
bool validateNPM(string str);
bool validateNilai(string str);
string shorten(string str, int maxLen);

// struktur data mahasiswa
struct Student {
	string nama;
	char npm[9];
	unsigned int nilai;
};

int main() {
	// inisialisasi file 'input.csv' ke dalam variabel input
	ifstream input("input.csv");

	// membuat variabel output yang mewakili file output.txt
	ofstream output;
	output.open("output.txt");
	  
	// apabila variabel input kosong
	if(!input) {
		cerr << "[\x1b[31mERROR\x1b[0m] : file 'input.csv' tidak terdeteksi!" << endl;
		exit(1);
	}

	int i = 0, n = 0;
	float total = 0, rata;
	string str;
	
	// deklarasi array dinamis dengan struktur Student
	vector<Student> students;

	// baca setiap baris file 'input.csv'
	while (getline(input, str)) {
		++i;
		vector<string> line;
		stringstream ss(str);
		string value;

		// merubah isi baris menjadi array berdasarkan pemisah ','
		while (getline(ss, value, ',')) {
			line.push_back(value);
		}

		// cek jumlah kolom, format npm, dan format nilai
		if (line.size() == 3 && validateNPM(line[1]) && validateNilai(line[2])) {
			// membuat var 'student' dengan struktur 'Student'
			Student student;
			size_t npmLen = sizeof(student.npm)/sizeof(char);

			// isi nilai var 'student'
			student.nama = shorten(line[0], 26);
			strncpy(student.npm, line[1].c_str(), npmLen);
			student.nilai = stoul(line[2]);
			students.push_back(student);

			// tambah jumlah data 1
			n++;

			// total nilai ditambah dengan data nilai baris baru
			total += student.nilai;
		} else {
			// keluarkan error invalid
			cerr << "[\x1b[33mWARNING\x1b[0m] : input invalid di baris " << i << " pada file 'input.csv'. Baris dilewati..." << endl;
		}
	}
	// menutup file input setelah semua baris selesai dibaca
	input.close();

	// mencetak judul dan header tabel
	output << setw(60) << left << "                       LAPORAN NILAI" << endl;
	output << setw(60) << left << "                  MAHASISWA ILMU KOMPUTER" << endl;
	output << setw(60) << left << "                        KELAS A & B" << endl;
	output << "------------------------------------------------------------" << endl;
	output << "|" << setw(6) << left << "  No";
	output << "|" << setw(28) << left << "       Nama Mahasiswa";
	output << "|" << setw(11) << left << "    NPM";
	output << "|" << setw(10) << left << "   Nilai";
	output << "|" << endl;
	output << "------------------------------------------------------------" << endl;
	
	// mencetak data mahasiswa satu per satu
	for (size_t i = 0; i < students.size(); i++) {
		output << "|" << setw(6) << left << "  " + to_string(i + 1);
		output << "| " << setw(27) << left << shorten(students[i].nama, 26);
		output << "| " << setw(10) << left << students[i].npm; 
		output << "|    " << setw(6) << left << students[i].nilai;
		output << "|" << endl; 
	}
	
	output << "------------------------------------------------------------" << endl;

	// menghitung dan menampilkan nilai rata-rata
	rata = total / n;
	output << "| " << setw(34) << left << "Jumlah Data : " + to_string(n);
	output << "|" << setw(11) << right << "Rata-rata " << setprecision(3);
	output << "|    " << setw(6) << left << rata;
	output << "|" << endl;

	output << "------------------------------------------------------------" << endl;

	// masukkan nilai tertinggi dari data mahasiswa ke dalam variabel max
	auto max = *max_element(students.begin(), students.end(), [](const Student& a, Student& b){return a.nilai < b.nilai;});
	// masukan nilai terendah dari data mahasiswa ke dalam variabel min
	auto min = *min_element(students.begin(), students.end(), [](const Student& a, Student& b){return a.nilai < b.nilai;});

	// mencetak nilai tertinggi
	output << "| " << setw(16) << left << "Nilai Tertinggi";
	output << setw(3) << left << " : ";
	output << setw(27) << left << "(" + shorten(max.nama, 20) + ")";
	output << "|    " << setw(6) << left << max.nilai;
	output << "|" << endl;
	
	// mencetak nilai terendah
	output << "| " << setw(16) << left << "Nilai Terendah";
	output << setw(3) << left << " : ";
	output << setw(27) << left << "(" + shorten(min.nama, 20) + ")";
	output << "|    " << setw(6) << left << min.nilai;
	output << "|" << endl;

	output << "------------------------------------------------------------" << endl;

	// menutup file output setelah selesai dipakai
	output.close();
	
	return 0;
}

/*
	FUNGSI-FUNGSI UNTUK VALIDASI INPUT dari file input.csv
*/

// validasi NPM
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

// validasi nilai
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

// Menyingkatkan nama 
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