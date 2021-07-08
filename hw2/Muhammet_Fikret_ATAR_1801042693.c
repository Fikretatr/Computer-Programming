#include<stdio.h>

int main()
{
	FILE * file = fopen ("input.txt", "r+");
	FILE * out = fopen("output.txt","w+");
	int main_num;
	int num;
	
	if(file == NULL||out ==NULL)
   	{
      printf("Dosya açýlamadý..");   //this is error message which show failed opening input.txt or output.txt..        
   	}
   	int i,basamaks=1,j=0,n,yedek_num,numbers[100],rept[100],index=0,count,flag=0;
   	fpos_t position;
	while(1)
	{
		if (fscanf (file, "%d", &main_num) != 1) // until EOF..
			break;
		fgetpos (file, &position); // the position hold the location of the next number ..
		count=1;
		flag=0;
		while(1)
		{
			if(fscanf(file, "%d", &num) != 1) //looking repater numbers until EOF..
				break;
				
			for(n = 0 ; n <= index; n++)
			{
				if(main_num == numbers [n])//dont look numbers which was counted before..
					flag=1;
			}
			if(flag==1)
				break;
			if(main_num == num)//find a matching between main and sub number
			{
        		count++; 
				fseek(file,0,SEEK_CUR);
				
			}
			
		}
		if(count>1)
		{
			numbers[index]=main_num;//fill up numbers array..
			rept[index]=count;//fill up as the same index numbers array..(common index )
			index++;	
		}
		fsetpos (file, &position); // update location for next number..

	}
	int a, key, b,key_2; 
	for (a = 0; a < index-1; a++)//for sorting..      
    {
    	for (b = 0; b < index-a-1; b++) 
		{ 
        	if (rept[b] > rept[b+1])  
            {
				key=rept[b+1];
				rept[b+1]=rept[b];
				rept[b]=key;
				
				key_2=numbers[b+1];
				numbers[b+1]=numbers[b];
				numbers[b]=key_2;
			}
			else if(rept[b]==rept [b+1])//for rule which is : "If the counts are the same, the smallest number should appear first.."
			{
				if(numbers[b]>numbers[b+1])
				{
					key_2=numbers[b+1];
					numbers[b+1]=numbers[b];
					numbers[b]=key_2;
				}		
						
			}
		}
	}
	
	
	for(i=0;i<index;i++)
		fprintf(out,"%d: %d\n",numbers[i],rept[i]);//finally writing information on output.txt..

  	fclose (file);        
	fclose (out);
	
}
