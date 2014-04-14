/*
 * IBM VisualAge C++ Professional, Version 4.0
 *
 * Licensed Materials - Property of IBM
 *
 * (C) Copyright IBM Corp. 1998. All Rights Reserved.
 *
 * The following [enclosed] code is sample code created by IBM
 * Corporation.  This sample code is not part of any standard IBM product
 * and is provided to you solely for the purpose of assisting you in the
 * development of your applications.  The code is provided 'AS IS',
 * without warranty of any kind.  IBM shall not be liable for any damages
 * arising out of your use of the sample code, even if they have been
 * advised of the possibility of such damages.
 */

#include <locale>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

typedef codecvt<wchar_t, char, mbstate_t> CVT;

// Return TRUE if string "str" matches pattern "pat".  The pattern may
// contain wildcard characters.  Parameter "anyOne" specifies a
// wildcard which matches exactly one character.  Parameter
// "zeroOrMore" specifies a wildcard which matches any number of
// characters (including matching zero characters).

// match() supports wchar_t* matching against char* strings, which
// may come from an external source.  The specified locale is consulted
// to determine how many chars are used to make up a given wchar_t character.

bool match(const wchar_t* pat, const char* str, locale loc,
    wchar_t anyOne = '?', wchar_t zeroOrMore = '*')
{
	const CVT& cc = use_facet<CVT> (loc);
	CVT::state_type st;

	while (*str) {
		const char* snext;
		wchar_t wc;
		wchar_t* wnext;

		size_t slen = strlen(str);
		int clen = cc.length(st, str, str + slen, 1);
		cc.in(st, str, str + clen, snext, &wc, &wc + 1, wnext);

		if (*pat == zeroOrMore) {
			if (match(pat + 1, str, loc, anyOne, zeroOrMore))
				return true;
			str += clen;
		}
		else if (*pat == wc || *pat == anyOne) {
			str += clen;
			pat++;
		}
		else {
			return false;
		}
	}

	while (*pat == zeroOrMore)
		pat++;

	return *str == '\0' && *pat == '\0';
}

int main()
{
    try {
	locale loc = locale();

	cout << match(L"abc", "abc", loc) << endl; // true
	cout << match(L"ab?", "abc", loc) << endl; // true
	cout << match(L"*bc", "abc", loc) << endl; // true
	cout << match(L"abd", "abc", loc) << endl; // false

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
