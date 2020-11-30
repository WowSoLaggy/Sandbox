#pragma once

#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/IEvent.h>
#include <LaggySdk/Vector.h>


class MouseEvent : public Sdk::IEvent
{
public:
  MouseEvent(Sdk::Vector2I i_mousePos)
    : d_mousePos(std::move(i_mousePos))
  {
  }

  const Sdk::Vector2I& getMousePos() const
  {
    return d_mousePos;
  }

private:
  Sdk::Vector2I d_mousePos;
};

class MouseKeyEvent : public MouseEvent
{
public:
  MouseKeyEvent(const Dx::MouseKey i_mouseKey, Sdk::Vector2I i_mousePos)
    : MouseEvent(std::move(i_mousePos))
    , d_mouseKey(i_mouseKey)
  {
  }

  Dx::MouseKey getMouseKey() const
  {
    return d_mouseKey;
  }

private:
  const Dx::MouseKey d_mouseKey = Dx::MouseKey::Left;
};


class MouseMovedEvent : public MouseEvent
{
public:
  MouseMovedEvent(Sdk::Vector2I i_mousePos)
    : MouseEvent(std::move(i_mousePos))
  {
  }
};

class MouseClickEvent : public MouseKeyEvent
{
public:
  MouseClickEvent(const Dx::MouseKey i_mouseKey, Sdk::Vector2I i_mousePos)
    : MouseKeyEvent(i_mouseKey, std::move(i_mousePos))
  {
  }
};

class MouseReleasedEvent : public MouseKeyEvent
{
public:
  MouseReleasedEvent(const Dx::MouseKey i_mouseKey, Sdk::Vector2I i_mousePos)
    : MouseKeyEvent(i_mouseKey, std::move(i_mousePos))
  {
  }
};

class MouseWheelEvent : public MouseEvent
{
public:
  MouseWheelEvent(Sdk::Vector2I i_mousePos, const int i_wheelChange)
    : MouseEvent(std::move(i_mousePos))
    , d_wheelChange(i_wheelChange)
  {
  }

  int getWheelChange() const { return d_wheelChange; }

private:
  const int d_wheelChange = 0;
};
