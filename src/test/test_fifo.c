#include "fifo.h"

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void putAndGetStringFromFifo()
{
  struct fifo f;
  char c[] = "testadfsafds\n";
  unsigned char size = sizeof(c);
  char b[size];
  clean(&f);

  put(&f, c, size);
  get(&f, b, size);
  assert(strncmp(c, b, size) == 0);
}

void putAndGetMoreThanCan()
{
  struct fifo f;
  clean(&f);
  char c[] = "tessaddfasdfasdfasdfsadfsdfsdafsdagfdgfdsgsdfgdsgfdsgfdsgsdfgsdfgdgfdsgdsfgsdfgshirfgoifdsgjsdfklgndfsjngjkdsfngkjfndsjgndsfkgndsfjkgnsdfkjgndsjkgnjdsfgnkdfngjdfngkjsdfngkjsfdngjksdfngjksdfngjsdnflgnsdkfjgndsfkgnsfdkljgnsdfjkngsjdkfgnskdfljjgnsdfjklgnsdklfjgndskjfgnsdlkfgnsdfkjgndsfkjgnsdfkjgnsdfkgnfsdkljgnsdkjfgnsdfklgjnsdfgst\n";
  unsigned char size = (sizeof(c) % 255);
  char b[size];
  
  put(&f, c, size);
  get(&f, b, size);
  assert(strncmp(c, b, size) == 0);
}

void addCoupleOfBytes()
{
  struct fifo f;
  clean(&f);

  char a[] = "asdfgrsgre34\n";
  char b[sizeof(a)];

  for (int i = 0; i < sizeof(a); ++i)
  {
    put_byte(&f, a[i]);
  }

  for (int i = 0; i < sizeof(a); ++i)
  {
    get_byte(&f, &b[i]);
  }
  
  assert(strncmp(a, b, sizeof(a)) == 0);
}

void putGetRepeatMoreThanBuffsize()
{
  struct fifo f;
  clean(&f);

  char test[] = "testdupatestdupa\n";
  char test2[] = "testdupatestdupa\n";
  unsigned char size = sizeof(test);
  char buf[size];
  char res[size];

  for (int i = 0; i < 28; ++i)
  {
    put(&f, test, size);
    get(&f, buf, size);
    put(&f, buf, size);
    get(&f, test, size);
  }
  put(&f, test, size);
  get(&f, res, size);

  assert(strncmp(test2, res, size) == 0);
}

int main() {
  putAndGetStringFromFifo();
  putAndGetMoreThanCan();
  addCoupleOfBytes();
  putGetRepeatMoreThanBuffsize();
  printf("All pass test!\n");
  return 0;
}