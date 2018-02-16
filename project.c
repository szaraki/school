#include <stdlib.h>
#include <stdio.h>
#include <png.h>



//
//   Program zmienia zdj stosując filtr( jako macierz),
// oraz wygładza obraz (antialiasing ). Aby móc go skompilować
// należy wgrać biblioteke libpng na urządzenie. Korzystałem z
// ang dokumentacji + tutoriala do filtrow.
//
//

typedef struct {
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;
} data;

data* load_png(char *filename) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  setjmp(png_jmpbuf(png));

  png_init_io(png, fp);

  png_read_info(png, info);
  
  data* file_data = malloc(sizeof(data));
  file_data->width      = png_get_image_width(png, info);
  file_data->height     = png_get_image_height(png, info);
  file_data->color_type = png_get_color_type(png, info);
  file_data->bit_depth  = png_get_bit_depth(png, info);

  if(file_data->bit_depth == 16)
    png_set_strip_16(png);

  if(file_data->color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(file_data->color_type == PNG_COLOR_TYPE_GRAY && file_data->bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(file_data->color_type == PNG_COLOR_TYPE_RGB ||
     file_data->color_type == PNG_COLOR_TYPE_GRAY ||
     file_data->color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(file_data->color_type == PNG_COLOR_TYPE_GRAY ||
     file_data->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  file_data->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * file_data->height);
  for(int y = 0; y < file_data->height; y++) {
    file_data->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, file_data->row_pointers);

  fclose(fp);
  return file_data;
}

/*
#not useful at the moment but it's working correctly
int det(int* matrix) {
  int sum=0;
  for(int x=0; x<3; x++) {
	int sum_temp=1;
	for(int m=0; m<3; m++) {
		if(x+m<3) {
		  sum_temp*=matrix[x+m+(3*m)];
		}
		else {
	  	  sum_temp*=matrix[x+m-3+(3*m)];
		}
	}
	sum+=sum_temp;
  }
  for(int x=0; x<3; x++) {
	int sum_temp=1;
	for(int m=0; m<3; m++) {
		if(x-m>=0) {
		  sum_temp*=matrix[x-m+(3*m)];
		}
		else {
	  	  sum_temp*=matrix[3+x-m+(3*m)];
		}
	}
	sum-=sum_temp;
  }
  return sum;
}
*/

void antialiasing(data* file_data) {
  for(int y = 0; y < file_data->height-3; y++) {
    png_bytep row = file_data->row_pointers[y+1];
    for(int x = 0; x < file_data->width-3; x++) {
      png_bytep px = &(row[(x+1) * 4]);
	  long sum;
	  for(int n=0; n<3; n++) {
		sum=0;
		for(int px_y=0; px_y<3; px_y++) {
		  for(int px_x=0; px_x<3; px_x++) {
			png_bytep row_temp = file_data->row_pointers[y+px_y];
            png_bytep px_temp = &(row_temp[(x+px_x) * 4]);
			sum+=px_temp[n];
		  }
		}
		px[n]=(png_uint_16)((int)(sum/9));
	  }
    }
  }
}


void filtr(data* file_data) {
  for(int y = 0; y < file_data->height; y++) {
    png_bytep row = file_data->row_pointers[y];
    for(int x = 0; x < file_data->width; x++) {
      png_bytep px = &(row[(x) * 4]);
	  int matrix[9]=   {1,0,0,
						0,1,0,
						0,1,2};
	  int a =matrix[0]*px[0]+matrix[1]*px[1]+matrix[2]*px[2];
	  int b =matrix[3]*px[0]+matrix[4]*px[1]+matrix[5]*px[2];
	  int c =matrix[6]*px[0]+matrix[7]*px[1]+matrix[8]*px[2];
	  if( a> 255) a=255;
	  if( b> 255) b=255;
	  if( c> 255) c=255;
	  px[0]=(png_uint_16)a;
	  px[1]=(png_uint_16)b;
	  px[2]=(png_uint_16)c;
    }
  }
}

void saving(char *filename, data* file_data) {
  int y;

  FILE *fp = fopen(filename, "wb");
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);

  setjmp(png_jmpbuf(png));

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR( png, info, file_data->width, file_data->height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);


  png_write_image(png, file_data->row_pointers);
  png_write_end(png, NULL);

  for(int y = 0; y < file_data->height; y++) {
    free(file_data->row_pointers[y]);
  }
  free(file_data->row_pointers);

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if(argc != 2) abort();

  data* file_data = load_png(argv[1]);
  filtr(file_data);
  saving("output_filtr.png", file_data);

  file_data = load_png(argv[1]);
  antialiasing(file_data);
  saving("output_anti.png", file_data);
  
  return 0;
}