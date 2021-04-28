/* #include "random.c" */


// -------------------------------------------------------------------------- //
// swap
#define AF_SWAP(X,Y,B)				\
  (B) = (X);					\
  (X) = (Y);					\
  (Y) = (B);


// -------------------------------------------------------------------------- //
// make blend char's 256
void gen_blend256(char *key) // 256 
{
  int i,k;
  char j;
  int find;
  i=0;
  while (i<256)
    {
      /* rnd */
      random512();
      j = random512_get();

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


// -------------------------------------------------------------------------- //
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


// -------------------------------------------------------------------------- //
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
      random512();
      j = random512_get();

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


// -------------------------------------------------------------------------- //
// make key with various size
void gen_var(char *key, long int size)
{
  long int i;
  for (i=0; i<size; i++)
    {
      random512();
      key[i] = random512_get();
    }
}
