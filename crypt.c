#include <time.h>


// -------------------------------------------------------------------------- //
// pseudo
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
	      break;
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
		  int a,     // only positive
		  int b,     // only positive
		  int step,  // only positive
		  int len)
{
  int i,j,k;
  char buf;
  if (a < 0)    a = 0 - a;
  if (b < 0)    b = 0 - b;
  if (step < 0) step = 0 - step;
  i = 0;
  while (i < step)
    {
      j = (unsigned int)(((i*a)+b)) % len;
      k = (unsigned int)i % len;
      AF_SWAP(data[k], data[j], buf);
      i++;
    }
}

void decoder_swap(char *data,
		  int a,     // only positive
		  int b,     // only positive
		  int step,  // only positive
		  int len)
{
  int i,j,k;
  char buf;
  if (a < 0)    a = 0 - a;
  if (b < 0)    b = 0 - b;
  if (step < 0) step = 0 - step;
  i = step-1;
  while (i >= 0)
    {
      j = (unsigned int)(((i*a)+b)) % len;
      k = (unsigned int)i % len;
      AF_SWAP(data[k], data[j], buf);
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

// -------------------------------------------------------------------------- //
// polybius
void gen_key_polybius(char *key,     // 256 
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
	      break;
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

void gen_word_polybius(char *word) // 16
{
  int i,j,k;
  int find;
  i=0;
  while (i < 16)
    {
      AF_RANDOM(seed);
      j = seed % 256;
      find = 0;
      for (k=0; k<i; k++)
	{
	  if (word[k] == j)
	    {
	      find = 1;
	      break;
	    }
	}
      if (find == 0)
	{
	  word[i] = j;
	  i++;
	}
    }
}

void encoder_polybius(int len,
		      char *wordx,    // 16 (only unique)
		      char *wordy,    // 16 (only unique)
		      char *key,      // 256
		      char *input,    //
		      char *output)   // input * 2
{
  int i,u;
  unsigned char x,y;
  for (i=0, u=0; 
       i<len; 
       i++, u += 2)
    {
      x = input[i];
      x = (unsigned char)key[x]; // pos
      y = x / 16;
      x = x % 16;
      output[u]   = wordx[x];
      output[u+1] = wordy[y];
    }
}


void decoder_polybius(int len,
		      char *wordx,   // 16 (only unique)
		      char *wordy,   // 16 (only unique)
		      char *key_inv, // 256
		      char *input,   //
		      char *output)  // input / 2
{
  int i,u,k;
  unsigned char x,y;
  for (i=0, u=0; 
       i<len; 
       i++, u += 2)
    {
      x = input[u];
      y = input[u+1];

      // find
      for (k=0; k<16; k++)
	{
	  if (x == wordx[k])
	    {
	      break;
	    }
	}
      x = k;

      // find
      for (k=0; k<16; k++)
	{
	  if (y == wordy[k])
	    {
	      break;
	    }
	}
      x = x + (k * 16);

      output[i] = key_inv[x];
    }
}


// -------------------------------------------------------------------------- //
// insert
int encoder_insert_this(int a,     // 2 >= a 
			int len,
			char *input,
			char *output) // max = input * 2
{
  int i,j,k;
  if (a < 1)    a = 1;
  i = 0;
  j = 0;
  while (i < len)
    {
      k = i % a;
      if (k == 0)
	{
	  AF_RANDOM(seed);
	  k = seed % len;
	  /* output[j] = '.'; */
	  output[j] = input[k];
	  j++;
	}

      output[j] = input[i];
      j++;

      i++;
    }
  return(j);
}

int encoder_insert_rnd(int a,        // 1 >= a 
		       int len,
		       char *input,
		       char *output) // max = input * 2
{
  int i,j,k;
  if (a < 1)    a = 1;
  i = 0;
  j = 0;
  while (i < len)
    {
      k = i % a;
      if (k == 0)
	{
	  AF_RANDOM(seed);
	  k = seed % len;
	  output[j] = k;
	  j++;
	}

      output[j] = input[i];
      j++;

      i++;
    }
  return(j);
}

int decoder_insert(int a,        // 1 >= a 
		   int len,
		   char *input,
		   char *output) // max = input * 2
{
  int i,j,k;
  if (a < 1)    a = 1;
  a += 1;
  i = 0;
  j = 0;
  while (i < len)
    {
      k = i % a;
      if (k == 0)
	{
	  i++;
	}

      output[j] = input[i];
      j++;

      i++;
    }
  return(j);
}

// -------------------------------------------------------------------------- //
// vernam
void gen_vernam(char *key, int len)
{
  int i;
  for (i=0; i<len; i++)
    {
      AF_RANDOM(seed);
      key[i] = seed;
    }
}

void encoder_vernam(char *data,
		    char *key,
		    int len_data,
		    int len_key)
{
  int i,j;
  for (i=0; i<len_data; i++)
    {
      j = i % len_key;
      data[i] = data[i] ^ key[j];
    }
}


void decoder_vernam(char *data,
		    char *key,
		    int len_data,
		    int len_key)
{
  int i,j;
  for (i=0; i<len_data; i++)
    {
      j = i % len_key;
      data[i] = data[i] ^ key[j];
    }
}

// -------------------------------------------------------------------------- //
// hash
void hash_r(int len,
	    int hash_len, // pos
	    char *input,
	    char *output) // 8
{
  int s; /* seed */
  int i,j,k;
  int len_1 = len - 1;
  s = 0;
  for (i=0; i<hash_len; i++)
    {
      // clip
      k = i;
      if (k > len_1) k = len_1;

      s = input[k] + i + s;
      j = 0;
      while (j < len)
	{
	  // clip
	  k = j;
	  if (k > len_1) k = len_1;

	  s += input[k];
	  AF_RANDOM(s);
	  j++;
	}
      output[i] = s;
    }
}
