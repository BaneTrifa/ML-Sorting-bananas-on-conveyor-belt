#include "ImageProcessing.h"
#include "ColorSpaces.h"
#include "Augmentations.h"

#include <QDebug>

void imageProcessingFun(
	const QString& prog_name,
	QImage& out_img,
	const QImage& in_img,
	const QVector<double>& params
) {
	int x_size = in_img.width();
	int y_size = in_img.height();

    if(prog_name == "Hue Change"){
        int increase = params[0];

        out_img = in_img;

        myAugmentation0(out_img.bits(), x_size, y_size, increase);

    }else if(prog_name == "Hide n Seek"){
        int w = params[0];
        int h = params[1];
        int percentage = params[2];
		
		out_img = in_img;

        myAugmentation1(out_img.bits(), x_size, y_size, w, h, percentage);
	}
    else if(prog_name == "Rotate"){
        double angle = params[0];

        out_img = in_img;

        myAugmentation2(out_img.bits(), x_size, y_size, angle);
    }
    else if(prog_name == "Unsharp Masking"){
        int N = params[0];
        int B = params[1];
        float lambda = params[2];

        // Create empty output image.
        out_img = QImage(x_size, y_size, in_img.format());

        // Create buffers for YUV image.
        uchar* Y_buff = new uchar[x_size*in_img.height()];
        char* U_buff = new char[x_size*in_img.height()/4];
        char* V_buff = new char[x_size*in_img.height()/4];

        // Convert input image to YUV420 image.
        RGBtoYUV420(in_img.bits(), x_size, y_size, Y_buff, U_buff, V_buff);

        myAugmentation3(Y_buff, x_size, y_size, N, B, lambda);

        // Zero out U and V component.
        procesing_YUV420(Y_buff, U_buff, V_buff, x_size, y_size, 1, 1, 1);

        // Convert YUV image back to RGB.
        YUV420toRGB(Y_buff, U_buff, V_buff, x_size, y_size, out_img.bits());

        // Delete used memory buffers.
        delete[] Y_buff;
        delete[] U_buff;
        delete[] V_buff;


    }

}
