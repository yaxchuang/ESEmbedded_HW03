int add(int a,int b,int c,int d)
{
	return a+b+c+d;
}

void reset_handler(void)
{
	int sum=0;
	sum=add(5,10,15,20);
	while (1)
	;
}
