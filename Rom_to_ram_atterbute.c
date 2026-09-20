#include "delay.h"
const char s[50]__attribute__((at(0x00000020)))=  "welcome";
char d[50]__attribute__((at(0x40000028)));
int main()
{
		int i;
		for(i=0;s[i];i++)
		{
			  delay_s(2);
		    d[i]=s[i];
		}
while(1);
}
