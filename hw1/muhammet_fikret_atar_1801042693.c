#include<stdio.h>


int main()
{
	FILE * file = fopen ("file.txt", "r+");
	int i;
	int num;
	
	if(file == NULL)
   	{
      printf("Dosya açýlamadý..");   //açýlamazsa hata..          
   	}
   	int basamaks=1;
   	int j=0;
   	int yedek_num;
   	fpos_t position;
	while(1)
	{
		if (fscanf (file, "%d", &i) != 1) // dosya bitene kadar..
			break;
		fgetpos (file, &position); // bir sonraki sayýdan baþlamak için tutulur
		while(1)
		{
			if(fscanf(file, "%d", &num) != 1) // dosya bitene kadar benzerlik kontrolü..
				break;
			yedek_num = num; // basamak sayisini bulurken sayý deðiþmesin diye..
			if(num<0)
			{
				yedek_num = -yedek_num;
				basamaks++; //"-" için..
			}
			if(i == num)
			{
				while(yedek_num>=10)// basamak sayisini bulmak..
				{
        			yedek_num=yedek_num/10;
        			basamaks++;
        		}
        		 
        		
        		fseek(file,-basamaks,SEEK_CUR); // olduðu yerden basamak sayisi kadar geri gelir..
				while(j<basamaks)
				{
					fprintf(file, "%c",' '); // ve boþlukla deðiþtirir
					j++;
				}
				fseek(file,0,SEEK_CUR);//diðer benzerlik var mý diye current pozisyona ayarlanýr..
				
			}
			basamaks=1;
			j=0;
			
		}
		fsetpos (file, &position); // bir sonraki sayýdan baþlamak için güncellenir
		
		
		
	}
	


  	fclose (file);        

	
}
