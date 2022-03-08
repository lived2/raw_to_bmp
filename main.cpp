#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
  FILE *f;
  unsigned char *img = NULL;
  unsigned char *bmp = NULL;
  int w = 1088, h = 2316;
  int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
#if 0
  int r, g, b;

  img = (unsigned char *)malloc(3*w*h);
  memset(img,0,3*w*h);

  for(int i=0; i<w; i++)
  {
    for(int j=0; j<h; j++)
    {
      x=i; y=(h-1)-j;
      r = red[i][j]*255;
      g = green[i][j]*255;
      b = blue[i][j]*255;
      if (r > 255) r=255;
      if (g > 255) g=255;
      if (b > 255) b=255;
      img[(x+y*w)*3+2] = (unsigned char)(r);
      img[(x+y*w)*3+1] = (unsigned char)(g);
      img[(x+y*w)*3+0] = (unsigned char)(b);
    }
  }
#endif

  if (argc != 4) {
    printf("Usage:%s W H <filename>\n", argv[0]);
    return 0;
  } else {
    w = atoi(argv[1]);
    h = atoi(argv[2]);
  }

  filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

  img = (unsigned char *)malloc(4*w*h);
  bmp = (unsigned char *)malloc(3*w*h);

  FILE *f_raw = fopen(argv[3], "r");

  //printf("sizeof(img)=%ld\n", sizeof(img));
  fread(img, sizeof(char), 4*w*h, f_raw);

  /*
  printf("img[0] = %x\n", img[0]);
  printf("img[1] = %x\n", img[1]);
  printf("img[2] = %x\n", img[2]);
  printf("img[3] = %x\n", img[3]);
  */

  int img_size = w * h;
  for (int i = 0; i < img_size; i++) {
    bmp[i*3] = img[i*4+2];
    bmp[i*3+1] = img[i*4+1];
    bmp[i*3+2] = img[i*4];
  }

  fclose(f_raw);

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(       w    );
  bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
  bmpinfoheader[ 6] = (unsigned char)(       w>>16);
  bmpinfoheader[ 7] = (unsigned char)(       w>>24);
  bmpinfoheader[ 8] = (unsigned char)(       h    );
  bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
  bmpinfoheader[10] = (unsigned char)(       h>>16);
  bmpinfoheader[11] = (unsigned char)(       h>>24);

  int len = strlen(argv[3]);
  //printf("len=%d\n", len);
  char new_filename[len+1];
  strcpy(new_filename, argv[3]);
  new_filename[len-3] = 'b';
  new_filename[len-2] = 'm';
  new_filename[len-1] = 'p';
  new_filename[len] = '\0';
  //printf("new=%s\n", new_filename);
  //f = fopen("img.bmp","wb");
  f = fopen(new_filename,"wb");
  fwrite(bmpfileheader,1,14,f);
  fwrite(bmpinfoheader,1,40,f);
  for(int i=0; i<h; i++)
  {
    //fwrite(img+(w*(h-i-1)*3),3,w,f);
    fwrite(bmp+(w*(h-i-1)*3),3,w,f);
    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
  }

  fclose(f);
  free(img);
}
