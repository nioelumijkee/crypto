#include <time.h>


// -------------------------------------------------------------------------- //
// random
static unsigned int  seed512;
static unsigned int  seed512_count;
static unsigned char seed512_key[512];


// random with key 512
// count shift 3
void random512()
{
  seed512 *= 1103515245;
  seed512 += 12345;

  seed512 *= seed512_key[seed512_count]+1;
  seed512_count++;
  seed512_count = seed512_count % 512;

  seed512 += seed512_key[seed512_count];
  seed512_count += 2;
  seed512_count = seed512_count % 512;
}


void random512_set(int i)
{
  seed512 = i;
}


void random512_set_count(int i)
{
  seed512_count = i;
  seed512_count = seed512_count % 512;
}


void random512_set_by_time()
{
  seed512 = time(NULL);
  seed512_count = seed512;
  seed512_count = seed512_count % 512;
}


void random512_set_key(char *c)
{
  int i;
  for (i=0; i<512; i++)
    {
      seed512_key[i] = c[i];
    }
}


unsigned int random512_get()
{
  return(seed512);
}


unsigned int random512_get_count()
{
  return(seed512_count);
}
