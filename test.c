/* 
 * test crypt
 */
#include <stdio.h>
#include <string.h>
#include "crypt.c"

#define MAXSTR 1024
#define MAXSTR_2 2048

#define CAESAR 1
#define AFFINE 2
#define COUPLE 3
#define SWAP 4
#define BITS 5

// -------------------------------------------------------------------------- //
int main(int ac, char **av)
{
  int i;
  int len;
  int alg;
  int err;

  char str[MAXSTR_2];
  char key0[MAXSTR];
  char key1[MAXSTR];
  char *buf;

  // arg
  err=0;
  if(ac<2)
    {
      err=1;
    }
  else
    {
      // select algorythms
      if      (strcmp("-caesar", av[1]) == 0)
	{
	  alg = CAESAR;
	}
      else if (strcmp("-affine", av[1]) == 0)
	{
	  alg = AFFINE;
	}
      else if (strcmp("-couple", av[1]) == 0)
	{
	  alg = COUPLE;
	}
      else if (strcmp("-swap", av[1]) == 0)
	{
	  alg = SWAP;
	}
      else if (strcmp("-bits", av[1]) == 0)
	{
	  alg = BITS;
	}
      else
	{
	  err=1;
	}

      // data
      str[0]='\0';
      len=1;
      for(i=2; i<ac; i++)
	{
	  len += strlen(av[i]);
	  if (len<MAXSTR)
	    {
	      strcat(str, av[i]);
	      if (i != (ac-1))
		{
		  len += 1;
		  strcat(str, " ");
		}
	    }
	  else
	    {
	      err=2;
	      break;
	    }
	}
      if (len == 1)
	{
	  err=1;
	}
    }


  if (err == 1)
    {
      printf("usage: -alg str str str ...\n");
      return(1);
    }
  else if (err == 2)
    {
      printf("maxlen = %d\n", MAXSTR);
      return(2);
    }

  // print
  printf("=================\n");
  printf("len = %d\n", len);
  printf("=================\n");
  printf("%s\n", str);

  // body

  // ramdom
  random_init();

  if (alg == CAESAR)
    {
      buf = encoder_caesar(3, str, len-1);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_caesar(3, buf, len-1);
      printf("=================\n");
      printf("%s\n",buf);
    }
  else if (alg == AFFINE)
    {
      buf = encoder_affine(2, 144, str, len-1);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_affine(2, 144, buf, len-1);
      printf("=================\n");
      printf("%s\n",buf);
    }
  else if (alg == COUPLE)
    {
      gen_couple(key0, key1);
      printf("=================\n");
      printf("%s\n",key0);
      printf("=================\n");
      printf("%s\n",key1);
      buf = encoder_couple(key0, str, len-1);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_couple(key1, buf, len-1);
      printf("=================\n");
      printf("%s\n",buf);
    }
  else if (alg == SWAP)
    {
      buf = encoder_swap(2, 144, len*4, str, len-1);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_swap(2, 144, len*4, buf, len-1);
      printf("=================\n");
      printf("%s\n",buf);
    }
  else if (alg == BITS)
    {
      gen_bits(key0, 256);
      printf("=================\n");
      printf("%s\n",key0);
      buf = encoder_bits(256, len-1, key0, str);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_bits(256, len-1, key0, buf);
      printf("=================\n");
      printf("%s\n",buf);
    }

  return(0);
}
