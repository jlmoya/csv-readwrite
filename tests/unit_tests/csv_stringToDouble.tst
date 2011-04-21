//
//  Copyright (C) 2010 - 2011 - DIGITEO - Allan CORNET
//  Copyright (C) 2011 - DIGITEO - Michael Baudin
//
//  This file must be used under the terms of the CeCILL.
//  This source file is licensed as described in the file COPYING, which
//  you should have received as part of this distribution.  The terms
//  are also available at
//  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//

// <-- JVM NOT MANDATORY -->

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");
exec(fullfile(path,"myassert_checkequal.sci"));


// =============================================================================
r = csv_stringtodouble("-Nani");
myassert_checkequal ( r , complex(0,%nan) );
// =============================================================================
r = csv_stringtodouble("Nani");
myassert_checkequal ( r , complex(0,%nan) );
// =============================================================================
r = csv_stringtodouble("+Nani");
myassert_checkequal ( r , complex(0,%nan) );
// =============================================================================
r = csv_stringtodouble("-Infi");
myassert_checkequal ( r , complex(0,-%inf) );
// =============================================================================
r = csv_stringtodouble("Infi");
myassert_checkequal ( r , complex(0,%inf) );
// =============================================================================
r = csv_stringtodouble("+Infi");
myassert_checkequal ( r , complex(0,%inf) );
// =============================================================================
r = csv_stringtodouble("Nan-Nani");
myassert_checkequal ( r , complex(%nan,%nan) );
// =============================================================================
r = csv_stringtodouble("Nan-2i");
myassert_checkequal ( r , complex(%nan,-2) );
// =============================================================================
r = csv_stringtodouble("-Nan-2i");
myassert_checkequal ( r , complex(%nan,-2) );
// =============================================================================
r = csv_stringtodouble("+Nan-2i");
myassert_checkequal ( r , complex(%nan,-2) );
// =============================================================================
r = csv_stringtodouble("Nan-Infi");
myassert_checkequal ( r , complex(%nan,-%inf) );
// =============================================================================
r = csv_stringtodouble("-Inf-2i");
myassert_checkequal ( r , complex(-%inf,-2) );
// =============================================================================
r = csv_stringtodouble("+Inf-2i");
myassert_checkequal ( r , complex(%inf,-2) );
// =============================================================================
r = csv_stringtodouble("Inf-2i");
myassert_checkequal ( r , complex(%inf,-2) );
// =============================================================================
r = csv_stringtodouble("Inf-Infi");
myassert_checkequal ( r , complex(%inf,-%inf) );
// =============================================================================
r = csv_stringtodouble("Inf+Infi");
myassert_checkequal ( r , complex(%inf,%inf) );
// =============================================================================
r = csv_stringtodouble("1+Nani");
myassert_checkequal ( r , complex(1,%nan) );
// =============================================================================
r = csv_stringtodouble("1-Nani");
myassert_checkequal ( r , complex(1,%nan) );
// =============================================================================
r = csv_stringtodouble("-1-Nani");
myassert_checkequal ( r , complex(-1,%nan) );
// =============================================================================
r = csv_stringtodouble("1+Infi");
myassert_checkequal ( r , complex(1,%inf) );
// =============================================================================
r = csv_stringtodouble("1-Infi");
myassert_checkequal ( r , complex(1,-%inf) );
// =============================================================================
myassert_checkequal ( csv_stringtodouble("Nan") , %nan );
myassert_checkequal ( csv_stringtodouble("-Nan"), %nan );
myassert_checkequal ( csv_stringtodouble("+Nan"), %nan );
myassert_checkequal ( csv_stringtodouble("-Inf") , -%inf );
myassert_checkequal ( csv_stringtodouble("Inf") , %inf );
myassert_checkequal ( csv_stringtodouble("+Inf") , %inf );
myassert_checkequal ( csv_stringtodouble("+i") , %i  );
myassert_checkequal ( csv_stringtodouble("-i") , -%i  );
myassert_checkequal ( csv_stringtodouble("+j") , %i  );
myassert_checkequal ( csv_stringtodouble("-j") , -%i  );
myassert_checkequal ( csv_stringtodouble("i") , %i  );
myassert_checkequal ( csv_stringtodouble("j") , %i  );
myassert_checkequal ( csv_stringtodouble(" 3 + 2i") , complex(3,2) );
myassert_checkequal ( csv_stringtodouble(" 3 - 2i") , complex(3,- 2) );
myassert_checkequal ( csv_stringtodouble(" -3 + 2i") , complex(-3,2) );
myassert_checkequal ( csv_stringtodouble(" 3 - 2i") , complex(3,-2) );
myassert_checkequal ( csv_stringtodouble("- 3 - 2i") , complex(-3,-2) );
myassert_checkequal ( csv_stringtodouble("+3 - 2i") , complex(+3,-2) );
myassert_checkequal ( csv_stringtodouble("+3 + 2i") , complex(3,2) );
myassert_checkequal ( csv_stringtodouble("+3 - 2i") , complex(3,-2) );
myassert_checkequal ( csv_stringtodouble("4+i") , complex(4,1) );
myassert_checkequal ( csv_stringtodouble("4-i") , complex(4,-1) );
myassert_checkequal ( csv_stringtodouble("-4+i") , complex(-4,1) );
myassert_checkequal ( csv_stringtodouble("-4-i") , complex(-4,-1) );
myassert_checkequal ( csv_stringtodouble("+4+i") , complex(4,1) );
myassert_checkequal ( csv_stringtodouble("+4-i") , complex(4,-1) );
myassert_checkequal ( csv_stringtodouble("10")  , 10 );
myassert_checkequal ( csv_stringtodouble("+10") , 10 );
myassert_checkequal ( csv_stringtodouble("-10") , -10 );
myassert_checkequal ( csv_stringtodouble("10.") , 10 );
myassert_checkequal ( csv_stringtodouble("+10.") , 10 );
myassert_checkequal ( csv_stringtodouble("-10.") , -10 );
myassert_checkequal ( csv_stringtodouble(".4") , .4 );
myassert_checkequal ( csv_stringtodouble("+.4") , .4 );
myassert_checkequal ( csv_stringtodouble("-.4") , -.4 );
myassert_checkequal ( csv_stringtodouble("10.4") , 10.4 );
myassert_checkequal ( csv_stringtodouble("+10.4") , 10.4 );
myassert_checkequal ( csv_stringtodouble("-10.4") , -10.4 );
myassert_checkequal ( csv_stringtodouble("10+10j") , complex(10, 10) );
myassert_checkequal ( csv_stringtodouble("+10+10j") , complex(10, 10) );
myassert_checkequal ( csv_stringtodouble("-10+10j") , complex(-10, 10) );
myassert_checkequal ( csv_stringtodouble("10.+10j") , complex(10, 10) );
myassert_checkequal ( csv_stringtodouble("+10.+10j") , complex(10, 10) );
myassert_checkequal ( csv_stringtodouble("-10.+10j") , complex(-10, 10) );
myassert_checkequal ( csv_stringtodouble("10.4+10j") , complex(10.4, 10) );
myassert_checkequal ( csv_stringtodouble("+10.4+10j") , complex(10.4, 10) );
myassert_checkequal ( csv_stringtodouble("-10.4+10j") , complex(-10.4, 10) );
myassert_checkequal ( csv_stringtodouble(".4+10j") , complex(.4, 10) );
myassert_checkequal ( csv_stringtodouble("+.4+10j") , complex(.4, 10) );
myassert_checkequal ( csv_stringtodouble("-.4+10j") , complex(-.4, 10) );
myassert_checkequal ( csv_stringtodouble("10+10.4j") , complex(10, 10.4) );
myassert_checkequal ( csv_stringtodouble("10.4+10.4j") , complex(10.4, 10.4) );
myassert_checkequal ( csv_stringtodouble("+10.4+10.4j") , complex(10.4, 10.4) );
myassert_checkequal ( csv_stringtodouble("+10.4-10.4j") , complex(10.4, -10.4) );
myassert_checkequal ( csv_stringtodouble("1i") , %i );
myassert_checkequal ( csv_stringtodouble("1j") , %i );
myassert_checkequal ( csv_stringtodouble("+1j") , %i );
myassert_checkequal ( csv_stringtodouble("+1i") , %i );
myassert_checkequal ( csv_stringtodouble("-1j") , complex(0,-1) );
myassert_checkequal ( csv_stringtodouble("-1i") , complex(0,-1) );
myassert_checkequal ( csv_stringtodouble("10j") , complex(0,10) );
myassert_checkequal ( csv_stringtodouble("+10j") , complex(0,10) );
myassert_checkequal ( csv_stringtodouble("-10j") , complex(0, -10) );
myassert_checkequal ( csv_stringtodouble("10.j") , complex(0,10) );
myassert_checkequal ( csv_stringtodouble("+10.j") , complex(0,10) );
myassert_checkequal ( csv_stringtodouble("-10.j") , complex(0,-10) );
myassert_checkequal ( csv_stringtodouble(".4j") , complex(0,.4) );
myassert_checkequal ( csv_stringtodouble("+.4j") , complex(0,.4) );
myassert_checkequal ( csv_stringtodouble("-.4j") , complex(0,-.4) );
myassert_checkequal ( csv_stringtodouble("10.4j") , complex(0,10.4) );
myassert_checkequal ( csv_stringtodouble("+10.4j") , complex(0,10.4) );
myassert_checkequal ( csv_stringtodouble("-10.4j") , complex(0,-10.4) );
myassert_checkequal ( csv_stringtodouble("4e2") , 400 );
myassert_checkequal ( csv_stringtodouble("-4e2") , -400 );
myassert_checkequal ( csv_stringtodouble("+4e2") , 400 );
myassert_checkequal ( csv_stringtodouble("0.4e2") , 40 );
myassert_checkequal ( csv_stringtodouble("3e2 + 2e3i") , complex(300, 2000) );
myassert_checkequal ( csv_stringtodouble("3e2 - 2e3i") , complex(300, -2000) );
if ( getos() == "Windows" ) then
    myassert_checkequal ( csv_stringtodouble("3e2 - 2d3i") , complex(300, -2000) );
    myassert_checkequal ( csv_stringtodouble("3e2 + 2d3i") , complex(300, 2000) );
    myassert_checkequal ( csv_stringtodouble("3d2 + 2e3i") , complex(300, 2000) );
    myassert_checkequal ( csv_stringtodouble("3d2 - 2e3i") , complex(300, -2000) );
    myassert_checkequal ( csv_stringtodouble("3d2 + 2d3i") , complex(300, 2000) );
    myassert_checkequal ( csv_stringtodouble("3d2 - 2d3i") , complex(300, -2000) );
end
// =============================================================================
r = csv_stringtodouble("3e2 - blabli");
myassert_checkequal ( r , %nan);
// =============================================================================
r = csv_stringtodouble("3e2 - blabli", %t);
myassert_checkequal ( r , %nan);
// =============================================================================
myassert_checkequal ( execstr("r = csv_stringtodouble(""3e2 - blabli"", %f);", "errcatch") , 999 );
myassert_checkequal ( lasterror() , msprintf(_("%s: can not convert data.\n"), "csv_stringtodouble") );
// =============================================================================
r = csv_stringtodouble("-Nan*%i");
myassert_checkequal ( isnan(imag(r)) , %t);
myassert_checkequal ( csv_stringtodouble("+%i") , %i  );
myassert_checkequal ( csv_stringtodouble("-%i") , -%i  );
myassert_checkequal ( csv_stringtodouble("%i") , %i  );
myassert_checkequal ( csv_stringtodouble(" 3 + 2*%i") , complex(3,2) );
myassert_checkequal ( csv_stringtodouble(" 3 - 2*%i") , complex(3,- 2) );
myassert_checkequal ( csv_stringtodouble(" -3 + 2*%i") , complex(-3,2) );
myassert_checkequal ( csv_stringtodouble(" 3 - 2*%i") , complex(3,-2) );
myassert_checkequal ( csv_stringtodouble("- 3 - 2*%i") , complex(-3,-2) );
myassert_checkequal ( csv_stringtodouble("+3 - 2*%i") , complex(+3,-2) );
myassert_checkequal ( csv_stringtodouble("+3 + 2*%i") , complex(3,2) );
myassert_checkequal ( csv_stringtodouble("+3 - 2*%i") , complex(3,-2) );
myassert_checkequal ( csv_stringtodouble("4+%i") , complex(4,1) );
myassert_checkequal ( csv_stringtodouble("4-%i") , complex(4,-1) );
myassert_checkequal ( csv_stringtodouble("-4+%i") , complex(-4,1) );
myassert_checkequal ( csv_stringtodouble("-4-%i") , complex(-4,-1) );
myassert_checkequal ( csv_stringtodouble("+4+%i") , complex(4,1) );
myassert_checkequal ( csv_stringtodouble("+4-%i") , complex(4,-1) );
myassert_checkequal ( csv_stringtodouble("1*%i") , %i );
myassert_checkequal ( csv_stringtodouble("+1*%i") , %i );
myassert_checkequal ( csv_stringtodouble("-1*%i") , complex(0,-1) );
myassert_checkequal ( csv_stringtodouble("3e2 + 2e3*%i") , complex(300, 2000) );
myassert_checkequal ( csv_stringtodouble("3e2 - 2e3*%i") , complex(300, -2000) );
// =============================================================================
