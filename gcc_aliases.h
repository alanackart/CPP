
#ifndef __GCC_ALIASES_H__
#define __GCC_ALIASES_H__ 1


# define _strong_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((alias (#name)));
# define strong_alias(name, aliasname) _strong_alias(name, aliasname)

#  define _weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));
#ifdef __CYGWIN__
#  define weak_alias(name, aliasname) _strong_alias(name, aliasname)
#else
#  define weak_alias(name, aliasname) _weak_alias (name, aliasname)
#endif

#  define _weak_extern(expr) _Pragma (#expr)
#  define weak_extern(symbol) _weak_extern (weak symbol)

#endif
