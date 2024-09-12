#ifndef CENSOR_H_4A244540_8CC1_43F3_9021
#define CENSOR_H_4A244540_8CC1_43F3_9021

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <system/nvector.h>
#include <System/nstring.h>

//#include <System/Pointers/BaseObjectMT.h>

//#include <wctype.h>



namespace CensorFilter
{
  wchar_t NormailizeChar(  wchar_t ch );
  
  struct DictEqualToPred : std::binary_function<std::wstring, std::wstring, bool>
  {
    bool operator()(std::wstring const& x,
      std::wstring const& y) const
    {
      if (x.length() != y.length())
        return false;

      std::size_t seed = 0;
      std::wstring::const_iterator it = x.begin();
      std::wstring::const_iterator it_y = y.begin();
      for(; it != x.end(); ++it, ++it_y)
      {
        if ( NormailizeChar(*it) != NormailizeChar(*it_y) )
          return false;
      }

      return true;//boost::algorithm::iequals(x, y, std::locale());
    }
  };

  struct DictHashFunc : std::unary_function<std::wstring, std::size_t>
  {
    std::size_t operator()(std::wstring const& x) const
    {
      std::size_t seed = 0;
      for(std::wstring::const_iterator it = x.begin();
        it != x.end(); ++it)
      {
        wchar_t ch = NormailizeChar(*it);
        if (!ch)
          continue;
        boost::hash_combine(seed, ch);
      }
      return seed;
    }
  };

class Censor// : public BaseObjectMT
{
  //NI_DECLARE_REFCOUNT_CLASS_1(Censor, BaseObjectMT);

  typedef boost::unordered_set< std::wstring, DictHashFunc, DictEqualToPred> TStringTable;
  
  struct FilterContext
  {
    void ResetSplitedWord();
    void FilterLastSplitedWord(Censor* pCensor);
    void BuildSplitedWord( wchar_t* pWordStart, int wordLength );
    void Reset()
    {
      ResetSplitedWord();
      key.clear();
    }

    wchar_t*                    pSplitedWordStart;
    wchar_t*                    pSplitedWordEnd;
    std::wstring                splitedWordKey;
    std::wstring                key;
  };  

public:
  Censor() : maxKeyLength(0), maskWholeWord(true) {}
  ~Censor() {}
  
  void Filter(wchar_t*);
  void FilterThreadSafe(wchar_t*);

  void SetMaskWholeWord(bool val) { maskWholeWord = val; }
  void AddDictionary( std::wstringstream& data, bool isWhiteList /*= false*/ );

  int LoadDictionary(const wchar_t* fileName, bool isWhiteList = false);
private:
  nstl::vector<TStringTable>  dicts;
  TStringTable                whiteList;
  size_t                      maxKeyLength;
  bool                        maskWholeWord;

  FilterContext               ctx;

  void FilterText(wchar_t*, FilterContext*);

  bool CheckInWhiteList( const std::wstring& word );
  bool CheckInWhiteList( const wchar_t* pWordStart,  wchar_t* const pWordEnd );
  bool FindInDicts(const nstl::wstring& key);
  bool FindInDicts(const std::wstring& key);
  bool FindWordInDicts(const std::wstring& word);

  bool RollUpString( const std::wstring& sourceStr, std::wstring& res );

  void AddWordToDict( const wchar_t* pWord, TStringTable& dict, bool isWhiteList = false );

};
}
#endif //#define CENSOR_H_4A244540_8CC1_43F3_9021