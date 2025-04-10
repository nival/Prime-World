/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    Widget.h
 *
 *  $Id: Widget.h 80826 2008-03-04 14:51:23Z wotte $
 *
 *  @author Christopher Kohlhoff <chris@kohlhoff.com>
 */
//=============================================================================

#ifndef WIDGET_H
#define WIDGET_H

#include "Widget_Part.h"

/**
 * @class Widget
 *
 * @brief An interface for some high-level application object.
 */
class Widget
{
public:
  /// Destructor.
  virtual ~Widget (void);

  /// Add a new part to the widget. The widget takes ownership of the part
  /// object.
  virtual void add_part (Widget_Part *part) = 0;

  /// Remove a random part from the widget. Ownership of the part is returned
  /// to the caller.
  virtual Widget_Part *remove_part (void) = 0;

  /// Ask the widget to print information about the parts that it contains.
  virtual void list_parts (void) = 0;
};

#endif /* WIDGET_H */
