/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "serverudp.hpp"

/*#######################################################################
#######################################################################*/
ogl::UDPServer::UDPServer(boost::asio::io_service& io_service, short port)
  : io_service_(io_service), socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
  socket_.async_receive_from(
    boost::asio::buffer(data_, max_length), sender_endpoint_,
    boost::bind(&UDPServer::handle_receive_from, this,
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred
    )
  );
}

/*#######################################################################
#######################################################################*/
ogl::UDPServer::~UDPServer()
{
  socket_.shutdown(boost::asio::ip::udp::socket::shutdown_both);
  socket_.close();
}

/*#######################################################################
#######################################################################*/
bool ogl::UDPServer::get_message(std::string& msg)
{
  bool result = false;
  mutex.lock();
  if (!msg_list.empty()) {
    msg = msg_list.front();
    msg_list.pop_front();
    result = true;
  }
  mutex.unlock();
  return result;
}

/*#######################################################################
#######################################################################*/
void ogl::UDPServer::print_messages()
{
  mutex.lock();
  std::cout << "msg_list: ";
  for (unsigned int i = 0; i < msg_list.size(); ++i) {
    std::cout << " " << msg_list.at(i);
  }
  std::cout << std::endl;
  mutex.unlock();
}

/*#######################################################################
#######################################################################*/
void ogl::UDPServer::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
  std::string msg;
  std::copy(data_, data_ + bytes_recvd, std::back_inserter(msg));
  std::cout << "Message: " << msg << std::endl;

  mutex.lock();
  msg_list.push_back(msg);
  mutex.unlock();

  if (!error && bytes_recvd > 0)
  {
    socket_.async_send_to(
      boost::asio::buffer(data_, bytes_recvd), sender_endpoint_,
      boost::bind(&UDPServer::handle_send_to, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred
      )
    );
  }
  else
  {
    socket_.async_receive_from(
      boost::asio::buffer(data_, max_length), sender_endpoint_,
      boost::bind(&UDPServer::handle_receive_from, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred
      )
    );
  }
}

/*#######################################################################
#######################################################################*/
void ogl::UDPServer::handle_send_to(const boost::system::error_code&, size_t)
{
  socket_.async_receive_from(
    boost::asio::buffer(data_, max_length), sender_endpoint_,
    boost::bind(&UDPServer::handle_receive_from, this,
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred
    )
  );
}
