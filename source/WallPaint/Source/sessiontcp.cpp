/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "sessiontcp.hpp"

/*#######################################################################
#######################################################################*/
ogl::TCPSession::TCPSession(boost::asio::io_service& io_service)
  : socket_(io_service)
{
}

/*#######################################################################
#######################################################################*/
boost::asio::ip::tcp::socket& ogl::TCPSession::socket()
{
  return socket_;
}

/*#######################################################################
#######################################################################*/
void ogl::TCPSession::start()
{
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
    boost::bind(&TCPSession::handle_read, this,
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred)
  );
}

/*#######################################################################
#######################################################################*/
void ogl::TCPSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
  if (!error)
  {
    boost::asio::async_write(socket_,
      boost::asio::buffer(data_, bytes_transferred),
      boost::bind(&TCPSession::handle_write, this,
      boost::asio::placeholders::error)
    );
  }
  else
  {
    delete this;
  }
}

/*#######################################################################
#######################################################################*/
void ogl::TCPSession::handle_write(const boost::system::error_code& error)
{
  if (!error)
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
      boost::bind(&TCPSession::handle_read, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred)
    );
  }
  else
  {
    delete this;
  }
}
