#include "../include/Exception.h"

jmp_buf exception_buffer; 						
enum ObjExceptionType  exception_code;
//enum ObjExceptionType ExceptionType;

const struct ObjException Exception = {.message = "An Exception", .code = 254};
const struct ObjException NullPointerException = {.message = "Null Pointer Exception", .code = __NullPointerException__};
const struct ObjException FileWriteException = {.message = "An exception occurred in file recording", .code = __FileWriteException__};
const struct ObjException FileOpenException = {.message = "An exception occurred while opening file", .code = __FileOpenException__};
const struct ObjException FileReadException = {.message = "An exception occurred in file reading", .code = __FileReadException__};
const struct ObjException ReWindExeption = {.message = "An exception occurred in Rewind operating", .code = __ReWindException__};
const struct ObjException FileSeekException = {.message = "An exception occurred in Seek operating", .code = __FileSeekException__};
const struct ObjException ClearErrorsException = {.message = "An exception occurred in clear errors operating", .code = __ClearErrorsException__};
const struct ObjException FileCloseException = {.message = "An exception occurred in close operating", .code = __FileCloseException__};
const struct ObjException MemoryAllocationException = {.message = "Unable to allocate memory", .code = __MemoryAllocationException__};