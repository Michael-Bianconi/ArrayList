/**
 * @author Michael Bianconi
 * @since 04-06-2019
 *
 * Collection of macros for easy verbose mode.
 *
 * To enable function calls, compile with -DVERBOSE_ENABLE_FUNC
 * To enable messages, compile with -DVERBOSE_ENABLE_MSG
 * To enable errors, compile with -DVERBOSE_ENABLE_ERR
 * To enable testing output, compile with -DVERBOSE_ENABLE_TESTS
 * To enable all messages, compile with -DVERBOSE_ENABLE_ALL
 */

#ifndef VERBOSE_H
#define VERBOSE_H


/** Prints "<func name>: start\n" */
#if defined(VERBOSE_ENABLE_FUNC) || defined(VERBOSE_ENABLE_ALL)
	#define VERBOSE_FUNC_START printf("%s(): start\n", __func__);
	#define VERBOSE_FUNC_END printf("%s(): end\n", __func__);
#else
	#define VERBOSE_FUNC_START
	#define VERBOSE_FUNC_END
#endif


/** Prints "<func name>: msg" */
#if defined(VERBOSE_ENABLE_MSG) || defined(VERBOSE_ENABLE_ALL)
	#define VERBOSE_MSG(x) printf("%s(): ",__func__); printf(x);
	#define VERBOSE_MSGARGS(x,...) printf("%s(): ",__func__); printf(x,__VA_ARGS__);
#else
	#define VERBOSE_MSG(x)
	#define VERBOSE_MSGARGS(x,...)
#endif


/** Prints to stderr */
#if defined(VERBOSE_ENABLE_ERR) || defined(VERBOSE_ENABLE_ALL)
	#define VERBOSE_ERR(x) fprintf(stderr, "%s(): ",__func__); fprintf(stderr, x);
	#define VERBOSE_ERRARGS(x,...) fprintf(stderr, "%s(): ",__func__); fprintf(stderr, x, __VA_ARGS__);
#else
	#define VERBOSE_ERR(x)
	#define VERBOSE_ERRARGS(x,...)
#endif

/** Used for unit testing */
#if defined(VERBOSE_ENABLE_TESTS) || defined(VERBOSE_ENABLE_ALL)
	#define VERBOSE_TESTS_SUCCESS printf("%s(): success\n",__func__);
	#define VERBOSE_TESTS_FAILURE printf("%s(): failure\n",__func__);
	#define VERBOSE_TESTS(x) printf("%s(): ",__func__); printf(x);
	#define VERBOSE_TESTSARGS(x,...) printf("%s(): ",__func__); printf(x,__VA_ARGS__);
#else
	#define VERBOSE_TESTS(x)
	#define VERBOSE_TESTSARGS(x,...)
#endif

#endif