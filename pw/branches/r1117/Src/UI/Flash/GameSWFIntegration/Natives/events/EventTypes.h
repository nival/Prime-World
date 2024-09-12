#pragma once

namespace avmplus
{

class EventTypes : public flash::SafeGCRoot<EventTypes>
{
public:

  explicit EventTypes( AvmCore * _core ) :
    flash::SafeGCRoot<EventTypes>(_core->gc)
  {
    CANCEL = _core->internConstantStringLatin1("cancel");
    ENTER_FRAME = _core->internConstantStringLatin1("enterFrame");
    SOUND_COMPLETE = _core->internConstantStringLatin1("soundComplete");
    UNLOAD = _core->internConstantStringLatin1("unload");
    INIT = _core->internConstantStringLatin1("init");
    RENDER = _core->internConstantStringLatin1("render");
    TAB_ENABLED_CHANGE = _core->internConstantStringLatin1("tabEnabledChange");
    ADDED_TO_STAGE = _core->internConstantStringLatin1("addedToStage");
    FRAME_CONSTRUCTED = _core->internConstantStringLatin1("frameConstructed");
    TAB_CHILDREN_CHANGE = _core->internConstantStringLatin1("tabChildrenChange");
    CUT = _core->internConstantStringLatin1("cut");
    CLEAR = _core->internConstantStringLatin1("clear");
    CHANGE = _core->internConstantStringLatin1("change");
    RESIZE = _core->internConstantStringLatin1("resize");
    COMPLETE = _core->internConstantStringLatin1("complete");
    FULLSCREEN = _core->internConstantStringLatin1("fullScreen");
    SELECT_ALL = _core->internConstantStringLatin1("selectAll");
    REMOVED = _core->internConstantStringLatin1("removed");
    CONNECT = _core->internConstantStringLatin1("connect");
    SCROLL = _core->internConstantStringLatin1("scroll");
    OPEN = _core->internConstantStringLatin1("open");
    CLOSE = _core->internConstantStringLatin1("close");
    MOUSE_LEAVE = _core->internConstantStringLatin1("mouseLeave");
    ADDED = _core->internConstantStringLatin1("added");
    REMOVED_FROM_STAGE = _core->internConstantStringLatin1("removedFromStage");
    EXIT_FRAME = _core->internConstantStringLatin1("exitFrame");
    TAB_INDEX_CHANGE = _core->internConstantStringLatin1("tabIndexChange");
    PASTE = _core->internConstantStringLatin1("paste");
    DEACTIVATE = _core->internConstantStringLatin1("deactivate");
    COPY = _core->internConstantStringLatin1("copy");
    ID3 = _core->internConstantStringLatin1("id3");
    ACTIVATE = _core->internConstantStringLatin1("activate");
    SELECT = _core->internConstantStringLatin1("select");

    //TimerEvents
    TIMER_COMPLETE = _core->internConstantStringLatin1("timerComplete");
    TIMER = _core->internConstantStringLatin1("timer");

    kFRAME_CONSTRUCTED = FRAME_CONSTRUCTED->atom();
    kENTER_FRAME = ENTER_FRAME->atom();
    kEXIT_FRAME = EXIT_FRAME->atom();
    kRENDER = RENDER->atom();
  }

  DRC(Stringp) CANCEL;
  DRC(Stringp) ENTER_FRAME;
  DRC(Stringp) SOUND_COMPLETE;
  DRC(Stringp) UNLOAD;
  DRC(Stringp) INIT;
  DRC(Stringp) RENDER;
  DRC(Stringp) TAB_ENABLED_CHANGE;
  DRC(Stringp) ADDED_TO_STAGE;
  DRC(Stringp) FRAME_CONSTRUCTED;
  DRC(Stringp) TAB_CHILDREN_CHANGE;
  DRC(Stringp) CUT;
  DRC(Stringp) CLEAR;
  DRC(Stringp) CHANGE;
  DRC(Stringp) RESIZE;
  DRC(Stringp) COMPLETE;
  DRC(Stringp) FULLSCREEN;
  DRC(Stringp) SELECT_ALL;
  DRC(Stringp) REMOVED;
  DRC(Stringp) CONNECT;
  DRC(Stringp) SCROLL;
  DRC(Stringp) OPEN;
  DRC(Stringp) CLOSE;
  DRC(Stringp) MOUSE_LEAVE;
  DRC(Stringp) ADDED;
  DRC(Stringp) REMOVED_FROM_STAGE;
  DRC(Stringp) EXIT_FRAME;
  DRC(Stringp) TAB_INDEX_CHANGE;
  DRC(Stringp) PASTE;
  DRC(Stringp) DEACTIVATE;
  DRC(Stringp) COPY;
  DRC(Stringp) ID3;
  DRC(Stringp) ACTIVATE;
  DRC(Stringp) SELECT;

  //TimerEvents
  DRC(Stringp) TIMER_COMPLETE;
  DRC(Stringp) TIMER;

  Atom  kFRAME_CONSTRUCTED;
  Atom  kENTER_FRAME;
  Atom  kEXIT_FRAME;
  Atom  kRENDER;
};

}
