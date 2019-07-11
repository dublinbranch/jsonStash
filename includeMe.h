#ifndef RAPIDJSON_INCLUDEME_H
#define RAPIDJSON_INCLUDEME_H

void rapidAssert(bool condition);
#define RAPIDJSON_ASSERT(x) rapidAssert(x); //Do not call ABORT, call our custom assert which has inside the stack unwid via Backward
#define RAPIDJSON_SSE42 1 //why not ? we do not target gameboy anymore
#define RAPIDJSON_48BITPOINTER_OPTIMIZATION 1 //stuff some data in the high part of 64bit ptr (x64 IGNORE after bit 48) 
#define RAPIDJSON_PARSE_DEFAULT_FLAGS 32 //add the ability to have comment inside 

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


#endif // RAPIDJSON_INCLUDEME_H
