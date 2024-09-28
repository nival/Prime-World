//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.IO;
//using System.IO.MemoryMappedFiles;
//using System.Diagnostics;

//namespace DockSample
//{
//    public class PWLogRecord
//        {
//            public string Thread { get; set; }
//            public string Time { get; set; }
//            public string Channel { get; set; }
//            public string Level { get; set; }
//            public string Message { get; set; }

//            public PWLogRecord ( string thread, string time, string channel, string level, string message )
//            {
//                Thread = thread;
//                Time = time;
//                Channel = channel;
//                Level = level;
//                Message = message;
//            }
//        }
    
//    public class QueryResultCashe
//    {
//        //public int PageSize = 5000;
//        //public long TotalCount;
//        //public List<PWLogRecord> cachedData = null;

		
//        //int _lastRowIndex = -1;

//        //public QueryResultCashe ( int pageSize )
//        //{
//        //    PageSize = pageSize;
//        //    LoadPage( 0 );
//        //}

//        //public void LoadPage( int rowIndex )
//        //{
//        //    int lastRowIndex = rowIndex - ( rowIndex % PageSize );
//        //    if( lastRowIndex == _lastRowIndex ) return;
//        //    _lastRowIndex = lastRowIndex;
//        //    if (cachedData == null) cachedData = new List<PWLogRecord>();
//        //    long? totalCount = 0;
//        //    //_adapter.Fill( CachedData, _lastRowIndex, PageSize, ref totalCount );
//        //    TotalCount = totalCount.Value;
//        //}



//        static int cacheSize = 100000000;
//        static int totalRowCount = 0;
//        static Dictionary<int, long> dispatch = new Dictionary<int, long>();
//        static int stringQuant = 1000000;
//        //int currentCachePageNumber;
//        //byte

//        public static void InitCache ( string fIn )
//        {
//            FileInfo fInfo = new FileInfo(fIn);
//            long fLength = fInfo.Length;
//            byte newLineByte = (byte)'\n';
//            byte[] byteArray = null;


//            Stopwatch sw = Stopwatch.StartNew();
//            long processed = 0;
//            int buffer = 0;
//            using (var mmf = MemoryMappedFile.CreateFromFile(fIn, FileMode.Open, "mapFile"))
//            {
//                while (processed < fLength)
//                {
//                    buffer = ((fLength - processed) >= cacheSize) ? cacheSize : (int)(fLength - processed);

//                    using (var accessor = mmf.CreateViewAccessor(processed, buffer))
//                    {
//                        byteArray = new byte[buffer];
//                        accessor.ReadArray<byte>(0, byteArray, 0, buffer);
//                        for (int i = 0; i < byteArray.Length; i++)
//                        {
//                            if (byteArray[i] == newLineByte)
//                            {
//                                totalRowCount++;
//                                if ((totalRowCount % stringQuant) == 0)
//                                    dispatch.Add(totalRowCount, processed + i);//если последняя строка!
//                            }
//                        }
//                    }
//                    processed += buffer;
//                }
//            }
//            Console.WriteLine("\n" + totalRowCount.ToString() + " строк, " + " Время = " + sw.Elapsed);
//            //Console.WriteLine("using dispatch");
//            //long currLength = dispatch[4 * stringQuant] - dispatch[3 * stringQuant]; ;
//            //long start = dispatch[3 * stringQuant];
//            ////long currLength = (fLength - dispatch[4 * stringQuant]) - 1;
//            ////long start = dispatch[4 * stringQuant];
//            //using (var mmf = MemoryMappedFile.CreateFromFile(fIn, FileMode.Open, "mapFile"))
//            //{
//            //    using (var accessor = mmf.CreateViewAccessor(start + 1, currLength))
//            //    {
//            //        byteArray = new byte[currLength];
//            //        accessor.ReadArray<byte>(0, byteArray, 0, (int)currLength);
//            //        foreach (byte b in byteArray)
//            //        {
//            //            Console.Write((char)b);
//            //        }
//            //    }
//            //}
//            //Console.WriteLine();
//        }

//        public static string GetByRowNumber ( int rowNumber )
//        {
//            return null;
//        }
//    }
//}
