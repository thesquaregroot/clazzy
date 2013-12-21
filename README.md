clazzy
======

A semi-natural-language code generation platform that can generate data 
structures in multiple programming languages.

Clazzy is an free (as in speech) C++11 program licensed under the GNU 
General Public License (GPL) version 3.  It is important to note that although
any derivative works of this program must also be free (per the GPL),
any generated code belongs to the copy-right holder of the input (i.e.
the user).

The executable itself is a "compiler" from a its own high-level class 
definition language into (typically) unimplemented class and function 
definitions in one or more actual programming languages. Using Clazzy, you 
can define a similar structure for use in multiple application, on multiple 
platforms, and only having to worry about writing the bodies of functions.


Architecture
------------
Clazzy is developed as a hand-written recursive-descent parser that makes use
of a flex++-generated lexical analyzer.  The generated metadata is then used
by one or more code generators for various commonly usedprogramming languages.

The grammar and token definitions for clazzy can be found in the 
accompanying README file, as well as the list of supported langauges 
and features.

Dependencies
------------
Clazzy is written in C++11 and depends upon flex (or flex++) for lexical
analysis and cmake for its build process.

For more information see the README file.

