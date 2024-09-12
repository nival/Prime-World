#pragma once

template<bool bFake>
struct SStaticAsserter;

template<>
struct SStaticAsserter<true>
{
};

#define COMPILE_TIME_ASSERT( EXPRESSION, MESSAGE_WITHOUT_WHITESPACES ) \
{ SStaticAsserter<( ( EXPRESSION ) != 0)> ERROR_##MESSAGE_WITHOUT_WHITESPACES; (void)ERROR_##MESSAGE_WITHOUT_WHITESPACES; }
