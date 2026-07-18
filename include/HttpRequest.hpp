
#pragma once 

#include <string>
#include <string_view>
#include <unordered_map>

class HTTPParser;

class HTTPRequest {
    public:
        HTTPRequest() = default;
        ~HTTPRequest() = default;

        [[nodiscard]] const std::string& method() const noexcept;
        [[nodiscard]] const std::string& target() const noexcept;
        [[nodiscard]] const std::string& version() const noexcept;
        [[nodiscard]] const std::string& body() const noexcept;
        [[nodiscard]] bool hasHeader(std::string_view name) const noexcept;
        [[nodiscard]] std::string_view header(std::string_view name) const noexcept;
        [[nodiscard]] const std::unordered_map<std::string, std::string>& 
            headers() const noexcept;
        
    private:
        std::string _method;
        std::string _target;
        std::string _version;
        std::unordered_map<std::string, std::string> _headers;
        std::string _body;
        friend class HTTPParser;
};