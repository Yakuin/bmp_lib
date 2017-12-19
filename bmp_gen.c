#include "bmp_gen.h"

// Initialize structures (header / file) and memory allocation
int init(t_env *e) {

    e->data = (t_color*)malloc(sizeof(t_color) * (WIN_WIDTH * WIN_HEIGHT));

    bmpHeaderInit(e);
    fileWriteInit(e, "filetest.bmp");

    return SUCCESS;
}

// Open file and get file descriptor
void fileWriteInit(t_env *e, const char *filename) {
    e->image = fopen(filename, "wb");
}

void bmpHeaderInit(t_env *e) {
    int dpi = 96;
    int image_size = WIN_WIDTH * WIN_HEIGHT;
    int file_size = 54 + 4 * image_size;
    int ppm = dpi * 39.375;

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

void fileWrite(t_env *e) {
    // Write headers into the file
    fwrite(&e->fh, 1, 14, e->image);
    fwrite(&e->ih, 1, 40, e->image);

    // Write data
    // fwrite(&e->data, 1, sizeof(e->data), e->image);
}

int main (void) {
    t_env *e;
    e = (t_env*)malloc(sizeof(t_env));

    if (init(e) == FAILURE)
        return 1;

    printf("Size of Bitmap File Header %i\n", sizeof(e->fh));
    printf("Size of Bitmap Image Header %i\n", sizeof(e->ih));

    t_color pix;
    pix.r = 200;
    pix.g = 0;
    pix.b = 0;

    int i = 0;
    for (int y = 0; y < WIN_HEIGHT; y++) {
        for (int x = 0; x < WIN_WIDTH; x++) {
            e->data[i] = pix;
            i++;
        }
    }

    fileWrite(e);
    return 0;
}