/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:31:07 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/29 15:44:20 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** MU_HAI
** MU_KTHXBYE
** MU_DUMMY_FUN
**
** MU_TEST_FUN
** MU_TEST_SUITE
**
** MU_RUN_TEST
** MU_RUN_SUITE
**
** MU_ASSERT
** MU_ASSERT_FATAL
*/

#ifndef MINUNIT
# define MINUNIT

# include <stdio.h> // printf
# include <stdlib.h> // exit

# ifndef TRUE
#  define TRUE  1
#  define FALSE 0
# endif

# ifndef CLR_BLACK
#  define CLR_BLACK "\033[30;01m"
#  define CLR_RED "\033[31;01m"
#  define CLR_GREEN "\033[32;01m"
#  define CLR_YELLOW "\033[33;01m"
#  define CLR_BLUE "\033[34;01m"
#  define CLR_MAGENTA "\033[35;01m"
#  define CLR_CYAN "\033[36;01m"
#  define CLR_WHITE "\033[37;01m"
#  define CLR_RESET "\033[0m"
# endif

typedef void		   (*MU_TEST_FUN)(void);

#define MAX_NAME_SIZE 63
struct s_fun
{
	MU_TEST_FUN f;
	char s[MAX_NAME_SIZE + 1];
};
typedef struct s_fun  t_fun;

typedef t_fun MU_TEST_SUITE[];

# define STRINGIFY(x) #x
# define TOSTRING(x)  STRINGIFY(x)
# define AT			  __FILE__ ":" TOSTRING(__LINE__)

# define FAIL_MSG(test, type, msg)	CLR_WHITE "\n" AT ": " CLR_RED type CLR_RESET msg \
	CLR_RESET "\n\t" test "\n\t " CLR_GREEN "^\n" CLR_RESET
# define MISSING_FUN_MSG(fun)		FAIL_MSG(" " #fun "()", "Error: ", "missing function")
# define FAIL_ASSERT_MSG(test, msg) FAIL_MSG("(" #test ")", "Assertion failed: ", msg)
# define SUCCESS_ASSERT_MSG			CLR_GREEN "." CLR_RESET

# define MU_ASSERT(test, msg, ...)										\
	do {																\
		if (g_exit) {													\
			g_exit = FALSE;												\
			return ;													\
		}																\
		if ((test)) {													\
			printf(SUCCESS_ASSERT_MSG);									\
			g_asserts_success++;										\
		} else {														\
			fprintf(stderr, FAIL_ASSERT_MSG(test, msg), ##__VA_ARGS__);	\
			g_success = FALSE;											\
		}																\
		g_asserts_run++;												\
	} while (0)

# define MU_ASSERT_FATAL(test, msg, ...)					\
	do {													\
		int asserts_success_before = g_asserts_success;		\
		MU_ASSERT(test, msg, ##__VA_ARGS__);				\
		if (asserts_success_before == g_asserts_success) {	\
			return ;										\
		}													\
	} while (0)

# define MU_RUN_TEST(test)						\
	do {										\
		g_success = TRUE;						\
		test();									\
		g_tests_run++;							\
		if (g_success) {						\
			g_tests_success++;					\
		}										\
		printf("\n");							\
	} while (0)

# define MU_RUN_TEST_FROM_SUITE(test_name, suite)						\
	do {																\
		for (size_t suite_counter = 0; suite_counter < sizeof(suite) / sizeof(t_fun); suite_counter++) { \
			if (!strcmp(test_name, suite[suite_counter].s)) {			\
				printf("+ Test %s: ", suite[suite_counter].s);			\
				MU_RUN_TEST(suite[suite_counter].f);					\
				break;													\
			}															\
		}																\
	} while (0)

# define MU_RUN_SUITE(suite, name, ...)									\
	do {																\
		setbuf(stdout, NULL); /* TODO: find a better place for this */	\
		printf("+ Suite " name ":\n", ##__VA_ARGS__);					\
		int tests_run = g_tests_run;									\
		int tests_success = g_tests_success;							\
		int asserts_run = g_asserts_run;								\
		int asserts_success = g_asserts_success;						\
		for (size_t suite_counter = 0; suite_counter < sizeof(suite) / sizeof(t_fun); suite_counter++) { \
			printf("++ Test %s: ", suite[suite_counter].s);				\
			MU_RUN_TEST(suite[suite_counter].f);						\
		}																\
		printf("Tests:	  %d/%d\n", g_tests_success - tests_success , g_tests_run - tests_run); \
		printf("Asserts:  %d/%d\n", g_asserts_success - asserts_success, g_asserts_run - asserts_run); \
		if (g_asserts_success - asserts_success == g_asserts_run - asserts_run \
			&& g_tests_success - tests_success == g_tests_run - tests_run)	{ \
			printf(CLR_GREEN "Suite passed." CLR_RESET "\n\n");			\
			g_suites_success++;											\
		} else {														\
			printf(CLR_RED "Suite failed." CLR_RESET "\n\n");			\
		}																\
		g_suites_run++;													\
	} while (0)

# define MU_DUMMY_FUN(x)						\
	void  __attribute__((weak)) x()				\
	{											\
		fprintf(stderr,	 MISSING_FUN_MSG(x));	\
		g_success = FALSE;						\
		g_exit = TRUE;							\
	}

# define MU_HAI()												\
	int g_tests_run = 0;										\
	int g_tests_success = 0;									\
	int g_asserts_run = 0;										\
	int g_asserts_success = 0;									\
	int g_suites_run = 0;										\
	int g_suites_success = 0;									\
	int g_success = TRUE;										\
	int g_exit = FALSE	/* the missing semi-colon is needed */	\

# define MU_KTHXBYE()													\
	do {																\
		printf("Total Suites:	%d/%d\n", g_suites_success, g_suites_run); \
		printf("Total Tests:	%d/%d\n", g_tests_success, g_tests_run); \
		printf("Total Asserts:	%d/%d\n", g_asserts_success, g_asserts_run); \
		if (g_asserts_success == g_asserts_run && g_tests_success == g_tests_run) {	\
			printf(CLR_GREEN "All tests passed!\n" CLR_RESET);			\
			exit(EXIT_SUCCESS);											\
		}																\
		printf(CLR_RED "Some test(s) failed :/\n" CLR_RESET);			\
		exit(EXIT_FAILURE);												\
	} while (0)

extern int g_tests_run;
extern int g_tests_success;

extern int g_asserts_run;
extern int g_asserts_success;

extern int g_suites_run;
extern int g_suites_success;

extern int g_success;
extern int g_status;
extern int g_exit;

#endif /* MINUNIT */
