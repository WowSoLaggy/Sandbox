#include "stdafx.h"
#include "Cursors.h"


Cursor getDefaultCursor()
{
  Cursor cursor;
  cursor.setTextureName("Cursor.png");
  cursor.setSize({ 25, 25 });
  return cursor;
}
