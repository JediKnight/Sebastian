#include <stdio.h>

typedef struct { int w, h; } Size;

Size GetJpegSize(const char *jpg)
{
  Size ret = { 0, 0 };
  unsigned char buf[8];
  FILE *f = fopen(jpg, "rb");

  while (f && fread(buf, sizeof(buf[0]), 2, f) == 2 && buf[0] == 0xff)
    {
      if (buf[1] == 0xc0 && fread(buf, sizeof(buf[0]), 7, f) == 7)
	{
	  ret.h = buf[3] * 256 + buf[4];
	  ret.w = buf[5] * 256 + buf[6];
	}
      else if (buf[1] == 0xd8 || (fread(buf, sizeof(buf[0]), 2, f) == 2 &&
				  !fseek(f, buf[0] * 256 + buf[1] - 2, SEEK_CUR))) continue;
      break;
    }

  if (f) fclose(f);

  return ret;
}

int main(int argc, char *argv[])
{
  int i;

  if (argc < 2) return -1;

  for (i = 1; i < argc; i++)
    {
      Size sz = GetJpegSize(argv[i]);
      printf("%s: %d, %d\n", argv[i], sz.w, sz.h);
    }
  return 0;
}
