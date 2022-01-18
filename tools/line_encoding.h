#ifndef CLOX_TOOLS_LINE_ENCODING_H_
#define CLOX_TOOLS_LINE_ENCODING_H_

#include "common.h"

typedef struct LineInfo {
	size_t end;
	int line;
} LineInfo;

typedef struct LineInfoList {
	size_t count;
	size_t capacity;
	LineInfo *nodes;
} LineInfoList;

LineInfoList *LineInfoListCreate();
void LineInfoListInit(LineInfoList *line_info_list);
void LineInfoListAddLine(LineInfoList *line_info_list, int line);
int LineInfoListGetLine(LineInfoList *line_info_list, size_t index);
void LineInfoListFree(LineInfoList **line_info_list);

#endif
