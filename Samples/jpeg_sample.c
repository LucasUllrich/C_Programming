/**
* Simple example program that uses libjpeg to illustrate reading and writing
* a JPEG image. the program essentially prints out the values of a pixel at
* a given coordinate.
*
* Compilation: gcc -Wall -ljpeg jpeg_demo.c -o jpeg_demo
* Usage: ./jpeg_demo infile.jpg outfile.jpg 0 0
*
* M. Horauer
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <C:\libjpeg-turbo-gcc\include\jpeglib.h>

/*************************************************************** Prototypes ***/
int read_jpeg_file(char *fname, unsigned char **raw_image, int *width, \
                   int *height, int *bytes_per_pixel);
void read_image_data (struct jpeg_decompress_struct * pCinfo, \
                      unsigned char * raw_image);
void print_pixel(unsigned char *img, int width, int height, int bpp, \
                 int x, int y);
int write_jpeg_file(char *fname,unsigned char *raw_image, int width, \
                    int height, int bytes_per_pixel);

/**************************************************************** Functions ***/

/**
* read_jpeg_file() Reads from a jpeg file on a disk specified by filename and
* saves them into the raw_image buffer in an uncompressed format.
*
* \returns positive integer if successful, -1 otherwise
* \param *fname char string specifying the file name to read from
*
*/
int read_jpeg_file(char *fname, unsigned char **raw_image, int *width, \
                   int *height, int *bytes_per_pixel)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * pFile;

  pFile = fopen( fname, "rb" );
  if ( pFile == NULL )
    perror("Error opening jpeg file!" );
  cinfo.err = jpeg_std_error( &jerr );
  jpeg_create_decompress( &cinfo );
  jpeg_stdio_src( &cinfo, pFile );
  jpeg_read_header( &cinfo, TRUE );
  *width = cinfo.image_width;
  *height = cinfo.image_height;
  *bytes_per_pixel = cinfo.num_components;
  jpeg_start_decompress( &cinfo );
  *raw_image = (unsigned char*)malloc(cinfo.output_width * \
                                     cinfo.output_height * \
                                     cinfo.num_components);
  read_image_data(&cinfo, *raw_image);
  jpeg_finish_decompress( &cinfo );
  jpeg_destroy_decompress( &cinfo );
  fclose( pFile );
  return 1;
}

/**
* read_image_data() Reads image pixel data and stores it in rawdata
*
* \returns positive integer if successful, -1 otherwise
* \param *filename char string specifying the file name to save to
*
*/
void read_image_data (struct jpeg_decompress_struct * pCinfo, \
                      unsigned char * raw_image)
{
  unsigned long location = 0;
  int i = 0;
  JSAMPROW row_pointer[1];

  row_pointer[0] = (unsigned char *)malloc(pCinfo->output_width * \
                                           pCinfo->num_components);

  while(pCinfo->output_scanline < pCinfo->image_height)
  {
    jpeg_read_scanlines(pCinfo, row_pointer, 1);
    for( i=0; i<pCinfo->image_width*pCinfo->num_components; i++)
      raw_image[location++] = row_pointer[0][i];
  }
  free(row_pointer[0]);
}

/**
* print_pixel() prints the values of a pixel at a given coordinate starting
* from the top-left corner.
*/
void print_pixel(unsigned char *img, int width, int height, int bpp, \
                 int x, int y)
{
  int r = -1;
  int g = -1;
  int b = -1;

  r = *(img+bpp*(y*width+x));
  g = *(img+bpp*(y*width+x)+1);
  b = *(img+bpp*(y*width+x)+2);
  assert(x<width);
  assert(y<height);
  printf("RGB value at [%d/%d] is %d %d %d\n",x,y,r,g,b);
}


/**
* write_jpeg_file Writes the raw image data stored in the raw_image buffer
* to a jpeg image with default compression and smoothing options in the file
* specified by *filename.
*
* \returns positive integer if successful, -1 otherwise
* \param *filename char string specifying the file name to save to
*
*/
int write_jpeg_file(char *fname,unsigned char *raw_image, int width, \
                    int height, int bytes_per_pixel)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  int color_space = JCS_RGB; /* or JCS_GRAYSCALE for grayscale images */
  JSAMPROW row_pointer[1];
  FILE *pFile;

  pFile = fopen( fname, "wb" );
  if ( pFile == NULL )
    perror("Error opening output jpeg file.");
  cinfo.err = jpeg_std_error( &jerr );
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, pFile);

  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = bytes_per_pixel;
  cinfo.in_color_space = color_space;
  jpeg_set_defaults( &cinfo );
  cinfo.num_components = 3;
  cinfo.dct_method = JDCT_FLOAT;
  jpeg_set_quality(&cinfo, 80, TRUE);  /* you may set the output quality here */
  jpeg_start_compress( &cinfo, TRUE );
  while(cinfo.next_scanline < cinfo.image_height)
  {
    row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * \
                                cinfo.input_components];
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress( &cinfo );
  jpeg_destroy_compress( &cinfo );
  fclose( pFile );
  return 1;
}

/**
* The main() routine simply reads and decompresses a JPEG file and stores the
* data in the RAM. Next, it prints the RGB values at a given position before it
* finally writes the output data to an output image.
*/
int main(int argc, char *argv[])
{
  int width = 640;
  int height = 480;
  int bytes_per_pixel = 3;
  unsigned char *raw_image = NULL;

  assert(argc==5);
  if(read_jpeg_file(argv[1],&raw_image,&width, &height, &bytes_per_pixel) > 0)
  {
    print_pixel(raw_image,width,height,bytes_per_pixel, \
                atoi(argv[3]),atoi(argv[4]));
    if(write_jpeg_file(argv[2],raw_image,width,height,bytes_per_pixel) < 0)
      return -1;
  }
  else
    return -1;
  return 0;
}

/** EOF */