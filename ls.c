#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char* fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;
  for(p=path+strlen(path); p >= path && *p != '/'; p--);    // Huruf pertama setelah slash

  p++;
  if(strlen(p) >= DIRSIZ) return p;                         // Return blank-padded name

  memmove(buf, p, strlen(p));                               // Mengcopy karakter dari p ke buf dengan overlapping memory
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));             // fill buf+strlen(p) dengan ' '
  return buf;
}

void ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){                             // Error hanlding Path tidak dapat dibuka dengan fungsi open
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){                                   // Error handling Path tidak dapat return informasi file menggunakan fstat
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:                                                              // Case jika type berupa satu file
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);    // Print informasi file
    break;

  case T_DIR:                                                               // Direktori dengan banyak file
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){                         // Error handling
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);                                      // Copy string path ke buf
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){                           // Error handling
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);   // Print informasi file
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  int i;
  if(argc < 2){
    ls(".");               // Jika argc kurang dari 2, path = '.' lalu keluar
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);           // Masuk fungsi ls dengan path dari argument argv
  exit();
}

