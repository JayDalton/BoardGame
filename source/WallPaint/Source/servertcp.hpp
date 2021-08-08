/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TCP_SERVER_HPP
#define OGL_TCP_SERVER_HPP

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "sessiontcp.hpp"

namespace ogl 
{
  class TCPServer 
  {
    public:
      TCPServer(boost::asio::io_service& io_service, short port);

    private:
      void start_accept();
      void handle_accept(ogl::TCPSession* new_session, const boost::system::error_code& error);
      boost::asio::io_service& io_service_;
      boost::asio::ip::tcp::acceptor acceptor_;
  };
}

#endif