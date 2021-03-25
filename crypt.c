/* 
 * crypto examples
 */

#include <time.h>


#define AF_RANDOM(SEED)         \
  (SEED) = (SEED)*1103515245;	\
  (SEED) += 12345;

#define AF_SWAP(X,Y,B)				\
  (B) = (X);					\
  (X) = (Y);					\
  (Y) = (B);


static unsigned int seed;


// -------------------------------------------------------------------------- //
// init random seed
void random_init()
{
  seed = time(NULL);
}

// set random seed
void random_set(unsigned int i)
{
  seed = i;
}

// -------------------------------------------------------------------------- //
// caesar
// encoder
static char * encoder_caesar(char a, char *str, int len)
{
  int i=0;
  while (i < len)
    {
      str[i] = str[i] + a;
      i++;
    }
  return (str);
}

// decoder
static char * decoder_caesar(char a, char *str, int len)
{    
  int i=0;
  while (i < len)
    {
      str[i] = str[i] - a;
      i++;
    }
  return (str);
}

// -------------------------------------------------------------------------- //
// affine
// encoder
static char * encoder_affine(char a, char b, char *str, int len)
{
  int i=0;
  while (i < len)
    {
      str[i] = str[i] + (i*a) + b;
      i++;
    }
  return (str);
}

// decoder
static char * decoder_affine(char a, char b, char *str, int len)
{    
  int i=0;
  while (i < len)
    {
      str[i] = str[i] - (i*a) - b;
      i++;
    }
  return (str);
}

// -------------------------------------------------------------------------- //
// swap
// encoder
static char * encoder_swap(unsigned int a, 
			   unsigned int b,
			   unsigned int step,
			   char *str, 
			   unsigned int len)
{
  unsigned int j,k;
  unsigned int i=0;
  char buf;
  while (i < step)
    {
      j = ((i*a)+b) % len;
      k = i % len;
      AF_SWAP(str[k], str[j], buf);
      i++;
    }
  return (str);
}

// decoder
static char * decoder_swap(unsigned int a, 
			   unsigned int b,
			   unsigned int step,
			   char *str, 
			   unsigned int len)
{    
  unsigned int j,k;
  int i=step-1;
  char buf;
  while (i >= 0)
    {
      j = ((i*a)+b) % len;
      k = i % len;
      AF_SWAP(str[k], str[j], buf);
      i--;
    }
  return (str);
}

// -------------------------------------------------------------------------- //
// couple
// gen
void gen_couple(char *key, char *key_inv)
{
  int i,j,k;
  int find;
  i=0;
  while (i < 256)
    {
      AF_RANDOM(seed);
      j = seed % 256;
      find = 0;
      for (k=0; k<i; k++)
	{
	  if (key[k] == j)
	    {
	      find = 1;
	      k=i;
	    }
	}
      if (find == 0)
	{
	  key[i] = j;
	  key_inv[j] = i;
	  i++;
	}
    }
}

// encoder
static char * encoder_couple(char *key, char *str, int len)
{
  int i;
  for(i=0; i<len; i++)
    {
      str[i] = key[(int)(unsigned char)str[i]];
    }
  return (str);
}

// decoder
static char * decoder_couple(char *key_inv, char *str, int len)
{    
  int i;
  for(i=0; i<len; i++)
    {
      str[i] = key_inv[(int)(unsigned char)str[i]];
    }
  return (str);
}


