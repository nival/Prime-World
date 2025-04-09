ChatScreen = {}
function ChatScreen.OnInit( obj )    
end

------------------------------------------------------------------------------------
ChatInputBox = {}
function ChatInputBox.OnKeyboardFocus( pWnd, gotFocus )
end

function ChatInputBox.OnKeyPressed( pWnd, ch )
end

------------------------------------------------------------------------------------
ChatScrollUpBtn = {}
function ChatScrollUpBtn.OnAction( pWnd )
	pWnd:GetContext():OnScrollChatMessages( 0 );
end

------------------------------------------------------------------------------------
ChatScrollDownBtn = {}
function ChatScrollDownBtn.OnAction( pWnd )
	pWnd:GetContext():OnScrollChatMessages(1);
end

------------------------------------------------------------------------------------
ChatScrollToLastBtn = {}
function ChatScrollToLastBtn.OnAction( pWnd )
	pWnd:GetContext():OnScrollChatMessages(2);
end

------------------------------------------------------------------------------------
ChatOutputWindow = {}
function ChatOutputWindow.OnMouseMove( pWnd, x, y )
  local ctxt = pWnd:GetContext();
  pWnd:GetContext():OnCursorOverChatOutput();	--show the chat background
  return false;
end

------------------------------------------------------------------------------------
--- show context menu with smiles, emotions, slash-commands
ChatContextMenuBtn = {}
function ChatContextMenuBtn.OnAction(pWnd)
	pWnd:GetContext():ShowChatContextMenu();
end
------------------------------------------------------------------------------------
