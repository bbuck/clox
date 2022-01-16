#include <stdlib.h>
#include <stdio.h>

typedef struct Demo {
	int line;
} Demo;

typedef struct Container {
	int count;
	Demo *demo;
} Container;

void ContainerInit(Container *container) {
	container->count = 0;
	container->demo = (Demo *)malloc(sizeof(Demo));
}

void ContainerFree(Container *container) {
	free(container->demo);
	container->demo = NULL;
}

int main(void) {
	Container container;

	ContainerInit(&container);
	printf("%d\n", container.count);
	ContainerFree(&container);

	return 0;
}
