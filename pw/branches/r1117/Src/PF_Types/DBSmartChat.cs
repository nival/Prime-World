using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;

namespace PF_GameLogic.DBSmartChat
{
  public class SmartChatMessage : DBResource
  {
    [Description("Уникальный идентификатор сообщения (передается по сети и интерпретируется клиентом, а также идентификатор команды для бинда")]
    public string commandId;

    [Description("Показывать ли маркер на отправителе")]
    public bool showMarker = false;

    [Description("Текст сообщения")]
    public TextRef text;
  }

  public class SmartChatGroup : DBResource
  {
    public List<DBPtr<SmartChatCategory>> categories;
    public List<DBPtr<SmartChatMessage>> messages;
  }

  [UseTypeName("SCCAT")]
  public class SmartChatCategory : SmartChatGroup
  {
    [Description("Идентификатор команды для бинда")]
    public string commandId;

    [Description("Название категории для отображения")]
    public TextRef name;
  }

  [UseTypeName("SCCFG")]
  public class SmartChatConfiguration : SmartChatGroup
  {
    [Description("Идентификатор команды Cancel/Back для бинда")]
    public string cancelCommandId = "cmd_smart_chat_cancel";
  }
}
