#ifndef STATEFUL_COMPARATOR_HPP
# define STATEFUL_COMPARATOR_HPP
# include <string>

// this class compare two string after applying a rotation on it
class stateful_comparator
{
private:
	int	key;
public:
	stateful_comparator() : key(rand()) {} // hehe
	stateful_comparator(const stateful_comparator &other) : key(other.key) {}
	stateful_comparator &operator=(const stateful_comparator &other) {
		this->key = other.key;
		return *this;
	}
	bool	operator()(const std::string &l, const std::string &r) const
	{
		return rotate(l) < rotate(r);
	}
	std::string rotate(std::string s) const
	{
		if (s.empty())
			return s;
		int shift = key % s.size();
		return s.substr(shift) + s.substr(0, shift);
	}
	friend bool operator==(const stateful_comparator &l, const stateful_comparator &r) {return l.key == r.key;}
	friend bool operator!=(const stateful_comparator &l, const stateful_comparator &r) {return l.key != r.key;}
};

#endif