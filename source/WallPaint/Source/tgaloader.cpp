/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include <iostream>
#include <iomanip>
#include "tgaloader.hpp"

const char ogl::TGALoader::uTGAcompare[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
const char ogl::TGALoader::cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

//############################################################################
/**
*/
//############################################################################
ogl::TGALoader::TGALoader()
	: memblock(0), memsize(0)
{
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TGALoader::load(boost::filesystem::path path, ogl::Texture*& tex)
{
	namespace fs = boost::filesystem;

	bool result = false;

	if (fs::exists(path)) {

		std::ifstream file (path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		if (file.is_open()) {

			memsize = file.tellg();
			memblock = new char [memsize];
			file.seekg (0, std::ios::beg);
			file.read (memblock, memsize);
			file.close();

			if (
				sizeof(uTGAcompare) < memsize && 
				std::equal(uTGAcompare, uTGAcompare + sizeof(uTGAcompare), memblock)
				) {

					result = loadUncompressedTGA(tex);

			} else if (
				sizeof(cTGAcompare) < memsize && 
				std::equal(cTGAcompare, cTGAcompare + sizeof(cTGAcompare), memblock)
				) {

					result = loadCompressedTGA(tex);
				  //std::cout << std::endl << "Error Dataformat: " << path << std::endl;

			} else {
				std::cout << std::endl << "Error Dataformat: " << path << std::endl;
			}

			delete[] memblock;
		}
	}

	return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TGALoader::loadUncompressedTGA(ogl::Texture*& tex)
{
	GLubyte header[6];
	bool result = false;
	unsigned int FileHeadSize = sizeof(uTGAcompare);
	unsigned int MetaHeadSize = sizeof(header);
	unsigned int HeadSize = FileHeadSize + MetaHeadSize;

	if (FileHeadSize + MetaHeadSize < memsize) {

		std::copy(memblock + FileHeadSize, memblock + HeadSize, header);

		GLuint width  = header[1] * 256 + header[0];     // Determine TGA Width (highbyte * 256 + lowbyte)
		GLuint height = header[3] * 256 + header[2];     // Determine TGA Height (highbyte * 256 + lowbyte)
		GLuint bpp    = header[4];	                     // Determine the bits per pixel

		if (0 < width && 0 < height && (bpp == 24 || bpp == 32)) {

			GLuint compo	= bpp / 8;									      // Compute the number of BYTES per pixel
			GLuint image_len = compo * width * height;		  // Compute the total amout of memory needed to store data
			GLuint type = (bpp == 24) ? GL_RGB : GL_RGBA;   // Set Image type to GL_RGB / GL_RGBA

			GLubyte* buffer = new GLubyte[image_len];
			std::copy(memblock + HeadSize, memblock + HeadSize + image_len, buffer);

			// Byte Swapping Optimized By Steve Thomas
			for (GLuint cswap = 0; cswap < image_len; cswap += compo) {
				buffer[cswap] ^= buffer[cswap + 2] ^= buffer[cswap] ^= buffer[cswap + 2];
			}

			// Need to have 4 Components
			if (bpp == 24) {
				compo	= 4;
				image_len = compo * width * height;
				type = GL_RGBA;
				GLubyte *help = 0;
				GLubyte *temp = new GLubyte[image_len];
				for (GLubyte *p = buffer, *q = temp; p < buffer + width * height * 3; p+=3, q+=4) {
					*(q + 0) = *(p + 0);
					*(q + 1) = *(p + 1);
					*(q + 2) = *(p + 2);
					*(q + 3) = 0xFF;
				}
				help = buffer;
				buffer = temp;
				delete help;
				help = 0;
				temp = 0;
			}

			tex = new Texture(width, height, type, buffer);
			result = true;
		}
	}
	return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TGALoader::loadCompressedTGA(ogl::Texture*& tex)
{
	GLubyte header[6];
	bool result = false;
	GLuint FileHeadSize = sizeof(uTGAcompare);
	GLuint MetaHeadSize = sizeof(header);
	GLuint HeadSize = FileHeadSize + MetaHeadSize;

	if (FileHeadSize + MetaHeadSize < memsize) {

		std::copy(memblock + FileHeadSize, memblock + HeadSize, header);

		GLuint width  = header[1] * 256 + header[0];     // Determine TGA Width (highbyte * 256 + lowbyte)
		GLuint height = header[3] * 256 + header[2];     // Determine TGA Height (highbyte * 256 + lowbyte)
		GLuint bpp    = header[4];	                     // Determine the bits per pixel

		if (0 < width && 0 < height && (bpp == 24 || bpp == 32)) {

			GLuint type = (bpp == 24) ? GL_RGB : GL_RGBA;   // Set Image type to GL_RGB / GL_RGBA
			GLuint pixel_bytes	= bpp / 8;									// Compute the number of BYTES per pixel
			GLuint image_size	= height * width;							// Nuber of pixels in the image
			GLuint image_length = pixel_bytes * image_size;	// Compute the total amout of memory needed to store data

			GLubyte* buffer = new GLubyte[image_length];

			GLuint currentpixel	= 0;												// Current pixel being read
			GLuint currentbyte	= 0;												// Current byte 

      std::cout << std::internal << std::setfill('0') << std::endl;
      int i = 1;
      for (char* p = memblock; p < memblock + memsize; ++p, ++i) {
        char tmp1 = *p;
        GLubyte tmp2 = *p;
        std::cout << std::setw(2) << std::uppercase << std::hex << (int)(*p) << " ";
        if((i % 8) == 0) {
          std::cout << "    ";
        }
        if((i % 16) == 0) {
          std::cout << std::endl;
        }
      } 

			while (currentpixel < image_size) {

        unsigned int a = sizeof(char);
        unsigned int b = sizeof(unsigned char);
        unsigned int c = sizeof(GLbyte);
        unsigned int d = sizeof(GLubyte);

        GLubyte chunkheader = 0;
        chunkheader = memblock[0];			    // Storage for "chunk" header
        chunkheader = memblock[1];			    // Storage for "chunk" header
        chunkheader = memblock[2];			    // Storage for "chunk" header
        chunkheader = memblock[3];			    // Storage for "chunk" header
        chunkheader = memblock[HeadSize + currentbyte];			    // Storage for "chunk" header
        //std::copy(HeadSize + currentbyte, sizeof(GLubyte), chunkheader);
        currentbyte++;

				if (chunkheader < 128) {												// If the header is < 128, it means the that is the number of RAW color packets minus 1
																					            // that follow the header
					chunkheader++;													    // add 1 to get number of following color values

          for (short counter = 0; counter < chunkheader; counter++) {		// Read RAW color values
					
						buffer[currentbyte		] = memblock[HeadSize + currentbyte + 2];					// switch R and B bytes around while copying
						buffer[currentbyte + 1] = memblock[HeadSize + currentbyte + 1];
						buffer[currentbyte + 2] = memblock[HeadSize + currentbyte + 0];
            buffer[currentbyte + 3] = (pixel_bytes == 4) ? memblock[HeadSize + currentbyte + 3] : 0;

            currentbyte += pixel_bytes;										// Increase thecurrent byte by the number of bytes per pixel
						currentpixel++;															// Increase current pixel by 1
					}

        }	else {																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times

          chunkheader -= 127;															// Subteact 127 to get rid of the ID bit

					for (short counter = 0; counter < chunkheader; counter++)	{				// copy the color into the image data as many times as dictated 
																								                            // by the header
						buffer[currentbyte		] = memblock[HeadSize + currentbyte + 2];					// switch R and B bytes around while copying
						buffer[currentbyte + 1] = memblock[HeadSize + currentbyte + 1];
						buffer[currentbyte + 2] = memblock[HeadSize + currentbyte + 0];
            buffer[currentbyte + 3] = (pixel_bytes == 4) ? memblock[HeadSize + currentbyte + 3] : 0;

            currentbyte += pixel_bytes;										// Increase current byte by the number of bytes per pixel
						currentpixel++;															// Increase pixel count by 1

            std::cout << std::internal << std::setfill('0') << std::endl;
            for (GLubyte* p = buffer; p < buffer + currentbyte; ++p) {
              std::cout << std::hex << std::setw(2) << (*p) << " ";
            } 

          }
				}
			}

			tex = new Texture(width, height, type, buffer);
			result = true;
		}
	}
	return result;
}
