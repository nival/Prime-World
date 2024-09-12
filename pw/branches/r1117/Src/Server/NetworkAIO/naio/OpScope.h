#pragma once

namespace naio
{
  template<class T>
  class OpScope
  {
    bool countlast(Ptr<T> const & first, Ptr<T> const & last, unsigned int & count)
    {
      count = 0;

      Ptr<T> op = first;
      while(op && op != last)
      {
        ++count;
        op = op->next();
      }

      return (op == last);
    }

  public:
    OpScope()
      :first_(0), last_(0), count_(0)
    {}

    void scope(Ptr<T> const & first, Ptr<T> const & last)
    {
      first_ = first;
      last_ = last;
      count_ = 0;

      unsigned int count = 0;
      if (countlast(first, last_, count))
        count_ = count;
    }

    OpScope(Ptr<T> const & first, Ptr<T> const & last)
      :first_(first), last_(last), count_(0)
    {
      scope(first_, last_);
    }

    Ptr<T> const & first() const
    {
      return first_;
    }

    Ptr<T> const & last() const
    {
      return last_;
    }

    unsigned int count() const
    {
      return count_;
    }

  private:
    Ptr<T> first_;
    Ptr<T> last_;
    unsigned int count_;
  };
}
