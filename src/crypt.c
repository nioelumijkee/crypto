// -------------------------------------------------------------------------- //
// bits
void encoder_bits(char *data,
		  char *key,
		  int size_key,
		  int start,
		  int len)
{
  int i,j;
  char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=start; i<start+len; i++)
    {
      j = i % size_key;
      k = key[j];
      buf = data[i];
      if (k == 0 || k > 64)
	{
	  buf = ~buf;
	}
      else if (k > 0 && k < 8)
	{
	  res_hi = buf >> k;
	  res_lo = buf << (8 - k);
	  buf = res_hi | res_lo;
	}
      else
	{
	  buf = buf ^ k;
	}
      data[i] = buf;
    }
}


// -------------------------------------------------------------------------- //
void decoder_bits(char *data,
		  char *key,
		  int size_key,
		  int start,
		  int len)
{
  int i,j;
  char k;
  unsigned char res_hi;
  unsigned char res_lo;
  unsigned char buf;
  for (i=start; i<start+len; i++)
    {
      j = i % size_key;
      k = key[j];
      buf = data[i];
      if (k == 0 || k > 64)
	{
	  buf = ~buf;
	}
      else if (k > 0 && k < 8)
	{
	  res_hi = buf << k;
	  res_lo = buf >> (8 - k);
	  buf = res_hi | res_lo;
	}
      else
	{
	  buf = buf ^ k;
	}
      data[i] = buf;
    }
}
