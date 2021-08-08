/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "servertcp.hpp"

/*#######################################################################
#######################################################################*/
ogl::TCPServer::TCPServer(boost::asio::io_service& io_service, short port)
  : io_service_(io_service), acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
  start_accept();
}

/*#######################################################################
#######################################################################*/
void ogl::TCPServer::start_accept()
{
  TCPSession* new_session = new TCPSession(io_service_);
  acceptor_.async_accept(new_session->socket(),
    boost::bind(&TCPServer::handle_accept, this, new_session,
    boost::asio::placeholders::error)
  );
}

/*#######################################################################
#######################################################################*/
void ogl::TCPServer::handle_accept(ogl::TCPSession* new_session, const boost::system::error_code& error)
{
  if (!error)
  {
    new_session->start();
  }
  else
  {
    delete new_session;
  }

  start_accept();
}
