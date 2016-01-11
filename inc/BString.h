/*******************************************************************************
 * BString.h
 *
 * Created on: 2015-09-21
 *     Author: fuliang
 *******************************************************************************/

#ifndef BSTRING_H_
#define BSTRING_H_

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>

#include <vector>
#include <string>

/*******************************************************************************
 * boost::to_lower
 * Parameters: (string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ToLower boost::to_lower

/*******************************************************************************
 * boost::to_lower_copy
 * Parameters: (string)
 * Return-Value: a copy string after lower
 *******************************************************************************/
#define BT_ToLowerCopy boost::to_lower_copy

/*******************************************************************************
 * boost:::to_upper
 * Parameters: (string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ToUpper boost::to_upper

/*******************************************************************************
 * boost::to_upper_copy
 * Parameters: (string)
 * Return-Value: a copy string after upper
 *******************************************************************************/
#define BT_ToUpperCopy boost::to_upper_copy

/*******************************************************************************
 * boost::starts_with
 * Parameters: (string, string, compare(char, char) = is_equal)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_StartsWith boost::starts_with

/*******************************************************************************
 * boost::istarts_with
 * Parameters: (string, string)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_StartsCaseWith boost::istarts_with

/*******************************************************************************
 * boost::ends_with
 * Parameters: (string, string, compare(char, char) const = is_equal)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_EndsWith boost::ends_with

/*******************************************************************************
 * boost::iends_with
 * Parameters: (string, string)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_EndsCaseWith boost::iends_with

/*******************************************************************************
 * boost::contains
 * Parameters: (string, string, compare(char, char) const = is_equal)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_Contains boost::contains

/*******************************************************************************
 * boost::icontains
 * Parameters: (string, string)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_ContainsCase boost::icontains

/*******************************************************************************
 * boost::equals
 * Parameters: (string, string, compare(char, char) const = is_equal)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_Equals boost::equals

/*******************************************************************************
 * boost::iequals
 * Parameters: (string, string)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_EqualsCase boost::iequals

/*******************************************************************************
 * boost::lexicographical_compare
 * Parameters: (string, string, compare(char, char) const = is_less)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_LexicographicalCompare boost::lexicographical_compare

/*******************************************************************************
 * boost::ilexicographical_compare
 * Parameters: (string, string, compare(char, char) const = is_less)
 * Return-Value: true or false
 *******************************************************************************/
#define BT_LexicographicalCaseCompare boost::ilexicographical_compare

/*******************************************************************************
 * boost::all
 * Parameters: (string, compare(char, char))
 * Return-Value: true or false
 *******************************************************************************/
#define BT_ALL boost::all

/*******************************************************************************
 * boost::is_equal()
 * Parameters: (T1, T2) use ==
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsEqual boost::is_equal()

/*******************************************************************************
 * boost::is_iequal()
 * Parameters: (char, char) use std::toupper
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsCaseEqual boost::is_iequal()

/*******************************************************************************
 * boost::is_less()
 * Parameters: (T, T) use <
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsLess boost::is_less()

/*******************************************************************************
 * boost::is_iless()
 * Parameters: (char, char) use std::toupper
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsCaseLess boost::is_iless()

/*******************************************************************************
 * boost::is_not_greater()
 * Parameters: (T, T) use <=
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsNotGreater boost::is_not_greater()

/*******************************************************************************
 * boost::is_not_igreater()
 * Parameters: (char, char) use std::toupper
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsCaseNotGreater boost::is_not_igreater()

/*******************************************************************************
 * boost::is_space()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsSpace boost::is_space()

/*******************************************************************************
 * boost::is_alnum() character or digit
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsAlnum boost::is_alnum()

/*******************************************************************************
 * boost::is_alpha() only character
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsAlpha boost::is_alpha()

/*******************************************************************************
 * boost::is_cntrl() control character
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsCntrl boost::is_cntrl()

/*******************************************************************************
 * boost::is_digit()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsDigit boost::is_digit()

/*******************************************************************************
 * boost::is_graph() graphic character
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsGraph boost::is_graph()

/*******************************************************************************
 * boost::is_lower()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsLower boost::is_lower()

/*******************************************************************************
 * boost::is_print()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsPrint boost::is_print()

/*******************************************************************************
 * boost::is_punct() punctuation
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsPunct boost::is_punct()

/*******************************************************************************
 * boost::is_upper()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsUpper boost::is_upper()

/*******************************************************************************
 * boost::is_xdigit() hex character
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsXdigit boost::is_xdigit()

/*******************************************************************************
 * boost::is_any_of()
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsAnyOf(set) boost::is_any_of(set)

/*******************************************************************************
 * boost::is_from_range
 * Parameters: (char)
 * Return-Value: true, or false
 *******************************************************************************/
#define BS_IsFromRange(from, to) boost::is_from_range(from, to)

/*******************************************************************************
 * boost::trim_left and trim_left_if
 * Parameters: (string, is_space())
 * Return-Value: void
 *******************************************************************************/
inline void BT_TrimLeft(std::string& strText) { boost::trim_left(strText); }
template <class T> inline void BT_TrimLeft(std::string& strText, T tPredicate) { boost::trim_left_if(strText, tPredicate); }

/*******************************************************************************
 * boost::trim_left_copy and trim_left_copy_if
 * Parameters: (string, is_space())
 * Return-Value: string after trim
 *******************************************************************************/
inline std::string BT_TrimLeftCopy(const std::string& strText) { return boost::trim_left_copy(strText); }
template <class T> inline std::string BT_TrimLeftCopy(const std::string& strText, T tPredicate) { return boost::trim_left_copy_if(strText, tPredicate); }

/*******************************************************************************
 * boost::trim_right and trim_right_if
 * Parameters: (string, is_space())
 * Return-Value: void
 *******************************************************************************/
inline void BT_TrimRight(std::string& strText) { boost::trim_right(strText); }
template <class T> inline void BT_TrimRight(std::string& strText, T tPredicate) { boost::trim_right_if(strText, tPredicate); }

/*******************************************************************************
 * boost::trim_right_copy and trim_right_copy_if
 * Parameters: (string, is_space())
 * Return-Value: string after trim
 *******************************************************************************/
inline std::string BT_TrimRightCopy(const std::string& strText) { return boost::trim_right_copy(strText); }
template <class T> inline std::string BT_TrimRightCopy(const std::string& strText, T tPredicate) { return boost::trim_right_copy_if(strText, tPredicate); }

/*******************************************************************************
 * boost::trim and trim_if
 * Parameters: (string, is_space())
 * Return-Value: string after trim
 *******************************************************************************/
inline void BT_Trim(std::string& strText) { boost::trim(strText); }
template <class T> inline void BT_Trim(std::string& strText, T tPredicate) { boost::trim_if(strText, tPredicate); }

/*******************************************************************************
 * boost::trim_copy and trim_copy_if
 * Parameters: (string, is_space())
 * Return-Value: string after trim
 *******************************************************************************/
inline std::string BT_TrimCopy(const std::string& strText) { return boost::trim_copy(strText); }
template <class T> inline std::string BT_TrimCopy(const std::string& strText, T tPredicate) { return boost::trim_copy_if(strText, tPredicate); }

/*******************************************************************************
 * boost::find_first
 * Parameters: (string, string)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindFirst(std::string& strText, const std::string& strSearch){boost::iterator_range<std::string::iterator> BIterRange = boost::find_first(strText, strSearch); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::ifind_first
 * Parameters: (string, string)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindCaseFirst(std::string& strText, const std::string& strSearch){boost::iterator_range<std::string::iterator> BIterRange = boost::ifind_first(strText, strSearch); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::find_last
 * Parameters: (string, string)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindLast(std::string& strText, const std::string& strSearch){boost::iterator_range<std::string::iterator> BIterRange = boost::find_last(strText, strSearch); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::ifind_last
 * Parameters: (string, string)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindCaseLast(std::string& strText, const std::string& strSearch){boost::iterator_range<std::string::iterator> BIterRange = boost::ifind_last(strText, strSearch); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::find_nth, n from 0
 * Parameters: (string, string, int)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindNth(std::string& strText, const std::string& strSearch, const int& iNth){boost::iterator_range<std::string::iterator> BIterRange = boost::find_nth(strText, strSearch, iNth); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::ifind_int, n form 0
 * Parameters: (string, string, int)
 * Return-Value: position
 *******************************************************************************/
inline size_t BT_FindCaseNth(std::string& strText, const std::string& strSearch, const int& iNth){boost::iterator_range<std::string::iterator> BIterRange = boost::ifind_nth(strText, strSearch, iNth); \
	return BIterRange.empty() ? std::string::npos : BIterRange.begin() - strText.begin();}

/*******************************************************************************
 * boost::find_head
 * Parameters: (string, int)
 * Return-Value: string
 *******************************************************************************/
inline std::string BT_FindHead(std::string& strText, const int& iNth){boost::iterator_range<std::string::iterator> BIterRange = boost::find_head(strText, iNth);\
	return BIterRange.empty() ? std::string() : std::string(BIterRange.begin(), BIterRange.end());}

/*******************************************************************************
 * boost::find_tail
 * Parameters: (string, int)
 * Return-Value: string
 *******************************************************************************/
inline std::string BT_FindTail(std::string& strText, const int& iNth){boost::iterator_range<std::string::iterator> BIterRange = boost::find_tail(strText, iNth);\
	return BIterRange.empty() ? std::string() : std::string(BIterRange.begin(), BIterRange.end());}

/*******************************************************************************
 * boost::erase_first
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseFirst boost::erase_first

/*******************************************************************************
 * boost::erase_first_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseFirstCopy boost::erase_first_copy

/*******************************************************************************
 * boost::ierase_first
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseCaseFirst boost::ierase_first

/*******************************************************************************
 * boost::ierase_first_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseCaseFirstCopy boost::ierase_first_copy

/*******************************************************************************
 * boost::erase_last
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseLast boost::erase_last

/*******************************************************************************
 * boost::erase_last_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseLastCopy boost::erase_last_copy

/*******************************************************************************
 * boost::ierase_last
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseCaseLast boost::ierase_last

/*******************************************************************************
 * boost::ierase_last_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseCaseLastCopy boost::ierase_last_copy

/*******************************************************************************
 * boost::erase_nth
 * Parameters: (string, string, int)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseNth boost::erase_nth

/*******************************************************************************
 * boost::erase_nth_copy
 * Parameters: (string, string, int)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseNthCopy boost::erase_nth_copy

/*******************************************************************************
 * boost::ierase_nth
 * Parameters: (string, string, int)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseCaseNth boost::ierase_nth

/*******************************************************************************
 * boost::ierase_nth_copy
 * Parameters: (string, string, int)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseCaseNthCopy boost::ierase_nth_copy

/*******************************************************************************
 * boost::erase_all
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseAll boost::erase_all

/*******************************************************************************
 * boost::erase_all_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseAllCopy boost::erase_all_copy

/*******************************************************************************
 * boost::ierase_all
 * Parameters: (string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseCaseAll boost::ierase_all

/*******************************************************************************
 * boost::ierase_all_copy
 * Parameters: (string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseCaseAllCopy boost::ierase_all_copy

/*******************************************************************************
 * boost::erase_head
 * Parameters: (string, int)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseHead boost::erase_head

/*******************************************************************************
 * boost::erase_head_copy
 * Parameters: (string, int)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseHeadCopy boost::erase_head_copy

/*******************************************************************************
 * boost::erase_tail
 * Parameters: (string, int)
 * Return-Value: void
 *******************************************************************************/
#define BT_EraseTail boost::erase_tail

/*******************************************************************************
 * boost::erase_tail_copy
 * Parameters: (string, int)
 * Return-Value: string
 *******************************************************************************/
#define BT_EraseTailCopy boost::erase_tail_copy

/*******************************************************************************
 * boost::replace_first
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceFirst boost::replace_first

/*******************************************************************************
 * boost::replace_first_copy
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceFirstCopy boost::replace_first_copy

/*******************************************************************************
 * boost::ireplace_first
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceCaseFirst boost::ireplace_first

/*******************************************************************************
 * boost::ireplace_first_copy
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceCaseFirstCopy boost::ireplace_first_copy

/*******************************************************************************
 * boost::replace_last
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceLast boost::replace_last

/*******************************************************************************
 * boost::replace_last_copy
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceLastCopy boost::replace_last_copy

/*******************************************************************************
 * boost::ireplace_last
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceCaseLast boost::ireplace_last

/*******************************************************************************
 * boost::ireplace_last_copy
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceCaseLastCopy boost::ireplace_last_copy

/*******************************************************************************
 * boost::replace_nth
 * Parameters: (string, string, int, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceNth boost::replace_nth

/*******************************************************************************
 * boost::replace_nth
 * Parameters: (string, string, int, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceNthCopy boost::replace_nth_copy

/*******************************************************************************
 * boost::ireplace_nth
 * Parameters: (string, string, int, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceCaseNth boost::ireplace_nth

/*******************************************************************************
 * boost::ireplace_nth_copy
 * Parameters: (string, string, int, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceCaseNthCopy boost::ireplace_nth_copy

/*******************************************************************************
 * boost::replace_all
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceAll boost::replace_all

/*******************************************************************************
 * boost::replace_all
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceAllCopy boost::replace_all_copy

/*******************************************************************************
 * boost::ireplace_all
 * Parameters: (string, string, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceCaseAll boost::ireplace_all

/*******************************************************************************
 * boost::ireplace_all_copy
 * Parameters: (string, string, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceCaseAllCopy boost::ireplace_all_copy

/*******************************************************************************
 * boost::replace_head
 * Parameters: (string, int, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceHead boost::replace_head

/*******************************************************************************
 * boost::replace_head_copy
 * Parameters: (string, int, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceHeadCopy boost::replace_head_copy

/*******************************************************************************
 * boost::replace_tail
 * Parameters: (string, int, string)
 * Return-Value: void
 *******************************************************************************/
#define BT_ReplaceTail boost::replace_tail

/*******************************************************************************
 * boost::replace_tail_copy
 * Parameters: (string, int, string)
 * Return-Value: string
 *******************************************************************************/
#define BT_ReplaceTailCopy boost::replace_tail_copy

/*******************************************************************************
 * boost::find_all
 * Parameters: (vector<string>, string, string)
 * Return-Value: vector<size_t>
 *******************************************************************************/
inline std::vector<size_t> BT_FindAll(std::vector<std::string>& vecRst, std::string& strText, const std::string& strSearch) { std::vector<boost::iterator_range<std::string::iterator> > vecRange;\
	boost::find_all(vecRange, strText, strSearch); std::vector<size_t> vecPos; for (std::vector<boost::iterator_range<std::string::iterator> >::iterator iterVec = vecRange.begin(); \
	iterVec != vecRange.end(); ++iterVec) {vecRst.push_back(std::string(iterVec->begin(), iterVec->end())); vecPos.push_back(iterVec->begin() - strText.begin());} return vecPos;}

/*******************************************************************************
 * boost::ifind_all
 * Parameters: (vector<string>, string, string)
 * Return-Value: vector<size_t>
 *******************************************************************************/
inline std::vector<size_t> BT_FindCaseAll(std::vector<std::string>& vecRst, std::string& strText, const std::string& strSearch) { std::vector<boost::iterator_range<std::string::iterator> > vecRange;\
	boost::ifind_all(vecRange, strText, strSearch); std::vector<size_t> vecPos; for (std::vector<boost::iterator_range<std::string::iterator> >::iterator iterVec = vecRange.begin(); \
	iterVec != vecRange.end(); ++iterVec) {vecRst.push_back(std::string(iterVec->begin(), iterVec->end())); vecPos.push_back(iterVec->begin() - strText.begin());} return vecPos;}

/*******************************************************************************
 * boost::split
 * Parameters: (vector<string>, string, pred, bool)
 * Return-Value: vector<size_t>
 *******************************************************************************/
template<class T>
inline void BT_Split(std::vector<std::string>& vecRst, std::string& strText, T tPred, bool bCompress = true){ boost::split(vecRst, strText, tPred, \
	bCompress ? boost::algorithm::token_compress_on : boost::algorithm::token_compress_off);
}

/*******************************************************************************
 * boost::join
 * Parameters: (vector<string>, string)
 * Return-Value: string
 *******************************************************************************/
inline std::string BT_Join(const std::vector<std::string>& vecText, const std::string& strSeparator) {return boost::join(vecText, strSeparator);}

/*******************************************************************************
 * boost::join
 * Parameters: (vector<string>, string, pred)
 * Return-Value: string
 *******************************************************************************/
template<class T>
inline std::string BT_Join(const std::vector<std::string>& vecText, const std::string& strSeparator, T tPred){return boost::join_if(vecText, strSeparator, tPred);}

/*******************************************************************************
 *  boost::iterator_range<std::string::iterator>
 *******************************************************************************/
typedef boost::iterator_range<std::string::iterator> BC_SIteratorRange;

/*******************************************************************************
 * boost::first_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_FirstFinder boost::first_finder

/*******************************************************************************
 * boost::last_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_LastFinder boost::last_finder

/*******************************************************************************
 * boost::nth_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_NthFinder boost::nth_finder

/*******************************************************************************
 * boost::head_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_HeadFinder boost::head_finder

/*******************************************************************************
 * boost::tail_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_TailFinder boost::tail_finder

/*******************************************************************************
 * boost::token_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_TokenFinder boost::token_finder

/*******************************************************************************
 * boost::range_finder
 * Parameters: (string)
 * Return-Value: BC_SIteratorRange f(begin(), end())
 *******************************************************************************/
#define BS_RangeFinder boost::range_finder

/*******************************************************************************
 *  boost::find_iterator<std::string::iterator>
 *******************************************************************************/
typedef boost::find_iterator<std::string::iterator> BC_SFindIterator;

/*******************************************************************************
 *  boost::split_iterator<std::string::iterator>
 *******************************************************************************/
typedef boost::split_iterator<std::string::iterator> BC_SPlitIterator;

/*******************************************************************************
 *  boost::make_find_iterator
 *  Parameters: (string, f)
 *  Return-Value: BC_SFindIterator
 *******************************************************************************/
#define BT_MakeFindIterator boost::make_find_iterator

/*******************************************************************************
 *  boost::make_split_iterator
 *  Parameters: (string, f)
 *  Return-Value: BC_SPlitIterator
 *******************************************************************************/
#define BT_MakeSplitIterator boost::make_split_iterator

/*******************************************************************************
 * boost::tokenizer
 * Parameters: (Iterator, Iterator, f = TokenizerFunc())(Container)(Container, f)
 * Return-Value: void
 *******************************************************************************/
#ifndef BC_Tokenizer
#define BC_Tokenizer boost::tokenizer
#endif

/*******************************************************************************
 * use for BC_Tokenizer
 *******************************************************************************/
#ifndef BF_Begin
#define BF_Begin begin
#endif

/*******************************************************************************
 * use for BC_Tokenizer
 *******************************************************************************/
#ifndef BF_End
#define BF_End end
#endif

/*******************************************************************************
 * use for BC_Tokenizer
 *******************************************************************************/
#ifndef BF_Assign
#define BF_Assign assign
#endif

/*******************************************************************************
 * token_functions
 * char
 * csv
 * offset
 *******************************************************************************/
#define BS_CharSeparator boost::char_separator
#define BS_EscapedListSeparator boost::escaped_list_separator
#define BS_OffsetSeparator boost::offset_separator

/*******************************************************************************
 * .: 匹配任意的单个字符，是单字符的通配符
 * ^: 匹配行的开头
 * $: 匹配行的末尾
 * (): 定义子表达式
 * *: 表示前面的元素可以重复任意多次>=0
 * +: 表示前面的元素可以重复一次或多次>0
 * ?: 表示前面的元素可以重复0次或1次
 * {}: 手工指定重复的次数{n}, {n,}, {n, m}
 * []: 定义字符的范围，集合或补集
 * \: 转义字符
 * |: 或
 *******************************************************************************/

/*******************************************************************************
 * boost::xpressive::sregex
 *******************************************************************************/
typedef boost::xpressive::sregex BC_SRegex;

/*******************************************************************************
 * boost::xpressive::cregex
 *******************************************************************************/
typedef boost::xpressive::cregex BC_CRegex;

/*******************************************************************************
 * boost::xpressive::smatch
 *******************************************************************************/
typedef boost::xpressive::smatch BC_SMatch;

/*******************************************************************************
 * boost::xpressive::cmatch
 *******************************************************************************/
typedef boost::xpressive::cmatch BC_CMatch;

/*******************************************************************************
 * boost::xpressive::sregex::compile
 *******************************************************************************/
#define BT_SCompile boost::xpressive::sregex::compile

/*******************************************************************************
 * boost::xpressive::cregex::compile
 *******************************************************************************/
#define BT_CCompile boost::xpressive::cregex::compile

/*******************************************************************************
 * boost::xpressive::regex_match
 *******************************************************************************/
#define BT_RegexMatch boost::xpressive::regex_match

/*******************************************************************************
 * boost::xpressive::regex_search
 *******************************************************************************/
#define BT_RegexSearch boost::xpressive::regex_search

/*******************************************************************************
 * boost::xpressive::regex_replace
 *******************************************************************************/
#define BT_RegexReplace boost::xpressive::regex_replace

/*******************************************************************************
 * boost::xpressive::sregex_iterator
 *******************************************************************************/
typedef boost::xpressive::sregex_iterator BC_SIterator;

/*******************************************************************************
 * boost::xpressive::cregex_iterator
 *******************************************************************************/
typedef boost::xpressive::cregex_iterator BC_CIterator;

/*******************************************************************************
 * boost::xpressive::sregex_token_iterator
 *******************************************************************************/
typedef boost::xpressive::sregex_token_iterator BC_STokenIterator;

/*******************************************************************************
 * boost::xpressive::cregex_token_iterator
 *******************************************************************************/
typedef boost::xpressive::cregex_token_iterator BC_CTokenIterator;

#endif
