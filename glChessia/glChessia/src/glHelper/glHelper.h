#ifndef _GL_HELPER_API_EXPORTS_
#define _GL_HELPER_API_EXPORTS_

#ifdef GLHELPER_EXPORTS
#define GL_HELPER_API __declspec(dllexport)
#else
#define GL_HELPER_API __declspec(dllimport)
#endif

#endif
