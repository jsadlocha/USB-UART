#ifndef __FIFO_H_
#define __FIFO_H_
#define MAX_BUF 254

struct fifo 
{
  unsigned char buffer[256];
  unsigned char head;
  unsigned char tail;
} hostDeviceFifo, deviceHostFifo;

/*
params struct, data in/data out, length
return how much bytes read/write
*/
unsigned char put(struct fifo *f, unsigned char *data, unsigned char len);
unsigned char get(struct fifo *f, unsigned char *buf, unsigned char maxlen);
unsigned char put_byte(struct fifo *f, unsigned char b);
unsigned char get_byte(struct fifo *f, unsigned char *b);
unsigned char isFull(struct fifo *f);
unsigned char isEmpty(struct fifo *f);
void clean(struct fifo *f);

#endif