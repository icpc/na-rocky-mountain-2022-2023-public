#include<stdio.h>
int main() {
  int r,f;
  scanf("%d%d",&r,&f);
  puts((f+r/2)/r&1?"down":"up");
}
