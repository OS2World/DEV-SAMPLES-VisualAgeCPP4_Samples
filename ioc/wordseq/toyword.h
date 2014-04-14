/******************************************************************************
* .FILE:         toyword.h                                                    *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1997 - All Rights Reserved                 *
*                                                                             *
* .DISCLAIMER:                                                                *
*   The following [enclosed] code is sample code created by IBM               *
*   Corporation.  This sample code is not part of any standard IBM product    *
*   and is provided to you solely for the purpose of assisting you in the     *
*   development of your applications.  The code is provided 'AS IS',          *
*   without warranty of any kind.  IBM shall not be liable for any damages    *
*   arising out of your use of the sample code, even if they have been        *
*   advised of the possibility of such damages.                               *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

/*-------------------------------------------------------------*\
|  toyword.h  -  Class Word for use with coding examples.       |
\*-------------------------------------------------------------*/

#include <istring.hpp>

class Word  {

  IString      ivWord;
  unsigned int ivKey;

public:

  //Constructor to be used for sample: wordbag.c
  Word (IString const& word, unsigned theLength)
  : ivWord (word), ivKey (theLength) {}

  //Constructor to be used for sample: wordseq.c
  Word (IString const& word)
  : ivWord (word) {}

  IBoolean operator> (Word const& w1)
           { return ivWord > w1.ivWord;
           }

  unsigned int setKey ()
            { return (ivKey = ivWord.length());
            }

  IString const& getWord() const
            { return ivWord;
            }

  unsigned int const& getKey() const
            { return ivKey;
            }
};

// Key access.  The length of the word is the key.
inline unsigned int const& key (Word const& aWord)
{ return aWord.getKey();
}
