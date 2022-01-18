#include <stdlib.h>

#include "line_encoding.h"
#include "../memory.h"

/**
 * @brief Create a new \c LineInfoList and return a pointer to it.
 *
 * @return LineInfoList* The newly created \c LineInfoList pointer.
 */
LineInfoList *LineInfoListCreate() {
	LineInfoList *list = (LineInfoList *)malloc(sizeof(LineInfoList));
	LineInfoListInit(list);

	return list;
}

/**
 * @brief Initialize the LineInfoList with zero values.
 *
 * @param line_info_list The \c LineInfoList pointer.
 */
void LineInfoListInit(LineInfoList *line_info_list) {
	line_info_list->count = 0;
	line_info_list->capacity = 0;
	line_info_list->nodes = NULL;
}

// append a node to the list of nodes
static void LineInfoListAppendNode(LineInfoList *line_info_list, LineInfo node) {
	line_info_list->nodes[line_info_list->count] = node;
	line_info_list->count++;
}

/**
 * @brief Add a line number to the LineInfoList.
 *
 * Adds a line number to the \c LineInfoList provided. The specific behavior of this function
 * depends on what is currently in the \c LineInfoList provided. An important note is that this
 * function is not meant for \a inserting a line number. So it's expected that the given line
 * number is either the same as the last line number, or comes after it.
 *
 * If there is currently no line info in the list then a new node started at index 0 and ending at
 * index 0 is added for the line.
 *
 * If there is already line info, and the last line_info node matches the line given, then that
 * nodes end index is incremented.
 *
 * Lastly, if the line provided does not match the last node's line then we add a new node for this
 * line starting and ending after the end index of the last node.
 *
 * @param line_info_list The \c LineInfoList pointer.
 * @param line The line number to add to the list.
 */
void LineInfoListAddLine(LineInfoList *line_info_list, int line) {
	if (line_info_list->capacity <= line_info_list->count) {
		size_t old_cap = line_info_list->capacity;
		line_info_list->capacity = GROW_CAPACITY(old_cap);
		line_info_list->nodes = GROW_ARRAY(
			LineInfo, line_info_list->nodes, old_cap, line_info_list->capacity);
	}

	// empty list
	if (line_info_list->count == 0) {
		LineInfo new_node = {
			.end = 0,
			.line = line,
		};
		LineInfoListAppendNode(line_info_list, new_node);

		return;
	}

	// if we have at least one node

	LineInfo last_node = line_info_list->nodes[line_info_list->count - 1];
	// If the last node is the line we're adding we just increment it's "end"
	// offset
	if (last_node.line == line) {
		last_node.end++;
		line_info_list->nodes[line_info_list->count - 1] = last_node;

		return;
	}

	// the new node starts and ends at the next offset from the last node
	LineInfo new_node = {
		.end = last_node.end + 1,
		.line = line,
	};
	LineInfoListAppendNode(line_info_list, new_node);
}

/**
 * @brief Find a line number from a given index.
 *
 * Search for an index in the encoded line information list. This will perform a binary search on
 * the information list searching for a line info node that references the index (where index is in
 * the range (start, end)) and returns that line number.
 *
 * If the given line number cannot be found, then a \c -1 is returned instead.
 *
 * @param line_info_list The \c LineInfoList pointer.
 * @param index The index of the value seeking line information for
 * @return int The line number of the given index (or -1 if not found).
 */
int LineInfoListGetLine(LineInfoList *line_info_list, size_t index) {
	size_t lower = 0;
	size_t upper = line_info_list->count;

	while (lower <= upper) {
		size_t target_index = (lower + upper) / 2;
		LineInfo node = line_info_list->nodes[target_index];
		if (target_index - 1 < 0 && index <= node.end) {
			return node.line;
		} else if (line_info_list->nodes[target_index - 1].end < index && index <= node.end) {
			return node.line;
		} else if (index > node.end) {
			lower = target_index + 1;
		} else {
			upper = target_index - 1;
		}
	}

	return -1;
}

/**
 * @brief Free the LineInfoList data, cleaning up memory.
 *
 * @param line_info_list The \c LineInfoList pointer.
 */
void LineInfoListFree(LineInfoList **line_info_list) {
	LineInfoList *list = *line_info_list;
	FREE_ARRAY(LineInfo, list->nodes, list->capacity);
	free(*line_info_list);
	*line_info_list = NULL;
}
