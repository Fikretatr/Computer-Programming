#include<stdio.h>
#include<math.h>
int main()
{
	FILE * f_values = fopen ("values.txt", "r+");
	FILE * f_poly= fopen("polynomial.txt","r+");
	FILE * f_evalu= fopen("evaluations.txt","w+");
	int i,j,number_of_Values=0,number_of_Poly=0 ;
	double val,power;
	if(f_values == NULL||f_poly ==NULL||f_evalu ==NULL)
   	{
      printf("Dosya açýlamadý..");   //this is error message which show failed opening input.txt or output.txt..        
   	}
	
	double values[100]; //for holds values which are in values.txt..
	char poly[1000]; //for holds chars which are in polynomial.txt..
	char c;
	for(i=0; i<100;i++)
	{
		if (fscanf (f_values, "%lf", &val) != 1) // until EOF..
			break;
		values[i]=val;
		number_of_Values++;//for holding # of values..
	}
	for(i=0;i<1000;i++)
	{
		if (fscanf (f_poly, "%c", &c) != 1) // until EOF..
			break;
		poly[i]=c;
		number_of_Poly++;//for holding # of chars that poly..
	}
	double sum=0;
	double coefficient;
	double sub_sum=0;
	char sign;
	int count=1;
	for(i=0;i<number_of_Values;i++)//first for run # of values times..
	{
		sum=0;
		for(j=0;j<number_of_Poly;j++)//inner loop run # run of not number_of_Poly it run only monomials time..
		{
			count=1;
			sub_sum=0;
			if(poly[j]=='x')
			{
				if(j!=0&&poly[j-1]=='-')//indicating sign..
					sign='-';
				else
					sign='+';
				if(poly[j+1]=='^')
					sscanf(poly+(j+2), "%lf", &power);//get power number..	
				else
					power=1;
				sub_sum=pow(values[i],power);//compute monomial..
				if(power==1)
				{
					count=-1;
				}
				while(power>=10)//compute digit number of power variable..
				{
					power=power/10;
					count++;
				}
				j+=(count+2);
				if(sign=='-')//finding sum...
					sum-=sub_sum;
				else
					sum+=sub_sum;
				
			}
			else
			{
				if(j==0&&poly[j]=='-'||poly[j]=='+')
					continue;
				if(j!=0&&poly[j-1]=='-')
					sign='-';
				else
					sign='+';	
				sscanf(poly+j, "%lf", &coefficient);//get coefficient variable..
				while(poly[j]!='x')
					j++;
				if(poly[j+1]=='^')
					sscanf(poly+(j+2), "%lf", &power);	
				else
					power=1;
				sub_sum=(pow(values[i],power)*coefficient);//compute monomial with coefficient..
				if(power==1)
					count=-1;	
				while(power>=10)
				{
					power=power/10;
					count++;
				}
				j+=(count+2);
				if(sign=='-')
					sum-=sub_sum;
				else
					sum+=sub_sum;
			}
		}
		fprintf(f_evalu,"%.2lf\n",sum);//write to files..
	}
	
	fclose (f_evalu);        
	fclose (f_poly);
	fclose (f_values);

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
	
