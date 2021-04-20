#include <time.h>


// -------------------------------------------------------------------------- //
// pseudo
#define AF_RANDOM(SEED)		\
  (SEED) = (SEED)*1103515245;	\
  (SEED) += 12345;

// -------------------------------------------------------------------------- //
// hash
void hash_r(long int size,
	    long int size_hash, // pos
	    char *input,
	    char *output)
{
  int s; /* seed */
  long int i,j,k;
  long int size_1 = size - 1;

  // init seed
  s = 0;
  for (i=0; i<size; i++)
    {
      s += input[i];
      AF_RANDOM(s);
    }

  // hash
  for (i=0; i<size_hash; i++)
    {
      // clip
      k = i;
      k = k % size;
      s = input[k] + i + s;
      j = 0;
      while (j < size)
	{
	  // clip
	  k = j;
	  k = k % size;
	  s += input[k] + size_hash;
	  AF_RANDOM(s);
	  j++;
	}
      output[i] = s;
    }
}
