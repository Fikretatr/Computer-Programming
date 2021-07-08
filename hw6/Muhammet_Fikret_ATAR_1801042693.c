#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE    50

const char *INPUT   = "input.txt";
const char *CIRCUIT = "circuit.txt";

/* Struct for all INPUT variables and new identations like and1,or1 etc. with id and values of them */
struct Label
{
   char iden[NAMESIZE];
   int  val;
   int  former_out;
};

/* My Functions */
int Logic_Process(struct Label *Arr, char *first, char *second, char Abbreviation, int last_index); /* Makes Logic Process with gates */
struct Label *Read_Names_Nums(struct Label *Arr, int Row_num, int Col_num, int line_num);
int Num_Row();
int Num_Col();
int Num_Keywords();
int **Write_Inputs(int num_inputs, int num_rows);                         /* Write input values to a 2d array(int).Num_in = size*/
char Chosen_Gate(char *Str);                                              /* Takes the gates from circuit text and return abbreviation of gate */
struct Label *Take_Keywords(struct Label *Arr, int num_inputs, int line); /* Takes keywords like and1,or1,f1,n1 */

/*_____________MAIN_____________*/

int main(int argc, char const *argv[])
{
   /* Array of Label Structe to keep the input variables with their bit values.(0-1) */
   struct Label *ARR;

   int i, line, num_inputs = 0, num_row, num_column, keyword_num, num_line;

   num_row     = Num_Row(); /* num of row was founded */
   num_column  = Num_Col(); /* num of column was founded. It is equal to the num_inputs */
   num_inputs  = num_column;
   keyword_num = Num_Keywords();
   num_line    = Num_Row();
   /* ARR alocated, and number of inputs founded=num_inputs in this function */

   ARR = malloc(sizeof(struct Label) * (num_inputs + keyword_num));

   for (i = 0; i < num_inputs + keyword_num; ++i)
   {
      ARR[i].former_out = 0;
   }


   for (line = 0; line < num_line; ++line)
   {
      ARR = Read_Names_Nums(ARR, num_row, num_column, line); /* Add inputs to arr with values */

      ARR = Take_Keywords(ARR, num_inputs, line);    /* Add keywords to the arr from inputs */

      printf("%d\n", ARR[i - 1].val);
   }
   return 0;
}


/*___________FUNCTIONS_______________*/

struct Label *Read_Names_Nums(struct Label *Arr, int Row_num, int Col_num, int line_num)
{
   int  num, i = 0, j = 0, flag, ch;
   char name[50];
   char c;
   int  **Input_Values;

   FILE *fp_c, *fp_in;

   /* File opening operation to read */
   fp_in = fopen(INPUT, "r");
   /* File opening operation to read */
   fp_c = fopen(CIRCUIT, "r");

   /* Allocation struct to keep the input values */
   //struct Label *Arr = malloc(sizeof(struct Label) * Col_num);

   /*Note: Values and inputs are same number of values => num_inputs .*/

   Input_Values = Write_Inputs(Col_num, Row_num);

   //----------------------------------------------- VALUES
   for (i = 0; i < Col_num; ++i)
   {
      Arr[i].val = Input_Values[line_num][i];       //i:input names,line: input vals alt  aalta sütunlar ilk inputun değerleri
   }


   /* this fscanf takes the first contents from circuit.txt */
   /* first strings are name of keywords */
   fscanf(fp_c, "%s", name);

   i = 0;
   //----------------------------------------------- Names
   for (i = 0; i < Col_num; ++i)
   {
      fscanf(fp_c, "%s", name);
      strcpy(Arr[i].iden, name);
   }

   return Arr;
}


/* _________________________________________________________________________________ */

int Logic_Process(struct Label *Arr, char *first, char *second, char Abbreviation, int last_index)
{
   int val1, val2, result;
   int i, j;

   for (i = 0; i < last_index; i++)
   {
      if (strcmp(Arr[i].iden, first) == 0)
      {
         val1 = Arr[i].val;
         break;
      }
   }

   if (second != NULL)
   {
      for (j = 0; j < last_index; j++)
      {
         if (strcmp(Arr[j].iden, second) == 0)
         {
            val2 = Arr[j].val;
            break;
         }
      }
   }


   if (second == NULL)
   {
      val2 = 0;
   }

   switch (Abbreviation)
   {
   case 'A':
      result = val1 & val2;
      break;

   /* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
   case 'O':
      result = val1 | val2;
      break;

   /* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
   case 'N':
      result = !(val1);
      break;

   /* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
   case 'F':
      result = val1 ^ (Arr[last_index].former_out);

      Arr[last_index].former_out = result;

      break;

      /* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
   }
   //printf("RESULT:%d\n", result);
   return result;
}


/*___________________________________________________________________*/
struct Label *Take_Keywords(struct Label *Arr, int num_inputs, int line)
{
   char str[NAMESIZE], keyword[NAMESIZE] = "", gate[NAMESIZE] = "", first[NAMESIZE] = "", second[NAMESIZE] = "", temp[NAMESIZE] = "";
   FILE *fp;
   int  count = 0, c;
   int  i = num_inputs, j, line2, col_num = 0; /* keywords will be added to arr  after inputs. Like a,b,c,d,and1,or1*/
   char Abbreviation;
   int  flag, l, k;
   int  keyword_num = Num_Keywords();

   /* File opening operation to read */
   fp = fopen(CIRCUIT, "r");

   /* Allocation for new keyword elements after inputs */
   /* Counts of keywords at the second column */
   /* Realloc for keywords after the inputs stored at arr */



   /* Takes pointer to 2nd line to ignore the input line in circuit */
   while ((c = getc(fp)) != '\n')
   {
   }
   for (j = 0; j < keyword_num; ++j)
   {
      fgets(str, NAMESIZE, fp);

      sscanf(str, "%s", gate);

      Abbreviation = Chosen_Gate(gate);    /* For logical process */

      if (Abbreviation == 'A')             // And a,b
      {
         sscanf(str + strlen(gate), "%s%s%s", keyword, first, second);
         strcpy(Arr[i].iden, keyword);
         Arr[i].val = Logic_Process(Arr, first, second, Abbreviation, i);
      }
      else if (Abbreviation == 'O')    // Or a,b
      {
         sscanf(str + strlen(gate), "%s%s%s%s", keyword, first, second);
         strcpy(Arr[i].iden, keyword);
         Arr[i].val = Logic_Process(Arr, first, second, Abbreviation, i);
      }
      else if (Abbreviation == 'N')    // Not a
      {
         sscanf(str + strlen(gate), "%s%s", keyword, first);
         strcpy(Arr[i].iden, keyword);
         Arr[i].val = Logic_Process(Arr, first, NULL, Abbreviation, i);
      }
      else if (Abbreviation == 'F')    // FF a
      {
         sscanf(str + strlen(gate), "%s%s", keyword, first);
         strcpy(Arr[i].iden, keyword);

         Arr[i].val = Logic_Process(Arr, first, NULL, Abbreviation, i);
      }
      i++;
   }
   fclose(fp);

   return Arr;
}


/* ______________________________________________________________________ */
int Num_Row()
{
   int c, line_num = 0;


   FILE *fp;

   /* File opening operation to read */
   fp = fopen(INPUT, "r");

   /* counts the line numbers */
   while ((c = getc(fp)) != EOF)
   {
      if (c == '\n')
      {
         line_num++;
      }
   }
   line_num++;

   /* Takes the pointer begining of the file */
   fseek(fp, 0, SEEK_SET);
   fclose(fp);

   return line_num;
}


/* ______________________________________________________________________ */
int Num_Col()
{
   int c, col_num = 0;

   FILE *fp;

   /* File opening operation to read */
   fp = fopen(INPUT, "r");
   /* Takes the pointer begining of the file */
   fseek(fp, 0, SEEK_SET);

   /* counts the line numbers */
   while ((c = getc(fp)) != '\n')
   {
      if (c != ' ')    /* if not space*/
      {
         col_num++;
      }
   }

   /* Takes the pointer begining of the file */
   fseek(fp, 0, SEEK_SET);
   fclose(fp);

   return col_num;
}


/* ______________________________________________________________________ */
int **Write_Inputs(int num_col, int num_rows)
{
   int i = 0, j = 0;
   int **Arr;

   FILE *fp;

   /* File opening operation to read */
   fp = fopen(INPUT, "r");
   /* Takes the pointer begining of the file */
   fseek(fp, 0, SEEK_SET);


   Arr = (int **)malloc(num_rows * sizeof(int *));
   //______________________________________________________________________
   for (i = 0; i < num_rows; ++i)
   {
      Arr[i] = (int *)malloc(num_col * sizeof(int));
   }
   i = 0;
   //______________________________________________________________________
   for (i = 0; i < num_rows; ++i)
   {
      for (j = 0; j < num_col; ++j)
      {
         (fscanf(fp, "%d", &Arr[i][j]));
      }
   }

   return Arr;
}


/* ______________________________________________________________________ */
char Chosen_Gate(char *Str)    /* keyword num founded in Count_Keyword function.*/
{
   char Abbreviation;

   if (strcmp(Str, "AND") == 0)
   {
      Abbreviation = 'A';
   }
   if (strcmp(Str, "OR") == 0)
   {
      Abbreviation = 'O';
   }
   if (strcmp(Str, "NOT") == 0)
   {
      Abbreviation = 'N';
   }
   if (strcmp(Str, "FLIPFLOP") == 0)
   {
      Abbreviation = 'F';
   }

   return Abbreviation;
}


/* ______________________________________________________________________ */
int Num_Keywords()
{
   FILE *fp;
   int  c, num = 0;

   /* File opening operation to read */
   fp = fopen(CIRCUIT, "r");
   /* counts the line numbers */
   while ((c = getc(fp)) != EOF)
   {
      if (c == '\n')
      {
         num++;
      }
   }
   /* Takes the pointer begining of the file */
   fseek(fp, 0, SEEK_SET);
   fclose(fp);

   return num;
}
