/*
SWAMI KARUPPASWAMI THUNNAI
Author       : Visweswaran Nagasivam
Date         : 11.12.2017
Copyright(C) : 2017
License      : GPL v2.0
*/

#include "url.h"
#include<SFML\Network.hpp>

std::string URL::get_request(std::string url)
{
	sf::Http http(url);
	sf::Http::Request request;
	request.setMethod(sf::Http::Request::Get);
	sf::Http::Response result = http.sendRequest(request);
	return result.getBody();
}

std::string URL::post_request(std::string domain, std::string relative_path, std::string params)
{
	sf::Http http(domain);
	sf::Http::Request request(relative_path, sf::Http::Request::Post);
	request.setBody(params);
	sf::Http::Response response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		std::string body = response.getBody();
		return body;
	}
	return "";
}
