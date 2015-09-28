// $Id: svn_revision.h 921 2007-07-21 07:41:21Z Burlex $

#ifndef _SVN_REVISION_H
#define _SVN_REVISION_H

static char * REVISION_TEXT = "$Rev: 921 $";

inline int g_getRevision()
{
	char * p = REVISION_TEXT + 6;
	return atoi(p);
}
///////////////////////////////////
#endif
