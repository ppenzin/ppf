/* This generated file is for internal use. Do not include it from headers. */

#ifdef PPF_CONFIG_H
#error config.h can only be included once
#else
#define PPF_CONFIG_H

/* Bug report URL. */
#define BUG_REPORT_URL "${BUG_REPORT_URL}"

/* Default linker to use. */
#define PPF_DEFAULT_LINKER "${PPF_DEFAULT_LINKER}"

/* Default runtime library to use. */
#define PPF_DEFAULT_RTLIB "${PPF_DEFAULT_RTLIB}"

/* Multilib suffix for libdir. */
#define PPF_LIBDIR_SUFFIX "${PPF_LIBDIR_SUFFIX}"

/* Relative directory for resource files */
#define PPF_RESOURCE_DIR "${PPF_RESOURCE_DIR}"

/* Default <path> to all compiler invocations for --sysroot=<path>. */
#define DEFAULT_SYSROOT "${DEFAULT_SYSROOT}"

/* Directory where gcc is installed. */
#define GCC_INSTALL_PREFIX "${GCC_INSTALL_PREFIX}"

/* Define if we have libxml2 */
#cmakedefine PPF_HAVE_LIBXML ${PPF_HAVE_LIBXML}

/* Define if we have z3 and want to build it */
#cmakedefine PPF_ANALYZER_WITH_Z3 ${PPF_ANALYZER_WITH_Z3}

/* Define if we have sys/resource.h (rlimits) */
#cmakedefine PPF_HAVE_RLIMITS ${PPF_HAVE_RLIMITS}

/* The LLVM product name and version */
#define BACKEND_PACKAGE_STRING "${BACKEND_PACKAGE_STRING}"

/* Linker version detected at compile time. */
#cmakedefine HOST_LINK_VERSION "${HOST_LINK_VERSION}"

/* pass --build-id to ld */
#cmakedefine ENABLE_LINKER_BUILD_ID

#endif
