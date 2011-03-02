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

function [flag,errmsg] = Myassert_checkequal ( computed , expected )
    //  Check that computed and expected are equal.
    //
    // Calling Sequence
    //   Myassert_checkequal ( computed , expected )
    //   flag = Myassert_checkequal ( computed , expected )
    //   [flag,errmsg] = Myassert_checkequal ( computed , expected )
    //
    // Parameters
    //   computed: the computed result
    //   expected : the expected result
    //   flag : a 1x1 matrix of boolean, %t if computed is close to expected, %f if not
    //   errmsg : a 1x1 matrix of strings, the error message. If flag==%t, then errormsg=="". If flag==%f, then errmsg contains the error message.
    //
    // Description
    //   Performs silently if computed and expected are equal.
    //
    //   If the type of both input arguments is 1 (i.e. a real matrix),
    //   we check that non-nan values are equal.
    //
    //   If the comparison shows that computed is equal to expected, 
    //   and if the errmsg output variable is not used, an error is generated.
    //   If the comparison shows that computed is equal to expected, 
    //   and if the errmsg output variable is used, no error is generated.
    //
    // Examples
    // // Tests with success
    // Myassert_checkequal ( %T , %T );
    // flag = Myassert_checkequal ( list() , list() );
    // [flag , errmsg] = Myassert_checkequal ( [%T %F], [%T %F] );
    // Myassert_checkequal ( %nan , %nan );
    // 
    // // Tests with failure
    // Myassert_checkequal ( %F , %T );
    // flag = Myassert_checkequal ( %F , %T );
    // // No error produced :
    // [flag , errmsg] = Myassert_checkequal ( %F , %T )
    // Myassert_checkequal ( [1 2], [3 4] )
    // Myassert_checkequal ( 1 , [2 3] )
    // Myassert_checkequal ( 1 , "b" )
    //
    // Authors
    //   Michael Baudin, 2010
    //
    // Bibliography
    //   "Automated Software Testing for Matlab", Steven Eddins, 2009

    [lhs,rhs]=argn()
    if ( rhs <> 2 ) then
        errmsg = sprintf ( gettext ( "%s: Unexpected number of input arguments : %d provided while %d are expected.") , "Myassert_checkequal" , rhs , 2 )
        error(errmsg)
    end
    //
    // Check types of variables
    if ( typeof(computed) <> typeof(expected) ) then
        errmsg = sprintf ( gettext ( "%s: Variable typeof(computed) = %s while typeof(expected) = %s: inconsistent match.") , "Myassert_checkequal" , typeof(computed) , typeof(expected) )
        error(errmsg)
    end
    //
    // Check sizes of variables
    ncom = size(computed)
    nexp = size(expected)
    if ( or(ncom <> nexp) ) then
        cstr = "[" + strcat(string(ncom)," ") + "]"
        estr = "[" + strcat(string(nexp)," ") + "]"
        errmsg = sprintf ( gettext ( "%s: We have size(computed) = %s while size(expected) = %s: not consistent comparison.") , "Myassert_checkequal" , cstr , estr )
        error(errmsg)
    end  
    //
    if ( type(computed) == 1 & type(expected) == 1 ) then
        // These are two matrices of doubles
        csize = size (computed,"*")
        esize = size (expected,"*")
        [cnonan , cnumb] = mythrownan(computed)
        [enonan , enumb] = mythrownan(expected)
        if ( and(enonan == cnonan) & and(enumb == cnumb) ) then
            flag = %t
        else
            flag = %f
        end
    else
        if ( and ( computed == expected ) ) then
            flag = %t
        else
            flag = %f
        end
    end
    if ( flag == %t ) then
        errmsg = ""
    else
        // Change the message if the matrix contains more than one value
        if ( size(expected,"*") == 1 ) then
            estr = string(expected)
        else
            estr = "[" + string(expected(1)) + " ...]"
        end
        if ( size(computed,"*") == 1 ) then
            cstr = string(computed)
        else
            cstr = "[" + string(computed(1)) + " ...]"
        end
        errmsg = msprintf(gettext(..
        "%s: Assertion failed: expected = %s while computed = %s"), ..
        "Myassert_checkequal",estr,cstr)
        if ( lhs < 2 ) then
            // If no output variable is given, generate an error
            error ( errmsg )
        end
    end
endfunction

function [nonan,numb] = mythrownan(x)
    //
    //
    // Copyright (C) 2000 - INRIA - Carlos Klimann
    // Copyright (C) 2010 - DIGITEO - Michael Baudin
    //This  function  returns  in  vector  nonan  the  values
    //(ignoring the NANs) of a  vector or matrix x and in the
    //corresponding places of vector  numb the indexes of the
    //value.
    //
    //For  a  vector  or matrix  x,  [nonan,numb]=thrownan(x)
    //considers x, whatever his dimensions are, like a linear
    //vector (columns  first).
    //
    //
    [lhs,rhs]=argn(0)
    if rhs<>1 then error(msprintf(gettext("%s: Wrong number of input argument: %d expected.\n"),"thrownan",1)), end
    numb=find(bool2s(~isnan(x)))
    nonan=x(~isnan(x))
endfunction

function [flag,errmsg] = Myassert_checkfilesequal ( varargin )
  //   Check two files are equal.
  //
  // Calling Sequence
  //   flag = Myassert_checkfilesequal ( filecomp , fileref )
  //   flag = Myassert_checkfilesequal ( filecomp , fileref , compfun )
  //   [flag,errmsg] = Myassert_checkfilesequal ( ... )
  //
  // Parameters
  //   filecomp : a 1x1 matrix of strings, the computed file.
  //   fileref : a 1x1 matrix of strings, the reference file.
  //   compfun : a function or a list, the comparison function (default compfun = []). If no comparison function is used, the equality operator "==" is used. See below for details. 
  //   flag : a 1x1 matrix of boolean, %t if computed is close to expected, %f if not
  //   errmsg : a 1x1 matrix of strings, the error message. If flag==%t, then errormsg=="". If flag==%f, then errmsg contains the error message.
  //
  // Description
  //   Performs silently if the files are equal.
  //   Generates an error if filecomp or fileref do not exist.
  //   Generates an error if the content of the files are not equal.
  //
  //   If the files are not equal, 
  //   <itemizedlist>
  //   <listitem>if the errmsg output variable is not used, an error is generated,</listitem>
  //   <listitem>if the errmsg output variable is used, no error is generated.</listitem>
  //   </itemizedlist>
  //
  //   If the comparison function compfun is a function, it should have header areequal = compfun ( txtcomp , txtref ) 
  //   where txtcomp is the content of the computed file, txtref is the content of the reference file and areequal
  //   is a boolean. The areequal boolean is true if the two contents are equal.
  //   If compfun is a list, it should be list (cf,a1,a2,...), where cf is a comparison function, 
  //   and the arguments a1, a2, will be automatically be appended at the 
  //   end of the calling sequence of cf.
  //
  // Examples
  // //
  // // Prepare data for the tests
  // // fileref1 : three lines of text.
  // // filecomp1 : == fileref1
  // // filecomp2 : <> fileref1
  // fileref1 = fullfile(TMPDIR,"fileref.txt");
  // txt1 = [
  //   "Line #1"
  //   "Line #2"
  //   "Line #3"
  // ];
  // fd = mopen(fileref1,"w");
  // mputl(txt1,fd);
  // mclose(fd);
  // filecomp1 = fullfile(TMPDIR,"filecomp1.txt");
  // fd = mopen(filecomp1,"w");
  // mputl(txt1,fd);
  // mclose(fd);
  // filecomp2 = fullfile(TMPDIR,"filecomp2.txt");
  // txt2 = [
  //   "Line #1"
  //   "Line #4"
  //   "Line #3"
  // ];
  // fd = mopen(filecomp2,"w");
  // mputl(txt2,fd);
  // mclose(fd);
  //
  // // A test which pass
  // flag = Myassert_checkfilesequal ( filecomp1 , fileref1 )
  // [flag,errmsg] = Myassert_checkfilesequal ( filecomp1 , fileref1 )
  //
  // // Failure: filecomp2 <> fileref1
  // // Error generated
  // flag = Myassert_checkfilesequal ( filecomp2 , fileref1 )
  // // No error generated
  // [flag,errmsg] = Myassert_checkfilesequal ( filecomp2 , fileref1 )
  //
  // // Prepare data for the tests
  // // fileref2 == filecomp3, given that comment lines are ignored.
  // // fileref2 <> filecomp4, given that comment lines are ignored.
  // // Notice that the comments are inserted at different positions in the files:
  // // sometimes at the begining, sometimes in the middle.
  // fileref2 = fullfile(TMPDIR,"fileref2.txt");
  // txt = [
  //   "// bla 2"
  //   "Line #1"
  //   "// bla 2"
  //   "Line #2"
  //   "Line #3"
  // ];
  // fd = mopen(fileref2,"w");
  // mputl(txt,fd);
  // mclose(fd);
  // filecomp3 = fullfile(TMPDIR,"filecomp3.txt");
  // txt = [
  //   "Line #1"
  //   "// bla 5168"
  //   "Line #2"
  //   "Line #3"
  //   "// bla oups"
  // ];
  // fd = mopen(filecomp3,"w");
  // mputl(txt,fd);
  // mclose(fd);
  // filecomp4 = fullfile(TMPDIR,"filecomp4.txt");
  // txt = [
  //   "// bla 3"
  //   "Line #1"
  //   "Line #4"
  //   "// bla 5168"
  //   "Line #3"
  //   "// bla oups"
  // ];
  // fd = mopen(filecomp4,"w");
  // mputl(txt,fd);
  // mclose(fd);
  //
  // // A test with a comparison function which ignores comment lines.
  // function otxt = myfilter ( itxt )
  //   nr = size(itxt,"r")
  //   // This is the pattern for a comment line of the form "// blabla"
  //   pattern = "/\/\/.*/"
  //   k = 1
  //   for i = 1 : nr
  //     start = regexp(itxt(i),pattern)
  //     if ( start == [] ) then
  //       otxt(k) = itxt(i)
  //       k = k + 1
  //     end
  //   end
  // endfunction
  // function areequal = mycompfun ( ctxt , etxt )
  //   ctxt = myfilter ( ctxt )
  //   etxt = myfilter ( etxt )
  //   areequal = ( ctxt == etxt )
  // endfunction
  // //
  // // A test which pass
  // [flag,errmsg] = Myassert_checkfilesequal ( filecomp3 , fileref2 , mycompfun )
  // // A test which fails
  // [flag,errmsg] = Myassert_checkfilesequal ( filecomp4 , fileref2 , mycompfun )
  //
  // Authors
  //   Michael Baudin, 2010

  [lhs,rhs]=argn()
  if ( and ( rhs <> [ 2 3 ] ) ) then
    errmsg = sprintf ( gettext ( "%s: Unexpected number of input arguments : %d provided while %d to %d are expected.") , "Myassert_checkfilesequal" , rhs , 2 , 3 )
    error(errmsg)
  end
  //
  // Get input arguments
  filecomp = varargin(1)
  fileref = varargin(2)
  if ( rhs <= 2 ) then
    compfun = []
  else
    compfun = varargin(3)
  end
  //
  // Check types of variables
  if ( typeof(filecomp) <> "string" ) then
    errmsg = sprintf ( gettext ( "%s: Expected type ""%s"" for input argument %s #%d, but got %s instead.") , "Myassert_checkfilesequal" , "string" , "filecomp" , 1 , typeof(filecomp) )
    error(errmsg)
  end
  if ( typeof(fileref) <> "string" ) then
    errmsg = sprintf ( gettext ( "%s: Expected type ""%s"" for input argument %s #%d, but got %s instead.") , "Myassert_checkfilesequal" , "string" , "fileref" , 2 , typeof(fileref) )
    error(errmsg)
  end
  if ( compfun <> [] ) then
    if ( and ( typeof(compfun) <> [ "function" "list" ] ) ) then
      errmsg = sprintf ( gettext ( "%s: Expected type ""%s"" or ""%s"" for input argument %s #%d, but got %s instead.") , "Myassert_checkfilesequal" , "function" , "list" , "compfun" , 3 , typeof(compfun) )
      error(errmsg)
    end
  end
  //
  // Check sizes of variables
  if ( size(filecomp,"*") <> 1 ) then
    errmsg = sprintf ( gettext ( "%s: Wrong size for input argument #%d: %s: Expected size %d, but got %d instead.") , "Myassert_checkfilesequal" , 1 , "filecomp" , 1 , size(filecomp,"*") )
    error(errmsg)
  end
  if ( size(fileref,"*") <> 1 ) then
    errmsg = sprintf ( gettext ( "%s: Wrong size for input argument #%d: %s: Expected size %d, but got %d instead.") , "Myassert_checkfilesequal" , 2 , "fileref" , 1 , size(fileref,"*") )
    error(errmsg)
  end
  //
  // Test if both files exist on disk
  if ( fileinfo(filecomp) == [] ) then
    flag = %f
    errmsg = sprintf ( gettext ( "%s: Computed file ""%s"" does not exist on disk.") , "Myassert_checkfilesequal" , filecomp )
    if ( lhs < 2 ) then
      error ( errmsg )
    else
      return
    end
  end
  if ( fileinfo(fileref) == [] ) then
    flag = %f
    errmsg = sprintf ( gettext ( "%s: Reference file ""%s"" does not exist on disk.") , "Myassert_checkfilesequal" , fileref )
    if ( lhs < 2 ) then
      error ( errmsg )
    else
      return
    end
  end
  //
  // Open files
  [fdc,err] = mopen(filecomp,"r")
  if ( err <> 0 ) then
    flag = %f
    errmsg = sprintf ( gettext ( "%s: Unable to open computed file ""%s"".") , "Myassert_checkfilesequal" , filecomp )
    if ( lhs < 2 ) then
      error ( errmsg )
    else
      return
    end
  end
  [fdr,err] = mopen(fileref,"r")
  if ( err <> 0 ) then
    flag = %f
    errmsg = sprintf ( gettext ( "%s: Unable to open reference file ""%s"".") , "Myassert_checkfilesequal" , fileref )
    if ( lhs < 2 ) then
      error ( errmsg )
    else
      return
    end
  end
  // 
  // Get contents
  txtcomp = mgetl(fdc)
  txtref = mgetl(fdr)
  //
  // Compare contents
  if ( compfun <> [] ) then
    if ( typeof(compfun) == "function" ) then
      areeq = compfun ( txtcomp , txtref )
    else
      // compfun is a list
      cf = compfun(1)
      areeq = cf ( txtcomp , txtref , compfun(2:$) )
    end
  else
    areeq = ( txtcomp == txtref )
  end
  if ( areeq ) then
    flag = %t
    errmsg = ""
  else
    flag = %f
    errmsg = msprintf(gettext("%s: The content of computed file ""%s"" is different from the content of reference file ""%s""."), ..
      "Myassert_checkfilesequal",filecomp,fileref)
    // Do not generate the error now: let us close the files before!
  end
  // 
  // Close the files
  err=mclose(fdc)
  if ( err <> 0 ) then
    flag = %f
    errmsg = sprintf ( gettext ( "%s: Unable to close computed file ""%s"": error = %d.") , "Myassert_checkfilesequal" , filecomp , err )
    // It may happen that we overwrite the content of the errmsg varaiable.
    // For example, we are there, while the file contents were different.
    // We consider that that not being able to close the file is a bigger issue, 
  end
  err=mclose(fdr)
  if ( err <> 0 ) then
    errmsg = sprintf ( gettext ( "%s: Unable to close reference file ""%s"": error = %d.") , "Myassert_checkfilesequal" , fileref , err )
    // It may happen that we overwrite the content of the errmsg varaiable.
    // For example, we are there, while the file contents were different.
    // We consider that that not being able to close the file is a bigger issue, 
  end

  if ( ~flag & lhs < 2 ) then
    // If no output variable is given, generate an error
    error ( errmsg )
  end
endfunction

path = fullfile(csv_getToolboxPath(),"tests","unit_tests");

// =============================================================================
M = eye(3, 5);
//
filename = fullfile(TMPDIR,"M_1.csv");
csv_write(M, filename);
Myassert_checkfilesequal ( filename , fullfile(path,"M_1.csv") );
//
filename = fullfile(TMPDIR,"M_2.csv");
csv_write(M, filename, ascii(9));
Myassert_checkfilesequal ( filename , fullfile(path,"M_2.csv") );
//
filename = fullfile(TMPDIR,"M_3.csv");
csv_write(M, filename, " ", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"M_3.csv") );
//
filename = fullfile(TMPDIR,"M_4.csv");
csv_write(M, filename, ";", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"M_4.csv") );
// =============================================================================
N = [%nan , 1, %nan ; -%inf , %inf, 4];
//
filename = fullfile(TMPDIR,"N_1.csv");
csv_write(N, filename);
Myassert_checkfilesequal ( filename , fullfile(path,"N_1.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csv_write(N, filename, ascii(9));
Myassert_checkfilesequal ( filename , fullfile(path,"N_2.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csv_write(N, filename, " ", ",");
Myassert_checkfilesequal (filename , fullfile(path,"N_3.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csv_write(N, filename, ";", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"N_4.csv") );
// =============================================================================
K = eye(3, 2) + 0.1;
//
filename = fullfile(TMPDIR,"K_1.csv");
csv_write(K, filename);
Myassert_checkfilesequal ( filename , fullfile(path,"K_1.csv") );
//
filename = fullfile(TMPDIR,"K_2.csv");
csv_write(K, filename, ascii(9));
Myassert_checkfilesequal ( filename , fullfile(path,"K_2.csv") );
//
filename = fullfile(TMPDIR,"K_3.csv");
csv_write(K, filename, " ", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"K_3.csv") );
//
filename = fullfile(TMPDIR,"K_4.csv");
csv_write(K, filename, ";", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"K_4.csv") );
// =============================================================================
S = [
    "Allan",                  "2", "CORNET";
    "csv read/write toolbox", "3", "for scilab"
];
//
filename = fullfile(TMPDIR,"S_1.csv");
csv_write(S, filename, "|");
Myassert_checkfilesequal ( filename , fullfile(path,"S_1.csv") );
//
filename = fullfile(TMPDIR,"S_2.csv");
csv_write(S, filename, ascii(9));
Myassert_checkfilesequal ( filename , fullfile(path,"S_2.csv") );
//
filename = fullfile(TMPDIR,"S_3.csv");
csv_write(S, filename, "!", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"S_3.csv") );
//
filename = fullfile(TMPDIR,"S_4.csv");
csv_write(S, filename, ";", ",");
Myassert_checkfilesequal ( filename , fullfile(path,"S_4.csv") );
// =============================================================================
M = [%inf, %nan];
filename = fullfile(TMPDIR,"datas.csv");
csv_write(M, filename);
Myassert_checkfilesequal ( filename , fullfile(path,"datas.csv") );
//
// =============================================================================
//
// Configure the comments
M = [1:4] * 0.1;
comm = [
"// Copyright (C) DIGITEO"
"//  This file must be used under the terms of the CeCILL."
];
filename = fullfile(TMPDIR,"test.csv");
csv_write(M, filename,[],[],[],comm);
Mstr = mgetl(filename);
expected = [
"// Copyright (C) DIGITEO"
"//  This file must be used under the terms of the CeCILL."
"0.10000000000000001,0.20000000000000001,0.30000000000000004,0.40000000000000002"
];
Myassert_checkequal ( Mstr , expected );



