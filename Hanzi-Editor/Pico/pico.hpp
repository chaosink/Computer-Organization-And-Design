#ifndef __PICO__
#define __PICO__

// .h head files
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

// Window
const int WINDOW_WIDTH  = 512;
const int WINDOW_HEIGHT = 514;
const int FONT_SIZE = 32;
const int FONT_MARGIN = 0;
const int BLOCK_SIZE = FONT_SIZE + FONT_MARGIN * 2;
const int N_BLOCK_A_LINE = WINDOW_WIDTH / BLOCK_SIZE;
const int N_OPTION_A_LINE = WINDOW_WIDTH / BLOCK_SIZE / 2;
const int BORDER_1_Y = BLOCK_SIZE * 1 + 1;
const int BORDER_2_Y = BLOCK_SIZE * 2 + 2;
const int TEXT_POSITION_INIT_X = 1;
const int TEXT_POSITION_INIT_Y = WINDOW_HEIGHT - BLOCK_SIZE + 1;
const int TEXT_POSITION_MIN_X = 1;
const int TEXT_POSITION_MAX_X = WINDOW_WIDTH - BLOCK_SIZE + 1;
const int TEXT_POSITION_MIN_Y = BORDER_2_Y + 1;
const int TEXT_POSITION_MAX_Y = WINDOW_HEIGHT - BLOCK_SIZE + 1;
const int PINYIN_POSITION_INIT_X = 1; 
const int PINYIN_POSITION_INIT_Y = BORDER_1_Y + 1;
const int PINYIN_POSITION_MIN_X = 1;
const int PINYIN_POSITION_MAX_X = WINDOW_WIDTH - BLOCK_SIZE + 1;
const int PINYIN_POSITION_MIN_Y = PINYIN_POSITION_INIT_Y;
const int PINYIN_POSITION_MAX_Y = PINYIN_POSITION_INIT_Y;
const int OPTION_POSITION_INIT_X = 1;
const int OPTION_POSITION_INIT_Y = 1;
const int OPTION_POSITION_MAX_X = WINDOW_WIDTH - BLOCK_SIZE + 1;
const int OPTION_POSITION_MIN_Y = 1;

// color
const float BACKGROUND_RGBA[4] = {0.f, 34.f / 255.f, 64.f / 255.f, 0.f};
const float CURSOR_RGBA[4] = {1.f, 1.5f, 1.5f, 1.f};
const float WHITE_RGBA[4] = {1.f, 1.5f, 1.5f, 1.f};
const float TEXT_RGBA[4] = {255.f / 255.f, 157.f / 255.f, 0.f / 255.f};
const float PINYIN_RGBA[4] = {255.f / 255.f, 157.f / 255.f, 0.f / 255.f};

// Key
const char* get_key_name(int key);
const char* get_action_name(int action);
const char* get_mods_name(int mods);
const char* get_character_string(int codepoint);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void char_callback(GLFWwindow* window, unsigned int codepoint);
void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods);

// Error
void error_callback(int error, const char* description);

// Pico
void draw_border();
void draw_lattice(char* lattice, int x, int y);

void draw_text_cursor(int x, int y);
void erase_text_cursor(int x, int y);
void draw_text(int x, int y, int option);
void erase_text(int x, int y);
void text_next();
void text_prior();

void draw_pinyin_cursor(int x, int y);
void erase_pinyin_cursor(int x, int y);
void draw_pinyin(char ch, int x, int y);
void erase_pinyin(int x, int y);
void pinyin_next();
void pinyin_prior();

void draw_option();
void erase_option();
void option_next();

void save_text();

// Pinyin2code
void pinyin2code(char *py);

#endif
