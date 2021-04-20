#include <time.h>


// -------------------------------------------------------------------------- //
// swap
#define AF_SWAP(X,Y,B)				\
  (B) = (X);					\
  (X) = (Y);					\
  (Y) = (B);



// -------------------------------------------------------------------------- //
// random
static unsigned int  seed512;
static unsigned int  seed512_count;
static unsigned char seed512_key[512];


// random with key 512
// count shift 3
#define AF_RANDOM512()				\
  seed512 *= 1103515245;			\
  seed512 += 12345;				\
						\
  seed512 *= seed512_key[seed512_count];	\
  seed512_count++;				\
  seed512_count = seed512_count % 512;		\
						\
  seed512 += seed512_key[seed512_count];	\
  seed512_count += 2;				\
  seed512_count = seed512_count % 512;		\
						\


void random512_init_by_time()
{
  seed512 = time(NULL);
  seed512_count = 0;
}


void random512_init(int i)
{
  seed512 = i;
  seed512_count = 0;
}


void random512_set_key(char *c)
{
  int i;
  for (i=0; i<512; i++)
    {
      seed512_key[i] = c[i];
    }
}


// -------------------------------------------------------------------------- //
// make blend char's 256
void gen_blend256(char *key) // 256 
{
  int i,k;
  unsigned char j;
  int find;
  i=0;
  while (i<256)
    {
      /* rnd */
      AF_RANDOM512();
      j = seed512;

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
	  i++;
	}
    }
}


// make invert key for blend char's 256
void gen_blend256_invert(char *key,     // 256 
			 char *key_inv) // 256
{
  int i;
  unsigned char j;
  for (i=0; i<256; i++)
    {
      j = key[i];
      key_inv[j] = i;
    }
}


// make blend char's 16
void gen_blend16(char *key) // 16 
{
  int i,k;
  unsigned char j;
  int find;
  i=0;
  while (i<16)
    {
      /* rnd */
      AF_RANDOM512();
      j = seed512;

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
	  i++;
	}
    }
}


// make key with various size
void gen_var(char *key, long int size)
{
  long int i;
  for (i=0; i<size; i++)
    {
      AF_RANDOM512();
      key[i] = seed512;
    }
}


// -------------------------------------------------------------------------- //
// caesar
void encoder_caesar(char *data, int a, long int size)
{
  long int i=0;
  while (i < size)
    {
      data[i] = data[i] + a;
      i++;
    }
}

void decoder_caesar(char *data, int a, long int size)
{    
  long int i=0;
  while (i < size)
    {
      data[i] = data[i] - a;
      i++;
    }
}

// -------------------------------------------------------------------------- //
// affine
void encoder_affine(char *data, int a, int b, long int size)
{
  long int i=0;
  while (i < size)
    {
      data[i] = data[i] + (i*a) + b;
      i++;
    }
}

void decoder_affine(char *data, int a, int b, long int size)
{
  long int i=0;
  while (i < size)
    {
      data[i] = data[i] - (i*a) - b;
      i++;
    }
}

// -------------------------------------------------------------------------- //
// couple
// for encode - key
// for decode - key_inv
void deencoder_couple(char *data, 
		      char *key, // 256 
		      long int size)
{
  long int i;
  for(i=0; i<size; i++)
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
		  long int size)
{
  long int i,j,k;
  char buf;
  if (a < 0)    a = 0 - a;
  if (b < 0)    b = 0 - b;
  if (step < 0) step = 0 - step;
  i = 0;
  while (i < step)
    {
      j = (unsigned int)(((i*a)+b)) % size;
      k = (unsigned int)i % size;
      AF_SWAP(data[k], data[j], buf);
      i++;
    }
}

void decoder_swap(char *data,
		  int a,     // only positive
		  int b,     // only positive
		  int step,  // only positive
		  long int size)
{
  long int i,j,k;
  char buf;
  if (a < 0)    a = 0 - a;
  if (b < 0)    b = 0 - b;
  if (step < 0) step = 0 - step;
  i = step-1;
  while (i >= 0)
    {
      j = (unsigned int)(((i*a)+b)) % size;
      k = (unsigned int)i % size;
      AF_SWAP(data[k], data[j], buf);
      i--;
    }
}

// -------------------------------------------------------------------------- //
// bits
void encoder_bits(char *data,
		  char *key,
		  long int size_data,
		  long int size_key)
{
  long int i,j;
  unsigned char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=0; i<size_data; i++)
    {
      j = i % size_key;
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
		  long int size_data,
		  long int size_key)
{
  long int i,j;
  unsigned char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=0; i<size_data; i++)
    {
      j = i % size_key;
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
void encoder_polybius(long int size,
		      char *wordx,    // 16 (only unique)
		      char *wordy,    // 16 (only unique)
		      char *key,      // 256
		      char *input,    //
		      char *output)   // input * 2
{
  long int i,u;
  unsigned char x,y;
  for (i=0, u=0; 
       i<size; 
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


void decoder_polybius(long int size,
		      char *wordx,   // 16 (only unique)
		      char *wordy,   // 16 (only unique)
		      char *key_inv, // 256
		      char *input,   //
		      char *output)  // input / 2
{
  long int i,u,k;
  unsigned char x,y;
  for (i=0, u=0; 
       i<size; 
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
int encoder_insert_this(int a, // 1 >= a 
			long int size,
			char *input,
			char *output) // max = input * 2
{
  long int i,j,k;
  if (a < 1)    a = 1;
  i = 0;
  j = 0;
  while (i < size)
    {
      k = i % a;
      if (k == 0)
	{
	  AF_RANDOM512();
	  k = seed512 % size;
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
		       long int size,
		       char *input,
		       char *output) // max = input * 2
{
  long int i,j,k;
  if (a < 1)    a = 1;
  i = 0;
  j = 0;
  while (i < size)
    {
      k = i % a;
      if (k == 0)
	{
	  AF_RANDOM512();
	  output[j] = seed512;
	  j++;
	}

      output[j] = input[i];
      j++;
      i++;
    }
  return(j);
}

int decoder_insert(int a,        // 1 >= a 
		   long int size,
		   char *input,
		   char *output) // max = input * 2
{
  long int i,j,k;
  if (a < 1)    a = 1;
  a += 1;
  i = 0;
  j = 0;
  while (i < size)
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
void deencoder_vernam(char *data,
		      char *key,
		      long int size_data,
		      long int size_key)
{
  long int i,j;
  for (i=0; i<size_data; i++)
    {
      j = i % size_key;
      data[i] = data[i] ^ key[j];
    }
}

