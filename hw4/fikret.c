#include<stdio.h>

void recursive_visualization(FILE * out,char array[],int step)
{
	if( *(array) == '*') // Base case...
	{
		return;
	}
	else
	{
		if(*array == '(') //when seen character '(' addition 1 to # of inner depth ('-') ..
			recursive_visualization(out,array+1,++step);
		else if(*array == ')') //when seen character ')' substract 1 to # of inner depth ('-') ..
			recursive_visualization(out,array+1,--step);
		else if (*array == ',') //ignore..
			recursive_visualization(out,array+1,step);
		else//when seen alphabetic character printing.. 
		{
			int j;
			for(j=0;j<step;j++)
				fprintf(out,"-");
			fprintf(out,"%c\n",array[0]);
			recursive_visualization(out,array+1,step);
		}
	}
}

int main()
{
	FILE * file = fopen ("input.txt", "r+");
	FILE * out = fopen("output.txt","w+");
	
	if(file == NULL||out ==NULL)
   	{
      printf("Dosya açýlamadý..");   //this is error message which show failed opening input.txt or output.txt..        
   	}
   	char char_;
   	int i=0,count,step=0;
   	char array[250];
	while(1)
	{
		if (fscanf (file, "%c", &char_) != 1) // until EOF..
			break;
		array[i] = char_;
		i++;
	}
	array[i]='*';
	count=i;
	int j;
	
	recursive_visualization(out,array,0);//recursion visualization ..

  	fclose (file);        
	fclose (out);
	
}
