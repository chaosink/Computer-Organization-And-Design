#include "pico.hpp"

extern FILE *zb16;
extern int text_x;
extern int text_y;
extern int pinyin_x;
extern int pinyin_y;
int option_x = OPTION_POSITION_INIT_X;
int option_y = OPTION_POSITION_INIT_Y;
int page_number;
int page_current;
unsigned char text[500];
int text_number = 0;

unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
int font_number = 0;
char font_code[1000];

void draw_border() {
	glBegin(GL_LINES);
		// Border 1
		glColor3f(1.f, 0.f, 0.f);
		glVertex2i(0, BORDER_1_Y);
		glColor3f(1.f, 1.f, 0.f);
		glVertex2i(WINDOW_WIDTH / 2, BORDER_1_Y);
		glColor3f(1.f, 1.f, 0.f);
		glVertex2i(WINDOW_WIDTH / 2, BORDER_1_Y);
		glColor3f(1.f, 0.f, 0.f);
		glVertex2i(WINDOW_WIDTH, BORDER_1_Y);
		// Border 2
		glColor3f(1.f, 0.f, 0.f);
		glVertex2i(0, BORDER_2_Y);
		glColor3f(1.f, 1.f, 0.f);
		glVertex2i(WINDOW_WIDTH / 2, BORDER_2_Y);
		glColor3f(1.f, 1.f, 0.f);
		glVertex2i(WINDOW_WIDTH / 2, BORDER_2_Y);
		glColor3f(1.f, 0.f, 0.f);
		glVertex2i(WINDOW_WIDTH, BORDER_2_Y);
	glEnd();
}

void draw_text_cursor(int x, int y) {
	static double time = 0;
	static int flag = 0;
	const float *rgb;
/*	glBegin(GL_POLYGON);
		glColor3f(rgb, rgb, rgb);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 17 - 14, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 17 - 14, y - 1);
		glVertex2i(x - 1, y - 1);
	glEnd();*/
	glBegin(GL_LINES);
		glColor3fv(flag ? BACKGROUND_RGBA : CURSOR_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 2, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y);
		glVertex2i(x - 1, y);
		glVertex2i(x + 2, y);
	glEnd();
	if(glfwGetTime() - time > 0.5) flag = 1 - flag, time = glfwGetTime();
}

void erase_text_cursor(int x, int y) {
	glBegin(GL_LINES);
		glColor3fv(BACKGROUND_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 2, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y);
		glVertex2i(x - 1, y);
		glVertex2i(x + 2, y);
	glEnd();
}

void draw_text(int x, int y, int option) {
	int offset;
	char lattice[32];
	unsigned char high, low;
	short int zbcode;

	if(text_x == TEXT_POSITION_MAX_X && text_y == TEXT_POSITION_MIN_Y) return;
	if(option < 0 || option > 7 || (page_current * N_OPTION_A_LINE + option) >= font_number) return;
	high = font_code[page_current * N_OPTION_A_LINE * 2 + option * 2 ];
	low = font_code[page_current * N_OPTION_A_LINE * 2 + option * 2 + 1];
	offset = (94 * (high - 0x00A1) + (low - 0x00A1)) * 32 + 0x2000;

	fseek(zb16, offset, SEEK_SET);
	fread(lattice, 1, 32, zb16);

	draw_lattice(lattice, x, y);
	text[text_number * 2] = high;
	text[text_number * 2 + 1] = low;
	text_next();
	printf("****font_number : %d\n", font_number);
}

void erase_text(int x, int y) {
	glBegin(GL_POLYGON);
		glColor3fv(BACKGROUND_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 1, y - 1);
		glVertex2i(x - 1, y - 1);
	glEnd();
}

void text_next() {
	if(text_x == TEXT_POSITION_MAX_X) {
		if(text_y == TEXT_POSITION_MIN_Y) return;
		text_x = 1;
		text_y -= BLOCK_SIZE;
	} else {
		text_x += BLOCK_SIZE;
		text_number++;
	}
}

void text_prior() {
	if(text_x == TEXT_POSITION_MIN_X) {
		if(text_y == TEXT_POSITION_MAX_Y) return;
		text_x = TEXT_POSITION_MAX_X;
		text_y += BLOCK_SIZE;
	} else {
		text_x -= BLOCK_SIZE;
		text_number--;
	}
}

void draw_pinyin_cursor(int x, int y) {
	static double time = 0;
	static int flag = 0;
	const float *rgb;
/*	glBegin(GL_POLYGON);
		glColor3f(rgb, rgb, rgb);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 17 - 14, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 17 - 14, y - 1);
		glVertex2i(x - 1, y - 1);
	glEnd();*/
	glBegin(GL_LINES);
		glColor3fv(flag ? BACKGROUND_RGBA : CURSOR_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 2, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y);
		glVertex2i(x - 1, y);
		glVertex2i(x + 2, y);
	glEnd();
	if(glfwGetTime() - time > 0.5) flag = 1 - flag, time = glfwGetTime();
}

void erase_pinyin_cursor(int x, int y) {
	glBegin(GL_LINES);
		glColor3fv(BACKGROUND_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 2, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + 1, y);
		glVertex2i(x - 1, y);
		glVertex2i(x + 2, y);
	glEnd();
}

void draw_pinyin(char ch, int x, int y) {
	int offset, i, j, k;
	char lattice[32];
	unsigned char high, low;
	short int zbcode;

	if(pinyin_x == PINYIN_POSITION_MAX_X && pinyin_y == PINYIN_POSITION_MIN_Y) return;
	
	offset = (ch + 155) * 32  + 0x2000;
	fseek(zb16, offset, SEEK_SET);
	fread(lattice, 1, 32, zb16);

	draw_lattice(lattice, x, y);
	printf("****font_number : %d\n", font_number);
}

void erase_pinyin(int x, int y) {
	glBegin(GL_POLYGON);
		glColor3fv(BACKGROUND_RGBA);
		glVertex2i(x - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 1, y + BLOCK_SIZE - 1);
		glVertex2i(x + BLOCK_SIZE - 1, y - 1);
		glVertex2i(x - 1, y - 1);
	glEnd();
}

void pinyin_next() {
	if(pinyin_x == PINYIN_POSITION_MAX_X) {
		if(pinyin_y == PINYIN_POSITION_MIN_Y) return;
		pinyin_x = 1;
		pinyin_y -= BLOCK_SIZE;
	} else {
		pinyin_x += BLOCK_SIZE;
	}
}

void pinyin_prior() {
	if(pinyin_x == PINYIN_POSITION_MIN_X) {
		if(pinyin_y == PINYIN_POSITION_MAX_Y) return;
		pinyin_x = PINYIN_POSITION_MAX_X;
		pinyin_y += BLOCK_SIZE;
	} else {
		pinyin_x -= BLOCK_SIZE;
	}
}

void draw_option() {
	int offset, i, x, y, font_left;
	char lattice[32];
	unsigned char high, low;
	short int zbcode;

	font_left = font_number - page_current * N_OPTION_A_LINE;
	for(i = 0; i < (8 < font_left ? 8 : font_left); i++) {
		high = font_code[page_current * N_OPTION_A_LINE * 2 + i * 2 ];
		low = font_code[page_current * N_OPTION_A_LINE * 2 + i * 2 + 1];
		offset = (i + 110) * 32 + 0x2000;
//		offset = (i + 110 + 20) * 32;
//		offset = (i + 110 + 40) * 32;
//		offset = (i + 110 + 52) * 32;
		fseek(zb16, offset, SEEK_SET);
		fread(lattice, 1, 32, zb16);
		draw_lattice(lattice, option_x, option_y);
		option_next();
		offset = (94 * (high - 0x00A1) + (low - 0x00A1)) * 32 + 0x2000;
		fseek(zb16, offset, SEEK_SET);
		fread(lattice, 1, 32, zb16);
		draw_lattice(lattice, option_x, option_y);
		option_next();
		printf("****font_number : %d\n", font_number);
	}
}

void erase_option() {
	glBegin(GL_POLYGON);
		glColor3fv(BACKGROUND_RGBA);
		glVertex2i(0, 0);
		glVertex2i(WINDOW_WIDTH, 0);
		glVertex2i(WINDOW_WIDTH, BORDER_1_Y - 1);
		glVertex2i(0, BORDER_1_Y - 1);
	glEnd();
	option_x = OPTION_POSITION_INIT_X;
	option_y = OPTION_POSITION_INIT_Y;
}

void option_next() {
	if(option_x == PINYIN_POSITION_MAX_X) {
		if(option_y == PINYIN_POSITION_MIN_Y) return;
		option_x = 1;
		option_y -= BLOCK_SIZE;
	} else {
		option_x += BLOCK_SIZE;
	}
}

void draw_lattice(char* lattice, int x, int y) {
	int i, j, k;

	y += 31;
	glColor3fv(PINYIN_RGBA);
	for(k = 0; k < 16; k++)
		for(j = 0; j < 2; j++)
			for(i = 0; i < 8; i++)
				if(lattice[ k * 2 + j] & key[i]) {
					glBegin(GL_POINTS);
						glVertex2i(x + 2 * (j * 8 + i),     y - 2 * k);
						glVertex2i(x + 2 * (j * 8 + i) + 1, y - 2 * k);
						glVertex2i(x + 2 * (j * 8 + i),     y - 2 * k - 1);
						glVertex2i(x + 2 * (j * 8 + i) + 1, y - 2 * k - 1);
					glEnd();
				}

	for(k = 0; k < 16; k++) {
		for(j = 0; j < 2; j++)
			for(i = 0; i < 8; i++)
				printf("%s", lattice[ k * 2 + j] & key[i] ? "█" : " ");
		printf("\n");
	}
}

void save_text() {
	FILE *fp = fopen("data/text.save", "w+");
	fwrite(text, 2, text_number, fp);
	printf("****Text saved !\n");
	fclose(fp);
}
