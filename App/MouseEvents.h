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
  Dx::MouseKey d_mouseKey;
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
