#include "bmp_gen.h"

// Initialize structures (header / file) and memory allocation
int                 init(t_env *e) {
    e->data = (unsigned char*)malloc(sizeof(unsigned char) * (WIN_WIDTH * WIN_HEIGHT * 3));
    if (e->data == NULL) {
        printf("Error during memory allocation !");
        return FAILURE;
    }
    bmpHeaderInit(e);

    if (fileWriteInit(e, "filetest.bmp") == FAILURE) {
        printf("Error during bitmap file creation !");
        return FAILURE;
    }
    return SUCCESS;
}

// Open file and get a pointer to the FILE object created
int                fileWriteInit(t_env *e, const char *filename) {
    e->image = fopen(filename, "wb");
    if (e->image != NULL)
        return SUCCESS;
    else
        return FAILURE;
}

void            bmpHeaderInit(t_env *e) {
    int         dpi = 96;
    int         image_size = WIN_WIDTH * WIN_HEIGHT;
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
    e->ih.width = WIN_WIDTH;
    e->ih.height = WIN_HEIGHT;
    e->ih.planes = 1;
    e->ih.bit_count = 24;
    e->ih.compression = 0;
    e->ih.image_size = file_size;
    e->ih.ppm_x = ppm;
    e->ih.ppm_y = ppm;
    e->ih.clr_used = 0;
    e->ih.clr_important = 0;
}

void                fileWrite(t_env *e) {
    unsigned char   bmppad[3] = {0,0,0};
    int             i;

    // Write headers into the file
    fwrite(&e->fh, 1, 14, e->image);
    fwrite(&e->ih, 1, 40, e->image);

    // Write data + padding when necessary
    i = 0;
    for(i = 0; i < WIN_HEIGHT; i++)
    {
        fwrite(e->data + (WIN_WIDTH * (WIN_HEIGHT - i - 1) * 3), 3, WIN_WIDTH, e->image);
        fwrite(bmppad, 1, (4 - (WIN_WIDTH * 3) % 4) % 4,e->image);
    }
}

// Draw a pixel in a specific (x,y) position
void                drawPixel(t_env *e, int x, int y, t_color pix) {
    int         i;
    int         j;

    i = x;
    j = (WIN_HEIGHT - 1) - y;
    e->data[(i + j * WIN_WIDTH) * 3 + 2] = (unsigned char)(pix.r);
    e->data[(i + j * WIN_WIDTH) * 3 + 1] = (unsigned char)(pix.g);
    e->data[(i + j * WIN_WIDTH) * 3 + 0] = (unsigned char)(pix.b);
}

int                 main (void) {
    t_env       *e;
    t_color     pix;
    int         x;
    int         y;

    e = (t_env*)malloc(sizeof(t_env));
    if (init(e) == FAILURE) {
        printf("Bitmap file creation failed, exiting...");
        return 1;
    }

    pix.r = 0;
    pix.g = 50;
    pix.b = 255;

    for (x = 0; x < WIN_WIDTH; x++) {
        for (y = 0; y < WIN_HEIGHT; y++) {
            drawPixel(e, x, y, pix);
        }
    }

    fileWrite(e);
    return 0;
}