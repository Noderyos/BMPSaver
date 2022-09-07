# BMPSaver
A simple Cpp wrapper to save images as bitmap

(it's just a simple function, so you can simply copy my function)

Usage : 
```cpp
#include "bmpsaver.h"
#include <vector>

#define W 127

int main() {
    std::vector<unsigned char> v(W*3*W);
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < W; ++j) {
            unsigned char gb = i+j;
            v[(i*W+j)*3+0] = gb;
            v[(i*W+j)*3+1] = gb;
            v[(i*W+j)*3+2] = gb;
        }
    }
    save_img("test.bmp",&v[0],W,W);
    return 0;
}
```
