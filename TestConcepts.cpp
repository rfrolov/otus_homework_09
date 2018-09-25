#include <vector>
#include <list>
#include "Concepts.h"

template<typename T>
struct BinaryPredicateValid : public std::binary_function<T, T, bool> {
    constexpr bool operator()(const T &a, const T &b) const { return a == b; }
};

template<typename T>
struct BinaryPredicateInvalid : public std::binary_function<T, T, bool> {
    constexpr void operator()(const T &a, const T &b) const {}
};


struct TestStruct {
    TestStruct() = default;
    bool operator<(const TestStruct &) {
        return true;
    }
};

struct TestStructWithoutOperatorLess {
    TestStructWithoutOperatorLess() = default;
};

struct TestStructWithoutConstructor {
    TestStructWithoutConstructor() = delete;
    bool operator<(const TestStructWithoutConstructor &) {
        return true;
    }
};

struct CopyConstructibleInvalidConstructor {
    CopyConstructibleInvalidConstructor(CopyConstructibleInvalidConstructor& ) = delete;
};

struct CopyConstructibleInvalidOperator {
    operator &() = delete;
};

int main(int argc, char *argv[]) {
    /* Концепт LessThanComparable не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::LessThanComparable<TestStruct>));
    /* Концепт LessThanComparable нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::LessThanComparable<TestStructWithoutOperatorLess>));
//    BOOST_CONCEPT_ASSERT((customConcept::LessThanComparable<TestStructWithoutConstructor>));


    /* Концепт Assignable не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::Assignable<int>));
    /* Концепт Assignable нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::Assignable<const int>));

    /* Концепт BinaryPredicate не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::BinaryPredicate<BinaryPredicateValid<int>, int, int>));
    /* Концепт BinaryPredicate нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::BinaryPredicate<BinaryPredicateInvalid<int>, int, int>));

    /* Концепт CopyConstructible не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::CopyConstructible<int>));
    /* Концепт CopyConstructible нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::CopyConstructible<CopyConstructibleInvalidConstructor>));
//    BOOST_CONCEPT_ASSERT((customConcept::CopyConstructible<CopyConstructibleInvalidOperator>));

    /* Концепт Convertible не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::Convertible<int, bool>));
    /* Концепт Convertible нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::Convertible<int, std::vector<int>>));

    /* Концепт RandomAccessIterator не нарушен: */
    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<std::vector<size_t>::iterator>));
    /* Концепт RandomAccessIterator нарушен: */
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<std::list<size_t>::iterator>));

}

