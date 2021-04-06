/*                        *
 *      test crypto       *
 *                        */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypt.c"

#define MAXSTR   1024
#define MAXSTR_2 2048

enum
{
  CAESAR = 1,
  AFFINE,
  COUPLE,
  SWAP,
  BITS,
  POLYBIUS
};

// -------------------------------------------------------------------------- //
int main(int ac, char **av)
{
  int i;
  int len; /* length input data */
  int alg; /* algorythm */
  int err; /* error */
  int arg; /* count arguments */
  int a,b,c; /* parametrs */

  char data[MAXSTR];

  // arg -------------------------------------------------------------- //
  err = 0;
  alg = CAESAR;
  arg = 1;

  if (ac < 2) 
    {
      err = 1;
    }
  else
    {
      // select alg
      if (strcmp("-caesar", av[arg]) == 0)
	{
	  alg = CAESAR;
	  if (ac < 4)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      a = atoi(av[arg]);
	    }
	}

      else if (strcmp("-affine", av[arg]) == 0)
	{
	  alg = AFFINE;
	  if (ac < 5)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      a = atoi(av[arg]);
	      arg++;
	      b = atoi(av[arg]);
	    }
	}

      else if (strcmp("-couple", av[arg]) == 0)
	{
	  alg = COUPLE;
	}

      else if (strcmp("-swap", av[arg]) == 0)
	{
	  alg = SWAP;
	  if (ac < 6)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      a = atoi(av[arg]);
	      arg++;
	      b = atoi(av[arg]);
	      arg++;
	      c = atoi(av[arg]);
	    }
	}

      else if (strcmp("-bits", av[arg]) == 0)
	{
	  alg = BITS;
	  if (ac < 4)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      a = atoi(av[arg]);
	    }
	}

      else if (strcmp("-polybius", av[arg]) == 0)
	{
	}

      else
	{
	  err = 1;
	}
      
      // copy data
      if (err == 0)
	{
	  arg++;
	  len = 0;
	  for(i=0; i<MAXSTR-1; i++)
	    {
	      if (av[arg][i] == '\0')
		break;
	      else
		{
		  data[i] = av[arg][i];
		  len++;
		}
	    }
	  data[i] = '\0';
	}
    }


  // print "usage" if error in arguments
  if (err == 1)
    {
      printf("usage:\n");
      printf("     alg:      par:         \n");
      printf("    -caesar    a      <data>\n");
      printf("    -affine    a b    <data>\n");
      printf("    -couple           <data>\n");
      printf("    -swap      a b c  <data>\n");
      printf("    -bits      a      <data>\n");
      printf("    -polybius\n");
      return(1);
    }


  // ramdom
  random_init();

  char key[MAXSTR];
  char key_inv[MAXSTR];

  // alg -------------------------------------------------------------- //
  switch (alg)
    {
    case CAESAR:
      {
	printf("-----------------\n");
	printf("caesar %d\n", a);
	printf("length = %d\n", len);
	printf("%s\n", data);

	printf("-----------------\n");
	encoder_caesar(data, a, len);
	printf("%s\n", data);

	printf("-----------------\n");
	decoder_caesar(data, a, len);
	printf("%s\n", data);
      }
      break;

    case AFFINE:
      {
	printf("-----------------\n");
	printf("affine %d %d\n", a, b);
	printf("length = %d\n", len);
	printf("%s\n", data);

	printf("-----------------\n");
	encoder_affine(data, a, b, len);
	printf("%s\n", data);

	printf("-----------------\n");
	decoder_affine(data, a, b, len);
	printf("%s\n", data);
      }
      break;

    case COUPLE:
      {
	gen_couple(key, key_inv);

	printf("-----------------\n");
	printf("couple\n");
	printf("length = %d\n", len);
	printf("%s\n", data);

	printf("-----------------\n");
	printf("key\n");
	printf("%s\n", key);
	printf("-----------------\n");
	printf("key inv\n");
	printf("%s\n", key_inv);

	printf("-----------------\n");
	deencoder_couple(data, key, len);
	printf("%s\n", data);

	printf("-----------------\n");
	deencoder_couple(data, key_inv, len);
	printf("%s\n", data);
      }
      break;
 
    case SWAP:
      {
	printf("-----------------\n");
	printf("swap %d %d %d\n", a, b, c);
	printf("length = %d\n", len);
	printf("%s\n", data);

	printf("-----------------\n");
	encoder_swap(data, a, b, c, len);
	printf("%s\n", data);

	printf("-----------------\n");
	decoder_swap(data, a, b, c, len);
	printf("%s\n", data);
      }
      break;

    case BITS:
      {
	gen_bits(key, a);

	printf("-----------------\n");
	printf("bits %d\n", a);
	printf("length = %d\n", len);
	printf("%s\n", data);

	printf("-----------------\n");
	printf("key\n");
	printf("%s\n", key);

	printf("-----------------\n");
	encoder_bits(data, key, len, a);
	printf("%s\n", data);

	printf("-----------------\n");
	decoder_bits(data, key, len, a);
	printf("%s\n", data);
      }
      break;
 
    /* case POLYBIUS: */
    /*   gen_key_polybius(key0, key1); */
    /*   printf("=================\n"); */
    /*   printf("%s\n",key0); */
    /*   printf("=================\n"); */
    /*   printf("%s\n",key1); */
    /*   gen_word_polybius(wordx); */
    /*   wordx[16] = '\0'; */
    /*   printf("=================\n"); */
    /*   printf("%s\n",wordx); */
    /*   gen_word_polybius(wordy); */
    /*   wordy[16] = '\0'; */
    /*   printf("=================\n"); */
    /*   printf("%s\n",wordy); */
    /*   buf = encoder_polybius(len-1, wordx, wordy, key0, key1, str, data2); */
    /*   printf("=================\n"); */
    /*   printf("%s\n",buf); */
    /*   buf = decoder_polybius(len-1, wordx, wordy, key0, key1, data2, str); */
    /*   printf("=================\n"); */
    /*   printf("%s\n",buf); */
    /*   break; */
      
    default:
      break;
    }

  return(0);
}
