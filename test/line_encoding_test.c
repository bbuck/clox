#include <stddef.h>

#include <criterion/criterion.h>

#include "../tools/line_encoding.h"

static void AssertLineInfoListInitialized(LineInfoList *list) {
	cr_assert(
		list->count == 0, "Expected LineInfoList::count to be %d, but got %zu", 0, list->count);
	cr_assert(
		list->capacity == 0,
		"Expected LineInfoList::capacity to be %d, but got %zu",
		0,
		list->capacity);
	cr_assert(list->nodes == NULL, "Expected LineInfoList::nodes to be NULL");
}

Test(LineInfoList, LineInfoListCreate) {
	LineInfoList *list = NULL;
	list = LineInfoListCreate();

	cr_assert(list != NULL, "Expected LineInfoListCreate() != NULL");

	LineInfoListFree(&list);
}

Test(LineInfoList, LineInfoListInit) {
	LineInfoList *list = LineInfoListCreate();

	AssertLineInfoListInitialized(list);

	LineInfoListFree(&list);
}

// NOTE(bbuck): LineInfoList::nodes uses the same dynamic growth logic as Chunk so I will not be
//     writing tests to verify count/capacity growth.

Test(LineInfoList, LineInfoListAddLine) {
	LineInfoList *list = LineInfoListCreate();

	LineInfoListAddLine(list, 1);

	cr_assert(
		list->count == 1, "Expected LineInfoList::count to be %d, but got %zu", 0, list->count);
	cr_assert(
		list->nodes[0].end == 0,
		"Expected LineInfo::end to be %d, but got %zu",
		0,
		list->nodes[0].end);
	cr_assert(
		list->nodes[0].line == 1,
		"Expected LineInfo::line to be %d, but got %d",
		1,
		list->nodes[0].line);

	LineInfoListAddLine(list, 1);

	cr_assert(
		list->count == 1, "Expected LineInfoList::count to be %d, but got %zu", 0, list->count);
	cr_assert(
		list->nodes[0].end == 1,
		"Expected LineInfo::end to be %d, but got %zu",
		1,
		list->nodes[0].end);
	cr_assert(
		list->nodes[0].line == 1,
		"Expected LineInfo::line to be %d, but got %d",
		1,
		list->nodes[0].line);

	LineInfoListAddLine(list, 2);

	cr_assert(
		list->count == 2, "Expected LineInfoList::count to be %d, but got %zu", 0, list->count);
	cr_assert(
		list->nodes[1].end == 2,
		"Expected LineInfo::end to be %d, but got %zu",
		2,
		list->nodes[1].end);
	cr_assert(
		list->nodes[1].line == 2,
		"Expected LineInfo::line to be %d, but got %d",
		2,
		list->nodes[1].line);

	LineInfoListFree(&list);
}

Test(LineInfoList, LineInfoListGetLine) {
	LineInfoList *list = LineInfoListCreate();

	for (int i = 0; i < 50; ++i) {
		int line = (i / 10) + 1;
		LineInfoListAddLine(list, line);
	}

	cr_assert(
		list->count == 5, "Expected LineInfoList::count to be %d, but got %zu", 5, list->count);

	int line = LineInfoListGetLine(list, 5);
	cr_assert(line == 1, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 5, 1, line);

	line = LineInfoListGetLine(list, 15);
	cr_assert(line == 2, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 15, 2, line);

	line = LineInfoListGetLine(list, 25);
	cr_assert(line == 3, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 25, 3, line);

	line = LineInfoListGetLine(list, 35);
	cr_assert(line == 4, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 35, 4, line);

	line = LineInfoListGetLine(list, 45);
	cr_assert(line == 5, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 45, 5, line);

	line = LineInfoListGetLine(list, 55);
	cr_assert(line == -1, "Expected LineInfoListGetLine(..., %d) == %d, but got %d", 55, -1, line);


	LineInfoListFree(&list);
}

Test(LineInfoList, LineInfoListFree) {
	LineInfoList *list = LineInfoListCreate();

	cr_assert(list != NULL, "Expected LineInfoList not to be NULL");

	LineInfoListFree(&list);

	cr_assert(list == NULL, "Expected LineInfoList to be NULL");
}
