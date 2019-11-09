/***************************************************************************
 *   Copyright (C) 2019 by Robert Middleton.                               *
 *   robert.middleton@rm5248.com                                           *
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

#ifndef DBUSCXX_DEMANGLE_H
#define DBUSCXX_DEMANGLE_H

#include <cxxabi.h>

namespace DBus {
  /**
   * demangle the given type.  Used for debugging purposes.
   */
  template <typename T>
  std::string demangle(){
#ifdef DBUS_CXX_CXA_DEMANGLE
    int status;
    char* demangled = abi::__cxa_demangle( typeid(arg1).name(), nullptr, nullptr, &status );
    std::string arg1_name( demangled );
    free( demangled );
    if( status < 0 ){
        arg1_name = typeid(T).name();
    }
#else
    std::string arg1_name = typeid(T).name();
#endif

    return arg1_name;
  }

} /* namespace DBus */

#endif
