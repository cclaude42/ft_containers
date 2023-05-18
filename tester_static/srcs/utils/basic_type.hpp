#ifndef BASIC_TYPE_HPP
# define BASIC_TYPE_HPP

class basic_type
{
public:
	basic_type() {}
	basic_type(const basic_type &) {}
	basic_type &operator=(const basic_type &) {return *this;}
	struct compare
	{
		compare() {}
		compare(const compare &) {}
		bool operator()(const basic_type &, const basic_type &) const {return false;}
	};
	struct unary_predicate
	{
		unary_predicate() {}
		unary_predicate(const unary_predicate &) {}
		bool operator()(const basic_type &) const {return false;}
	};
};

#endif