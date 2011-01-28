// =============================================================================
// Allan CORNET - DIGITEO - 2011
// =============================================================================
tlbxs = atomsGetInstalled();
if grep(tlbxs, 'csv_readwrite') <> [] then
  atomsLoad("csv_readwrite");
else
  root_path = getenv('CSV_READWRITE_PATH', '');
  if root_path <> '' then 
    exec(root_path + 'loader.sce'); 
  end 
end
// =============================================================================
r = csv_stringtodouble("-Nani");
if real(r) <> 0 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("Nani");
if real(r) <> 0 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("+Nani");
if real(r) <> 0 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("-Infi");
if real(r) <> 0 then pause, end
if imag(r) <> -%inf then pause, end
// =============================================================================
r = csv_stringtodouble("Infi");
if real(r) <> 0 then pause, end
if imag(r) <> %inf then pause, end
// =============================================================================
r = csv_stringtodouble("+Infi");
if real(r) <> 0 then pause, end
if imag(r) <> %inf then pause, end
// =============================================================================
r = csv_stringtodouble("Nan-Nani");
if ~isnan(real(r)) then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("Nan-2i");
if ~isnan(real(r)) then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("-Nan-2i");
if ~isnan(real(r)) then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("+Nan-2i");
if ~isnan(real(r)) then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("Nan-Infi");
if ~isnan(real(r)) then pause, end
if imag(r) <> -%inf then pause, end
// =============================================================================
r = csv_stringtodouble("-Inf-2i");
if real(r) <> -%inf then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("+Inf-2i");
if real(r) <> %inf then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("Inf-2i");
if real(r) <> %inf then pause, end
if imag(r) <> -2 then pause, end
// =============================================================================
r = csv_stringtodouble("Inf-Infi");
if real(r) <> %inf then pause, end
if imag(r) <> -%inf then pause, end
// =============================================================================
r = csv_stringtodouble("Inf+Infi");
if real(r) <> %inf then pause, end
if imag(r) <> %inf then pause, end
// =============================================================================
r = csv_stringtodouble("1+Nani");
if real(r) <> 1 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("1-Nani");
if real(r) <> 1 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("-1-Nani");
if real(r) <> -1 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("1+Infi");
if real(r) <> 1 then pause, end
if imag(r) <> %inf then pause, end
// =============================================================================
r = csv_stringtodouble("1-Infi");
if real(r) <> 1 then pause, end
if imag(r) <> -%inf then pause, end
// =============================================================================
if ~isnan(csv_stringtodouble("Nan")) then pause, end
if ~isnan(csv_stringtodouble("-Nan")) then pause, end
if ~isnan(csv_stringtodouble("+Nan")) then pause, end
if csv_stringtodouble("-Inf") <> -%inf then pause, end
if csv_stringtodouble("Inf") <> %inf then pause, end
if csv_stringtodouble("+Inf") <> %inf then pause, end
if csv_stringtodouble("+i") <> %i  then pause, end
if csv_stringtodouble("-i") <> -%i  then pause, end
if csv_stringtodouble("+j") <> %i  then pause, end
if csv_stringtodouble("-j") <> -%i  then pause, end
if csv_stringtodouble("i") <> %i  then pause, end
if csv_stringtodouble("j") <> %i  then pause, end
if csv_stringtodouble(" 3 + 2i") <> complex(3,2) then pause, end
if csv_stringtodouble(" 3 - 2i") <> complex(3,- 2) then pause, end
if csv_stringtodouble(" -3 + 2i") <> complex(-3,2) then pause, end
if csv_stringtodouble(" 3 - 2i") <> complex(3,-2) then pause, end
if csv_stringtodouble("- 3 - 2i") <> complex(-3,-2) then pause, end
if csv_stringtodouble("+3 - 2i") <> complex(+3,-2) then pause, end
if csv_stringtodouble("+3 + 2i") <> complex(3,2) then pause, end
if csv_stringtodouble("+3 - 2i") <> complex(3,-2) then pause, end
if csv_stringtodouble("4+i") <> complex(4,1) then pause, end
if csv_stringtodouble("4-i") <> complex(4,-1) then pause, end
if csv_stringtodouble("-4+i") <> complex(-4,1) then pause, end
if csv_stringtodouble("-4-i") <> complex(-4,-1) then pause, end
if csv_stringtodouble("+4+i") <> complex(4,1) then pause, end
if csv_stringtodouble("+4-i") <> complex(4,-1) then pause, end
if csv_stringtodouble("10")  <> 10 then pause, end
if csv_stringtodouble("+10") <> 10 then pause, end
if csv_stringtodouble("-10") <> -10 then pause, end
if csv_stringtodouble("10.") <> 10 then pause, end
if csv_stringtodouble("+10.") <> 10 then pause, end
if csv_stringtodouble("-10.") <> -10 then pause, end
if csv_stringtodouble(".4") <> .4 then pause, end
if csv_stringtodouble("+.4") <> .4 then pause, end
if csv_stringtodouble("-.4") <> -.4 then pause, end
if csv_stringtodouble("10.4") <> 10.4 then pause, end
if csv_stringtodouble("+10.4") <> 10.4 then pause, end
if csv_stringtodouble("-10.4") <> -10.4 then pause, end
if csv_stringtodouble("10+10j") <> complex(10, 10) then pause, end
if csv_stringtodouble("+10+10j") <> complex(10, 10) then pause, end
if csv_stringtodouble("-10+10j") <> complex(-10, 10) then pause, end
if csv_stringtodouble("10.+10j") <> complex(10, 10) then pause, end
if csv_stringtodouble("+10.+10j") <> complex(10, 10) then pause, end
if csv_stringtodouble("-10.+10j") <> complex(-10, 10) then pause, end
if csv_stringtodouble("10.4+10j") <> complex(10.4, 10) then pause, end
if csv_stringtodouble("+10.4+10j") <> complex(10.4, 10) then pause, end
if csv_stringtodouble("-10.4+10j") <> complex(-10.4, 10) then pause, end
if csv_stringtodouble(".4+10j") <> complex(.4, 10) then pause, end
if csv_stringtodouble("+.4+10j") <> complex(.4, 10) then pause, end
if csv_stringtodouble("-.4+10j") <> complex(-.4, 10) then pause, end
if csv_stringtodouble("10+10.4j") <> complex(10, 10.4) then pause, end
if csv_stringtodouble("10.4+10.4j") <> complex(10.4, 10.4) then pause, end
if csv_stringtodouble("+10.4+10.4j") <> complex(10.4, 10.4) then pause, end
if csv_stringtodouble("+10.4-10.4j") <> complex(10.4, -10.4) then pause, end
if csv_stringtodouble("1i") <> %i then pause, end
if csv_stringtodouble("1j") <> %i then pause, end
if csv_stringtodouble("+1j") <> %i then pause, end
if csv_stringtodouble("+1i") <> %i then pause, end
if csv_stringtodouble("-1j") <> complex(0,-1) then pause, end
if csv_stringtodouble("-1i") <> complex(0,-1) then pause, end
if csv_stringtodouble("10j") <> complex(0,10) then pause, end
if csv_stringtodouble("+10j") <> complex(0,10) then pause, end
if csv_stringtodouble("-10j") <> complex(0, -10) then pause, end
if csv_stringtodouble("10.j") <> complex(0,10) then pause, end
if csv_stringtodouble("+10.j") <> complex(0,10) then pause, end
if csv_stringtodouble("-10.j") <> complex(0,-10) then pause, end
if csv_stringtodouble(".4j") <> complex(0,.4) then pause, end
if csv_stringtodouble("+.4j") <> complex(0,.4) then pause, end
if csv_stringtodouble("-.4j") <> complex(0,-.4) then pause, end
if csv_stringtodouble("10.4j") <> complex(0,10.4) then pause, end
if csv_stringtodouble("+10.4j") <> complex(0,10.4) then pause, end
if csv_stringtodouble("-10.4j") <> complex(0,-10.4) then pause, end
if csv_stringtodouble("4e2") <> 400 then pause, end
if csv_stringtodouble("-4e2") <> -400 then pause, end
if csv_stringtodouble("+4e2") <> 400 then pause, end
if csv_stringtodouble("0.4e2") <> 40 then pause, end
if csv_stringtodouble("3e2 + 2e3i") <> complex(300, 2000) then pause, end
if csv_stringtodouble("3e2 - 2e3i") <> complex(300, -2000) then pause, end
if getos() == "Windows" then
if csv_stringtodouble("3e2 - 2d3i") <> complex(300, -2000) then pause, end
if csv_stringtodouble("3e2 + 2d3i") <> complex(300, 2000) then pause, end
if csv_stringtodouble("3d2 + 2e3i") <> complex(300, 2000) then pause, end
if csv_stringtodouble("3d2 - 2e3i") <> complex(300, -2000) then pause, end
if csv_stringtodouble("3d2 + 2d3i") <> complex(300, 2000) then pause, end
if csv_stringtodouble("3d2 - 2d3i") <> complex(300, -2000) then pause, end
end
// =============================================================================
r = csv_stringtodouble("3e2 - blabli");
if real(r) <> 300 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
r = csv_stringtodouble("3e2 - blabli", %t);
if real(r) <> 300 then pause, end
if ~isnan(imag(r)) then pause, end
// =============================================================================
if execstr("r = csv_stringtodouble(""3e2 - blabli"", %f);", "errcatch") <> 999 then pause, end
if lasterror() <> msprintf(_("%s: can not convert data.\n"), "csv_stringtodouble") then pause, end
// =============================================================================
