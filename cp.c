#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char buf[512];

void
cat(int fd1, int fd2)
{
  int n;
  while((n = read(fd1, buf, sizeof(buf))) > 0) { //Menyalin isi file 1 dan menyimpan buf
    printf(fd2, "%s", buf); //Mencetak isi file 1 di file salinan
  }
  if(n < 0){ // Jika n<0 gagal
    printf(1, "copy: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd1;
  if(argc < 3){ // Kontroling input
    printf(1, "copy: read error\n");
    exit();
  }
  if((fd1 = open(argv[1], 0)) < 0){ // Membuka file yang akan di copy
    printf(1, "copy: cannot open %s\n", argv[1]);
    exit();
  }
  int fd2;
  
  if ((fd2 = open(argv[2], O_CREATE | O_RDWR)) < 0) { // Membuat file baru dengan nama yang sudah inputkan argv[2]
    printf(1, "copy: error initializing file: %s\n", argv[2]);
    exit();
  }
  cat(fd1,fd2); // Melakukan fungsi cat ( fungsi mensalin isi file )
  close(fd1);
  close(fd2);
  exit();
}
