#ifndef CONFIG_H
#define CONFIG_H

#define FUNCVIZ_PROJECT_NAME  "@CMAKE_PROJECT_NAME@"

#define FUNCVIZ_CONFIG_DATE   "@FUNCVIZ_CONFIG_DATE@"
#define FUNCVIZ_CONFIG_OS     "@CMAKE_HOST_SYSTEM_VERSION@"
#define FUNCVIZ_CONFIG_CMVER  "@CMAKE_VERSION@"
#define FUNCVIZ_CONFIG_ARCH   "@CMAKE_HOST_SYSTEM_PROCESSOR@"
#define FUNCVIZ_CONFIG_ENDIAN "@CMAKE_CXX_BYTE_ORDER@"
#define FUNCVIZ_CONFIG_COMPID "@CMAKE_CXX_COMPILER_ID@"

#define FUNCVIZ_VERSION       "@FuncViz_VERSION@"
#define FUNCVIZ_VERSION_MAJOR @FuncViz_VERSION_MAJOR@
#define FUNCVIZ_VERSION_MINOR @FuncViz_VERSION_MINOR@
#define FUNCVIZ_VERSION_PATCH @FuncViz_VERSION_PATCH@
#define FUNCVIZ_VERSION_TWEAK @FuncViz_VERSION_TWEAK@
#define FUNCVIZ_VERSION_TAG   "v@FuncViz_VERSION@"
#define FUNCVIZ_VERSION_DATE  "@FUNCVIZ_VERSION_DATE@"

#define FUNCVIZ_FOUND_DOXYGEN @FUNCVIZ_FOUND_DOXYGEN@
#define FUNCVIZ_FOUND_BTEST   @FUNCVIZ_FOUND_BTEST@
#define FUNCVIZ_FOUND_MRASTER @FUNCVIZ_FOUND_MRASTER@

#define FUNCVIZ_OPT_DOXYGEN   @FUNCVIZ_OPT_DOXYGEN@
#define FUNCVIZ_OPT_BTEST     @FUNCVIZ_OPT_BTEST@
#define FUNCVIZ_OPT_MRASTER   @FUNCVIZ_OPT_MRASTER@

#include <string>

std::string funcviz_version_string() { return std::string(FUNCVIZ_VERSION_TAG) + " -- " + std::string(FUNCVIZ_VERSION_DATE); }

int funcviz_version_major() { return FUNCVIZ_VERSION_MAJOR; }
int funcviz_version_minor() { return FUNCVIZ_VERSION_MINOR; }
int funcviz_version_patch() { return FUNCVIZ_VERSION_PATCH; }
int funcviz_version_tweak() { return FUNCVIZ_VERSION_TWEAK; }

bool funcviz_support_mraster() { return FUNCVIZ_OPT_MRASTER; }

#endif
