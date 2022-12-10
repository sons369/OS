#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char *
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while ((*s++ = *t++) != 0)
    ;
  return os;
}

int strcmp(const char *p, const char *q)
{
  while (*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint strlen(const char *s)
{
  int n;

  for (n = 0; s[n]; n++)
    ;
  return n;
}

void *
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char *
strchr(const char *s, char c)
{
  for (; *s; s++)
    if (*s == c)
      return (char *)s;
  return 0;
}

char *
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for (i = 0; i + 1 < max;)
  {
    cc = read(0, &c, 1);
    if (cc < 1)
      break;
    buf[i++] = c;
    if (c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if (fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int atoi(const char *s)
{
  int n;

  n = 0;
  while ('0' <= *s && *s <= '9')
    n = n * 10 + *s++ - '0';
  return n;
}

void *
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while (n-- > 0)
    *dst++ = *src++;
  return vdst;
}

// void printinfo(int fd, char *fname)
// {
//   struct stat fs;
//   int tmp;

//   if ((tmp = fstat(fd, &fs)) != 0)
//   {
//     printf(2, "fstat error!\n");
//     exit();
//   }
//   /*파일 정보를 fstat로 받아와서 출력해주기*/
//   printf(1, "FILE NAME: %s\nINODE NUM: %d\n", fname, fs.ino);
//   if (fs.type == T_FILE)
//     printf(1, "FILE TYPE: %s\n", "FILE");
//   else if (fs.type == T_CS)
//     printf(1, "FILE TYPE: %s\n", "CS");
//   printf(1, "FILE SIZE: %d Bytes\n", fs.size);
//   printf(1, "DIRECT BLOCK INFO:\n");
//   if (fs.type == T_FILE)
//   {
//     for (int i = 0; i < 12 && fs.addr[i]; i++)
//     {
//       printf(1, "[%d] %d\n", i, fs.addr[i]);
//     }
//   }
//   else if (fs.type == T_CS)
//   {
//     for (int i = 0; i < 12 && fs.cs[i].len; i++)
//     {
//       printf(1, "[%d] %d (num: %d, length: %d)\n", i, fs.addr[i], fs.cs[i].addr, fs.cs[i].len);
//     }
//   }
// }