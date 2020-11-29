#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class CursorEvent : public Sdk::IEvent
{
public:
  CursorEvent(const Cursor& i_cursor)
    : d_cursor(i_cursor)
  {
  }

  const Cursor& getCursor() const { return d_cursor; }

private:
  const Cursor& d_cursor;
};


class CursorTextureChangedEvent : public CursorEvent
{
public:
  CursorTextureChangedEvent(const Cursor& i_cursor)
    : CursorEvent(i_cursor)
  {
  }
};

class CursorSizeChangedEvent : public CursorEvent
{
public:
  CursorSizeChangedEvent(const Cursor& i_cursor)
    : CursorEvent(i_cursor)
  {
  }
};

class CursorShownEvent : public CursorEvent
{
public:
  CursorShownEvent(const Cursor& i_cursor)
    : CursorEvent(i_cursor)
  {
  }
};

class CursorHiddenEvent : public CursorEvent
{
public:
  CursorHiddenEvent(const Cursor& i_cursor)
    : CursorEvent(i_cursor)
  {
  }
};
