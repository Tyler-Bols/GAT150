#pragma once
#include <string>
#ifndef NDEBUG

#define ASSERT(condition) ((void)0))
#define ASSERT_MSG(condition,message) ((void)0)


#else

#define ASSERT(condition) _assert((condition),#condition,_FILE_,_LINE_,_func_)
#define ASSERT_MSG(condition,message) _assert((condition),#condition,_FILE_,_LINE_,_func_, message)
#endif

void _assert
(
	bool condition,
	const std::string& conditionString,
	const std::string& filename,
	int line,
	const std::string& functionName
);
void _assert
(
	bool condition,
	const std::string& conditionString,
	const std::string& filename,
	int line,
	const std::string& functionName,
	const std::string& message
);