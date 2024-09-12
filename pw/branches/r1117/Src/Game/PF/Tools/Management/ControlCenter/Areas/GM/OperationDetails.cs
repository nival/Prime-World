//Author - Oleg Karlovskiy
namespace ControlCenter.Areas.GM
{
    public class OperationDetails<T>
    {
        public T ObjectToReturn { get; private set; }
        public bool SuccessStatus { get; private set; }
        public string ErrorDetails { get; private set; }

        /// <summary>
        /// Create success operation details
        /// </summary>
        /// <param name="objectToReturn">object from operation</param>
        /// <param name="SuccessStatus">operation status - bad or success</param>
        public OperationDetails(T objectToReturn, bool SuccessStatus)
            : this(objectToReturn, SuccessStatus, string.Empty)
        {
        }

        /// <summary>
        /// Create bad operation details
        /// </summary>
        /// <param name="errorDetails"></param>
        public OperationDetails(string errorDetails)
            : this(default(T), false, errorDetails)
        {
        }

        private OperationDetails(T objectToReturn, bool successStatus, string errorDetails)
        {
            ObjectToReturn = objectToReturn;
            SuccessStatus = successStatus;
            ErrorDetails = errorDetails;
        }
    }
}