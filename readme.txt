CSV read/write toolbox

Purpose
-------

The purpose of this module is to read and write
Comma Separated Values (CSV) data files.
The goal of this toolbox is to improve the flexibility, consistency and speed of
CSV reading and writing with respect to Scilab built-in
write_csv and read_csv functions.

On a 1000-by-1000 matrix, we observed a 73x improvement of the
speed in writing and 3x improvement in reading.

Features
--------

 * csv_default : Get or set defaults for csv files.
 * csv_getToolboxPath : Returns the path to the current module.
 * csv_read : Read comma-separated value file
 * csv_stringtodouble : Convert a matrix of strings to a matrix of doubles.
 * csv_textscan : Read comma-separated value in a matrix of strings
 * csv_write : Write comma-separated value file

Authors
-------

Copyright (C) 2010 - 2011 - DIGITEO - Allan Cornet
Copyright (C) 2011 - DIGITEO - Michael Baudin

Licence
-------

This toolbox is released under the CeCILL_V2 licence :

http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt






