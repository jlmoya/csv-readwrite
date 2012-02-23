//
//  Copyright (C) 2011 - DIGITEO - Michael Baudin
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//


// See all the available fields
allvalues = csv_default();
expected = [
    "separator"  ","
    "decimal"    "."
    "conversion" "double"
    "precision"  "%.17lg"
    "regexp" ""
];

if getos() == "Windows" then
  expected = [expected; "eol" "windows"];
else
  expected = [expected; "eol" "linux"];
end
expected = [expected; "encoding" "utf-8"];

assert_checkequal ( allvalues , expected );
// Get the value of the "precision" field
value = csv_default("precision");
assert_checkequal ( value , "%.17lg" );
// Set the value of the "precision" field
bRes = csv_default("precision","%.17e");
assert_checkequal ( bRes , %t );
// Set the value of the "precision" field to
// an impossible value
bRes = csv_default("precision","Ouch!");
assert_checkequal ( bRes , %f );

