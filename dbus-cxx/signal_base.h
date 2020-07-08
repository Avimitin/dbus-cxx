/***************************************************************************
 *   Copyright (C) 2009,2010 by Rick L. Vinyard, Jr.                       *
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
#include <dbus-cxx/path.h>
#include <dbus-cxx/dbus-cxx-config.h>
#include <stddef.h>
#include <memory>
#include <string>

#ifndef DBUSCXX_SIGNALBASE_H
#define DBUSCXX_SIGNALBASE_H

namespace DBus
{
  class Connection;
  class Message;

  /**
   * @defgroup signals Signals 
   * Classes for interacting with signals(sending and receiving)
   */

  /**
   * Base class of all signals(proxy and adapter).  This is required to interact with signals
   * in a generic manner, as the actual signal implementation class is templated.
   *
   * @ingroup signals
   * @ingroup local
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class signal_base
  {
    protected:
      
      signal_base(const std::string& path, const std::string& interface_name, const std::string& name);

      signal_base(const std::string& interface_name, const std::string& name);

      signal_base(std::shared_ptr<Connection> connection, const std::string& path, const std::string& interface_name, const std::string& name);

      signal_base(std::shared_ptr<Connection> connection, const std::string& interface_name, const std::string& name);

    public:
      virtual ~signal_base();

      std::shared_ptr<Connection> connection();

      void set_connection(std::shared_ptr<Connection> connection);

      const std::string& sender() const;

      void set_sender(const std::string& s);

      const std::string& interface_name() const;

      void set_interface(const std::string& i);

      const std::string& name() const;

      void set_name( const std::string& n );

      const Path& path() const;

      void set_path(const std::string& s);

      const std::string& destination() const;

      void set_destination(const std::string& s);

      /**
       * This method is needed to be able to create a duplicate of a child
       * capable of parsing their specific template type message.
       */
//      virtual std::shared_ptr<signal_base> clone() = 0;

      /** Returns a DBus XML description of this interface */
      virtual std::string introspect(int space_depth=0) const { return std::string(); }

      virtual std::string arg_name(size_t i) { return std::string(); }

      virtual void set_arg_name(size_t i, const std::string& name) { }

    protected:
      bool handle_dbus_outgoing( std::shared_ptr<const Message> );

  private:
      class priv_data;

      DBUS_CXX_PROPAGATE_CONST(std::unique_ptr<priv_data>) m_priv;
  };

}

#endif
