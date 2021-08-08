/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TCP_SESSION_HPP
#define OGL_TCP_SESSION_HPP

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace ogl 
{
  class TCPSession 
  {
    public:
      TCPSession(boost::asio::io_service& io_service);
      boost::asio::ip::tcp::socket& socket();
      void start();

    private:
      void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
      void handle_write(const boost::system::error_code& error);

      boost::asio::ip::tcp::socket socket_;
      enum { max_length = 1024 };
      char data_[max_length];
  };
}

#endif