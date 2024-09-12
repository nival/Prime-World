#pragma once

namespace PF_Minigames
{

_interface ICollidable : public IObjectBase
{
  virtual const SVector & Position() const = 0;
  virtual int             Size() const = 0;
  virtual int             Speed() const = 0;
  virtual const SVector & Direction() const = 0;

  virtual bool        Hit() = 0;
  virtual bool        IsExhausted() const = 0;
};

}