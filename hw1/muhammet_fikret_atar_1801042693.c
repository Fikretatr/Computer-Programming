#include<stdio.h>


int main()
{
	FILE * file = fopen ("file.txt", "r+");
	int i;
	int num;
	
	if(file == NULL)
   	{
      printf("Dosya a��lamad�..");   //a��lamazsa hata..          
   	}
   	int basamaks=1;
   	int j=0;
   	int yedek_num;
   	fpos_t position;
	while(1)
	{
		if (fscanf (file, "%d", &i) != 1) // dosya bitene kadar..
			break;
		fgetpos (file, &position); // bir sonraki say�dan ba�lamak i�in tutulur
		while(1)
		{
			if(fscanf(file, "%d", &num) != 1) // dosya bitene kadar benzerlik kontrol�..
				break;
			yedek_num = num; // basamak sayisini bulurken say� de�i�mesin diye..
			if(num<0)
			{
				yedek_num = -yedek_num;
				basamaks++; //"-" i�in..
			}
			if(i == num)
			{
				while(yedek_num>=10)// basamak sayisini bulmak..
				{
        			yedek_num=yedek_num/10;
        			basamaks++;
        		}
        		 
        		
        		fseek(file,-basamaks,SEEK_CUR); // oldu�u yerden basamak sayisi kadar geri gelir..
				while(j<basamaks)
				{
					fprintf(file, "%c",' '); // ve bo�lukla de�i�tirir
					j++;
				}
				fseek(file,0,SEEK_CUR);//di�er benzerlik var m� diye current pozisyona ayarlan�r..
				
			}
			basamaks=1;
			j=0;
			
		}
		fsetpos (file, &position); // bir sonraki say�dan ba�lamak i�in g�ncellenir
		
		
		
	}
	


  	fclose (file);        

	
}
