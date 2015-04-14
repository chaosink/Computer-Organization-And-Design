#include "pico.hpp"

int text_x = TEXT_POSITION_INIT_X;
int text_y = TEXT_POSITION_INIT_Y;
int pinyin_x = PINYIN_POSITION_INIT_X;
int pinyin_y = PINYIN_POSITION_INIT_Y;
FILE *zb16;

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	printf("GLFW initialized\n");

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pico", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, char_callback);
	glfwSetCharModsCallback(window, char_mods_callback);
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(BACKGROUND_RGBA[0], BACKGROUND_RGBA[1], BACKGROUND_RGBA[2], 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.375, WINDOW_WIDTH + 0.375, 0.375, WINDOW_HEIGHT + 0.375, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setlocale(LC_ALL, "");
	zb16 = fopen("data/zb16.data", "rb");

	draw_border();
	while (!glfwWindowShouldClose(window)) {
		draw_text_cursor(text_x, text_y);
		draw_pinyin_cursor(pinyin_x, pinyin_y);
		glfwSwapBuffers(window);
		glfwWaitEvents();
		fflush(stdout);
	}

	fclose(zb16);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
