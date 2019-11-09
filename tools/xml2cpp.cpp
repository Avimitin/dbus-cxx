/***************************************************************************
 *   Copyright (C) 2007,2008,2009 by Rick L. Vinyard, Jr.                  *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the dbus-cxx library.                            *
 *                                                                         *
 *   The dbus-cxx library is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The dbus-cxx library is distributed in the hope that it will be       *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#include <popt.h>
#include <sstream>
#include <fstream>
#include <dbus-cxx.h>
#include <cstring>
#include <expat.h>
#include <stack>
#include <cppgenerate/class.h>

#include "code-generator.h"

int main( int argc, const char** argv )
{

  poptContext opt_context;
  int verbose=0;
  int make_proxy=0;
  int make_adapter=0;
  int output_to_file = 0;
  const char* xml_file=NULL;
  const char* file_prefix = "";
  const char* output_dir = ".";
  int c;
  DBus::CodeGenerator generator;
  std::string outputDirString;

  struct poptOption option_table[] = {
    { "xml",          'x', POPT_ARG_STRING, &xml_file,       0, "The file containing the XML specification" },
    //{ "prefix",       'p', POPT_ARG_STRING, &file_prefix,    0, "A prefix to place on all output files" },
    { "file",         'f', POPT_ARG_NONE,   &output_to_file, 0, "Output to files [default=no]" },
    { "output_dir",       'o', POPT_ARG_STRING, &output_dir,    0, 
         "The output directory for files(only if outputting to files)[default=.]" },
    { "proxy",          0, POPT_ARG_NONE,   &make_proxy,     0, "Make a proxy class for the specification.  "
         "Proxies are used when you want to talk with a DBus service [default=no]" },
    { "adapter",        0, POPT_ARG_NONE,   &make_adapter,   0, "Make an adapter class for the specification.  "
         "Adapters are used when you want to implement a service [default=no]" },
    { "verbose",        0, POPT_ARG_NONE,   &verbose,        0, "Verbose printing of output" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0 }
  };

  opt_context = poptGetContext(NULL, argc, argv, option_table, 0 );

  while ( (c = poptGetNextOpt(opt_context)) >= 0) { }

  if ( not (poptPeekArg(opt_context) == NULL) or not (make_proxy or make_adapter) or not xml_file )
  {
    poptPrintUsage(opt_context, stderr, 0);
    return 1;
  }

  poptFreeContext(opt_context);

  std::string specification;

    // open the file and load into specification
    std::ifstream fin;
    char buffer[1025];
    size_t n;
    fin.open( xml_file );
    if( fin.fail() ){
      std::cerr << "ERROR: Can't open file " << xml_file << std::endl;
      return 1;
    }
    while ( ! fin.eof() )
    {
      fin.read(buffer, 1024);
      n = fin.gcount();
      if ( n > 0 )
      {
        buffer[n] = '\0';
        specification += buffer;
      }
    }
    fin.close();

    generator.setXML( specification );

    if( !generator.parse() ){
        return 1;
    }

    outputDirString = std::string( output_dir );
    if( outputDirString.back() != '/' ){
        outputDirString += "/";
    }

    if( make_proxy ){
        generator.generateProxyClasses( output_to_file, outputDirString );
    }

    if( make_adapter ){
        generator.generateAdapterClasses( output_to_file, outputDirString );
    }

    return 0;
}
