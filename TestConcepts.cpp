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
    CopyConstructibleInvalidConstructor(CopyConstructibleInvalidConstructor &) = delete;
};

struct CopyConstructibleInvalidOperator {
    operator&() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidDefaultConstructible : std::vector<T>::iterator {
    RandomAccessIteratorInvalidDefaultConstructible() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidCopyConstructible : std::vector<T>::iterator {
    RandomAccessIteratorInvalidCopyConstructible() = default;
    RandomAccessIteratorInvalidCopyConstructible(RandomAccessIteratorInvalidCopyConstructible &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorAssign : std::vector<T>::iterator {
    RandomAccessIteratorInvalidOperatorAssign &operator=(RandomAccessIteratorInvalidOperatorAssign &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorEqual : std::vector<T>::iterator {
    bool operator==(RandomAccessIteratorInvalidOperatorEqual &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorNotEqual : std::vector<T>::iterator {
    bool operator!=(RandomAccessIteratorInvalidOperatorNotEqual &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorDereference : std::vector<T>::iterator {
    T operator*() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidSwap : std::vector<T>::iterator {
    RandomAccessIteratorInvalidSwap() = default;
    RandomAccessIteratorInvalidSwap(RandomAccessIteratorInvalidSwap &) = default;
    RandomAccessIteratorInvalidSwap &operator=(RandomAccessIteratorInvalidSwap &) = default;
    RandomAccessIteratorInvalidSwap &operator=(RandomAccessIteratorInvalidSwap &&) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorIncrement : std::vector<T>::iterator {
    T operator++() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorDecrement : std::vector<T>::iterator {
    T operator--() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorDecrementPlus : std::vector<T>::iterator {
    T operator+() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorDecrementMinus : std::vector<T>::iterator {
    T operator-() = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorAssignPlus : std::vector<T>::iterator {
    T operator+=(T &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorAssignMinus : std::vector<T>::iterator {
    T operator-=(T &) = delete;
};

template<typename T>
struct RandomAccessIteratorInvalidOperatorBraces : std::vector<T>::iterator {
    T operator[](size_t) = delete;
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
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidDefaultConstructible<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidCopyConstructible<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorAssign<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorEqual<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorNotEqual<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorDereference<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidSwap<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorIncrement<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorDecrement<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorDecrementPlus<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorDecrementMinus<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorAssignPlus<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorAssignMinus<int>>));
//    BOOST_CONCEPT_ASSERT((customConcept::RandomAccessIterator<RandomAccessIteratorInvalidOperatorBraces<int>>));

}

