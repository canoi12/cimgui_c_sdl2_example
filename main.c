#include <stdio.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char ** argv) {
	if (SDL_Init(SDL_INIT_VIDEO)== 1) {
		printf("Failed to init SDL\n");
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow("Hello Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);


	if (!window) {
		printf("Failed to init Window\n");
		exit(1);
	}

	if (gl3wInit()) {
		printf("Failed to init gl3w\n");
		exit(1);
	}

	igCreateContext(NULL);
	ImGuiIO io = *igGetIO();
	ImGui_ImplSDL2_InitForOpenGL(window, &context);
	ImGui_ImplOpenGL3_Init("#version 150");

	igStyleColorsDark(NULL);

	GLuint vao, vbo;


	SDL_Event event;
	int running = 1;

	bool demo_window = false;

	while (running) {
		while(SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				running = 0;
		}

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		igNewFrame();

		{
			if (igBeginMainMenuBar()) {
				if (igBeginMenu("File", true)) {
					if (igMenuItemBool("Open", "Ctrl+O", false, true)) {}
					if (igMenuItemBool("Save", "Ctrl+S", false, true)) {}
					if (igMenuItemBool("Close", "Ctrl+Q", false, true)) {}
					igEndMenu();
				}
				if (igBeginMenu("Show", true)) {
					if (igMenuItemBool("Show Examples", "", false, true)) demo_window = !demo_window;
					igEndMenu();
				}
				igEndMainMenuBar();
			}
		}

		if (igBegin("Test Window", NULL, ImGuiWindowFlags_None)) {
			igText("Hello World");
		}
		igEnd();

		if (demo_window) {
			igShowDemoWindow(&demo_window);
		}

		igRender();
		ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
