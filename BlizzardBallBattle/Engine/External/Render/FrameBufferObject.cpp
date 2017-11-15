// #include "FrameBufferObject.h"

// FrameBufferObject::FrameBufferObject() {//call when loading the game
//     initialiseFrameBuffer();
// }

// void FrameBufferObject::cleanUp() {//call when closing the game
//     glDeleteFramebuffers(1, &frameBuffer);
//     glDeleteTextures(1, &texture);
//     glDeleteRenderbuffers(1, &depthBuffer);
// }

// void FrameBufferObject::bindFrameBuffer() {//call before rendering to this FBO
//     bindFrameBuffer(frameBuffer, WIDTH, HEIGHT);
// }

// void FrameBufferObject::unbindCurrentFrameBuffer() {//call to switch to default frame buffer
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     glViewport(0, 0, WIDTH, HEIGHT);
// }

// int FrameBufferObject::getTexture() {//get the resulting texture
//     return texture;
// }
 
// int FrameBufferObject::getDepthTexture(){//get the resulting depth texture
//     return texture;
// }

// void FrameBufferObject::initialiseFrameBuffer() {
//     createFrameBuffer(&frameBuffer);
//     texture = createTextureAttachment(WIDTH,HEIGHT);
//     depthBuffer = createDepthBufferAttachment(WIDTH,HEIGHT);
//     unbindCurrentFrameBuffer();
// }

// void FrameBufferObject::bindFrameBuffer(GLuint frameBuffer, int width, int height){
//     glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
//     glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//     glViewport(0, 0, width, height);
// }

// void FrameBufferObject::createFrameBuffer(GLuint* frameBuffer) {
//     glGenFramebuffers(1, frameBuffer);
//     //generate name for frame buffer
//     glBindFramebuffer(GL_FRAMEBUFFER, *frameBuffer);
//     //create the framebuffer
//     glDrawBuffer(GL_COLOR_ATTACHMENT0);
// }

// int FrameBufferObject::createTextureAttachment( int width, int height) {
//     GLuint texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
//             0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//             texture, 0);
//     return texture;
// }

// int FrameBufferObject::createDepthBufferAttachment(int width, int height) {
//     GLuint depthBuffer;
//     glGenRenderbuffers(1, &depthBuffer);
//     glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
//     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
//             height);
//     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//             GL_RENDERBUFFER, depthBuffer);
//     return depthBuffer;
// }