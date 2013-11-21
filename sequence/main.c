#include <string.h>
#include <stdio.h>

typedef struct _seq {
	size_t position;
	size_t size;
	char *array;
} sequence;


void init(sequence * seq,char * dat)
{
	seq->array=dat;
	seq->size=strlen(dat);
	seq->position = 0x0000;
}

int get(sequence *seq)
{
	int ret = -1;
	if ( seq->position <= seq->size)
	{
		ret = seq->array[seq->position];
		if (seq->position < seq->size)
			seq->position++;
	}
	else
	{
		ret = -1;
		seq->position = seq->size;
	}
	return ret;
}
int unget(sequence *seq)
{
	int ret = -1;
	if (seq->position > 0 )
		seq->position--;
	ret = seq->position <= seq->size ?  seq->array[seq->position] : -1;
	return ret;
}
int main(int argc, char *argv[])
{
	char buffer[] = "(+ 1 2)";
	sequence s;
	int c;

	init(&s,buffer);
	//c = get(&s);
	while(c = get(&s))
	{
		printf("%c %d\n", c , c );
	}
	c = unget(&s);

	while(c = get(&s))
	{
		printf("%c %d\n", c , c );
	}

	return 0;
}