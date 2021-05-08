// -------------------------------------------------------------------------- //
// swap
#define AF_SWAP(X,Y,B)				\
  (B) = (X);					\
  (X) = (Y);					\
  (Y) = (B);


// -------------------------------------------------------------------------- //
// reverse
void reverse(char *data, 
	     int start, 
	     int len)
{
  int i, m, p1, p2;
  char buf;
  int end = start + len;

  
  m = len / 2;
  for (i = 0; i < m; i++)
    {
      p1 = start + i;
      p2 = end - i - 1;
      AF_SWAP(data[p1], data[p2], buf);
    }
}


// -------------------------------------------------------------------------- //
// shift
void shift(char *data, 
	   int start, 
	   int len, 
	   int shift)
{
  int end = start + len;
  int sh = shift;
  sh = sh % len;
  if (sh < 0)
    {
      sh = len + sh;
    }

  int i, p1, p2, m;
  int a_s = start;
  int a_l = sh;
  int b_s = start + sh;
  int b_l = len - sh;
  char buf;
  
  // reverse a
  if (a_l > 1)
    {
      m = a_l / 2;
      for (i = 0; i < m; i++)
	{
	  p1 = i + a_s;
	  p2 = a_l - i - 1 + a_s;
	  AF_SWAP(data[p1], data[p2], buf);
	}
    }
  
  // reverse b
  if (b_l > 1)
    {
      m = b_l /2;
      for (i = 0; i < m; i++)
	{
	  p1 = i + b_s;
	  p2 = b_l - i - 1 + b_s;
	  AF_SWAP(data[p1], data[p2], buf);
	}
    }
  
  // reverse ab
  for (i = 0; i < (len / 2); i++)
    {
      p1 = i + a_s;
      p2 = len - i - 1 + a_s;
      AF_SWAP(data[p1], data[p2], buf);
    }
  if(end) {} // dis
}

// -------------------------------------------------------------------------- //
// validate
void validate_ssl(int size, 
		  int *start, 
		  int *len)
{
  int end;

  // start 0 ... size-1
  if (*start < 0)
    {
      *start = size + *start;
      if (*start < 0)
	{
	  *start = 0;
	}
    }
  else if (*start >= size)
    {
      *start = size - 1;
    }

 
  // end 0 ... size
  if (*len <= 0)
    {
      end = size + *len;
      if (end < 0)
	{
	  end = 0;
	}
    }
  else
    {
      end = *start + *len;
      if (end > size)
	{
	  end = size;
	}

    }

  // len
  *len = end - *start;
  if (*len < 1)
    {
      *len = 0;
    }
}

