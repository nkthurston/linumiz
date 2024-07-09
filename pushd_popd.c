#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

#define MAX_DIR 100
#define MAX_DIR_LEN 1024

char *dirs[MAX_DIR];
int top=-1;

void pushd(char *dir){
  if(top>=MAX_DIR-1){
    fprintf(stderr,"Directory stack overflow\n");
    return;
  }
  dirs[++top]=strdup(dir);
  chdir(dir);
}

char *popd()
{
  if(top<0){
    fprintf(stderr,"Directory stack underflow\n");
    return NULL;
  }
  char *dir= dirs[top--];
  chdir(getenv("HOME"));
  return dir;
}

int main(int argc,char *argv[])
{
  if(argc!=2){
    fprintf(stderr,"Usage: %s <pushd|popd> <directory>\n",argv[0]);
    return 1;
  }
  if(strcmp(argv[1],"pushd")==0){
    if(argc!=3){
      fprintf(stderr,"Usage: %s <pushd> <directory>\n",argv[0]);
      return 1;
    }
    pushd(argv[2]);
  }
  else if(strcmp(argv[1],"popd")==0){
    if(argc!=2){
      fprintf(stderr,"Usage: %s <popd>\n",argv[0]);
      return 1;
    }
    popd();
  }
  else{
    fprintf(stderr,"Unknown command : %s\n",argv[1]);
    return 1;
  }
  return 0;
}

  
  
