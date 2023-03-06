#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

std::string base64_encode(const std::string &input)
{
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    size_t input_length = input.length();
    size_t encoded_length = 4 * ((input_length + 2) / 3);

    std::string encoded(encoded_length, '=');

    size_t i, j;
    for (i = 0, j = 0; i < input_length;)
    {
        uint32_t octet_a = i < input_length ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    return encoded;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

bool send_to_wecom(const std::string &text,
                   const std::string &wecom_cid,
                   const std::string &wecom_aid,
                   const std::string &wecom_secret,
                   const std::string &wecom_touid = "@all")
{
    std::string get_token_url =
        "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=" + wecom_cid +
        "&corpsecret=" + wecom_secret;

    CURL *curl = curl_easy_init();
    if (!curl)
    {
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, get_token_url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_cleanup(curl);
    std::cout << response << std::endl;
    json json_response = json::parse(response);

    std::string access_token = json_response.value("access_token", "");
    std::cout << "Access Token: " << access_token << std::endl;
    if (access_token.empty())
    {
        return false;
    }

    std::string send_msg_url =
        "https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token=" +
        access_token;

    curl = curl_easy_init();
    if (!curl)
    {
        return false;
    }

    // std::string encoded_text = base64_encode(text);
    // std::string json_str = R"({"touser": "@all", "agentid": )" + wecom_aid + R"(, "msgtype": "text", "text": {"content": "不需要编码吧"}})";
    json data = {
        {"touser", wecom_touid},
        {"agentid", wecom_aid},
        {"msgtype", "text"},
        {"text", {{"content", text}}},
        {"duplicate_check_interval", 600}
    };
    std::string json_str = data.dump(0).c_str();
    std::replace(json_str.begin(), json_str.end(), '\n', ' ');
    std::cout << json_str.c_str() << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, send_msg_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    std::cout << response << std::endl;

    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_cleanup(curl);

    return true;
}

int main()
{
    // Example usage
    std::string wecom_cid = "";
    std::string wecom_aid = "";
    std::string wecom_secret = "";
    std::string wecom_touid = "@all";
    std::string text = "Hello, World!";

    bool result =
        send_to_wecom(text, wecom_cid, wecom_aid, wecom_secret, wecom_touid);

    if (result)
    {
        std::cout << "Message sent successfully.\n";
    }
    else
    {
        std::cout << "Failed to send message.\n";
    }

    return 0;
}
