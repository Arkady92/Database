#include <stdio.h>

int main (int argc, char **argv)
{
  FILE *fp = NULL;
  fpos_t length;
  char* text;
  char buf[100];
  if (argc != 2) {
    printf ("Usage: %s <file_name>\n", argv[0]);
    return 1;
    }
  if ((fopen_s(&fp,argv[1],"r"))) {
    printf ("Error in opening file: %s!\n", argv[1]);
    return 1;
    }
  while ((text = fgets(buf,100,fp)) != NULL)
  {
	  fputs(text,stdout);
  }
  fseek (fp, 0, SEEK_END);
  fgetpos (fp, &length);
  printf ("\nSize of file: %d\n", length);
  fclose (fp);
  return 0;
}