// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
    // TODO: Define correct data type for r, g, b channel
    char r;
    char g;
    char b;
};

int main()
{
    // Initialize a framebuffer
    auto framebuffer = new Pixel[SIZE][SIZE];

    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    std::ifstream File("lena.raw", std::ios::binary);

    // TODO: Read data to framebuffer and close the file
    File.read(reinterpret_cast<char *>(framebuffer), SIZE * SIZE * 3);
    File.close();



    // Traverse the framebuffer
    for (unsigned int y = 0; y < SIZE; y++) {
        for (unsigned int x = 0; x < SIZE; x++) {
            // TODO: Apply pixel operation
            framebuffer[x][y].g = rand() % 255;
        }
    }

    // TODO: Open file result.raw
    std::cout << "Generating result.raw file ..." << std::endl;

    // TODO: Write the framebuffer to the file and close it
    std::ofstream writer("result.raw", std::ios::binary);
    writer.write(reinterpret_cast<const char *>(framebuffer), SIZE * SIZE * 3);
    writer.close();

    std::cout << "Done." << std::endl;
    delete[] framebuffer;
    return EXIT_SUCCESS;
}