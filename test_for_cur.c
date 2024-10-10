#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <locale.h>
#include <conio.h>
//#define SIZE 100000
char *mont[]= {"JAN", "FEB", "MAR", "APR", "MAY", "YUN", "YUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
 struct sensor
 {
     uint16_t year;
     uint8_t month;
     uint8_t day;
     uint8_t hour;
     uint8_t minute;    
     int8_t t;
 };


void print_out(struct sensor* info, int number)
{
    printf("========================\n");
    for(int i=0;i<number; i++)
            printf("%04d/%02d/%02d %02d:%02d t=%3d\n",
            info[i].year,
            info[i].month,
            info[i].day,
            info[i].hour,
			info[i].minute,
            info[i].t);
     printf("========================\n");
}
void add_record(struct sensor* info , int number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, int8_t t )
{
	info[number].year=year;
	info[number].month=month;
	info[number].day=day;
	info[number].hour=hour;
	info[number].minute=minute;
	info[number].t=t;
}
int add_info(struct sensor* info)
{
int counter =0;
add_record(info, counter++,2023,11,16,0,0,19);
add_record(info, counter++,2021,9,16,0,0,8);
add_record(info, counter++,2021,9,16,0,0,-18);
add_record(info, counter++,2021,9,16,0,0,9);
add_record(info, counter++,2021,10,16,0,0,22);
add_record(info, counter++,2021,8,16,0,0,-1);
add_record(info, counter++,2022,9,16,0,0,-5);
add_record(info, counter++,2022,7,16,0,0,8);
return counter;
}

void change_i_j(struct sensor* info , int i, int j) //сортировка замена местами
{
    struct sensor temp;
    temp= info[i];
    info[i]=info[j];
    info[j]=temp;
}
uint32_t date_to_int(struct sensor* info)
{return (info->year<<16)|(info->month<<8)|info->day;}
 
 void sort_by_t(struct sensor* info , int number)// сортировка по температуре 
{
for(int i=0; i<number; i++)
    for(int j=i; j<number;j++)
        if(info[i].t>=info[j].t)
            change_i_j(info, i, j);
}
 void sort_by_date(struct sensor* info , int number)// сортировка по дате 
{
for(int i=0; i<number; i++)
    for(int j=i; j<number;j++)
        if(date_to_int(info+i)>=date_to_int(info+j))
            change_i_j(info, i, j);
}


 void sort_by_month(struct sensor* info , int number)// сортировка по месяцам в поряд возраст
{
for(int i=0; i<number; i++)
    for(int j=i; j<number;j++)
        if(info[i].month>=info[j].month)
            change_i_j(info, i, j);
}
float find_by_aver_mont(struct sensor* info , int number, int mon, int yea)// поиск среднеквадратич за месяц
{
uint32_t count=0;
float sum=0.0;
float rez=0;
for(int i=0; i<number; i++)
        if(info[i].month==mon && info[i].year==yea )
            {count++;
			sum=sum+info[i].t;
             }
rez=sum/count;            
return rez;    
}
int find_by_min_mont(struct sensor* info , int number, int mon, int yea)// поиск среднеквадратич за месяц
{
int min=99;//struct sensor tempinfo;
for(int i=0; i<number; i++)
{
  if(info[i].month==mon && info[i].year==yea)
	{
	if(info[i].t < min)
	min=info[i].t;
	}
}//for
return min;           
}
int find_by_max_mont(struct sensor* info , int number, int mon, int yea)// поиск среднеквадратич за месяц
{
int max=-99;//struct sensor tempinfo;
for(int i=0; i<number; i++)
{
  if(info[i].month==mon && info[i].year==yea)
	{
	if(info[i].t > max)
	max=info[i].t;
	}
}//for
return max;           
}
float find_by_aver_year(struct sensor* info , int number, int yea)// поиск среднеквадратич за год
{
uint32_t count=0;
float sum=0.0;
float rez=0;
for(int i=0; i<number; i++)
        if(info[i].year==yea)
            {count++;
			sum=sum+info[i].t;
             }
rez=sum/count;            
return rez;    
}
int find_by_min_year(struct sensor* info , int number, int yea)// поиск среднеквадратич за год
{
int min=99;//struct sensor tempinfo;
for(int i=0; i<number; i++)
{
  if(info[i].year==yea)
	{
	if(info[i].t < min)
	min=info[i].t;
	}
}//for
return min;           
}
int find_by_max_year(struct sensor* info , int number, int yea)// поиск среднеквадратич за год
{
int max=-99;//struct sensor tempinfo;
for(int i=0; i<number; i++)
{
  if(info[i].year==yea)
	{
	if(info[i].t > max)
	max=info[i].t;
	}
}//for
return max;           
}
float find_by_aver_mont_all_year(struct sensor* info, int number, int m)
{
	sort_by_date(info, number);	//sort by year then every year aver by month
	uint32_t count=0;
float sum=0.0;
float rez=0;
for(int i=0; i<number; i++)
        if(info[i].month==m)
            {count++;
			sum=sum+info[i].t;
             }
rez=sum/count;            
return rez;    

	//printf("\n");
	m=m+0.0;
	return m;
	}


void print_month(struct sensor* info, int number, int mon)
{
    printf("****************************\n");
    //char tt;
    for(int i=0;i<number; i++)
            {if(info[i].month==mon)
				{//enum number_month tt = mon;
					//printf("%c", tt);
				printf("* %s  ", mont[(info[i].month)-1]);
				printf("%04d-%02d %02d:%02d t=%3d *\n",
				info[i].year,
				info[i].day,
				info[i].hour,
				info[i].minute,
				info[i].t);}
            else if (mon==0)
            printf("%04d-%02d-%02d %02d:%02d t=%3d\n",
            info[i].year,
            info[i].month,
            info[i].day,
            info[i].hour,
			info[i].minute,
            info[i].t);
            }
     printf("****************************\n");
}
void print_file(const char *filename)
{
	int N=6;
	FILE *open;
//char *name[]=filename;
open=fopen(filename, "r");
if(open!=NULL)
{
int Y,M,D,H,I,t;
int r;
int count_line=0;
char ch=0;
while((r=fscanf(open,"%d;%d;%d;%d;%d;%d", &Y,&M,&D,&H,&I,&t))>0)
{
	count_line++;
if(r<N)	
	{
		do
		{
			putchar(ch);
			ch=fgetc(open);
		}while(EOF!=ch && '\n'!=ch);
		ch=0;
		printf("  ");
		printf("error in line = %d ", count_line);
		printf("\n");
	}
	else
	printf("%d = %d/%d/%d %d:%d t=%d\n", count_line,Y,M,D,H,I,t);
}
}
else printf("file not open!");
	
	
	}
	
int read_file(const char *filename, struct sensor* info)
{
	int count=0;
	int count_line=0;
	int N=6; //struct number
	FILE *open;
//char *name[]=filename;
open=fopen(filename, "r");
if(open!=NULL)
{
int Y,M,D,H,I,t;
int r;
char ch=0;
while((r=fscanf(open,"%d;%d;%d;%d;%d;%d", &Y,&M,&D,&H,&I,&t))>0)
{
	count_line++;
if(r<N)	
	{
		do
		{
			putchar(ch);
			ch=fgetc(open);
		}while(EOF!=ch && '\n'!=ch);
		ch=0;
		printf("  ");
		printf("error in line = %d ", count_line);
		printf("\n");
	}
	else
	//printf("%d = %d/%d/%d %d:%d t=%d\n", count_line,Y,M,D,H,I,t);
   add_record(info,count++,Y,M,D,H,I,t);
}
}
else printf("file not open!");
	
	return count;
	}

int main(int argc, char *argv[])
{
setlocale(LC_ALL, "");
//uint64_t SIZE=100000;
//ru_RU.UTF-8");
//struct sensor info[SIZE];
struct sensor *info=malloc(sizeof *info);
//int number = add_info(info);
int number =0;
int menu_func='1';
while ( (menu_func = getopt(argc,argv,"hf:y:m:x:a:i:p")) != -1)
{
switch (menu_func)
    {
case 'f' :
    char* f=optarg;
    if(f!=NULL)
   {// printf("%s",f);
    //char * input_fn = "temerature_small.csv";
//char *input_fn =(f);
 //printf("%s", f);
 //printf("\n");
 //print_file(f);
 number=read_file(f, info);
 printf("\n");
	}
    printf("\n");
    break;
case 'y' :
    int y=atoi(optarg);
    //printf("\naverege temp of year %d %5.2f", y, find_by_aver_year(info, number, y));
    printf("\n");
    break;
case 'm' :
    int m=atoi(optarg);
    if(y!=0){
    printf("averege temp of month %s %5.2f", mont[m-1], find_by_aver_year(info, number, y));
    }
    else {
		printf("averege temp of month for all years %s %5.2f", mont[m-1], find_by_aver_mont_all_year(info, number, m));
		//printf("have not year in key");
		}
    printf("\n");
    break;    

case 'a' : //find averege
    int a=atoi(optarg);
    if(a>=1900)
    printf("\naverege temp of year %d %5.2f", a, find_by_aver_year(info, number, a));
    if(a>0 && a<13)
     {
		if(y==0)
			{printf("have not year in key");
		 	}
		else printf("averege temp of month %s year %d %5.2f", mont[a-1],y, find_by_aver_mont(info, number, a, y));	
	  }
    printf("\n");
    break;
case 'i' : //find minimum
    int i=atoi(optarg);
    if(i>12)
		{if(find_by_min_year(info, number, i)!=99)
		printf("\nminimum temp of year %d %d", y, find_by_min_year(info, number, i));
		else
		printf("\nminimum temp of year %d - have not date",i);
		}
    if(i<=12 && i>0)
		{
		
		if(y==0)
			{printf("have not year in key");
		 printf("\n");
		 break;	}
		if (find_by_min_mont(info, number, i, y)!=99)
		printf("\nminimum temp of month %s year %d %d", mont[i-1], y, find_by_min_mont(info, number, i, y) );
		else printf("\nminimum temp of month %s - have not date", mont[i-1]);
		}
	printf("\n");
    break;
case 'x' : //find maximum
    int x=atoi(optarg);
    if(x>12)
		{if(find_by_max_year(info, number, x)!=-99)
			printf("\nmaximum temp of year %d %d", x, find_by_max_year(info, number, x));
		else 
		printf("\nmaximum temp of year %d - have not date",x);
		}
    if(x<=12 && i>0)
		{
			if(y==0)
			{printf("have not year in key");
		printf("\n");
		break;}
		if(find_by_max_mont(info, number, x, y)!=-99)
		printf("\nmaximum temp of month %s year %d %d", mont[x-1], y, find_by_max_mont(info, number, x, y) );
		else
		printf("\nmaximum temp of month %s - have not date", mont[x-1]);
		}
        //printf("\nmaximum temp of month %s %d", mont[x-1], find_by_max_mont(info, number, x));
    printf("\n");
    break;    
case 'h' :
    printf("\nHelp\n");
    printf("-h помощь\n");
    printf("-m:(1-12) month среднее значение температуры,по месяцу если указан год, то года -y \n");
    printf("-y(xxxx) year год  обязательно для расчетов по месяцам\n");
    printf("-a(xxxx) среднее значение температуры, если >1900 - расчет средней температуры за год\n");
	printf("-a(xx) среднее значение температуры, если до 12 - в месяце года -y(xxxx) \n");
    printf("-i(>1900) min за год, если до 12 то за месяц(1-12) года -y(xxxx) \n");
    printf("-x(>1900) max за год, если до 12 то за месяц(1-12) года -y(xxxx) \n");
    printf("example: -ffilename -y2021 -m9 \n");
    printf("example: -ffilename -a2021 \n");
    printf("example: -ffilename -y2021 -i12 \n");
    printf("-p печать всего\n"); // + -s сортировка по год или мес
    printf("\n");
    break;
case 'p':
	sort_by_date(info, number);
	print_out(info, number);
	break;
case '?': 
    printf("Error found ! Type -h\n");
    printf("\n");
    break;
default:
	printf("\nHelp\n");// hy:f:m:x:a:i:ps
    printf("-h помощь\n -m(1-12) month -y(xxxx) year\n ");
    printf("-x(1-12) -x(xxxx) max \n");
    printf("-a(1-12) -a(xxxx) aver\n");
    printf("-i(1-12) -i(xxxx) min \n ");
    printf("example: -y2021 -m9 -ffilename\n");
    printf("-p print -f(ffffff.fff) file \n");
    printf("\n");
    break;
  
    } //switch
} //while




//sort_by_t(info, number);
//sort_by_month(info, number);
//print_out(info, number);
//printf("averege of month %f", find_by_aver_mont(info, number, 9));
//printf("\n");
//printf("averege of year %f", find_by_aver_year(info, number,2022));
//printf("\n");
//print_month(info, number, 9);
//printf("\n min= %d",find_by_min_mont(info, number, 9));
//printf("\n max= %d",find_by_max_mont(info, number, 9));
//printf("\n%s",mont[9]);
//for (int i=ret_nam_mon(9);i>;i++)


//char * input_fn = "temerature_small.csv";
//char * output_fn = "output.txt";
//char line[line_size];
//FILE *fp;
// fp = fopen(input_fn, "r");
// fscanf(fp, "%[^\n]", line);
// fclose(fp);
// change_symbols(strlen(line),line);

// fp = fopen(output_fn, "w");
 //fprintf(fp, "%s", line);
 //fclose(fp);
//printf("\n");
free(info);
return 0;
}
