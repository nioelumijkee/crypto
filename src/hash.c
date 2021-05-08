// -------------------------------------------------------------------------- //
// pseudo
#define AF_RANDOM(SEED)		\
  (SEED) = (SEED)*1103515245;	\
  (SEED) += 12345;

// -------------------------------------------------------------------------- //
// hash
void hash_r(int size_data,
	    int size_hash,
	    char *input,
	    char *output)
{
  int s; /* seed */
  int i,j,k;

  // init seed
  s = 0;
  for (i=0; i<size_data; i++)
    {
      s += input[i];
      AF_RANDOM(s);
    }

  // hash
  for (i=0; i<size_hash; i++)
    {
      // clip
      k = i;
      k = k % size_data;
      s = input[k] + i + s;
      j = 0;
      while (j < size_data)
	{
	  // clip
	  k = j;
	  k = k % size_data;
	  s += input[k] + size_hash;
	  AF_RANDOM(s);
	  j++;
	}
      output[i] = s;
    }
}
