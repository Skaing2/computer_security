/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once

// you may need to put something here...

enum Control {
  Public, Confidential, Privileged, Secret
};

inline bool securityConditionWrite(Control userControl, Control textControl) {
  return userControl <= textControl;
}

inline bool securityConditionRead(Control userControl, Control textControl) {
  return userControl >= textControl;
}


// test cases
// username: Lucas
// password: Diamond
// Security Levels: Secret
// Explaination:  