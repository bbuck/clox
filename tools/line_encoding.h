#ifndef CLOX_TOOLS_LINE_ENCODING_H_
#define CLOX_TOOLS_LINE_ENCODING_H_

#include "common.h"

typedef struct LineInfo {
	int end;
	int line;
} LineInfo;

typedef struct LineInfoList {
	int count;
	int capacity;
	LineInfo *nodes;
} LineInfoList;

LineInfoList *LineInfoListCreate();
void LineInfoListInit(LineInfoList *line_info_list);
void LineInfoListAddLine(LineInfoList *line_info_list, int line);
int LineInfoListGetLine(LineInfoList *line_info_list, int index);
void LineInfoListFree(LineInfoList *line_info_list);

#endif
