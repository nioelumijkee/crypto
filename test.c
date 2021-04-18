/*                         *
 *       test crypto       *
 *                         */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypt.c"

#define MAXSTR    1024
#define MAXSTR2   4096

enum
{
  CAESAR = 1,
  AFFINE,
  COUPLE,
  SWAP,
  BITS,
  POLYBIUS,
  INSERT_T,
  INSERT_R,
  VERNAM,
  HASH_R
};

// -------------------------------------------------------------------------- //
int main(int ac, char **av)
{
  long int i,j;
  long int len; /* size input data */
  int alg; /* algorythm */
  int err; /* error */
  int arg; /* count arguments */
  int a,b,c; /* parametrs */

  char data[MAXSTR2];
  char buf[MAXSTR2];
  char key[MAXSTR];
  char key_inv[MAXSTR];
  char wordx[MAXSTR];
  char wordy[MAXSTR];

  // arg -------------------------------------------------------------- //
  err = 0;
  alg = CAESAR;
  arg = 1;

  if (ac < 3) 
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
	  alg = POLYBIUS;
	  if (ac < 5)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      strncpy(wordx, av[arg], 17);
	      wordx[16] = '\0';
	      arg++;
	      strncpy(wordy, av[arg], 17);
	      wordy[16] = '\0';
	    }
	}

      else if (strcmp("-insert_t", av[arg]) == 0)
	{
	  alg = INSERT_T;
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

      else if (strcmp("-insert_r", av[arg]) == 0)
	{
	  alg = INSERT_R;
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

      else if (strcmp("-vernam", av[arg]) == 0)
	{
	  alg = VERNAM;
	  if (ac < 4)
	    {
	      err = 1;
	    }
	  else
	    {
	      arg++;
	      a = atoi(av[arg]);
	      if (a >= MAXSTR) a = MAXSTR;
	    }
	}

      else if (strcmp("-hash_r", av[arg]) == 0)
	{
	  alg = HASH_R;
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
      printf("     alg:      par:          .... \n");
      printf("    -caesar    a            <data>\n");
      printf("    -affine    a b          <data>\n");
      printf("    -couple                 <data>\n");
      printf("    -swap      a b c        <data>\n");
      printf("    -bits      a            <data>\n");
      printf("    -polybius  wordx wordy  <data>\n");
      printf("    -insert_t  a            <data>\n");
      printf("    -insert_r  a            <data>\n");
      printf("    -vernam    a            <data>\n");
      printf("    -hash_r    len          <data>\n");
      return(1);
    }


  // ramdom
  random_init();


  // alg -------------------------------------------------------------- //
  switch (alg)
    {
    case CAESAR:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("caesar %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	encoder_caesar(data, a, len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_caesar(data, a, len);
	printf("%s\n", data);
      }
      break;

    case AFFINE:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("affine %d %d\n", a, b);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	encoder_affine(data, a, b, len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_affine(data, a, b, len);
	printf("%s\n", data);
      }
      break;

    case COUPLE:
      {
	gen_couple(key, key_inv);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("couple\n");
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("key\n");
	printf("%s\n", key);
	printf("- - - - - - - - - - - - - - - -\n");
	printf("key inv\n");
	printf("%s\n", key_inv);

	printf("- - - - - - - - - - - - - - - -\n");
	deencoder_couple(data, key, len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	deencoder_couple(data, key_inv, len);
	printf("%s\n", data);
      }
      break;
 
    case SWAP:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("swap %d %d %d\n", a, b, c);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	encoder_swap(data, a, b, c, len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_swap(data, a, b, c, len);
	printf("%s\n", data);
      }
      break;

    case BITS:
      {
	gen_bits(key, a);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("bits %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("key\n");
	printf("%s\n", key);

	printf("- - - - - - - - - - - - - - - -\n");
	encoder_bits(data, key, len, a);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_bits(data, key, len, a);
	printf("%s\n", data);
      }
      break;
 
    case POLYBIUS:
      {
	gen_key_polybius(key, key_inv);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("polybius %s %s\n", wordx, wordy);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("key\n");
	printf("%s\n", key);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("key inv\n");
	printf("%s\n", key_inv);

	printf("- - - - - - - - - - - - - - - -\n");
	encoder_polybius(len, wordx, wordy, key, data, buf);
	printf("%s\n", buf);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_polybius(len, wordx, wordy, key_inv, buf, data);
	printf("%s\n", data);
      }
      break;
       
    case INSERT_T:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("insert_t %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	j = encoder_insert_this(a, len, data, buf);
	printf("%ld\n", j);
	printf("%s\n", buf);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_insert(a, j, buf, data);
	printf("%s\n", data);
      }
      break;

    case INSERT_R:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("insert_r %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	j = encoder_insert_rnd(a, len, data, buf);
	printf("%ld\n", j);
	printf("%s\n", buf);

	printf("- - - - - - - - - - - - - - - -\n");
	decoder_insert(a, j, buf, data);
	printf("%s\n", data);
      }
      break;

    case VERNAM:
      {
	gen_vernam(key, a);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("vernam %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	printf("key\n");
	printf("%s\n", key);

	printf("- - - - - - - - - - - - - - - -\n");
	deencoder_vernam(data, key, len, a);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	deencoder_vernam(data, key, len, a);
	printf("%s\n", data);
      }
      break;

    case HASH_R:
      {
	printf("- - - - - - - - - - - - - - - -\n");
	printf("hash_r %d\n", a);
	printf("size = %ld\n", len);
	printf("%s\n", data);

	printf("- - - - - - - - - - - - - - - -\n");
	hash_r(len, a, data, buf);
	for(i=0; i<a; i++)
	  printf("%.2hhX", buf[i]);
	printf("\n");
      }
      break;

    default:
      break;
    }

  return(0);
}
