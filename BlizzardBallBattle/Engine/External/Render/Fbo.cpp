// #include "Fbo.h"

// 	/**
// 	 * Creates an FBO of a specified width and height, with the desired type of
// 	 * depth buffer attachment.
// 	 * 
// 	 * @param width
// 	 *            - the width of the FBO.
// 	 * @param height
// 	 *            - the height of the FBO.
// 	 * @param depthBufferType
// 	 *            - an int indicating the type of depth buffer attachment that
// 	 *            this FBO should use.
// 	 */
// 	Fbo::Fbo(int width, int height, int depthBufferType) {
// 		this.width = width;
// 		this.height = height;
// 		initialiseFrameBuffer(depthBufferType);
// 	}

// 	/**
// 	 * Deletes the frame buffer and its attachments when the game closes.
// 	 */
// 	void Fbo::cleanUp() {
// 		glDeleteFramebuffers(frameBuffer);
// 		glDeleteTextures(colourTexture);
// 		glDeleteTextures(depthTexture);
// 		glDeleteRenderbuffers(depthBuffer);
// 		glDeleteRenderbuffers(colourBuffer);
// 	}

// 	/**
// 	 * Binds the frame buffer, setting it as the current render target. Anything
// 	 * rendered after this will be rendered to this FBO, and not to the screen.
// 	 */
// 	void Fbo::bindFrameBuffer() {
// 		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
// 		glViewport(0, 0, width, height);
// 	}

// 	/**
// 	 * Unbinds the frame buffer, setting the default frame buffer as the current
// 	 * render target. Anything rendered after this will be rendered to the
// 	 * screen, and not this FBO.
// 	 */
// 	void Fbo::unbindFrameBuffer() {
// 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 		glViewport(0, 0, Display.getWidth(), Display.getHeight());
// 	}

// 	/**
// 	 * Binds the current FBO to be read from (not used in tutorial 43).
// 	 */
// 	void Fbo::bindToRead() {
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 		glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
// 		glReadBuffer(GL_COLOR_ATTACHMENT0);
// 	}

// 	/**
// 	 * @return The ID of the texture containing the colour buffer of the FBO.
// 	 */
// 	int Fbo::getColourTexture() {
// 		return colourTexture;
// 	}

// 	/**
// 	 * @return The texture containing the FBOs depth buffer.
// 	 */
// 	int Fbo::getDepthTexture() {
// 		return depthTexture;
// 	}

// 	/**
// 	 * Creates the FBO along with a colour buffer texture attachment, and
// 	 * possibly a depth buffer.
// 	 * 
// 	 * @param type
// 	 *            - the type of depth buffer attachment to be attached to the
// 	 *            FBO.
// 	 */
// 	void Fbo::initialiseFrameBuffer(int type) {
// 		createFrameBuffer();
// 		createTextureAttachment();
// 		if (type == DEPTH_RENDER_BUFFER) {
// 			createDepthBufferAttachment();
// 		} else if (type == DEPTH_TEXTURE) {
// 			createDepthTextureAttachment();
// 		}
// 		unbindFrameBuffer();
// 	}

// 	/**
// 	 * Creates a new frame buffer object and sets the buffer to which drawing
// 	 * will occur - colour attachment 0. This is the attachment where the colour
// 	 * buffer texture is.
// 	 * 
// 	 */
// 	void Fbo::createFrameBuffer() {
// 		glGenFramebuffers(1, &frameBuffer);
// 		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
// 		glDrawBuffer(GL_COLOR_ATTACHMENT0);
// 	}

// 	/**
// 	 * Creates a texture and sets it as the colour buffer attachment for this
// 	 * FBO.
// 	 */
// 	void Fbo::createTextureAttachment() {
// 		glGenTextures(1, colourTexture);
// 		glBindTexture(GL_TEXTURE_2D, colourTexture);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
// 				(ByteBuffer) null);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourTexture,
// 				0);
// 	}

// 	/**
// 	 * Adds a depth buffer to the FBO in the form of a texture, which can later
// 	 * be sampled.
// 	 */
// 	 void Fbo::createDepthTextureAttachment() {
// 		glGenTextures(1, &depthTexture);
// 		glBindTexture(GL_TEXTURE_2D, depthTexture);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT,
// 				GL_FLOAT, (ByteBuffer) null);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
// 	}

// 	/**
// 	 * Adds a depth buffer to the FBO in the form of a render buffer. This can't
// 	 * be used for sampling in the shaders.
// 	 */
// 	void Fbo::createDepthBufferAttachment() {
// 		glGenRenderbuffers(1, &depthBuffer);
// 		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
// 		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
// 		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
// 				depthBuffer);
// 	}
