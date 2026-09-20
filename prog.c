int main()
{
	int n=123,h=0,sh=0,rem;
	while(n)
	{
		rem=n%10;
		if(rem>h)
		{
			sh=h;
			h=rem;
		}
		else if(rem>sh && rem!=h)
		{
			sh=rem;
		}
		n=n/10;
	}
	
	
}
