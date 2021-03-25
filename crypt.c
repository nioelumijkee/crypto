/* 
 * crypto examples
 */

#include <time.h>


// random
#define AF_RANDOM(SEED)         \
    (SEED) = (SEED)*1103515245; \
    (SEED) += 12345;

// -------------------------------------------------------------------------- //
// caesar
// encoder
static char * encoder_caesar(char c, char *str, int len)
{
  int i=0;
  while (i < len)
    {
      str[i] = str[i] + c;
      i++;
    }
  return (str);
}

// decoder
static char * decoder_caesar(char c, char *str, int len)
{    
  int i=0;
  while (i < len)
    {
      str[i] = str[i] - c;
      i++;
    }
  return (str);
}

// -------------------------------------------------------------------------- //
// couple
// gen
void gen_couple(char *key, char *key_inv)
{
  unsigned int seed = time(NULL);
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


