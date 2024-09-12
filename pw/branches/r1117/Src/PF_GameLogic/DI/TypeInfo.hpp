#pragma once

namespace DI
{
  namespace Detail
  {
    struct TypeInfo
    {
      template <typename T>
      static inline TypeInfo Make()
      {
        return TypeInfo(typeid(T));
      }

      TypeInfo()
        : value(&typeid(NullType))
      {
      }

      TypeInfo(const std::type_info& typeinfo)
        : value(&typeinfo)
      {
      }

      TypeInfo(const TypeInfo& other)
        : value(other.value)
      {
        NI_ASSERT(!!value, "Invalid type_info!");
      }

      bool IsEmpty() const
      {
        return (*value == typeid(NullType));
      }

      const std::type_info& Get() const
      {
        return *value;
      }

      TypeInfo& operator=(const std::type_info& typeinfo)
      {
        value = &typeinfo;
        return *this;
      }

      TypeInfo& operator=(const TypeInfo& other)
      {
        value = other.value;
        NI_ASSERT(!!value, "Invalid type_info!");
        return *this;
      }
    private:
      struct NullType
      {
        /* dummy */
      };

      const std::type_info* value;
    };

    inline bool operator==(const TypeInfo& left, const TypeInfo& right)
    {
      return (left.Get() == right.Get());
    }

    inline bool operator!=(const TypeInfo& left, const TypeInfo& right)
    {
      return !(left == right);
    }

    inline bool operator<(const TypeInfo& left, const TypeInfo& right)
    {
      return (left.Get().before(right.Get()) != 0);
    }

    inline bool operator>(const TypeInfo& left, const TypeInfo& right)
    {
      return (right < left);
    }

    inline bool operator<=(const TypeInfo& left, const TypeInfo& right)
    {
      return !(right < left);
    }

    inline bool operator>=(const TypeInfo& left, const TypeInfo& right)
    {
      return !(left < right);
    }
  }
}
