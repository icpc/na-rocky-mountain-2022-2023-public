/*  2022/2023 Regional
    International Collegiate Programming Contest

    Problem ?
    I Could Have Won
    M. K. Furon.                    2023-01-05.                       */




#include  <stdio.h>
#include  <stdlib.h>

#define   MAXPOINTS  2000

int alicewins, i, lastwin, winner;
char letter;

int points[(MAXPOINTS + 1)][2], wins[(MAXPOINTS + 1)][2];




void abend (char *message)
{
(void) fputs (message, stderr);
(void) fputc ('\n', stderr);
exit (4);
}




int main (int argc, char *argv[], char *envp[])
{
/*  Zero table of "first to n points" scores and wins for each
    possible value of n.                                              */
for (i = 0; i <= MAXPOINTS; i++)
   points[i][0] = points[i][1] = wins[i][0] = wins[i][1] = 0;

while ((letter = getchar ()) != EOF)
   {
   /*  Process each point in turn, which should be either 'A' or 'B'. */
   if (letter == 'A')
      winner = 0;
   else if (letter == 'B')
      winner = 1;
   else if (letter == '\n')
      break;
   else
      abend ("Unexpected character in input.");
      
   /*  Credit each point for the possible "first to n" values.  If
       a game is won at n points, add the game to the win count for
       the player and reset the scores to zero.                       */
   for (i = 1; i <= MAXPOINTS; i++)
      {
      (points[i][winner])++;
      if (points[i][winner] == i)
         {
	 (wins[i][winner])++;
         points[i][0] = points[i][1] = 0;
         }
      }
   }

/*  Count the number of values of n where Alice wins.  Store the
    highest such value.                                               */
alicewins = 0;
for (i = 1; i <= MAXPOINTS; i++)
   if (wins[i][0] > wins[i][1])
      {
      alicewins++;
      lastwin = i;
      }
(void) printf ("%d\n", alicewins);

/*  If Alice wins for at least one such value of n, print the list
    of all such values separated by single spaces.  Print a new-line
    after the last such value.                                        */
if (alicewins)
   {
   for (i = 1; i <= MAXPOINTS; i++)
      if (wins[i][0] > wins[i][1])
         {
         (void) printf ("%d", i);
         (void) putchar ((i < lastwin) ? ' ' : '\n');
         }
   }
   
return (0);
}
