#ifndef BMP_GEN_H
# define BMP_GEN_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define SUCCESS 1
# define FAILURE 0

typedef	struct  	s_color {
	double		    r;
	double		    g;
	double		    b;
}				    t_color;

#pragma pack(push, 1)
typedef struct	    s_bmp_file_header {
    unsigned char   bitmap_type[2];     // 2 bytes
    int             file_size;          // 4 bytes
    short           reserved1;          // 2 bytes
    short           reserved2;          // 2 bytes
    unsigned int    offset_bits;        // 4 bytes
}				    t_bmp_file_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct	    s_bmp_image_header {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
}				    t_bmp_image_header;
#pragma pack(pop)

typedef struct	        s_env {
    FILE                *image;
    t_color             *data;
    t_bmp_file_header   fh;
    t_bmp_image_header  ih;
}				        t_env;

int init(t_env *e);
void fileWriteInit(t_env *e, const char *filename);
void bmpHeaderInit(t_env *e);
void fileWrite(t_env *e);

#endif