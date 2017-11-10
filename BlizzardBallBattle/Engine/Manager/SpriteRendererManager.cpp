#include "SpriteRendererManager.h"
#include <iostream>
#include <algorithm>
#include <condition_variable>

//Statics must be given definitions
SpriteRendererManager* SpriteRendererManager::instance;

SpriteRendererManager* SpriteRendererManager::GetInstance() {
	if (instance == NULL)
		instance = new SpriteRendererManager();
	return instance;
}

/*void SpriteRendererManager::Subscribe(int id, SpriteRenderer* spriteRenderer) {
spriteRenderers[id] = spriteRenderer;
}

void SpriteRendererManager::UnSubscribe(int id) {
spriteRenderers.erase(id);
}*/

void SpriteRendererManager::OnUpdate(int ticks) {
	Render();
	//for (std::map<int,SpriteRenderer*>::iterator renderer=spriteRenderers.begin(); renderer!=spriteRenderers.end(); ++renderer)
	//    spriteRenderer.Render();
}

SpriteRendererManager::SpriteRendererManager() {
	quadVertices = {
		//Position         
		0.5f, 0.5f, 0.0f,  //Top Right
		0.5f, -0.5f, 0.0f, //Bottom Right
		-0.5f, -0.5f, 0.0f,//Bottom Left
		-0.5f, 0.5f, 0.0f, //Top Left
	};
	textCoordinates = {
		1.0f, 1.0f,  //Top Right
		1.0f, 0.0f,  //Bottom Right
		0.0f, 0.0f,  //Bottom Left
		0.0f, 1.0f   //Top Left
	};
	indices = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	renderingThreadIsAlive = true;
	rendering = false;
	renderingThread = std::thread(&SpriteRendererManager::PrepareRenderingThread, this);
	renderingThread.detach();
}


bool SpriteRendererManager::SetOpenGLAttributes() {
	//All SDL_Gl_SetAttribute returns negative on fail, 0 on success. If result is zero, all succeeded
	int result = 0;
	//SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//OpenGL 3.3 using GLSL 330
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//Turn on double buffering with a 24bit Z buffer
	//You may need to change this to 16 or 32 for your system
	result += SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return result == 0;
}

void SpriteRendererManager::PrintSDL_GL_Attributes() {
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

void SpriteRendererManager::CheckSDLError(int line) {
	std::string error = SDL_GetError();
	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;
		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;
		SDL_ClearError();
	}
}

bool SpriteRendererManager::Init() {
	////Setup SDL
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	if (!SetOpenGLAttributes()) {
		return false;
	}

	// Create our window centered as an OpenGL window
	mainWindow = SDL_CreateWindow("Blizzard Ball Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!mainWindow) {
		std::cout << "Unable to create window\n";
		CheckSDLError(__LINE__);
		return false;
	}

	// Create our opengl context and attach it to our window
	glContext = SDL_GL_CreateContext(mainWindow);

	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	////Setup glew
	glewExperimental = GL_TRUE;
	glewInit();

	////Setup OpenGL Viewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_TEXTURE_2D); ///
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glMatrixMode(GL_PROJECTION); ///
	//gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); ///
	//glMatrixMode(GL_MODELVIEW); ///

	////Setup VBO/VAO/EBO's. This is for the concept of sprite specifically where we assume it will all be quads (two triangles) to make a sprite
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &CBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
	//4 points cause quad, 8 points cause x/y/z/r/g/b/tx/ty
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//textture coordinate attribute
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordinates), textCoordinates.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); //Unbind BAO

	return true;
}

void SpriteRendererManager::Cleanup() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Delete our OpengL context
	if (glContext != NULL) {
		SDL_GL_DeleteContext(glContext);
	}
	// Destroy our window
	if (mainWindow != NULL) {
		SDL_DestroyWindow(mainWindow);
	}
	// Shutdown SDL 2
	SDL_Quit();
}

GLuint SpriteRendererManager::GenerateTexture(std::string textureFileName) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_Surface *temp = IMG_Load(textureFileName.c_str());
	if (temp == nullptr) {
		GLenum errors = glGetError();
		const char* sdlErrors = SDL_GetError();
		std::cout << "ERROR::SPRITERENDERERMANAGER::FAILED TO READ FILE IN GENERATETEXTURE\n GLError: " << errors << " \nSDLErrors: " << sdlErrors << std::endl;
		return 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp->w, temp->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	const char* sdlError = SDL_GetError();
	GLenum glError = glGetError();
	if (strlen(sdlError) > 0) {
		std::cout << sdlError << std::endl;
	}
	if (glError != GL_NO_ERROR) {
		std::cout << glError << std::endl;
	}

	SDL_FreeSurface(temp);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

bool SortByZ(SpriteRenderer* lhs, SpriteRenderer* rhs) {
	return lhs->GetGameObject()->GetTransform()->getZ() < rhs->GetGameObject()->GetTransform()->getZ();
}

std::mutex threadMutex;
std::condition_variable condition;

void SpriteRendererManager::PrepareRenderingThread() {
	GLuint lastShaderUnset = 1000000;
	std::unique_lock<std::mutex> lock(threadMutex);

	while (renderingThreadIsAlive) {
		condition.wait(lock);
		renderReadingStick.lock();
		renderingGroups.clear();
		GLuint lastShader = lastShaderUnset;
		std::sort(activeSprites.begin(), activeSprites.end(), SortByZ);
		RenderingShaderGroup rg;

		if (activeSprites.size() == 0) {
			std::cout << "SPRITERENDERERERMANAGER::PREPARERENDERINGTHREAD::EMPTY SPRITE LIST" << std::endl;
		}
		else {
			for (size_t i = 0; i < activeSprites.size(); i++) {
				SpriteRenderer* spriteRenderer = activeSprites[i];

				if (IsRenderingLayerEnabled(spriteRenderer->GetLayer())) {
					RenderingObject ro;
					GLuint roShader = spriteRenderer->GetShader()->Program;
					ro.sprite = spriteRenderer->GetSprite();

					if (lastShader == lastShaderUnset) {
						lastShader = roShader;
						rg.shaderProgram = roShader;
					}

					if (rg.shaderProgram != lastShader) {
						renderingGroups.push_back(rg);
						lastShader = roShader;
						rg = RenderingShaderGroup();
						rg.shaderProgram = roShader;
					}

					//Pass in transform
					ro.transform = spriteRenderer->GetGameObject()->GetTransform();

					ro.spriteRenderer = spriteRenderer;

					rg.children.push_back(ro);
				}
			}
			renderingGroups.push_back(rg);
		}

		//renderTalkingStick.lock();
		renderReadingStick.unlock();
	}
}

void SpriteRendererManager::Render() {
	renderReadingStick.lock();
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	std::cout << "RG Size: " << renderingGroups.size() << std::endl;
	for (size_t i = 0; i < renderingGroups.size(); i++) {
		RenderingShaderGroup rg = renderingGroups[i];
		glUseProgram(rg.shaderProgram);

		//Pass in Transform
		GLint transformLocation = glGetUniformLocation(rg.shaderProgram, "transform");
		//Pass in aspect ratio
		GLint aspectRatioLocation = glGetUniformLocation(rg.shaderProgram, "aspectRatio");
		//Pass in texture
		glActiveTexture(GL_TEXTURE0);
		GLint ourTextureLocation = glGetUniformLocation(rg.shaderProgram, "ourTexture");
		glUniform1i(ourTextureLocation, 0);
		std::cout << "  -RB Size: " << rg.children.size() << std::endl;

		for (size_t j = 0; j < rg.children.size(); j++) {
			RenderingObject ro = rg.children[j];

			ro.sprite->BindTextCoordinates(CBO);

			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, *(ro.transform));

			glUniform1f(aspectRatioLocation, ASPECT_RATIO);

			glBindTexture(GL_TEXTURE_2D, ro.sprite->GetTextureBufferID());

			//Bind vertex array
			glBindVertexArray(VAO);

			//Draw
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			ro.spriteRenderer->Render();
		}

		rg.children.clear();
	}
	SDL_GL_SwapWindow(mainWindow);
	condition.notify_one();
	renderReadingStick.unlock();
}

void SpriteRendererManager::AddSpriteForRendering(SpriteRenderer* sprite) {
	activeSprites.push_back(sprite);
}

void SpriteRendererManager::DisableRenderingLayer(int layer) {
	disabledLayers.insert(layer);
}

void SpriteRendererManager::EnableRenderingLayer(int layer) {
	disabledLayers.erase(layer);
}

void SpriteRendererManager::EnableAllRenderingLayers() {
	disabledLayers.clear();
}

bool SpriteRendererManager::IsRenderingLayerEnabled(int layer) {
	return disabledLayers.find(layer) == disabledLayers.end();
}

void SpriteRendererManager::RemoveSpriteFromRendering(SpriteRenderer* sprite) {
	activeSprites.erase(std::remove(activeSprites.begin(), activeSprites.end(), sprite), activeSprites.end());
}

void SpriteRendererManager::Purge() {
	activeSprites.clear();
}