/****************************************************************************
 *
 * getopt() replacement
 * Copyright (c) 2007 Burlex
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech ASA of Norway and appearing in the file
 * COPYING included in the packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef _ANTRIX_GETOPT_H
#define _ANTRIX_GETOPT_H

/* getopt() wrapper */
#define antrix_no_argument            0
#define antrix_required_argument      1
#define antrix_optional_argument      2
struct antrix_option
{
	char *name;
	int has_arg;
	int *flag;
	int val;
};
extern char antrix_optarg[514];
int antrix_getopt_long_only (int ___argc, char *const *___argv, const char *__shortopts, const struct antrix_option *__longopts, int *__longind);

#endif
