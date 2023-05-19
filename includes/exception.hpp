#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <iostream>
# include <exception>

namespace ft
{
	//////////////////////////////
	// Exception base class
	//////////////////////////////

	class exception {
	public:
				exception					(void)					throw()		{};
				exception					(const exception &)		throw()		{};
		virtual ~exception					(void)					throw()		{};

				exception &		operator=	(const exception &)		throw()		{ return (*this); };
		virtual const char * 	what		(void) const			throw()		{ return "ft::exception"; };
	};

	//////////////////////////////
	// Out of range
	//////////////////////////////

	class out_of_range : public ft::exception {
	public:
		explicit out_of_range	(const std::string & what_arg)		{ s = what_arg.c_str(); };
		const char * what		(void) const throw()				{ return s; };
	private:
		const char * s;
	};

	//////////////////////////////
	// Length error
	//////////////////////////////

	class length_error : public ft::exception {
	public:
		explicit length_error	(const std::string & what_arg)		{ s = what_arg.c_str(); };
		const char * what		(void) const throw()				{ return s; };
	private:
		const char * s;
	};
}

#endif
