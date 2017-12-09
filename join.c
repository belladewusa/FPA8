#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int length(char *input){
    int length = 0;
    while(input[length]!='\0')
    {
        length++;                               // menunjukkan berapa banyak character dalam input
    }
    return length;
}

int main(int argc, char *argv[]){
	int fiel1, file2;
	int a, b;
	char buf1[256], buf2[256], fill[512];
	int counter1 = 0, counter2 = 0, counter = 0, counters1 = 0, counters2 = 0, cs1 = 0, cs2 =0;

	if((file1 = open(argv[1], O_RDONLY)) < 0){                      // Error handling : cannot read file 1
		printf(1, "Failed to read files %s\n", argv[1]);
		exit();
	}
	if((file2 = open(argv[2], O_RDONLY)) < 0){                      // Error handling : cannot read file 2
		printf(1, "failed to read %s\n", argv[2]);
		exit();
	}

	a = read(file1, buf1, sizeof(buf1));                        // read n character from file1 and places it to  buf1
	b = read(file2, buf2, sizeof(buf2));                        // read n character from file2 and places it to  buf2
	int p1, p2;
	p1 = length(buf1);                                          // Masuk fungsi lenght dengan inout buf1
	p2 = length(buf2);                                          // Masuk fungsi lenght dengan input buf2


	close(file1);
	close(file2);
	printf(1, "%s", fill);
	exit();
}
