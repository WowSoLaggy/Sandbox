#include "stdafx.h"
#include "KeyboardHandler.h"

#include "Controller.h"

#include <LaggyDx/KeyboardState.h>


namespace
{
  std::unordered_set<Dx::KeyboardKey> getKeys(const Dx::KeyboardKeysState& i_state)
  {
    std::unordered_set<Dx::KeyboardKey> actions;

    if (i_state.Back) actions.insert(Dx::KeyboardKey::Back);
    if (i_state.Tab) actions.insert(Dx::KeyboardKey::Tab);
    if (i_state.Enter) actions.insert(Dx::KeyboardKey::Enter);
    if (i_state.Pause) actions.insert(Dx::KeyboardKey::Pause);
    if (i_state.CapsLock) actions.insert(Dx::KeyboardKey::CapsLock);
    if (i_state.Kana) actions.insert(Dx::KeyboardKey::Kana);
    if (i_state.Escape) actions.insert(Dx::KeyboardKey::Escape);
    if (i_state.ImeConvert) actions.insert(Dx::KeyboardKey::ImeConvert);
    if (i_state.ImeNoConvert) actions.insert(Dx::KeyboardKey::ImeNoConvert);
    if (i_state.Space) actions.insert(Dx::KeyboardKey::Space);
    if (i_state.PageUp) actions.insert(Dx::KeyboardKey::PageUp);
    if (i_state.PageDown) actions.insert(Dx::KeyboardKey::PageDown);
    if (i_state.End) actions.insert(Dx::KeyboardKey::End);
    if (i_state.Home) actions.insert(Dx::KeyboardKey::Home);
    if (i_state.Left) actions.insert(Dx::KeyboardKey::Left);
    if (i_state.Up) actions.insert(Dx::KeyboardKey::Up);
    if (i_state.Right) actions.insert(Dx::KeyboardKey::Right);
    if (i_state.Down) actions.insert(Dx::KeyboardKey::Down);
    if (i_state.Select) actions.insert(Dx::KeyboardKey::Select);
    if (i_state.Print) actions.insert(Dx::KeyboardKey::Print);
    if (i_state.Execute) actions.insert(Dx::KeyboardKey::Execute);
    if (i_state.PrintScreen) actions.insert(Dx::KeyboardKey::PrintScreen);
    if (i_state.Insert) actions.insert(Dx::KeyboardKey::Insert);
    if (i_state.Delete) actions.insert(Dx::KeyboardKey::Delete);
    if (i_state.Help) actions.insert(Dx::KeyboardKey::Help);
    if (i_state.D0) actions.insert(Dx::KeyboardKey::D0);
    if (i_state.D1) actions.insert(Dx::KeyboardKey::D1);
    if (i_state.D2) actions.insert(Dx::KeyboardKey::D2);
    if (i_state.D3) actions.insert(Dx::KeyboardKey::D3);
    if (i_state.D4) actions.insert(Dx::KeyboardKey::D4);
    if (i_state.D5) actions.insert(Dx::KeyboardKey::D5);
    if (i_state.D6) actions.insert(Dx::KeyboardKey::D6);
    if (i_state.D7) actions.insert(Dx::KeyboardKey::D7);
    if (i_state.D8) actions.insert(Dx::KeyboardKey::D8);
    if (i_state.D9) actions.insert(Dx::KeyboardKey::D9);
    if (i_state.A) actions.insert(Dx::KeyboardKey::A);
    if (i_state.B) actions.insert(Dx::KeyboardKey::B);
    if (i_state.C) actions.insert(Dx::KeyboardKey::C);
    if (i_state.D) actions.insert(Dx::KeyboardKey::D);
    if (i_state.E) actions.insert(Dx::KeyboardKey::E);
    if (i_state.F) actions.insert(Dx::KeyboardKey::F);
    if (i_state.G) actions.insert(Dx::KeyboardKey::G);
    if (i_state.H) actions.insert(Dx::KeyboardKey::H);
    if (i_state.I) actions.insert(Dx::KeyboardKey::I);
    if (i_state.J) actions.insert(Dx::KeyboardKey::J);
    if (i_state.K) actions.insert(Dx::KeyboardKey::K);
    if (i_state.L) actions.insert(Dx::KeyboardKey::L);
    if (i_state.M) actions.insert(Dx::KeyboardKey::M);
    if (i_state.N) actions.insert(Dx::KeyboardKey::N);
    if (i_state.O) actions.insert(Dx::KeyboardKey::O);
    if (i_state.P) actions.insert(Dx::KeyboardKey::P);
    if (i_state.Q) actions.insert(Dx::KeyboardKey::Q);
    if (i_state.R) actions.insert(Dx::KeyboardKey::R);
    if (i_state.S) actions.insert(Dx::KeyboardKey::S);
    if (i_state.T) actions.insert(Dx::KeyboardKey::T);
    if (i_state.U) actions.insert(Dx::KeyboardKey::U);
    if (i_state.V) actions.insert(Dx::KeyboardKey::V);
    if (i_state.W) actions.insert(Dx::KeyboardKey::W);
    if (i_state.X) actions.insert(Dx::KeyboardKey::X);
    if (i_state.Y) actions.insert(Dx::KeyboardKey::Y);
    if (i_state.Z) actions.insert(Dx::KeyboardKey::Z);
    if (i_state.LeftWindows) actions.insert(Dx::KeyboardKey::LeftWindows);
    if (i_state.RightWindows) actions.insert(Dx::KeyboardKey::RightWindows);
    if (i_state.Apps) actions.insert(Dx::KeyboardKey::Apps);
    if (i_state.Sleep) actions.insert(Dx::KeyboardKey::Sleep);
    if (i_state.NumPad0) actions.insert(Dx::KeyboardKey::NumPad0);
    if (i_state.NumPad1) actions.insert(Dx::KeyboardKey::NumPad1);
    if (i_state.NumPad2) actions.insert(Dx::KeyboardKey::NumPad2);
    if (i_state.NumPad3) actions.insert(Dx::KeyboardKey::NumPad3);
    if (i_state.NumPad4) actions.insert(Dx::KeyboardKey::NumPad4);
    if (i_state.NumPad5) actions.insert(Dx::KeyboardKey::NumPad5);
    if (i_state.NumPad6) actions.insert(Dx::KeyboardKey::NumPad6);
    if (i_state.NumPad7) actions.insert(Dx::KeyboardKey::NumPad7);
    if (i_state.NumPad8) actions.insert(Dx::KeyboardKey::NumPad8);
    if (i_state.NumPad9) actions.insert(Dx::KeyboardKey::NumPad9);
    if (i_state.Multiply) actions.insert(Dx::KeyboardKey::Multiply);
    if (i_state.Add) actions.insert(Dx::KeyboardKey::Add);
    if (i_state.Separator) actions.insert(Dx::KeyboardKey::Separator);
    if (i_state.Subtract) actions.insert(Dx::KeyboardKey::Subtract);
    if (i_state.Decimal) actions.insert(Dx::KeyboardKey::Decimal);
    if (i_state.Divide) actions.insert(Dx::KeyboardKey::Divide);
    if (i_state.F1) actions.insert(Dx::KeyboardKey::F1);
    if (i_state.F2) actions.insert(Dx::KeyboardKey::F2);
    if (i_state.F3) actions.insert(Dx::KeyboardKey::F3);
    if (i_state.F4) actions.insert(Dx::KeyboardKey::F4);
    if (i_state.F5) actions.insert(Dx::KeyboardKey::F5);
    if (i_state.F6) actions.insert(Dx::KeyboardKey::F6);
    if (i_state.F7) actions.insert(Dx::KeyboardKey::F7);
    if (i_state.F8) actions.insert(Dx::KeyboardKey::F8);
    if (i_state.F9) actions.insert(Dx::KeyboardKey::F9);
    if (i_state.F10) actions.insert(Dx::KeyboardKey::F10);
    if (i_state.F11) actions.insert(Dx::KeyboardKey::F11);
    if (i_state.F12) actions.insert(Dx::KeyboardKey::F12);
    if (i_state.F13) actions.insert(Dx::KeyboardKey::F13);
    if (i_state.F14) actions.insert(Dx::KeyboardKey::F14);
    if (i_state.F15) actions.insert(Dx::KeyboardKey::F15);
    if (i_state.F16) actions.insert(Dx::KeyboardKey::F16);
    if (i_state.F17) actions.insert(Dx::KeyboardKey::F17);
    if (i_state.F18) actions.insert(Dx::KeyboardKey::F18);
    if (i_state.F19) actions.insert(Dx::KeyboardKey::F19);
    if (i_state.F20) actions.insert(Dx::KeyboardKey::F20);
    if (i_state.F21) actions.insert(Dx::KeyboardKey::F21);
    if (i_state.F22) actions.insert(Dx::KeyboardKey::F22);
    if (i_state.F23) actions.insert(Dx::KeyboardKey::F23);
    if (i_state.F24) actions.insert(Dx::KeyboardKey::F24);
    if (i_state.NumLock) actions.insert(Dx::KeyboardKey::NumLock);
    if (i_state.Scroll) actions.insert(Dx::KeyboardKey::Scroll);
    if (i_state.LeftShift) actions.insert(Dx::KeyboardKey::LeftShift);
    if (i_state.RightShift) actions.insert(Dx::KeyboardKey::RightShift);
    if (i_state.LeftControl) actions.insert(Dx::KeyboardKey::LeftControl);
    if (i_state.RightControl) actions.insert(Dx::KeyboardKey::RightControl);
    if (i_state.LeftAlt) actions.insert(Dx::KeyboardKey::LeftAlt);
    if (i_state.RightAlt) actions.insert(Dx::KeyboardKey::RightAlt);
    if (i_state.BrowserBack) actions.insert(Dx::KeyboardKey::BrowserBack);
    if (i_state.BrowserForward) actions.insert(Dx::KeyboardKey::BrowserForward);
    if (i_state.BrowserRefresh) actions.insert(Dx::KeyboardKey::BrowserRefresh);
    if (i_state.BrowserStop) actions.insert(Dx::KeyboardKey::BrowserStop);
    if (i_state.BrowserSearch) actions.insert(Dx::KeyboardKey::BrowserSearch);
    if (i_state.BrowserFavorites) actions.insert(Dx::KeyboardKey::BrowserFavorites);
    if (i_state.BrowserHome) actions.insert(Dx::KeyboardKey::BrowserHome);
    if (i_state.VolumeMute) actions.insert(Dx::KeyboardKey::VolumeMute);
    if (i_state.VolumeDown) actions.insert(Dx::KeyboardKey::VolumeDown);
    if (i_state.VolumeUp) actions.insert(Dx::KeyboardKey::VolumeUp);
    if (i_state.MediaNextTrack) actions.insert(Dx::KeyboardKey::MediaNextTrack);
    if (i_state.MediaPreviousTrack) actions.insert(Dx::KeyboardKey::MediaPreviousTrack);
    if (i_state.MediaStop) actions.insert(Dx::KeyboardKey::MediaStop);
    if (i_state.MediaPlayPause) actions.insert(Dx::KeyboardKey::MediaPlayPause);
    if (i_state.LaunchMail) actions.insert(Dx::KeyboardKey::LaunchMail);
    if (i_state.SelectMedia) actions.insert(Dx::KeyboardKey::SelectMedia);
    if (i_state.LaunchApplication1) actions.insert(Dx::KeyboardKey::LaunchApplication1);
    if (i_state.LaunchApplication2) actions.insert(Dx::KeyboardKey::LaunchApplication2);
    if (i_state.OemSemicolon) actions.insert(Dx::KeyboardKey::OemSemicolon);
    if (i_state.OemPlus) actions.insert(Dx::KeyboardKey::OemPlus);
    if (i_state.OemComma) actions.insert(Dx::KeyboardKey::OemComma);
    if (i_state.OemMinus) actions.insert(Dx::KeyboardKey::OemMinus);
    if (i_state.OemPeriod) actions.insert(Dx::KeyboardKey::OemPeriod);
    if (i_state.OemQuestion) actions.insert(Dx::KeyboardKey::OemQuestion);
    if (i_state.OemTilde) actions.insert(Dx::KeyboardKey::OemTilde);
    if (i_state.OemOpenBrackets) actions.insert(Dx::KeyboardKey::OemOpenBrackets);
    if (i_state.OemPipe) actions.insert(Dx::KeyboardKey::OemPipe);
    if (i_state.OemCloseBrackets) actions.insert(Dx::KeyboardKey::OemCloseBrackets);
    if (i_state.OemQuotes) actions.insert(Dx::KeyboardKey::OemQuotes);
    if (i_state.Oem8) actions.insert(Dx::KeyboardKey::Oem8);
    if (i_state.OemBackslash) actions.insert(Dx::KeyboardKey::OemBackslash);
    if (i_state.ProcessKey) actions.insert(Dx::KeyboardKey::ProcessKey);
    if (i_state.OemCopy) actions.insert(Dx::KeyboardKey::OemCopy);
    if (i_state.OemAuto) actions.insert(Dx::KeyboardKey::OemAuto);
    if (i_state.OemEnlW) actions.insert(Dx::KeyboardKey::OemEnlW);
    if (i_state.Attn) actions.insert(Dx::KeyboardKey::Attn);
    if (i_state.Crsel) actions.insert(Dx::KeyboardKey::Crsel);
    if (i_state.Exsel) actions.insert(Dx::KeyboardKey::Exsel);
    if (i_state.EraseEof) actions.insert(Dx::KeyboardKey::EraseEof);
    if (i_state.Play) actions.insert(Dx::KeyboardKey::Play);
    if (i_state.Zoom) actions.insert(Dx::KeyboardKey::Zoom);
    if (i_state.Pa1) actions.insert(Dx::KeyboardKey::Pa1);
    if (i_state.OemClear) actions.insert(Dx::KeyboardKey::OemClear);

    return actions;
  }

  std::unordered_set<Dx::KeyboardKey> getAllKeysFromStates(const Dx::KeyboardState& i_keyboardState)
  {
    auto keys = getKeys(i_keyboardState.getPressedKeys());
    const auto keys2 = getKeys(i_keyboardState.getCurrentKeys());

    keys.insert(keys2.cbegin(), keys2.cend());
    return keys;
  }

} // anon NS


KeyboardHandler::KeyboardHandler(Controller& io_controller)
  : d_contoller(io_controller)
{
}


void KeyboardHandler::handleKeyboard(const Dx::KeyboardState& i_keyboardState)
{
  const auto keys = getAllKeysFromStates(i_keyboardState);
  const auto& actionsMap = d_contoller.getActionsMap();
  for (const auto key : keys)
  {
    if (const auto actionOpt = actionsMap.getAction(key))
      d_contoller.runAction(*actionOpt);
  }
}
