// #pragma once

// #include "GLHeaders.h"

// class Fbo {
// private:
// 	const int width;
// 	const int height;

// 	GLuint frameBuffer;

// 	GLuint colourTexture;
// 	GLuint depthTexture;

// 	GLuint depthBuffer;
// 	GLuint colourBuffer;
	
// public:
// 	static const int NONE = 0;
// 	static const int DEPTH_TEXTURE = 1;
// 	static const int DEPTH_RENDER_BUFFER = 2;

// 	Fbo(int width, int height, int depthBufferType);
// 	void cleanUp();
// 	void bindFrameBuffer();
// 	void unbindFrameBuffer();
// 	void bindToRead();
// 	int getColourTexture();
// 	int getDepthTexture();
// 	void initialiseFrameBuffer(int type);
// 	void createFrameBuffer();
// 	void createTextureAttachment();
// 	void createDepthTextureAttachment();
// 	void createDepthBufferAttachment();

// }
