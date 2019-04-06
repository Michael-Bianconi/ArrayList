/**
 * @author Michael Bianconi
 * @since 04-06-2019
 *
 * Collection of macros for easy verbose mode.

 * To enable, compile with -DVERBOSE.
 */

#ifndef VERBOSE_H
#define VERBOSE_H

/** Prints "<func name>: start\n" */
#ifdef VERBOSE
	#define VERBOSE_FUNC_START printf("%s(): start\n", __func__);
#else
	#define VERBOSE_FUNC_START
#endif

/** Prints "<func name>: end\n" */
#ifdef VERBOSE
	#define VERBOSE_FUNC_END printf("%s(): end\n", __func__);
#else
	#define VERBOSE_FUNC_END
#endif

/** Prints "<func name>: msg" */
#ifdef VERBOSE
	#define VERBOSE_MSG(x,...) printf("%s(): ",__func__); printf(x,__VA_ARGS__);
#else
	#define VERBOSE_MSG(x,...)
#endif

/** Prints "<func name>: msg" to stderr */
#ifdef VERBOSE
	#define VERBOSE_ERR(x,...) fprintf(stderr, "%s(): ",__func__); fprintf(stderr, x, __VA_ARGS__);
#else
	#define VERBOSE_ERR
#endif

#endif