#include <vector>
#include <istream>
#include "bmpsaver.h"

#define fopen_s(pFile,filename,mode) ((pFile)=fopen((filename),(mode)))==NULL

void save_img(const char* filename, const unsigned char* pixels, int W, int H){
    unsigned char bmpfileheader[14] = {'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0,0,0,0,0,0,0,0,0,1,0,24,0};
    unsigned char bmppad[3] = {0,0,0};

    int filesize = 54 + 3 * W * H;
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4]  = (unsigned char)(W);
    bmpinfoheader[5]  = (unsigned char)(W >> 8);
    bmpinfoheader[6]  = (unsigned char)(W >> 16);
    bmpinfoheader[7]  = (unsigned char)(W >> 24);
    bmpinfoheader[8]  = (unsigned char)(H);
    bmpinfoheader[9]  = (unsigned char)(H >> 8);
    bmpinfoheader[10] = (unsigned char)(H >> 16);
    bmpinfoheader[11] = (unsigned char)(H >> 24);

    FILE* f;
    fopen_s(f,filename, "wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    std::vector<unsigned char> pix(W*H*3);
    for (int i = 0; i < W*H; ++i) {
        pix[i * 3 + 0] = pixels[i*3+2];
        pix[i * 3 + 1] = pixels[i*3+1];
        pix[i * 3 + 2] = pixels[i*3];
    }
    for (int i = 0; i < H; ++i) {
        fwrite(&pix[0]+(W * (H - i - 1) * 3),3,W,f);
        fwrite(bmppad,1,(4 - (W * 3) % 4) % 4,f);
    }
}