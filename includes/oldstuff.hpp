// Old vector iterator

template <bool IsConst, bool IsRev>
class vectorIterator {
public:
	// Friend other instances
	template <bool U, bool V>
	friend class vectorIterator;
	// Member types
	typedef typename ft::conditional<IsConst, const T, T>::type			ValueType;
	typedef typename ft::conditional<IsConst,
	typename Alloc::const_pointer, typename Alloc::pointer>::type		PointerType;
	typedef typename ft::conditional<IsConst,
	typename Alloc::const_reference, typename Alloc::reference>::type	ReferenceType;

	// -structors
	vectorIterator		(void)											{ _ptr = NULL; }
	vectorIterator		(const PointerType ptr)							{ _ptr = ptr; }
	vectorIterator		(const vectorIterator & x)						{ _ptr = x._ptr; }
	~vectorIterator		(void)											{}
	// Cast non-const => const
	template <bool U, bool V>
	vectorIterator		(const vectorIterator<U, V> & x,
						typename ft::enable_if<!U>::type* = 0,
						typename ft::enable_if<IsRev == V>::type* = 0)	{ _ptr = x._ptr; }

	// Assignment
	vectorIterator &	operator=	(const vectorIterator & x)			{ _ptr = x._ptr; return (*this); }
	vectorIterator &	operator+=	(int n)								{ _ptr = IsRev ? _ptr - n : _ptr + n; return (*this); }
	vectorIterator &	operator-=	(int n)								{ _ptr = IsRev ? _ptr + n : _ptr - n; return (*this); }
	vectorIterator &	operator-=	(const vectorIterator & x)			{ _ptr = IsRev ? x._ptr - _ptr : _ptr - x._ptr; return (*this); }
	// Comparison
	bool				operator==	(const vectorIterator & x) const	{ return (_ptr == x._ptr); }
	bool				operator!=	(const vectorIterator & x) const	{ return (_ptr != x._ptr); }
	bool				operator<	(const vectorIterator & x) const	{ return (IsRev ? _ptr > x._ptr : _ptr < x._ptr); }
	bool				operator>	(const vectorIterator & x) const	{ return (IsRev ? _ptr < x._ptr : _ptr > x._ptr); }
	bool				operator<=	(const vectorIterator & x) const	{ return (IsRev ? _ptr >= x._ptr : _ptr <= x._ptr); }
	bool				operator>=	(const vectorIterator & x) const	{ return (IsRev ? _ptr <= x._ptr : _ptr >= x._ptr); }
	// -crementation
	vectorIterator &	operator++	(void)								{ IsRev ? _ptr-- : _ptr++; return (*this); }
	vectorIterator &	operator--	(void)								{ IsRev ? _ptr++ : _ptr--; return (*this); }
	vectorIterator		operator++	(int)								{ vectorIterator x(*this); IsRev ? _ptr-- : _ptr++; return (x); }
	vectorIterator		operator--	(int)								{ vectorIterator x(*this); IsRev ? _ptr++ : _ptr--; return (x); }
	// Operation
	vectorIterator		operator+	(int n) const						{ return (IsRev ? _ptr - n : _ptr + n); }
	vectorIterator		operator-	(int n) const						{ return (IsRev ? _ptr + n : _ptr - n); }
	std::ptrdiff_t		operator-	(const vectorIterator & x) const	{ return (IsRev ? x._ptr - _ptr : _ptr - x._ptr); }
	// Dereference
	ReferenceType		operator*	(void)								{ return (*_ptr); }
	ReferenceType		operator[]	(size_t n)							{ return (IsRev ? *(_ptr - n) : *(_ptr + n)); }

private:
	PointerType		_ptr;
};
