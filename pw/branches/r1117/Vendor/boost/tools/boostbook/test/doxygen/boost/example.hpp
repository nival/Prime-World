
// Copyright 2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*!
    \class example::example
    
    \brief Documentation for class example
 */

/*!
    \def EXAMPLE
    
    \brief Documentation for macro example
 */

int global_integer;
static int global_static_integer;
const int global_const_integer = 1;
static const int global_static_const_integer = 2;
enum global_enum { enumerator1 = 1, enumerator2 };

namespace example
{
    int namespace_integer;
    static int namespace_static_integer;
    const int namespace_const_integer = 1;
    static const int namespace_static_const_integer = 2;
    enum namespace_enum { enumerator };

    class example
    {
    public:
        int integer;
        static int static_integer;
        mutable int mutable_integer;
        const int const_integer;
        static const int static_const_integer;
        
        class inner_class {
        public:
            int x;
        };

        enum class_enum { enumerator };
        
        /// INTERNAL ONLY
        enum internal_enum { internal_enumerator };
    protected:
        int protected_integer;
        static int protected_static_integer;
        mutable int protected_mutable_integer;
        const int protected_const_integer;
        static const int protected_static_const_integer;

        enum protected_class_enum { enumerator2 };
    private:
        int private_integer;
        static int private_static_integer;
        mutable int private_mutable_integer;
        const int private_const_integer;
        static const int private_static_const_integer;

        enum private_class_enum { enumerator3 };
    };
    
    /**
     * Test some doxygen markup
     *
     * Embedded docbook list:
     *
     * \xmlonly
     * <orderedlist><listitem><simpara>1</simpara></listitem><listitem><simpara>2</simpara></listitem></orderedlist>
     * \endxmlonly
     *
     * \a Special \b Bold \c Typewriter \e Italics \em emphasis \p parameter
     *
     * \arg Arg1 first argument.
     * \arg Arg2 second argument.
     *
     * \li First list item.
     * \li Second list item
     *
     * Line 1\n
     * Line 2
     *
     * \code
     *     void foo() {}
     * \endcode
     *
     */

    template <typename TypeParameter, int NonTypeParameter,
        typename TypeParameterWithDefault = int>
    struct example_template {};
}

#define EXAMPLE(m) The macro
