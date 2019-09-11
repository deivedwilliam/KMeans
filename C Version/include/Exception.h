#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <setjmp.h>
#include <stdio.h>

#define NULLReference(Obj) (Obj == ((void*)0x00000000))

#define try    										\
													\
	exception_code = setjmp(exception_buffer);		\
	if(!exception_code)								


#define catch(ObjException)	else if(ObjException.code == exception_code)
#define throw(code) longjmp(exception_buffer, code)
#define finally else


#define PrintExceptionStdOut(Obj) printf("File: %s Function: %s %i %s, Exception Code: %i\n",__FILE__, __FUNCTION__, __LINE__, Obj.message, Obj.code); exit(-1);


#define FileOpen(ptr, filename, mode)				\
													\
	try												\
	{												\
		ptr = fopen(filename, mode);				\
		if(ptr == NULL)								\
		{											\
			throw(__FileOpenException__);			\
		}											\
	}catch(FileOpenException)						\
	{												\
		PrintExceptionStdOut(FileOpenException);	\
	}


#define FileWrite(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fwrite(ptr, size, count, file);		\
			if(res != (size*count))						\
			{											\
				ExceptionType = __FileWriteException__;	\
				throw(__FileWriteException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(__FileWriteException__)						\
	{													\
		PrintExceptionStdOut(FileWriteException);		\
	}													\
	catch(__NullPointerException__)						\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define FileRead(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fread(ptr, size, count, file);		\
			if(res != (size*count))						\
			{											\
				ExceptionType = __FileReadException__;	\
				throw(__FileReadException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(__FileReadException__)						\
	{													\
		PrintExceptionStdOut(FileReadException);		\
	}													\
	catch(__NullPointerException__)						\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define ReWind(file)									\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			rewind(file);								\
			if(ferror(file))							\
			{											\
				ObjExceptionType = __ReWindException__;	\
				throw(__ReWindException__);				\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(ReWindExeption)								\
	{													\
		PrintExceptionStdOut(ReWindExeption);			\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define FileSeek(file, offset, origin)					\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			fseek(file, offset, origin);				\
			if(ferror(file))							\
			{											\
				ObjExceptionType=__FileSeekException__; \
				throw(__FileSeekException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileSeekException)							\
	{													\
		PrintExceptionStdOut(FileSeekException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define ClearErr(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			clearerr(file);								\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
		exit(-1);										\
	}



#define FileClose(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			if(fclose(file))							\
			{											\
				throw(__FileCloseException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileCloseException)							\
	{													\
		PrintExceptionStdOut(FileCloseException);		\										\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}


extern enum ObjExceptionType
{
	__NoExceptionsOccurred = 255,
	__FileOpenException__ = 1,
	__FileReadException__,
	__FileFlushException__,		
	__MemoryAllocationException__,
	__FileWriteException__,
	__NullPointerException__,
	__EndOfFileException__,
	__FileReOpenException__,
	__FileSeekException__,
	__PrintException__,
	__ReWindException__,
	__ClearErrorsException__,
	__FileCloseException__
}ExceptionType;

extern const struct ObjException
{
	unsigned char* message;
	enum ObjExceptionType code; 
}Exception;

extern jmp_buf exception_buffer; 						
extern  enum ObjExceptionType  exception_code;
			
//extern enum ObjExceptionType ExceptionType;
extern const struct ObjException NullPointerException;
extern const struct ObjException Exception;
extern const struct ObjException FileWriteException;
extern const struct ObjException FileOpenException;
extern const struct ObjException FileReadException;
extern const struct ObjException ReWindExeption;
extern const struct ObjException FileSeekException;
extern const struct ObjException ClearErrorsException;
extern const struct ObjException FileCloseException;
extern const struct ObjException MemoryAllocationException;
#endif