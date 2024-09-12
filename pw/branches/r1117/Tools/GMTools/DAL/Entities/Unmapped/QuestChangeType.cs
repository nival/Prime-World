namespace DAL.Entities
{
  /// <summary>
  /// Тип изменения состояния квеста
  /// </summary>
  public enum QuestChangeType
  {
    Add = 0,     // Квест получен
    Accept = 1,  // Квест принят
    Complete = 2 // Квест завершен
  }
}