#include "courseRegistration.h"

//membuat list parent dan child
void createList_Course(listCourse &LC){
    first(LC) = NULL;
};
void createList_Student(listStudent &LS){
    first(LS) = NULL;
};
//membuat elemen parent dan child baru
adrCourse newElm_Course(infotypeCourse newCourse){
    adrCourse C = new elmCourse;
    info(C) = newCourse;
    next(C) = NULL;
    prev(C) = NULL;
    nextStudent(C) = NULL;
    return C;
};
adrStudent newElm_Student(infotypeStudent newStudent){
    adrStudent S = new elmStudent;
    info(S) = newStudent;
    next(S) = NULL;
    prev(S) = NULL;
    return S;
};
//procedure menambah mata kuliah
void addCourse(listCourse &LC, adrCourse &C){

    if(first(LC) == NULL){//insert first
        first(LC) = C;
    }else{//insert last
        adrCourse P = first(LC);
        while(next(P) != NULL){//P diset menunjuk elemen terakhir di list
            P = next(P);
        }
        prev(C) = P;
        next(P) = C;
    }
};

//procedure menghapus mata kuliah
void deleteCourse(listCourse &LC, adrCourse &C){

    //menghapus data mata kuliah berdasarkan letak
    if(C = first(LC)){//jika letak address mata kuliah di awal
        first(LC) = next(C);
        next(C) = NULL;
        prev(first(LC)) = NULL;
    }else{
        adrCourse found = NULL; //mencari letak address mata kuliah selain di awal
        adrCourse P = first(LC);
        while(P != NULL && found == NULL){
            if(P == C){
                found = P;
            }
            P = next(P);
        }
        if(found != NULL){
            if(next(found) == NULL){//jika letak mata kuliah ada di akhir, menggunakan delete last
                next(prev(found)) = NULL;
                prev(found) = NULL;
            }else{//jika letak mata kuliah berada di tengah, menggunakan delete before
                adrCourse prec = prev(found);
                next(prec) = next(found);
                prev(next(found)) = prec;
                prev(found) = NULL;
                next(found) = NULL;
            }
        }else{
            cout << "Data mata kuliah tidak ditemukan"<<endl;
        }
    }
};

//procedure menambah mahasiswa
void addStudent(listCourse &LC, listStudent &LS, adrCourse C, adrStudent S){

    if(nextStudent(C) == NULL){//insert first
        nextStudent(C) = S;
    }else{//insert last
        adrStudent P = nextStudent(C);
        while(next(P) != NULL){//P diset menunjuk elemen terakhir di list
            P = next(P);
        }
        prev(S) = P;
        next(P) = S;
    }
};

//procedure menghapus mahasiswa
void deleteStudent(listCourse &LC, adrCourse C, adrStudent &S){
    //mencari address course
    if(S == nextStudent(C)){//delete first
        nextStudent(C) = next(S);
        next(S) = NULL;
        prev(nextStudent(C)) = NULL;
    }else if(next(S) == NULL){//delete last
        next(prev(S)) = NULL;
        prev(S) = NULL;
    }else{//delete after
        adrStudent prec = prev(S);
        next(prec) = next(S);
        prev(next(S)) = prec;
        prev(S) = NULL;
        next(S) = NULL;
    }
};

//procedure menghubungkan relasi mata kuliah dan mahasiswa
void setClass(listCourse &LC, listStudent &LS, adrStudent S, string courseName){
    adrCourse C = searchCourseByQuota(LC, courseName, info(S).studentType);

    //menyambungkan relasi
    if(C != NULL){
        addStudent(LC, LS, C, S);
    }else{
        cout << "Tidak ditemukan mata kuliah dengan kuota tersedia :("<<endl;
    }
};

//procedure menghapus hubungan relasi mata kuliah dan mahasiswa
void deleteClass(listCourse &LC, listStudent &LS, string studentName, string courseName){
    adrStudent S;
    adrCourse C;
    searchStudentInCourse(LC, LS, studentName, courseName, S, C);

    //menghapus relasi
    deleteStudent(LC, C, S);
};

//procedure update jumlah mahasiswa di setiap mata kuliah
void updateCount(listCourse LC, listStudent LS){
    int n = 0;
    adrCourse C = first(LC);

    while(C != NULL){
        adrStudent S = nextStudent(C);
        while(S != NULL){
            n++;
            S = next(S);
        }
        info(C).Count = n;
        C = next(C);
    }
};
//procedure menampilkan data semua mata kuliah beserta jumlah mahasiswa
void showCourses(listCourse LC){
    adrCourse C = first(LC);
    int i = 1;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    cout<< "| No \t | Mata kuliah \t\t | Kelas \t | Kuota | Jumlah Mahasiswa \t | Jenis Mahasiswa" <<endl;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    while(C != NULL){
        cout<< "|"<<i<<"\t | "<<info(C).courseName <<"\t | "<<info(C).className<< "\t | "<< info(C).quota<<"\t | "<<info(C).Count<<"\t\t\t | "<<info(C).studentType <<endl;
        i++;
        C = next(C);
    }
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
};
//procedure menampilkan data mahasiswa di MK dan kelas tertentu
void showStudentInCourse(listCourse LC, listStudent LS, string course, string Class){
    //mencari letak address course dan Class
    adrCourse C = first(LC);
    while(C != NULL && info(C).courseName == course && info(C).className == Class){
        C = next(C);
    }

    //menampilkan data mahasiswa
    adrStudent S = nextStudent(C);
    int i = 1;
    while(S != NULL){
        cout<< "Data Mahasiswa Mata Kuliah "<<course<<" Kelas "<<Class<<endl;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<< "No \t Nama \t NIM \t Kelas Asal \t Jenis Mahasiswa"<<endl;
        cout<< i << "\t" <<info(S).studentName<<"\t"<<info(S).studentID<<"\t"<<info(S).classOrigin<<"\t"<<info(S).studentType<<endl;
        i++;
        S = next(S);
    }
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
};
//procedure menampilkan semua data mata kuliah beserta mahasiswanya
void showAllData(listCourse LC, listStudent LS){
    adrCourse C = first(LC);
    int i = 1;

    cout << "[DATA REGISTRASI MATA KULIAH]"<<endl;
    while(C != NULL){
        cout << "-----MATA KULIAH "<< i <<"-----"<<endl;
        cout << "Mata Kuliah : "<< info(C).courseName<<endl;
        cout << "Kelas       : "<< info(C).className<<endl;
        cout << "Kuota Maksimal  : "<< info(C).quota<<endl;
        cout << "Jumlah Mahasiswa: "<< info(C).Count<<endl;
        cout << "Jenis Mahasiswa : "<< info(C).studentType<<endl;
        cout << "Data Mahasiswa  : "<<endl;
        adrStudent S = nextStudent(C);
        int j = 1;
        while(S != NULL){
            cout<<"---------------------------------------------------------------------------------------------"<<endl;
            cout<< "No \t Nama \t NIM \t Kelas Asal \t Jenis Mahasiswa"<<endl;
            cout<<"---------------------------------------------------------------------------------------------"<<endl;
            cout<< j << "\t" <<info(S).studentName<<"\t"<<info(S).studentID<<"\t"<<info(S).classOrigin<<"\t"<<info(S).studentType<<endl;
            j++;
            S = next(S);
        }
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        C = next(C);
    }
};
//Mencari nama mk tertentu dengan kuota masih tersedia
adrCourse searchCourseByQuota(listCourse LC, string course, string type){
    adrCourse C = first(LC);
    while(C != NULL){
        if(info(C).courseName == course && info(C).Count < info(C).quota && info(C).studentType == type){
            return C;
        }
        C = next(C);
    }
    return NULL;
};

//Mencari nama mahasiswa tertentu pada sebuah MK
void searchStudentInCourse(listCourse LC, listStudent LS, string name, string course, adrStudent &S, adrCourse &C){
    C = first(LC);
    while(C != NULL){
        if(info(C).courseName == course){
            adrStudent S = nextStudent(C);
            while(S != NULL){
                if(info(S).studentName == name){
                    break;
                }
                S = next(S);
            }
        }
        C = next(C);
    }
};

int selectMenu(){
    cout<<"___________________________ MENU ______________________________________________"<<endl;
    cout<<"1. Menambahkan data mata kuliah baru"<<endl;
    cout<<"2. Menghapus mata kuliah"<<endl;
    cout<<"3. Mendaftar registrasi mata kuliah"<<endl;
    cout<<"4. Menghapus registrasi mata kuliah"<<endl;
    cout<<"5. Mengupdate jumlah mahasiswa di setiap mata kuliah" <<endl;
    cout<<"6. Menampilkan semua data mata kuliah yang ditawarkan beserta jumlah mahasiswa"<<endl;
    cout<<"7. Menampilkan data mahasiswa di mata kuliah dan kelas tertentu"<<endl;
    cout<<"8. Menampilkan seluruh mata kuliah beserta data mahasiswanya"<<endl;
    cout<<"9. Mencari nama mata kuliah tertentu dengan kuota masih tersedia"<<endl;
    cout<<"10. Mencari nama mahasiswa tertentu pada sebuah mata kuliah"<<endl;
    cout<<"11. Finalisasi registrasi"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Masukkan menu : ";

    int input = 0;
    cin>> input;

    return input;
};
