#include <stdio.h>
#include <unistd.h> //extern char ** environ;	/* Environment itself */

extern char ** environ;

int main()
{
	int i = 0;
	while(environ[i++] != NULL) {}
	--i;
	printf("Lenth of char ** environ array of string : %d\n", i);
	printf("environ[i-1] = %s\n", environ[i-1]);
	printf("environ[i] = %s\n", environ[i]);
	
	environ[i] = "MY_VAR_0=000";
	environ[++i] = "MY_VAR_1=777";
	environ[++i] = NULL;
	
	printf("Lenth of char ** environ array of string : %d\n", i);
	printf("environ[i-2] = %s\n", environ[i-2]);
	printf("environ[i-1] = %s\n", environ[i-1]);
	printf("environ[i] = %s\n", environ[i]);
		
	//light way: 
	//#include <system.h>
	//system("export MY_ENV_VAR_2=999"); system("echo $MY_ENV_VAR_2");
	//another way: #include <stdlib.h> //char * getenv (const char * name);
	//int setenv (const char * name, const char * value, int overwrite);
	
	return 0;
}