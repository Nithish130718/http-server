
#include "HttpRequest.hpp"

const std::string& HTTPRequest::method() const noexcept {
    return _method;
}

const std::string& HTTPRequest::target() const noexcept {
    return _target;
}

const std::string& HTTPRequest::version() const noexcept {
    return _version;
}

const std::string& HTTPRequest::body() const noexcept {
    return _body;
}

bool HTTPRequest::hasHeader(std::string_view name) const noexcept {
    return _headers.find(std::string(name)) != _headers.end();
}

std::string_view HTTPRequest::header(std::string_view name) const noexcept {
    auto it = _headers.find(std::string(name));
    if (it == _headers.end()) return {};
    return it -> second;
}

const std::unordered_map<std::string, std::string>&
HTTPRequest::headers() const noexcept {
    return _headers;
}