#include <math.h>
#include "Augmentations.h"
#include "ColorSpaces.h"
#include "DCT.h"


//Augmentation - Hue Change

void myAugmentation0(
	uchar in_out_y[],
	int x_size,
    int y_size,
    int hue_increase
) {
    float hue, s, v;
    float r, g, b;


    for(int y = 0; y < y_size; y++){
        for(int xx = 0; xx < x_size; xx++){

            r = in_out_y[(y * x_size + xx) * 3 + 0] / 255.0;
            g = in_out_y[(y * x_size + xx) * 3 + 1] / 255.0;
            b = in_out_y[(y * x_size + xx) * 3 + 2] / 255.0;


            float m = fmax(r, fmax(g, b));
            float n = fmin(r, fmin(g, b));

            v = m;
            s = 1 - n / m;

            if(m == r){
                hue = (g - b) / (m - n);
            }
            else if(m == g){
                hue = 2.0 + (b - r) / (m - n);
            }
            else{
                hue = 4.0 + (r - g) / (m - n);
            }

            hue *= 60;

            hue += hue_increase;
            if(hue < 360)
                hue += 360;
            if(hue > 360)
                hue -= 360;

            //HSV -> RGB

            //m = 255 * v;
            //n = m * (1 - s);

            float c = v * s;

            float x = c * (1 - abs(fmod(hue / 60, 2) - 1));

            m = v - c;

            if(hue > 0 && hue < 60){
                r = c;
                g = x;
                b = 0;
            }
            else if(hue >= 60 && hue < 120){
                r = x;
                g = c;
                b = 0;
            }
            else if(hue >= 120 && hue < 180){
                r = 0;
                g = c;
                b = x;
            }
            else if(hue >= 180 && hue < 240){
                r = 0;
                g = x;
                b = c;
            }
            else if(hue >= 240 && hue < 300){
                r = x;
                g = 0;
                b = c;

            }
            else if(hue >= 300 && hue < 360){
                r = c;
                g = 0;
                b = x;
            }


            r = floor((r + m) * 255);
            g = floor((g + m) * 255);
            b = floor((b + m) * 255);

            in_out_y[(y * x_size + xx) * 3 + 0] = r;
            in_out_y[(y * x_size + xx) * 3 + 1] = g;
            in_out_y[(y * x_size + xx) * 3 + 2] = b;

        }
    }
}



//Augmentation - Hide 'n seek

void myAugmentation1(
	uchar in_out_rgb[],
	int x_size,
	int y_size,
    int w,  //number of horizontal blocks
    int h,   //number of vertical blocks
    int percentage
) {

    uchar* input = new uchar[x_size * y_size * 3];

    for(int i = 0; i < x_size * y_size * 3; i++){
        input[i] = in_out_rgb[i];
    }

    int x_block_size = x_size / w;
    int y_block_size = y_size / h;

    int blackout_number = percentage / 100. * h * w;

    int blackout[blackout_number];

    srand((unsigned) time(NULL));

    for(int i = 0; i < blackout_number; i++){
        int num = rand() % (w * h);

        for(int j = 0; j < i; j++){
            if(blackout[j] == num)
            {
                i--;
                break;
            }
        }

        blackout[i] = num;
    }


    for(int block_num: blackout){

        int x_start = x_block_size * (block_num % w);
        int y_start = y_block_size * floor(block_num / h);

        for(int y = 0; y < y_block_size; y++){
            for(int x = 0; x < x_block_size; x++){

                in_out_rgb[((y_start + y) * x_size + x_start + x) * 3 + 0] = 0;
                in_out_rgb[((y_start + y) * x_size + x_start + x) * 3 + 1] = 0;
                in_out_rgb[((y_start + y) * x_size + x_start + x) * 3 + 2] = 0;

            }
        }

    }

    delete[] input;
}



//Augmentation - Image Rotate

void myAugmentation2(
    uchar in_out_rgb[],
    int x_size,
    int y_size,
    double angle // [0, 360]
) {


    uchar* input = new uchar[x_size * y_size * 3];

    for(int i = 0; i < x_size * y_size * 3; i++){
        input[i] = in_out_rgb[i];
    }

    int m, n;

    m = x_size / 2;
    n = y_size / 2;


    angle = (angle * 3.14159296) / 180.0;

    for(int y = 0; y < y_size; y++){
        for(int x = 0; x < x_size; x++){
            in_out_rgb[3 * (y*x_size + x)] = 0;
            in_out_rgb[3 * (y*x_size + x) + 1] = 0;
            in_out_rgb[3 * (y*x_size + x) + 2] = 0;
        }
    }

    for(int y = 0; y < y_size; y++){
        for(int x = 0; x < x_size; x++){
            int oy = y * cos(angle) + x * sin(angle) - m* sin(angle) - n* cos(angle) + n;
            int ox = x * cos(angle) - y * sin(angle) - m* cos(angle) + n* sin(angle) + m;
            if ((oy < y_size && oy > 0) && (ox < x_size && ox > 0) ) {
                in_out_rgb[3 * (y*x_size + x)] = input[3 * (oy*x_size + ox)];
                in_out_rgb[3 * (y*x_size + x) + 1] = input[3 * (oy*x_size + ox) + 1];
                in_out_rgb[3 * (y*x_size + x) + 2] = input[3 * (oy*x_size + ox) + 2];
            }
        }
    }

    delete[] input;
}



//Augmentation - DCT lowpass unsharp masking
void myAugmentation3(
    uchar in_out_rgb[],
    int x_size,
    int y_size,
    int N, //
    int B,
    float lambda
) {

    uchar* input = new uchar[x_size * y_size];

    for(int i = 0; i < x_size * y_size; i++){
        input[i] = in_out_rgb[i];
    }


    performMaskDCTCoeffs(in_out_rgb, x_size, y_size, N, B);


    for(int i = 0; i < x_size * y_size; i++){

        in_out_rgb[i] = input[i] + (input[i] - in_out_rgb[i]) * lambda;

    }

    delete[] input;
}
