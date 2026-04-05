#include "lib.hpp"

std::string encode(std::vector<int> array, std::string name_array)
{
    std::string result;
    size_t index = 1;
    std::for_each(array.begin(), array.end(), [&](int value)
                  {
        result += std::format("{}[{}]={}", name_array, index++, value);
        if (index <= array.size())
        {
            result += "&";
        } });
    return result;
}

char *encode(int *array, size_t size_array, const char *name_array)
{

    std::vector<int> new_array(size_array);
    std::copy_n(array, size_array, new_array.begin());

    std::string new_name_array(name_array);

    std::string formatted_string = encode(new_array, new_name_array);

    char *result = new char[formatted_string.size() + 1]{};
    std::copy(formatted_string.begin(), formatted_string.end(), result);

    return result;
}

char *encode(int *array, size_t size_array, const char *name_array, size_t size_name)
{

    std::vector<int> new_array(size_array);
    std::copy_n(array, size_array, new_array.begin());

    std::string new_name_array(name_array, size_name);

    std::string formatted_string = encode(new_array, new_name_array);

    char *result = new char[formatted_string.size() + 1]{};
    std::copy(formatted_string.begin(), formatted_string.end(), result);

    return result;
}

int is_urlencoded(std::string &str)
{
    size_t pos = str.find('[', 0);
    size_t pos_next;
    if (pos == str.npos)
    {
        return 0;
    }
    int index = 1;
    std::string name_array = str.substr(0, pos);
    pos = 0;
    while (pos < str.size())
    {
        pos_next = str.find('[', pos);
        // std::cout << str.substr(pos, pos_next - pos) << std::endl;
        if (str.substr(pos, pos_next - pos) != name_array)
        {
            return 0;
        }

        pos = pos_next + 1;

        pos_next = str.find(']', pos);
        if (pos_next == str.npos)
        {
            return 0;
        }
        std::string ind_str = str.substr(pos, pos_next - pos);
        // std::cout << ind_str << std::endl;
        int ind;
        try
        {
            ind = std::stol(ind_str);
            if (!std::isdigit(static_cast<unsigned char>(ind_str[ind_str.size() - 1])))
            {
                return 0;
            }
        }
        catch (std::exception &e)
        {
            return 0;
        }
        if (ind != index++)
        {
            return 0;
        }

        pos = pos_next + 2;

        if (str[pos - 1] != '=')
        {
            return 0;
        }

        pos_next = str.find('&', pos);
        pos_next = (pos_next == str.npos ? str.size() : pos_next);
        std::string val_str = str.substr(pos, pos_next - pos);

        try
        {
            std::stol(val_str);
            if (!std::isdigit(static_cast<unsigned char>(val_str[val_str.size() - 1])))
            {
                return 0;
            }
        }
        catch (std::exception &e)
        {
            return 0;
        }
        if (pos_next == str.npos)
        {
            return 1;
        }
        pos = pos_next + 1;
    }

    return 1;
}

std::vector<int> decode(std::string urlencoded, std::string &name_array)
{
    if (!is_urlencoded(urlencoded))
    {
        throw std::invalid_argument("Is not urlencoded");
    }

    std::vector<int> result;

    size_t pos = 0;
    while (pos < urlencoded.size())
    {
        size_t equal_pos = urlencoded.find('=', pos);
        if (equal_pos == std::string::npos)
        {
            break;
        }

        size_t amp_pos = urlencoded.find('&', equal_pos + 1);

        size_t value_end = (amp_pos == std::string::npos) ? urlencoded.size() : amp_pos;
        size_t value_start = equal_pos + 1;

        std::string value_str = urlencoded.substr(value_start, value_end - value_start);

        int number = std::stoi(value_str);
        result.push_back(number);

        pos = (amp_pos == std::string::npos) ? urlencoded.length() : amp_pos + 1;
    }
    name_array = urlencoded.substr(0, urlencoded.find('['));
    return result;
}

int *decode(const char *urlencoded, size_t &size_array, char *&name_array_c)
{
    std::string urlencoded_str(urlencoded);
    std::vector<int> result_vec;
    std::string name_array;
    try
    {
        result_vec = decode(urlencoded_str, name_array);
    }
    catch (std::invalid_argument &e)
    {
        throw e;
    }

    int *result = new int[result_vec.size()];
    std::copy(result_vec.begin(), result_vec.end(), result);

    size_array = result_vec.size();
    name_array_c = new char[name_array.size() + 1]{};
    std::copy(name_array.begin(), name_array.end(), name_array_c);
    return result;
}

int *decode(const char *urlencoded, size_t size, size_t &size_array, char *&name_array_c)
{
    std::string urlencoded_str(urlencoded, size);

    std::vector<int> result_vec;
    std::string name_array;
    try
    {
        result_vec = decode(urlencoded_str, name_array);
    }
    catch (std::invalid_argument &e)
    {
        throw e;
    }

    int *result = new int[result_vec.size()];
    std::copy(result_vec.begin(), result_vec.end(), result);
    size_array = result_vec.size();
    name_array_c = new char[name_array.size() + 1]{};
    std::copy(name_array.begin(), name_array.end(), name_array_c);
    return result;
}
