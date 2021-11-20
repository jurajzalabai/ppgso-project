// Task 3 - Implement Bresenham drawing alg.
//        - Draw a star using lines
//        - Make use of std::vector to define the shape
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <ppgso/ppgso.h>
using namespace std;

// Size of the framebuffer
const unsigned int SIZE = 512;

struct Point {
    int x,y;
};

// Bresenham drawing algorithm
void drawLine(ppgso::Image& framebuffer, Point& from, Point& to) {
    int x = from.x;
    int y = from.y;
    int y1 = to.y;
    int xdiff = to.x - from.x;
    int ydiff = to.y - from.y;
    if(abs(xdiff) > abs(ydiff)) {
        x = from.y;
        y = from.x;
        xdiff = to.y - from.y;
        ydiff = to.x - from.x;
        y1 = to.x;
    }
    int e = -abs(ydiff);
    while ((ydiff >= 0 && y <= y1) || (ydiff < 0 && y >= y1)) {
        if (abs(to.x - from.x) < abs(to.y - from.y)) {
            framebuffer.setPixel(x, y, 255, 255, 255);
        }
        else {
            framebuffer.setPixel(y, x, 255, 255, 255);
        }
        if (ydiff > 0){
            y++;
        }
        else {
            y--;
        }
        e += 2 * abs(xdiff);
        if (e > 0) {
            if (xdiff >= 0){
                x++;
            }
            else {
                x--;
            }
            e -= 2 * abs(ydiff);
        }
    }
//    else {
//        int e = -abs(xdiff);
//        while ((xdiff >= 0 && x <= to.x) || (xdiff < 0 && x >= to.x)) {
//            framebuffer.setPixel(x, y, 255, 255, 255);
//            if (xdiff > 0){
//                x++;
//            }
//            else {
//                x--;
//            }
//            e += 2 * abs(ydiff);
//            if (e > 0) {
//                if (ydiff >= 0){
//                    y++;
//                }
//                else {
//                    y--;
//                }
//                e -= 2 * abs(xdiff);
//            }
//        }
//    }

}

int main()
{
    // Use ppgso::Image as our framebuffer
    ppgso::Image framebuffer(SIZE, SIZE);

    // TODO: Generate star points
    // stred je 256, 256
    std::vector<Point> points;
    for (int angle = 0; angle < 360; angle += 30) {
        double angle_rad = angle / 180.0 * ppgso::PI;
        points.push_back({int(256 + 100 * sin(angle_rad)), int(256 + 100 * cos(angle_rad))});
        points.push_back({int(256 + 150 * sin(angle_rad)), int(256 + 150 * cos(angle_rad))});
    }

    // Draw lines
    for(unsigned int i = 0; i < points.size() - 1; i+=2)
        drawLine(framebuffer, points[i], points[i+1]);

    // Save the result
    std::cout << "Generating task2_bresenham.bmp file ..." << std::endl;
    ppgso::image::saveBMP(framebuffer, "task2_bresenham.bmp");

    std::cout << "Done." << std::endl;
    return EXIT_SUCCESS;
}

