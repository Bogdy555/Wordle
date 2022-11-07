#ifndef WordleAPI_Macros_hpp

#define WordleAPI_Macros_hpp



#ifdef _DEBUG

#define WORDLEAPI_DEBUG_CALL(X) X
#define WORDLEAPI_RELEASE_CALL(X)

#endif

#ifndef _DEBUG

#define WORDLEAPI_DEBUG_CALL(X)
#define WORDLEAPI_RELEASE_CALL(X) X

#endif



#ifdef _WIN64

#define WORDLEAPI_X86_CALL(X)
#define WORDLEAPI_X64_CALL(X) X

#endif

#ifndef _WIN64

#define WORDLEAPI_X86_CALL(X) X
#define WORDLEAPI_X64_CALL(X)

#endif



#endif
