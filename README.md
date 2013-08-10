clazzy
======

A semi-natural-language code generation platform for projects that need 
similar data structures in multiple programming languages.

Clazzy is an free (as in speech) C++11 program licensed under the GNU 
General Public License (GPL) version 3.  It is important to note that although
any derivative works of this program must also be free (per the GPL),
any generated code belongs to the copy-right holder of the input (i.e.
the user).

The executable itself is a "compiler" from a its own high level class 
definition language into unimplemented class and function definitions
in one or more actual programming languages. Using Clazzy, you can 
define a similar structure for use in multiple application, on multiple 
platforms, and only having to worry about writing the bodies of functions.


Architecture
------------
Clazzy is developed as a hand-written recursive-descent parser, 
fed by tokens by code generated with flex, which passes metadata on
to one or more code generators for programming language structures.

The grammar and token definitions for Clazzy can be found in the 
accompanying README file, as well as the list of supported langauges 
and features.

Dependencies
------------
Clazzy is written in C++11 and has no external dependancies. Some of 
the code is generated with flex, a lexical analyser, but the generated 
code should compile with any C++11 compiler.

Though the Makefile used is fairly general, the build process is still 
somewhat geared more for a UNIX-based system, and only officially tested 
in a GNU/Linux environment.

Clazzy also makes use of makedepend for class dependancy tracking.

