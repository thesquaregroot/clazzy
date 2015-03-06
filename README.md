clazzy
======

Clazzy is a code generation library, which focuses on representing
object-oriented projects in a language-agnostic fashion.  In doing so, clazzy
makes it possible to, given appropriate input, generate source-code skeletons
in a variety of languages.

In a manner similar to how many machine-code compilers generate assembly rather
than directly translating high-level code in binary, clazzy operates by
generating an intermediate representation that can be used as a bridge between
various forms of input and output.

Clazzy is an free (as in speech) C++11 program licensed under the GNU 
General Public License (GPL) version 3.  It is important to note that although
any derivative works of this program must also be free (per the GPL),
any generated code belongs to the copy-right holder of the input (i.e.
the user).

Dependencies
------------
Clazzy is written in C++11 and depends upon flex (or flex++) for lexical
analysis and cmake for its build process.

For more information see the README file.

