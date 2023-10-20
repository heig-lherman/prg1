#ifndef PRG1_D21_L5_FRACTIONS_TYPECHOOSER_H
#define PRG1_D21_L5_FRACTIONS_TYPECHOOSER_H

template<typename T, typename U, bool>
struct TypeChooser {
};

template <typename T, typename U>
struct TypeChooser<T, U, true> {
    using type = U;
};

template <typename T, typename U>
struct TypeChooser<T, U, false> {
    using type = T;
};

template<typename T, typename U>
using LargerType = typename TypeChooser<T, U, (sizeof(T) < sizeof(U))>::type;

#endif //PRG1_D21_L5_FRACTIONS_TYPECHOOSER_H
