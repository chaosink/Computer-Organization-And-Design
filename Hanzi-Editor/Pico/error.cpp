#include "pico.hpp"

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}
