#include <boost/concept_check.hpp>

namespace customConcept {
    template<typename T>
    void ignore_warning(T const &) {}

    template<typename Func, typename FirstArg, typename SecondArg>
    struct BinaryPredicate {
        BOOST_CONCEPT_USAGE(BinaryPredicate) {
            bool x = foo(a, b);
        }
    private:
        Func      foo;
        FirstArg  a;
        SecondArg b;
    };

    template<typename T>
    struct Assignable {
        BOOST_CONCEPT_USAGE(Assignable) {
            // require assignment operator
            a = b;
            const_constraints(b);
        }

    private:
        void const_constraints(const T &x) {
            // const required for argument to assignment
            a = x;
            ignore_warning(a);
            ignore_warning(x);
        }
        T a;
        T b;
    };

    template<typename T>
    struct CopyConstructible {
        BOOST_CONCEPT_USAGE(CopyConstructible) {
            // require copy constructor
            T a(b);

            // require address of operator
            T *ptr = &a;

            const_constraints(a);
            ignore_warning(ptr);
        }
    private:
        void const_constraints(const T &a) {
            // require const copy constructor
            T c(a);

            // require const address of operator
            const T *ptr = &a;

            ignore_warning(c);
            ignore_warning(ptr);
        }
        T b;
    };

    template<typename T, typename U>
    struct Convertible {
        BOOST_CONCEPT_USAGE(Convertible) {
            b = a;
            ignore_warning(b);
        }
    private:
        T a;
        U b;
    };

    template<typename T>
    struct RandomAccessIterator {
        BOOST_CONCEPT_USAGE(RandomAccessIterator) {
            typename std::iterator_traits<T>::difference_type n{};

            // Is default-constructible, copy-constructible, copy-assignable and destructible
            T a;
            T b(a);
            b = a;

            // Can be compared for equivalence using the equality/inequality operators
            // (meaningful when both iterator values iterate over the same underlying sequence).
            a == b;
            a != b;

            //Can be dereferenced as an rvalue (if in a dereferenceable state).
            ignore_warning(*a);

            //For mutable iterators (non-constant iterators):
            //Can be dereferenced as an lvalue (if in a dereferenceable state).
            *a = std::move(*b);

            //Can be incremented (if in a dereferenceable state).
            //The result is either also dereferenceable or a past-the-end iterator.
            //Two iterators that compare equal, keep comparing equal after being both increased.
            ++a;
            a++;
            *a++;

            //Can be decremented (if a dereferenceable iterator value precedes it).
            --a;
            a--;
            *a--;

            //Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
            ignore_warning(a + n);
            ignore_warning(n + a);
            ignore_warning(a - n);
            ignore_warning(a - b);

            //Can be compared with inequality relational operators (<, >, <= and >=).
            ignore_warning(a < b);
            ignore_warning(a > b);
            ignore_warning(a <= b);
            ignore_warning(a >= b);

            //Supports compound assignment operations += and -=
            a += n;
            a -= n;

            //Supports the offset dereference operator ([])
            ignore_warning(a[n]);

            //Lvalues are swappable.
            std::swap(a, b);
        }
    };

    template<typename T>
    struct DefaultConstructible {
        BOOST_CONCEPT_USAGE(DefaultConstructible) {
            //The object u is default-initialized
            T a;

            //The object u is value-initialized or aggregate-initialized.
            T b{};

            //A temporary object of type T is value-initialized or aggregate-initialized.
            ignore_warning(T());
            ignore_warning(T{});
        }
    };

    template<typename T>
    struct LessThanComparable : DefaultConstructible<T> {
        BOOST_CONCEPT_USAGE(LessThanComparable)  {
            ignore_warning(left < right);
        }

    private:
        T left, right;
    };
}


