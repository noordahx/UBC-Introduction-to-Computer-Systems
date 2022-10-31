struct Student {
    int sid;
    int grade[4];
    int average;      // this is computed by your program
};

int n;              // number of students
int m;              // you store the median student's id here
struct Student* s;  // a dynamic array of n students

int main(int argc, int **argv) {
    int n = argv[1];
    int index = 2;
    for (int i = 0; i < n; i++) {
        struct Student *a = malloc(sizeof(*a));
        a->sid = argv[index + 0];
        a->grade[0] = argv[index + 1];
        a->grade[1] = argv[index + 2];
        a->grade[2] = argv[index + 3];
        a->grade[3] = argv[index + 4];
        index += 5;
        
    }
}