#include <string.h>
#include <stdio.h>

#include <Windows.h>

#include "firmware.h"
#include "cbuffer.h"
#define TKBUFFERN 1024
char tkbuffer[TKBUFFERN];

#define GETC(x) circular_buffer_pop(x)

CircularBuffer g_cb;
int lreadf(CircularBuffer *f);
int flush_ws(CircularBuffer *f);
int lreadparen(CircularBuffer *f);
int lreadtk(long j);

DWORD WINAPI TestSleep(LPVOID lpParam)
{
     int c;
	while(1)
     {
          //if((c=circular_buffer_pop(&g_cb)) != 0) 
          //     printf("%d",c);
          //
          if(!circular_buffer_empty(&g_cb))
               lreadr(&g_cb);
    		//Sleep(5000);
     }

	return 0;
}

int lreadf(CircularBuffer *f)
{
    int c;
    c = flush_ws(f,(char *)NULL);
    if (c == EOF) return(-1);
    ungetc(c,f);
    return(lreadr(f));
}

int flush_ws(CircularBuffer *f)
{
    int c;
    while(1)
    {
        //c = getc(f);
        c = circular_buffer_pop(f);
        if (c == EOF) 
             return(c);
        if (isspace(c)) 
             continue;
        return(c);
    }
}

int lreadr(CircularBuffer *f)
{
    int c,j;
    char *p;
    c = flush_ws(f);
    switch (c)
    {
    case '(':
        return(lreadparen(f));
    case ')':
        printf("unexpected close paren\n");
    case '\'':
        lreadr(f);
    }
    p = tkbuffer;
    *p++ = c;
    for(j = 1; j<TKBUFFERN; ++j)
    {
        //c = getc(f);
        c = circular_buffer_pop(f);
        if (c == EOF) return(lreadtk(j));
        if (isspace(c)) return(lreadtk(j));
        if (strchr("()'",c))
        {
            //ungetc(c,f);
            circular_buffer_push(f,c);
            return(lreadtk(j));
        }
        *p++ = c;
    }
    //err("token larger than TKBUFFERN",NIL);
}

int lreadparen(CircularBuffer *f)
{
    int c;
    int tmp;
    c = flush_ws(f);
    if (c == ')') return(-1);
    ungetc(c,f);
    tmp = lreadr(f);
    return lreadparen(f);
}

int lreadtk(long j)
{
    //int k;
    char c,*p;
    p = tkbuffer;
    p[j] = 0;
    if (*p == '-') p+=1;
    {
        int adigit = 0;
        while(isdigit(*p))
        {
            p+=1;
            adigit=1;
        }
        if (*p=='.')
        {
            p += 1;
            while(isdigit(*p))
            {
                p+=1;
                adigit=1;
            }
        }
        if (!adigit) goto a_symbol;
    }
    if (*p=='e')
    {
        p+=1;
        if (*p=='-'||*p=='+') p+=1;
        if (!isdigit(*p)) goto a_symbol;
        else p+=1;
        while(isdigit(*p)) p+=1;
    }
    if (*p) goto a_symbol;
    return 0;
a_symbol:
    return 0;
}

DWORD WINAPI TestWait(LPVOID lpParam)
{
	while(1)
     {
          Sleep(5000);
     }

	return 0;
}

int main(void)
{
	HANDLE  hThread;
	ULONG   id;
	INT     res;
     int     c;
     circular_buffer_init(&g_cb);	

     
	hThread= CreateThread(NULL, 0, TestSleep, NULL, 0, &id);
	/* Sleep for a while; then send an APC to hThread */
	//Sleep(100);
	
	
     /*
	hThread= CreateThread(NULL, 0, TestWait, NULL, 0, &id);
	Sleep(5000);
	WaitForSingleObject(hThread, INFINITE);
     */
     while(c = getchar())
     {
          circular_buffer_push(&g_cb,c);
     }
     WaitForSingleObject(hThread, INFINITE);
	return 0;
}

/*
int main(int argc, char *argv[])
{
	//char buffer[] = "(+ 1 2)";
	sequence s;
	int c;

	init(&s,firmware,sizeof(firmware));
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


*/