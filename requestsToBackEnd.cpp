
#include <nlohmann/json.hpp>
#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>


//const static std::string AP
namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
namespace json = boost::json;       // from <boost/json.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


std::string host = "example.com";
std::string port = "80";
std::string target = "/api/login";
std::string login = "your_login";
std::string password = "your_password";
std::string api_url = "";

json::value send_request(const json::value& json_obj, const std::string& url, const std::string& method) {
    try {
        // Разбор URL
        std::string scheme, host, port, target;
        if (url.substr(0, 8) == "https://") {
            scheme = "https";
            host = url.substr(8);
        } else if (url.substr(0, 7) == "http://") {
            scheme = "http";
            host = url.substr(7);
        } else {
            throw std::runtime_error("Invalid URL scheme");
        }

        auto pos = host.find('/');
        if (pos != std::string::npos) {
            target = host.substr(pos);
            host = host.substr(0, pos);
        } else {
            target = "/";
        }

        pos = host.find(':');
        if (pos != std::string::npos) {
            port = host.substr(pos + 1);
            host = host.substr(0, pos);
        } else {
            port = (scheme == "https") ? "443" : "80";
        }

        // Создаем IO-контекст
        net::io_context ioc;

        // Разрешаем хост
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, port);

        // Создаем и подключаемся к сокету
        beast::tcp_stream stream(ioc);
        stream.connect(results);

        // Сериализация JSON
        std::string json_str = json::serialize(json_obj);

        // Создаем HTTP-запрос
        int version = 11; // HTTP 1.1
        http::request<http::string_body> req{http::string_to_verb(method), target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "application/json");
        req.body() = json_str;
        req.prepare_payload();

        // Отправляем HTTP-запрос
        http::write(stream, req);

        // Буфер для чтения ответа
        beast::flat_buffer buffer;

        // Объект для хранения ответа
        http::response<http::dynamic_body> res;

        // Читаем HTTP-ответ
        http::read(stream, buffer, res);

        // Закрываем сокет
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // Ошибка при закрытии
        if (ec && ec != beast::errc::not_connected) {
            throw beast::system_error{ec};
        }

        // Десериализация ответа JSON
        auto body = beast::buffers_to_string(res.body().data());
        json::value response_json = json::parse(body);

        return response_json;

    } catch (std::exception const& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return nullptr;
    }
}



// struct AuthUser{
//     std::string email;
//     std::string password;// in md5 hash
//     std::string token;
//     json::value get_token(){
//         json::value json_obj;
//         json_obj["email"] = this->email;
//         json_obj["password"] =  this->password;
//         json::value response_json = send_request(json_obj, "https://" + host + ":" + port + target, "POST");
//         this->token = response_json["token"].as_string();
//         return response_json;
//     };
//     json::value get_post_text(std::string request){
//         json::value json_obj;
//         json_obj["token"] = this->token;
//         json_obj["request"] =  request;
//         json::value response_json = send_request(json_obj, api_url+"/text_request", "POST");
//         this->token = response_json["token"].as_string();
//         return response_json;
//     };


// };

