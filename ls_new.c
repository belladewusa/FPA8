#include <syscall.h>
#include <stdio.h>
#include <string.h>

#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>

int pathstat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);		// Open for read only
  if(fd < 0)				
    return -1;
  r = fstat(fd, st);			// berisi informasi file dari fd
  close(fd);
  return r;
}

char*
fmtname(char *path)
{
  static char buf[NAME_MAX+1];
  char *p;
  
  for(p=path+strlen(path); p >= path && *p != '/'; p--)		// Huruf pertama setelah slash
    ;
  p++;
  
 
  if(strlen(p) >= NAME_MAX)					// Return blank-padded name
    return p;
  memmove(buf, p, strlen(p));					// Mengcopy karakter dari p ke buf dengan overlapping memory
  memset(buf+strlen(p), ' ', NAME_MAX-strlen(p));		// fill buf+strlen(p) dengan ' '
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;						// Struct dari readdir
  struct stat st;						// struct dari stat
  
  if((fd = open(path, 0)) < 0){					// Error hanlding Path tidak dapat dibuka dengan fungsi open
    fprintf(stderr, "ls: cannot open %s\n", path);
    return;
  }
  
  if(fstat(fd, &st) < 0){					// Error handling Path tidak dapat return informasi file menggunakan fstat
    fprintf(stderr, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  
  switch(st.type){
  case T_FILE:								// Case jika type berupa satu file
    printf("%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);	// Print informasi file
    break;
  
  case T_DIR:								// Case direktori dengan banyak file di dalamnya
    if(strlen(path) + 1 + NAME_MAX + 1 > sizeof buf){			// Error handling
      fprintf(stderr, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);							// Copy string path ke buf
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){			// Perulangan sebanyak size directory pada readdir
      if(de.d_ino == 0)							// Inode number
        continue;
      memmove(p, de.d_name, NAME_MAX);					// Copy null-terminated filename de ke p dengan overlapping
      p[NAME_MAX] = 0;
      if(pathstat(buf, &st) < 0){					// Error handling saat tidak bisa menampilkan stat dari path di buf
        fprintf(stderr, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);	//print informasi file
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){			// Error handling saat argc kurang dari 2, path diisi dengan "."
    ls(".");
    sysexit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);		// Masuk fungsi ls dengan path dari argument argv
  sysexit();
}
