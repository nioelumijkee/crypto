#include <time.h>


// -------------------------------------------------------------------------- //
#define AF_RANDOM(SEED)         \
  (SEED) = (SEED)*1103515245;	\
  (SEED) += 12345;

#define AF_SWAP(X,Y,B)				\
  (B) = (X);					\
  (X) = (Y);					\
  (Y) = (B);


static unsigned int seed;

// -------------------------------------------------------------------------- //
// random
void random_init()
{
  seed = time(NULL);
}

void random_set(int i)
{
  seed = i;
}

// -------------------------------------------------------------------------- //
// caesar
void encoder_caesar(char *data, int a, int len)
{
  int i=0;
  while (i < len)
    {
      data[i] = data[i] + a;
      i++;
    }
}

void decoder_caesar(char *data, int a, int len)
{    
  int i=0;
  while (i < len)
    {
      data[i] = data[i] - a;
      i++;
    }
}

// -------------------------------------------------------------------------- //
// affine
void encoder_affine(char *data, int a, int b, int len)
{
  int i=0;
  while (i < len)
    {
      data[i] = data[i] + (i*a) + b;
      i++;
    }
}

void decoder_affine(char *data, int a, int b, int len)
{
  int i=0;
  while (i < len)
    {
      data[i] = data[i] - (i*a) - b;
      i++;
    }
}

// -------------------------------------------------------------------------- //
// couple
void gen_couple(char *key,     // 256 
		char *key_inv) // 256
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

void deencoder_couple(char *data, 
		      char *key, // 256 
		      int len)
{
  int i;
  for(i=0; i<len; i++)
    {
      data[i] = key[(int)(unsigned char)data[i]];
    }
}

// -------------------------------------------------------------------------- //
// swap
void encoder_swap(char *data,
		  int a, // only positive
		  int b,
		  int step,
		  int len)
{
  int i,j;
  char buf;
  i = 0;
  while (i < step)
    {
      j = (unsigned int)((i*a)+b);
      j = j % len;
      AF_SWAP(data[i], data[j], buf);
      i++;
    }
}

void decoder_swap(char *data,
		  int a, // only positive
		  int b,
		  int step,
		  int len)
{
  int i,j;
  char buf;
  i = step-1;
  while (i >= 0)
    {
      j = (unsigned int)((i*a)+b);
      j = j % len;
      AF_SWAP(data[i], data[j], buf);
      i--;
    }
}

// -------------------------------------------------------------------------- //
// bits
void gen_bits(char *key, int len)
{
  int i;
  for (i=0; i<len; i++)
    {
      AF_RANDOM(seed);
      key[i] = seed;
    }
}

void encoder_bits(char *data,
		  char *key,
		  int len_data,
		  int len_key)
{
  int i,j;
  unsigned char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=0; i<len_data; i++)
    {
      j = i % len_key;
      k = (unsigned char)key[j] % 8;
      buf = data[i];
      if (k == 0)
	{
	  buf = ~buf;
	}
      else
	{
	  res_hi = buf >> k;
	  res_lo = buf << (8 - k);
	  buf = res_hi | res_lo;
	}
      data[i] = buf;
    }
}


void decoder_bits(char *data,
		  char *key,
		  int len_data,
		  int len_key)
{
  int i,j;
  unsigned char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=0; i<len_data; i++)
    {
      j = i % len_key;
      k = (unsigned char)key[j] % 8;
      buf = data[i];
      if (k == 0)
	{
	  buf = ~buf;
	}
      else
	{
	  res_hi = buf << k;
	  res_lo = buf >> (8 - k);
	  buf = res_hi | res_lo;
	}
      data[i] = buf;
    }
}

/* // -------------------------------------------------------------------------- // */
/* // polybius */
/* // gen key */
/* void gen_key_polybius(char *key, char *key_inv) */
/* { */
/*   int i,j,k; */
/*   int find; */
/*   i=0; */
/*   while (i < 256) */
/*     { */
/*       AF_RANDOM(seed); */
/*       j = seed % 256; */
/*       find = 0; */
/*       for (k=0; k<i; k++) */
/* 	{ */
/* 	  if (key[k] == j) */
/* 	    { */
/* 	      find = 1; */
/* 	      k=i; */
/* 	    } */
/* 	} */
/*       if (find == 0) */
/* 	{ */
/* 	  key[i] = j; */
/* 	  key_inv[j] = i; */
/* 	  i++; */
/* 	} */
/*     } */
/* } */

/* // gen word                 16 */
/* void gen_word_polybius(char *word) */
/* { */
/*   int i,j,k; */
/*   int find; */
/*   i=0; */
/*   while (i < 16) */
/*     { */
/*       AF_RANDOM(seed); */
/*       j = seed % 256; */
/*       find = 0; */
/*       for (k=0; k<i; k++) */
/* 	{ */
/* 	  if (word[k] == j) */
/* 	    { */
/* 	      find = 1; */
/* 	      k=i; */
/* 	    } */
/* 	} */
/*       if (find == 0) */
/* 	{ */
/* 	  word[i] = j; */
/* 	  i++; */
/* 	} */
/*     } */
/* } */

/* // encoder  */
/* static char * encoder_polybius(int len, */
/* 			       char *wordx, // 16 */
/* 			       char *wordy, // 16 */
/* 			       char *key, // 256 */
/* 			       char *key_inv, // 256 */
/* 			       char *input, //  */
/* 			       char *output) // length must be twice as long input */
/* { */
/*   int i,j,x,y; */
/*   for (i=0, j=0; i<len; i++, j += 2) */
/*     { */
/*       x = input[i]; */
/*       x = key_inv[x]; // pos */
/*       y = x / 16; */
/*       x = x % 16; */
/*       output[j]   = wordx[x]; */
/*       output[j+1] = wordy[y]; */
/*     } */
/*   return (output); */
/* } */


/* // decoder */
/* static char * decoder_polybius(int len, */
/* 			       char *wordx, // 16 */
/* 			       char *wordy, // 16 */
/* 			       char *key, // 256 */
/* 			       char *key_inv, // 256 */
/* 			       char *input, //  */
/* 			       char *output) // / 2 */
/* { */
/*   int i,j,k,x,y; */
/*   for (i=0, j=0; i<len; i++, j += 2) */
/*     { */
/*       x = input[j]; */
/*       y = input[j+1]; */

/*       // find */
/*       for (k=0; k<16; k++) */
/* 	{ */
/* 	  if (x == wordx[k]) */
/* 	    { */
/* 	      break; */
/* 	    } */
/* 	} */
/*       x = k; */

/*       // find */
/*       for (k=0; k<16; k++) */
/* 	{ */
/* 	  if (y == wordy[k]) */
/* 	    { */
/* 	      break; */
/* 	    } */
/* 	} */
/*       x = x + (y * 16); */

/*       output[i]   = key_inv[x]; */
/*     } */
/*   return (output); */
/* } */

