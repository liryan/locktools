dnl $Id$
dnl config.m4 for extension locktools

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(locktools, for locktools support,
Make sure that the comment is aligned:
[  --with-locktools             Include locktools support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(locktools, whether to enable locktools support,
dnl Make sure that the comment is aligned:
dnl [  --enable-locktools           Enable locktools support])

if test "$PHP_LOCKTOOLS" != "no"; then
  dnl Write more examples of tests here...
  AC_MSG_CHECKING([checking pthread support])
  dnl # --with-locktools -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/locktools.h"  # you most likely want to change this
  dnl if test -r $PHP_LOCKTOOLS/$SEARCH_FOR; then # path given as parameter
  dnl   LOCKTOOLS_DIR=$PHP_LOCKTOOLS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for locktools files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LOCKTOOLS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LOCKTOOLS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the locktools distribution])
  dnl fi

  dnl # --with-locktools -> add include path
  dnl PHP_ADD_INCLUDE($LOCKTOOLS_DIR/include)

  dnl # --with-locktools -> check for lib and symbol presence
  dnl LIBNAME=locktools # you may want to change this
  dnl LIBSYMBOL=locktools # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LOCKTOOLS_DIR/$PHP_LIBDIR, LOCKTOOLS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LOCKTOOLSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong locktools lib version or lib not found])
  dnl ],[
  dnl   -L$LOCKTOOLS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(LOCKTOOLS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(locktools, locktools.c, $ext_shared)
fi
