/*
 * Unit tests for the filter module.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "filter.h"

#define MAXSTR (50)

/*
 * Local test and support functions.
 */
static bool test_filter_ch_index() ;
static bool test_filter_ch_ptr() ;
static bool test_filter_any_index() ;
static bool test_filter_any_ptr() ;
static bool test_filter_substr() ;
static void test_failure() ;
static void summary() ;
static bool assert_impl(bool expr, char *f_name, int f_line, char *message) ;
static bool assert_eql_impl(
	char *want, char *have, char *f_name, int f_line, char *message) ;

/*
 * Macros so we don't have to explicitly pass filenames and line numbers
 * for each assertion.
 */
#define assert(e, m) assert_impl(e, __FILE__, __LINE__, m)
#define assert_eql(w, h, m) assert_eql_impl((w), (h), __FILE__, __LINE__, (m))

/*
 * Macro to determine whether of not to strings are equal.
 */
#define streql(a, b) (strcmp((a), (b)) == 0)

/*
 * Number of tests, number of assertions passed, number of assertions failed.
 */
static int ntests = 0 ;
static int npass = 0 ;
static int nfail = 0 ;

/*
 * Strings used in the tests.
 * We need constant names for them so we can test accuracy of
 * the returned pointed.
 */

char ts_abccba[] = "abccba" ;
char ts_empty[] = "" ;

int main(int ac, char **av) {
	fprintf(stderr, "** Tests of filter_ch_index **\n") ;
	if( ! test_filter_ch_index() ) {
		test_failure() ;
	}

	fprintf(stderr, "** Tests of filter_ch_ptr **\n") ;
	if( ! test_filter_ch_ptr() ) {
		test_failure() ;
	}

	fprintf(stderr, "** Tests of filter_any_index **\n") ;
	if( ! test_filter_any_index() ) {
		test_failure() ;
	}

	fprintf(stderr, "** Tests of filter_any_ptr **\n") ;
	if( ! test_filter_any_ptr() ) {
		test_failure() ;
	}

	fprintf(stderr, "** Tests of filter_substr **\n") ;
	if( ! test_filter_substr() ) {
		test_failure() ;
	}

	summary() ;
	return 0 ;
}

static bool test_filter_ch_index() {
	bool pass = true ;
	char result[MAXSTR+1] ;

	ntests++ ;

	filter_ch_index(ts_abccba, result, 'a') ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("bccb", result,
		"filter_ch_index(\"abccba\", result, 'a')") && pass ;

	filter_ch_index(ts_abccba, result, 'b') ;
	pass = assert_eql("acca", result,
		"filter_ch_index(\"abccba\", result, 'b')") && pass ;

	filter_ch_index(ts_abccba, result, 'c') ;
	pass = assert_eql("abba", result,
		"filter_ch_index(\"abccba\", result, 'c')") && pass ;

	filter_ch_index(ts_abccba, result, 'z') ;
	pass = assert(! result[6],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_abccba, result,
		"filter_ch_index(\"abccba\", result, 'z')") && pass ;

	filter_ch_index(ts_empty, result, 'a') ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_ch_index(\"\", result, 'a')") && pass ;

	return pass ;
}

static bool test_filter_ch_ptr() {
	bool pass = true ;
	char *result ;

	ntests++ ;

	result = filter_ch_ptr(ts_abccba, 'a') ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("bccb", result,
		"filter_ch_ptr(\"abccba\", 'a')") && pass ;
	free(result) ;

	result = filter_ch_ptr(ts_abccba, 'b') ;
	pass = assert_eql("acca", result,
		"filter_ch_ptr(\"abccba\", 'b')") && pass ;
	free(result) ;

	result = filter_ch_ptr(ts_abccba, 'c') ;
	pass = assert_eql("abba", result,
		"filter_ch_ptr(\"abccba\", 'c')") && pass ;
	free(result) ;

	result = filter_ch_ptr(ts_abccba, 'z') ;
	pass = assert(! result[6],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_abccba, result,
		"filter_ch_ptr(\"abccba\", 'z')") && pass ;
	free(result) ;

	result = filter_ch_ptr(ts_empty, 'a') ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_ch_ptr(\"\", 'a')") && pass ;
	free(result) ;

	return pass ;
}

static bool test_filter_any_index() {
	bool pass = true ;
	char result[MAXSTR+1] ;

	ntests++ ;

	filter_any_index(ts_abccba, result, "cba") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_any_index(\"abccba\", result, \"cba\")") && pass ;

	filter_any_index(ts_abccba, result, "ba") ;
	pass = assert(! result[2],
		"result not properly terminated") && pass ;
	pass = assert_eql("cc", result,
		"filter_any_index(\"abccba\", result, \"ba\")") && pass ;

	filter_any_index(ts_abccba, result, "c") ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("abba", result,
		"filter_any_index(\"abccba\", result, \"c\")") && pass ;

	filter_any_index(ts_abccba, result, "") ;
	pass = assert(! result[6],
		"result not properly terminated") && pass ;
	pass = assert_eql("abccba", result,
		"filter_any_index(\"abccba\", result, \"\")") && pass ;

	filter_any_index(ts_empty, result, "cba") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_any_index(\"\", result, \"cba\")") && pass ;

	return pass ;
}

static bool test_filter_any_ptr() {
	bool pass = true ;
	char *result ;

	ntests++ ;

	result = filter_any_ptr(ts_abccba, "cba") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_any_ptr(\"abccba\", \"cba\")") && pass ;
	free(result) ;

	result = filter_any_ptr(ts_abccba, "ba") ;
	pass = assert(! result[2],
		"result not properly terminated") && pass ;
	pass = assert_eql("cc", result,
		"filter_any_ptr(\"abccba\", \"ba\")") && pass ;
	free(result) ;

	result = filter_any_ptr(ts_abccba, "c") ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("abba", result,
		"filter_any_ptr(\"abccba\", \"c\")") && pass ;
	free(result) ;

	result = filter_any_ptr(ts_abccba, "") ;
	pass = assert(! result[6],
		"result not properly terminated") && pass ;
	pass = assert_eql("abccba", result,
		"filter_any_ptr(\"abccba\", \"\")") && pass ;
	free(result) ;

	result = filter_any_ptr(ts_empty, "cba") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_any_ptr(\"\", \"cba\")") && pass ;
	free(result) ;

	return pass ;
}

static bool test_filter_substr() {
	bool pass = true ;
	char *result ;

	ntests++ ;

	result = filter_substr(ts_abccba, "cba") ;
	pass = assert(! result[3],
		"result not properly terminated") && pass ;
	pass = assert_eql("abc", result,
		"filter_substr(\"abccba\", \"cba\")") && pass ;
	free(result) ;

	result = filter_substr(ts_abccba, "ab") ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("ccba", result,
		"filter_substr(\"abccba\", \"ab\")") && pass ;
	free(result) ;

	result = filter_substr(ts_abccba, "c") ;
	pass = assert(! result[4],
		"result not properly terminated") && pass ;
	pass = assert_eql("abba", result,
		"filter_substr(\"abccba\", \"c\")") && pass ;
	free(result) ;

	result = filter_substr("abcabcabc", "abc") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_substr(\"abcabcabc\", \"abc\")") && pass ;
	free(result) ;

	result = filter_substr(ts_empty, "cba") ;
	pass = assert(! result[0],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_empty, result,
		"filter_substr(\"\", \"cba\")") && pass ;
	free(result) ;

	result = filter_substr(ts_abccba, "ccbx") ;
	pass = assert(! result[6],
		"result not properly terminated") && pass ;
	pass = assert_eql(ts_abccba, result,
	   "filter_substr(\"abccba\", \"ccbx\")") &&
	       pass ;
	free(result) ;

	result = filter_substr("Moses supposes his toeses are roses.", "oses") ;
	pass = assert(! result[24],
		"result not properly terminated") && pass ;
	pass = assert_eql("M supp his toeses are r.", result,
	   "filter_substr(\"Moses supposes his toeses are roses.\", \"oses\")") &&
	       pass ;
	free(result) ;

	return pass ;
}

static void test_failure() {
	fprintf(stderr, "** Test failed - exiting **\n") ;
	summary() ;
	exit(1) ;
}
	
static void summary() {
	fprintf(stderr, "*** TEST SUMMARY ***\n") ;
	fprintf(stderr, "%d test%s, ",
			ntests, ntests != 1 ? "s" : "");
	fprintf(stderr, "%d assertion%s ",
			npass + nfail, npass + nfail != 1 ? "s" : "") ;
	fprintf(stderr, "(%d passed/%d failed)\n",
			npass, nfail) ;
}

static bool assert_impl(bool expr, char *f_name, int f_line, char *message) {
	if( expr ) {
		npass++ ;
		return true ;
	}

	nfail++ ;
	if( message ) {
		fprintf(stderr, "Assertion failure (%s @ %d): %s\n",
				f_name, f_line, message) ;
	} else {
		fprintf(stderr, "Assertion failure (%s @ %d)\n",
				f_name, f_line) ;
	}
	return false ;
}

static bool assert_eql_impl(char *want, char *have, char *f_name,
		int f_line, char *message) {
	if( streql(want, have) ) {
		npass++ ;
		return true ;
	}

	nfail++ ;
	fprintf(stderr, "Assertion failure (%s @ %d)\n", f_name, f_line) ; 

	if( message ) {
		fprintf(stderr, "%s\n", message) ;
	}
	fprintf(stderr, "    Want: \"%s\"\n", want) ;
	fprintf(stderr, "    Have: \"%s\"\n", have) ;
	return false ;
}
