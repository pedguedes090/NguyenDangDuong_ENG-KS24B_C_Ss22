#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[100];
int num_students = 0;

void loadStudents() {
    FILE *file = fopen("students.dat", "rb");
    if (file != NULL) {
        fread(&num_students, sizeof(int), 1, file);
        fread(students, sizeof(Student), num_students, file);
        fclose(file);
    }
}

void saveStudents() {
    FILE *file = fopen("students.dat", "wb");
    fwrite(&num_students, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), num_students, file);
    fclose(file);
}

void printStudents() {
    for (int i = 0; i < num_students; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (num_students < 100) {
        printf("Nhap student ID: ");
        scanf("%d", &students[num_students].id);
        printf("Nhap student name: ");
        scanf("%s", students[num_students].name);
        printf("Nhap student age: ");
        scanf("%d", &students[num_students].age);
        num_students++;
        saveStudents();
    } else {
        printf("Danh sach sinh vien day.\n");
    }
}

void updateStudent() {
    int id;
    printf("Nhap student ID de cap nhat: ");
    scanf("%d", &id);
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            scanf("%s", students[i].name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            saveStudents();
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}

void deleteStudent() {
    int id;
    printf("Nhap student ID de xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            for (int j = i; j < num_students - 1; j++) {
                students[j] = students[j + 1];
            }
            num_students--;
            saveStudents();
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}

void searchStudent() {
    int id;
    printf("Nhap student ID de tim: ");
    scanf("%d", &id);
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}

void sortStudents() {
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = i + 1; j < num_students; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents();
}

int main() {
    loadStudents();
    int choice;
    do {
        printf("MENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Goodbye!\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 7);
    
    return 0;
}

