#include "bmp_gen.h"

void    bmpHeaderInit(t_bmp *e) {
    int         dpi = 96;
    int         image_size = e->img_width * e->img_height;
    int         file_size = 54 + 4 * image_size;
    int         ppm = dpi * 39.375;

    // Write File Header (14 bytes)
    memcpy(e->fh.bitmap_type, "BM", 2);
    e->fh.file_size = file_size;
    e->fh.reserved1 = 0;
    e->fh.reserved2 = 0;
    e->fh.offset_bits = 0x36;

    // Write Image Header (40 bytes)
    e->ih.size_header = sizeof(t_bmp_image_header);
    e->ih.width = e->img_width;
    e->ih.height = e->img_height;
    e->ih.planes = 1;
    e->ih.bit_count = 24;
    e->ih.compression = 0;
    e->ih.image_size = file_size;
    e->ih.ppm_x = ppm;
    e->ih.ppm_y = ppm;
    e->ih.clr_used = 0;
    e->ih.clr_important = 0;
}

// Open file and get a pointer to the FILE object created
int     fileWriteInit(t_bmp *e, const char *filename) {
    e->image = fopen(filename, "wb");
    if (e->image != NULL)
        return SUCCESS;
    else
        return FAILURE;
}

// Initialize structures (header / file) and memory allocation
t_bmp*  bmpInit(int img_width, int img_height, const char *filename) {
    t_bmp   *e;

    e = (t_bmp*)malloc(sizeof(t_bmp));
    e->data = (unsigned char*)malloc(sizeof(unsigned char) * (img_width * img_height * 3));
    if (e->data == NULL) {
        printf("Error during memory allocation !");
        return NULL;
    }
    e->img_height = 800;
    e->img_width = 600;
    bmpHeaderInit(e);

    if (fileWriteInit(e, filename) == FAILURE) {
        printf("Error during bitmap file creation !");
        return NULL;
    }
    return (e);
}

void    fileWrite(t_bmp *e) {
    unsigned char   bmppad[3] = {0,0,0};
    int             i;

    // Write headers into the file
    fwrite(&e->fh, 1, 14, e->image);
    fwrite(&e->ih, 1, 40, e->image);

    // Write data (+ padding when necessary)
    i = 0;
    for(i = 0; i < e->img_height; i++)
    {
        fwrite(e->data + (e->img_width * (e->img_height - i - 1) * 3), 3, e->img_width, e->image);
        fwrite(bmppad, 1, (4 - (e->img_width * 3) % 4) % 4, e->image);
    }
}

// Draw a pixel in a specific (x,y) position
void    drawPixel(t_bmp *e, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    int         i;
    int         j;

    i = x;
    j = (e->img_height - 1) - y;
    e->data[(i + j * e->img_height) * 3 + 2] = (unsigned char)(r);
    e->data[(i + j * e->img_height) * 3 + 1] = (unsigned char)(g);
    e->data[(i + j * e->img_height) * 3 + 0] = (unsigned char)(b);
}