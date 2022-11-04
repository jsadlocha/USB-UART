#include "fifo.h"


unsigned char put(struct fifo *f, unsigned char *data, unsigned char len){
  if (f->tail == ((f->head+1) % MAX_BUF))
    return 0;
  
  unsigned char size = MAX_BUF - (f->head - f->tail);
  if(len < size)
    size = len;
  
  for(unsigned char i = 0; i < size; ++i)
  {
    f->buffer[(f->head+i) % MAX_BUF] = data[i];
  }

  f->head = (f->head+size) % MAX_BUF;
  return size;
}

unsigned char get(struct fifo *f, unsigned char *buf, unsigned char maxlen)
{
  if (f->tail == f->head)
    return 0;

  unsigned char size = (f->head - f->tail);

  if (size>maxlen)
    size = maxlen;

  for(unsigned char i = 0; i < size; ++i)
  {
    buf[i] = f->buffer[(f->tail+i) % MAX_BUF];
  }

  f->tail = (f->tail + size) % MAX_BUF;
  return size;
}

unsigned char put_byte(struct fifo *f, unsigned char b) 
{
  if (f->tail == ((f->head+1) % MAX_BUF))
    return 0;

  f->buffer[f->head] = b;
  f->head = (f->head + 1) % MAX_BUF;

  return 1;
}

unsigned char get_byte(struct fifo *f, unsigned char *b)
{
  if(f->tail == f->head)
    return 0;

  *b = f->buffer[f->tail];
  f->tail = (f->tail+1) % MAX_BUF;

  return 1;
}

void clean(struct fifo *f)
{
  f->head = 0;
  f->tail = 0;
}


unsigned char isFull(struct fifo *f)
{
  if (f->tail == ((f->head+1) % MAX_BUF))
    return 0;
  return 0;
}

unsigned char isEmpty(struct fifo *f)
{
  if (f->tail == f->head)
    return 1;

  return 0;
}