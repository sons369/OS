#define T_DIR 1  // Directory
#define T_FILE 2 // File
#define T_DEV 3  // Device
#define T_CS 4   // T_CS용 파일 번호

struct stat
{
  short type;        // Type of file
  int dev;           // File system's disk device
  uint ino;          // Inode number
  short nlink;       // Number of links to file
  uint size;         // Size of file in bytes
  uint addr[12 + 1]; // 일반 파일의 데이터블럭 주소를 담는 공간
  /*T_CS파일의 주소와 길이를 담을 공간, 32비트에 각각 24비트, 8비트를 담는다.*/
  struct cs
  {
    uint addr : 24,
        len : 8;
  } cs[12];
};
