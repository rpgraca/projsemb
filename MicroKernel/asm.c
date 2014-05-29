/* Para ver o funcionamento do compilador.
 * Compilar com "avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328 -o asm.asm asm.c -S -O0"
 * Saida em assembly em asm.asm */

//int funcA(int x) __attribute__((naked));
int funcA(int x)
{
	int z;
	z=2000;
	return x+z;
}

int main()
{
	int x;
	x=funcA(1000);

	asm volatile("add r2,r4\n\t"
				"add r4,r5");
	while(x)
	{

	}
	return 1;
}
