//seg_test.c
#include "seg.h"
#include "types.h"
int main()
{
	u32 i;
	f32 f;
	Init_7seg();
	for(f=0.0; f<=9.9; f+=0.1)
	{
		
		disp_2fmux_7seg(f);
	}
	
	for(i=0; i<100; i++)
	{
		disp_2mux_7seg(i);
	}
  while(1);
}
