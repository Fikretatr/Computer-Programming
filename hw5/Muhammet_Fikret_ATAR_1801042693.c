#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    100

// """"""""""""""""""""""""""""""""""""""""""""""""""""""""
int Seperate_Text(char *str, char seperated[SIZE][SIZE])
{
   char *Arr;
   int  i = 0, num_splited = 0;

   Arr = strtok(str, "*+ ");

   while (Arr != NULL)
   {
      strcpy(seperated[i++], Arr);
      num_splited++;
      Arr = strtok(NULL, "*+ ");
   }

   if (!num_splited)
   {
      strcpy(seperated[0], "1");
      strcpy(seperated[1], str);
   }

   return num_splited;
}


// """"""""""""""""""""""""""""""""""""""""""""""""""""""""
int Check_Double(char *txt, double *price)
{
   int i;

   for (i = 0; i < strlen(txt); ++i)
   {
      if (((txt[i] < 48) || (txt[i] > 58)) && (txt[i] != '.') && (txt[i] != ' '))
      {
         return 0;
      }
   }

   return sscanf(txt, "%lf", price); // If text is double it will return 1,else 0.
}


// """"""""""""""""""""""""""""""""""""""""""""""""""""""""

// RECURSIVE FOR PRICE
double FIND_PRICE(char *Entered_Str)
{
   char   Arr[SIZE][SIZE];
   int    i, j, Count_Splited, Coef_Num;
   double Price = 0;
   double obj_price;

   printf("What is %s?:\n", Entered_Str); // All questions to user

   gets(Entered_Str);                     // Getting the text string from user

   if (Check_Double(Entered_Str, &obj_price) != 0)
   {
      return obj_price;
   }

   Count_Splited = Seperate_Text(Entered_Str, Arr); // Seperate text

   /*
    * Even indexes are coefficient of the objects as string in Arr.
    * Odd indexes are name of the objects as string in Arr.
    */

   for (i = 0; i < Count_Splited; i += 2)
   {
      sscanf(Arr[i], "%d", &Coef_Num);
      Price += Coef_Num * FIND_PRICE(Arr[i + 1]);
   }

   return Price;
}


// """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
int main()
{
   char   Entered_Str [SIZE], ObjectName[SIZE];

   printf("Define the object:\n");
   gets(Entered_Str);

   strcpy(ObjectName, Entered_Str);
   printf("Total cost of %s is %.1lf\n", ObjectName, FIND_PRICE(Entered_Str));

   return 0;
}
