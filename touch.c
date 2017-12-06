#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
	int f;
	if(argc != 2){
	printf(2, "need 2 arguments\n");
	} //jika tidak terdapat 2 argumen, maka akan muncul perintah untuk membuat 2 argumen
	if((f = open(argv[1], O_CREATE | O_RDWR)) < 0){
		printf(1, "touch: %s failed to create\n", argv[1]);
	} //jika terdapat 2 argumen, maka ketika return value negatif berarti terdapat eror. 
	close(f); //jika return value positif
	exit();
}
