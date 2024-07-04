#include "../libs/glad/src/glad.c"
//#include <GLFW/glfw3.h>
//#include "../libs/imgui/imgui.h"
//#include <math.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <stdlib.h>

// Globals
int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = NULL;
SDL_GLContext gOpenGLContext = NULL;

bool gQuit = false; // If true, we quit

void GetOpenGLVersionInfo() {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));
	printf("Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void InitializeProgram() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    perror("SDL2 could not initialize video subsystem\n");
    exit(21); 
  }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL Window", 0, 0, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

  if (gGraphicsApplicationWindow == NULL) {
    perror("SDL_Window was not able to be created\n");
    exit(21);
  }

  gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

  if (gOpenGLContext == NULL) {
		perror("OpenGL context not available\n");
		exit(21);
	}

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		perror("glad was not initialized");
		exit(21);
	}

	GetOpenGLVersionInfo();
}

void Input() {
	SDL_Event e;

	while(SDL_PollEvent(&e) !=0) {
		if(e.type == SDL_QUIT) {
			printf("Goodbye!\n");
			gQuit = true;
		}
	}
}

void PreDraw() {

}
  
void Draw() {

}

void MainLoop() {
	while(!gQuit) {
		Input();
		PreDraw();
		Draw();

		// Update the screen
		SDL_GL_SwapWindow(gGraphicsApplicationWindow);
	}
}

void CleanUp() {
	SDL_DestroyWindow(gGraphicsApplicationWindow);
  SDL_Quit();
}

int main() {
  InitializeProgram();
  
  MainLoop();

  CleanUp();
  return 0;
}
