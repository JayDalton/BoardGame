/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_UDP_SERVER_HPP
#define OGL_UDP_SERVER_HPP

#include <deque>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace ogl 
{
  class UDPServer
  {
    private:
      boost::asio::io_service& io_service_;
      boost::asio::ip::udp::socket socket_;
      boost::asio::ip::udp::endpoint sender_endpoint_;
      enum { max_length = 1024 };
      char data_[max_length];
      std::deque<std::string> msg_list;
      boost::mutex mutex;

    public:
      UDPServer(boost::asio::io_service& io_service, short port);
      ~UDPServer();
      void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);
      void handle_send_to(const boost::system::error_code&, size_t);
      bool get_message(std::string& msg);
      void print_messages();
  };
}

#endif