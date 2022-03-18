#include "courseRegistration.h"
#include <stdlib.h>
int main()
{
    listCourse LC;
    listStudent LS;
    adrCourse C;
    adrStudent S;
    int i, n;

    createList_Course(LC);
    createList_Student(LS);

    int opsi = 0;
    string kembali = "Y";

    opsi = selectMenu();
    cout<<endl;
    while(opsi != 0 && kembali == "Y"){
        switch(opsi){
        case 1:
            n = 0;
            cout << "Banyak data mata kuliah yang ingin ditambahkan : ";
            cin >> n;

            i = 1;
            infotypeCourse newCourse;
            while(i<= n){
                cout <<"Data ke-"<<i<<" : "<<endl;
                cout<< "Nama mata kuliah: ";
                cin >> newCourse.courseName;
                cout<< "Nama kelas      : ";
                cin>> newCourse.className;
                cout<< "Kuota maksimal  : ";
                cin>> newCourse.quota;
                newCourse.Count = 0; //jumlah di set 0
                cout<< "Jenis mahasiswa : ";
                cin>> newCourse.studentType;

                C = newElm_Course(newCourse);
                addCourse(LC, C);
                cout<<endl;
                i++;
            }
            break;

        case 2:
            string course;
            string type;
            cout << "Masukkan data mata kuliah yang ingin dihapus: ";
            cout << "Nama : ";
            cin >> course;
            cout << "Kelas: ";
            cin >> type;

            C = first(LC);
            while(C != NULL && info(C).courseName == course &&info(C).studentType == type){
                C = next(C);
            }
            deleteCourse(LC, C);
            cout << "List data mata kuliah setelah penghapusan : "<<endl;
            showCourses(LC);
            break;

        case 3:
            cout << "----Input Data Diri Mahasiswa----";

            infotypeStudent newStudent;
            cout <<"Data ke-"<<i<<" : "<<endl;
            cout<< "Nama : ";
            cin >> newStudent.studentName;
            cout<< "NIM  : ";
            cin>> newStudent.studentID;
            cout<< "Asal Kelas      : ";
            cin>> newStudent.classOrigin;
            cout<< "Jenis mahasiswa : ";
            cin>> newStudent.studentType;
            S = newElm_Student(newStudent);
            cout<<endl;

            n = 0;
            cout<< "Banyak mata kuliah yang ingin didaftarkan: ";
            cin>> n;
            if(n > 3){
                cout<<"Maaf, batas maksimal registrasi hanya 3 mata kuliah."<<endl;
                cout<<"Masukkan kembali banyak mata kuliah: ";
                cin >> n;
            }

            i = 1;
            while(i <= n){
                cout << "Nama mata kuliah ke-"<< i <<": ";
                cin >> course;
                setClass(LC,LS, S, course);
                i++;
            }
            cout<<endl;
            break;

        case 4:
            string nama;
            string MK;
            cout<< "Masukkan nama mahasiswa yang ingin dihapus: ";
            cin>> nama;
            cout<< "Masukkan mata kuliah yang ingin dihapus: ";
            cin>> MK;

            //mencari letak address yang sesuai dengan nama mahasiswa
            deleteClass(LC, LS, nama, MK);
            break;

        case 5:
            updateCount(LC, LS);
            cout<<"Status: berhasil mengupdate jumlah mahasiswa."<<endl;
            break;

        case 6:
            cout<<"LIST DATA MATA KULIAH"<<endl;
            cout<<endl;
            showCourses(LC);
            break;

        case 7:
            cout<<"Nama mata kuliah : ";
            cin >> MK;

            string kelas;
            cout<<"Kelas : ";
            cin >> kelas;

            showStudentInCourse(LC, LS, MK, kelas);
            cout<<endl;
            break;

        case 8:
            showAllData(LC, LS);
            break;

        case 9:
            cout<< "Masukkan nama mata kuliah yang dicari: ";
            cin >> MK;

            string tipe;
            cout<< "Masukkan tipe yang dicari (reguler/internasional): ";
            cin >> tipe;

            C = searchCourseByQuota(LC, MK, tipe);
            if (C == NULL){
                cout<<"Tidak ditemukan mata kuliah dan tipe yang sesuai dengan kuota tersedia :("<<endl;
            }else{
                cout<<"Berikut data mata kuliah yang sesuai.";
                cout<<"Mata Kuliah : "<<info(C).courseName<<endl;
                cout<<"Kelas       : "<<info(C).className <<endl;
                cout<<"Kuota Max.  : "<<info(C).quota <<endl;
                cout<<"Jumlah Mahasiswa : "<<info(C).Count<< endl;
                cout<<"Jenis Mahasiswa  : "<<info(C).studentType <<endl;
                cout<<endl;
            }
            break;

        case 10:
            cout<< "Masukkan nama mahasiswa yang dicari: ";
            cin >> nama;

            cout<< "Masukkan mata kuliah yang dicari : ";
            cin >> MK;

            searchStudentInCourse(LC, LS, nama, MK, S, C);
            if (S == NULL){
                cout<<"Tidak ditemukan nama mahasiswa tersebut pada mata kuliah yang dicari :("<<endl;
            }else{
                cout<<"Berikut data mata kuliah yang sesuai.";
                cout<<"Nama : "<<info(S).studentName<<endl;
                cout<<"NIM       : "<<info(S).studentID <<endl;
                cout<<"Kelas Asal : "<<info(S).classOrigin <<endl;
                cout<<"Jenis Mahasiswa  : "<<info(S).studentType <<endl;
                cout<<endl;
            }
            break;

        case 11:
            string jawaban;
            cout<<"Apakah anda yakin untuk memfinalisasi registrasi? (ya/tidak): ";
            cin>> jawaban;

            if(jawaban == "ya"){
                C = first(LC);
                while(C != NULL){
                    if(info(C).Count == 0){
                        deleteCourse(LC,C);
                    }
                    C = next(C);
                }
            }else if(jawaban != "ya" || jawaban != "tidak"){
                cout << "Input salah, masukkan kembali jawaban: "<<endl;
                cin>>jawaban;
            }
            break;
        }

        cout << "Kembali ke menu utama? (Y/N): ";
        cin >> kembali;
        if (kembali == "N"){
            break;
        }else if (kembali != "Y" && kembali != "N"){
            cout<<"INPUT TIDAK VALID, kembali ke menu utama? (Y/N): ";
            cin >> kembali;
        }
        system("CLS");

        opsi = selectMenu();
        cout<<endl;
    }
    cout<< "ANDA TELAH KELUAR DARI PROGRAM"<<endl;
    return 0;
}
