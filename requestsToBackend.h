#ifndef AUTH_REQUESTS_H
#define AUTH_REQUESTS_H

#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace json = boost::json;
using tcp = net::ip::tcp;

extern std::string host;
extern std::string port;
extern std::string target;
extern std::string login;
extern std::string password;
extern std::string api_url;

json::value send_request(const json::value& json_obj, const std::string& url, const std::string& method);

struct AuthUser {
    std::string email;
    std::string password; // in md5 hash
    std::string token;
    json::value get_token();
    json::value get_post_text(std::string request);
};

#endif /* AUTH_REQUESTS_H */
