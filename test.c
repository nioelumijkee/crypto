/* 
 * test crypt
 */
#include <stdio.h>
#include <string.h>
#include "crypt.c"

#define MAXSTR 1024

#define CAESAR 1
#define COUPLE 2

// -------------------------------------------------------------------------- //
int main(int ac, char **av)
{
  int i;
  int len;
  int alg;
  int err;

  char str[MAXSTR];
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
      else if (strcmp("-couple", av[1]) == 0)
	{
	  alg = COUPLE;
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
  if (alg == CAESAR)
    {
      buf = encoder_caesar(3, str, len-1);
      printf("=================\n");
      printf("%s\n",buf);
      buf = decoder_caesar(3, buf, len-1);
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

  return(0);
}
