#include <stdio.h>
#include "ft_printf.h"

int main()
{
	ft_printf("====\ncheck 0\n====\n");
	ft_printf("%c",'0');
	printf("%c\n",'0');

	ft_printf("%s",NULL);
	printf("%s\n",NULL);

	ft_printf("%p",NULL);
	printf("%p\n",NULL);

	ft_printf("%d",0);
	printf("%d\n",0);

	ft_printf("%i",0);
	printf("%i\n",0);

	ft_printf("%u",0);
	printf("%u\n",0);

	ft_printf("%x",0);
	printf("%x\n",0);

	ft_printf("%X",0);
	printf("%X\n",0);


	ft_printf("====\ncheck c\n====\n");
	ft_printf("%c",97);
	printf("%c\n",97);

	ft_printf("%c",60);
	printf("%c\n",60);

	ft_printf("%c",259);
	printf("%c",259);

	ft_printf("%c",-1);
	printf("%c\n",-1);


	ft_printf("check s\n====\n");
	ft_printf("%s","");
	printf("%s\n","");
	
	ft_printf("%s"," ");
	printf("%s\n"," ");
	
	ft_printf("%s","a");
	printf("%s\n","a");
	
	ft_printf("%s","asddddddddddddddddf");
	printf("%s\n","asddddddddddddddddf");
	
	ft_printf("====\ncheck p\n====\n");
	
	ft_printf("%p\n","asddddddddddddddddf");
	printf("%p\n\n","asddddddddddddddddf");
	
	ft_printf("%p\n","");
	printf("%p\n\n","");
	
	char *s = "abc";
	ft_printf("%p\n",s);
	printf("%p\n\n",s);
	
	ft_printf("%p\n",&s);
	printf("%p\n\n",&s);
	
	ft_printf("====\ncheck d\n====\n");
	ft_printf("%d\n",123);
	printf("%d\n",123);
	
	ft_printf("%d\n",2147483647);
	printf("%d\n",2147483647);
	
	ft_printf("%d\n",-2147483648);
	//printf("%d\n",-2147483648);
	
	ft_printf("====\ncheck u\n====\n");
	ft_printf("%u\n",2147483647);
	printf("%u\n",2147483647);
	
	ft_printf("%u\n",4294967295);
	//printf("%u\n",4294967295);
	
	ft_printf("====\ncheck x\n====\n");
	ft_printf("%x\n",2147483647);
	printf("%x\n",2147483647);
	
	ft_printf("%x\n", 16);
	printf("%x\n", 16);
	
	ft_printf("%x\n", -16);
	printf("%x\n", -16);
	
	ft_printf("====\ncheck X\n====\n");
	ft_printf("%X\n",2147483647);
	printf("%X\n",2147483647);
	
	ft_printf("%X\n", 16);
	printf("%X\n", 16);
	
	ft_printf("%X\n", -16);
	printf("%X\n", -16);
	
	ft_printf("====\ncheck %%\n====\n");
	ft_printf("%%\n");
	printf("%%\n");
	
	ft_printf("====\ncheck combination\n====\n");
	ft_printf("%d %s %u %x%%\n",123,"abc",1111,123);
	printf("%d %s %u %x%%\n",123,"abc",1111,123);
	ft_printf("%X %x %u %p%%\n",123,0,1111,"123");
	printf("%X %x %u %p%%\n",123,0,1111,"123");
	ft_printf("%d %d %d %d %d %d %d\n",123,1111,123,1111,0,1255,66);
	printf("%d %d %d %d %d %d %d\n",123,1111,123,1111,0,1255,66);
	ft_printf("%c %c %c %c %c %c %c\n",123,1111,123,1111,0,1255,66);
	printf("%c %c %c %c %c %c %c\n",123,1111,123,1111,0,1255,66);
}
