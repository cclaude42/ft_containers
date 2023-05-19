#ifndef CONTAINERS_HPP
# define CONTAINERS_HPP

# include <iostream>

# include "algorithm.hpp"
# include "exception.hpp"
# include "functional.hpp"
# include "iterator.hpp"
# include "string.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

# ifndef MACOS_
#  if __APPLE__
#   define MACOS_ 1
#  else
#   define MACOS_ 0
#  endif
# endif

# ifndef RED_
#  define RED_ true
# endif
# ifndef BLACK_
#  define BLACK_ false
# endif

# ifndef SIZE_OR_CAP_
#  if __APPLE__
#   define SIZE_OR_CAP_ _capacity
#  else
#   define SIZE_OR_CAP_ _size
#  endif
# endif

#endif
