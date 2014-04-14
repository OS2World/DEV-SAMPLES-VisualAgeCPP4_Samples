/******************************************************************************
* .FILE:         graph.h                                                      *
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

#include <istring.hpp>
#include <iostream.h>


class Graphics
{

protected:


  IString ivId;    //*** graphics ID ****/
  int     ivKey;   //*** graphics key ****/

public:


  Graphics (int graphicsKey, IString id) : ivKey(graphicsKey),
                                           ivId(id)
                                           { }


  ~Graphics()
    {
     cout << this->ivId
           << " will now be deleted ... "
          << endl;
    }


  IBoolean operator== (Graphics const& graphics) const
    {
     return (this->ivId == graphics.ivId);
    }


  IString const& id() const
    {
     return ivId;
    }


  virtual        void           draw() const =0;

  /**** This member function returns the graphic's key ****/
  /*    Note that we are returning the int by reference,  */
  /*    because this member function will be used by the  */
  /*    key(...) function, which must return a reference. */
  /********************************************************/
  int const& graphicsKey() const
    {
     return ivKey;
    }

};

/****************       key function       *********************/
/****   note that this interface must always be used with:  ****/
/****              Keytype const& key(....)                 ****/
/****                                                       ****/
/****   We are providing this key function for the element  ****/
/****   type Graphics  and not for the managed pointer.     ****/
/***************************************************************/
  inline int const& key (Graphics const& graphics)
    {
     return graphics.graphicsKey();
    }
