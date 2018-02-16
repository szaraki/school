#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <math.h>



//
//   Program się włącza po dodaniu argumentu input_file.png
//  Przykład: project.o plik.png
//
//   Program zmienia zdj stosując filtr( jako macierz),
// oraz wygładza obraz (antialiasing ). Aby móc go skompilować
// należy wgrać biblioteke libpng na urządzenie. Korzystałem z
// ang dokumentacji + tutoriala do filtrow.
//
//   Przy pisaniu filtra należy dawać 0 albo 1, ponieważ są to najbardziej
//  oczekiwane rozwiązania.
//
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


void merge(data* file_data_a, data* file_data_b, int start_x, int start_y, int scale) {
  for(int y = start_y; y < file_data_a->height && y < file_data_b->height ; y++) {
    png_bytep row_a = file_data_a->row_pointers[y];
    png_bytep row_b = file_data_b->row_pointers[y];
    for(int x = start_x; x < file_data_a->width && x < file_data_b->width ; x++) {
      png_bytep px_a = &(row_a[(x) * 4]);
      png_bytep px_b = &(row_b[(x) * 4]);
	  for( int n= 0; n< 3; n++) {
		px_a[n]= (px_a[n]*(100-scale)+px_b[n]*(scale))/100; 
	  }
	}
  }
}

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


void filtr(data* file_data, int matrix[9]) {
  for(int y = 0; y < file_data->height-3; y++) {
    png_bytep row = file_data->row_pointers[y];
    for(int x = 0; x < file_data->width-3; x++) {
      png_bytep px = &(row[(x) * 4]);
//	  int matrix[9]=   {1,0,0,
//						0,1,0,
//						0,1,2};

	  int arr[3];
	  for(int n=0; n<3; n++) {
        arr[n] =matrix[3*n]*px[0]+matrix[3*n+1]*px[1]+matrix[3*n+2]*px[2];
	    if( arr[n]> 255) arr[n]=255;
	  }
	  
	  px[0]=(png_uint_16)(arr[0]);
	  px[1]=(png_uint_16)(arr[1]);
	  px[2]=(png_uint_16)(arr[2]);
    }
  }
}

void depth(data* file_data) {
  for(int y = 0; y < file_data->height-3; y++) {
    png_bytep row = file_data->row_pointers[y];
    for(int x = 0; x < file_data->width-3; x++) {
      png_bytep px = &(row[(x) * 4]);
	  int matrix[9]=   {1000,0,0,
						0,1000,0,
						0,0,1000};
						
	  int arr[3];
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
        arr[n] =matrix[3*n]*px[0]+matrix[3*n+1]*px[1]+matrix[3*n+2]*px[2];
		arr[n]/=sum;
	    //if( arr[n]> 255) arr[n]=255;
	  }
	  
	  px[0]=(png_uint_16)(arr[0]);
	  px[1]=(png_uint_16)(arr[1]);
	  px[2]=(png_uint_16)(arr[2]);
    }
  }
}

void delate_one_of_rgb(int color, data* file_data) {
  for(int y = 0; y < file_data->height-3; y++) {
    png_bytep row = file_data->row_pointers[y];
    for(int x = 0; x < file_data->width-3; x++) {
      png_bytep px = &(row[(x) * 4]);
	  px[color]=0;
	}
  }
}

//próba zrobienia http://www.algorytm.org/przetwarzanie-obrazow/histogram.html

int** histogram( data* file_data) {
  //init
  png_bytep px = &(file_data->row_pointers[0][0]);
  int** histogram_arr;
  histogram_arr= malloc(3*sizeof(int*));
  int max[3];
  for( int n=0; n< 3; n+=1) {
	max[n] = pow(2, sizeof(px));
	printf("%f", max[n]);
	printf("%lf\n", pow(2, sizeof(px)));
    histogram_arr[n]= malloc(max[n]*sizeof(int));
	for( int m= 0; m< max[n]; m+=1) {
		histogram_arr[n][m]= 0;
	}
  }
  //add data
  for(int y = 0; y < file_data->height-3; y++) {
    png_bytep row = file_data->row_pointers[y];
    for(int x = 0; x < file_data->width-3; x++) {
      png_bytep px = &(row[(x) * 4]);
	  for( int n= 0; n< 3; n+=1) {
		  histogram_arr[n][px[n]]+=1;
	  }
	}
  }
  
  //end
  return histogram_arr;
}
void histogram_equalization(data* file_data, int** histogram_arr ) {
  int max = pow(2, 16);
  float** LUT = malloc(3* sizeof(float*));
  int s= file_data->width* file_data->height;
  for( int n= 0; n<3; n+=1) {
	LUT[n]= malloc(max* sizeof(float));  
  }
  
  int min_index[3]={0,0,0};
  long histogram[3]={0,0,0};
  for( int n= 0; n<3; n+=1) { 
    for( int x = 0; x < max; x++) {
	  histogram[n]+=histogram_arr[n][x];
	  LUT[n][x]=(float)histogram_arr[n][x]/s;
	  if( LUT[n][min_index[n]] > LUT[n][x]) {
	    min_index[n]=x;  
	  }
    }
  }/*
  printf("test");
  for( int n= 0; n<3; n+=1) { 
    float min= LUT[n][min_index[n]];
    for( int x = 0; x < max; x++) {
	 // LUT[n][x]= (((float)LUT[n][x] - min) / (1. - min)) * (5); 
	}
  }*/
  
  free(LUT);
  
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
  int** histogram_arr= histogram(file_data);
  histogram_equalization(file_data, histogram_arr);
  
  printf("Do you want antialiasing? [y/n]:");
  char c;
  scanf("%c", &c);
  if(  c == 'y') {
	antialiasing(file_data);
  }
  
  printf("Do you want filr? [y/n]:");
  //clear buffer
  while ((c = getchar()) != '\n' && c != EOF) { }
  scanf("%c", &c);
  if(  c == 'y') {
	int filtr_arr[9];
	printf("Enter 9 int of your filtr\n");
	for( int n= 0; n< 9; n++) {
	  scanf("%d", filtr_arr+n);
	}
    filtr(file_data, filtr_arr);
  }
  printf("Do you want depth? [y/n]:");
  //clear buffer
  while ((c = getchar()) != '\n' && c != EOF) { }
  scanf("%c", &c);
  if(  c == 'y') {
    depth(file_data);
  }
  printf("Do you want to merge? [y/n]:");
  //clear buffer
  while ((c = getchar()) != '\n' && c != EOF) { }
  scanf("%c", &c);
  if(  c == 'y') {
	printf("Enter the name of another file.png: ");
	char name[100];
	scanf("%s", name);
	data* file_data_b= load_png(name);
	int start_x;
	printf("Enter starting position x: ");
	scanf("%d", &start_x);
	int start_y;
	printf("Enter starting position y: ");
	scanf("%d", &start_y);
	int scale;
	printf("Wpisz jak bardzo widoczny ma być drugi obrazek skala (0-100): ");
	scanf("%d", &scale);
    merge(file_data, file_data_b, start_x, start_y, scale);
  }
  printf("Do you want to delate one of the main color? [y/n]:");
  //clear buffer
  while ((c = getchar()) != '\n' && c != EOF) { }
  scanf("%c", &c);
  if(  c == 'y') {
	int color;
	printf("Enter one int of color you want to delate (red=0, green=1, blue=2): ");
	scanf("%d", &color);
	
    delate_one_of_rgb(color, file_data);
  }
  saving("output.png", file_data);
  
  return 0;
}
