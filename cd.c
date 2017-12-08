
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  //validasi input
  if(argc<2)
  {
    printf(1,"need 2 arguments\n"); //karena argumen kurang dari 2 maka tdk bisa dijalankan
    exit();
  }  
  
  if(chdir(argv[1])<0) //menjalankan cd
  {
    printf(1,"Failed to change directory\n"); //jika return negatif maka fail
  }
  
  exit();
}


