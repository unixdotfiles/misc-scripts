#include <stdio.h>
__attribute__((visibility("default"))) void free() {
	printf("leaking...");
}
