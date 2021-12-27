#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iterator>
using namespace std;

int main(int argc, char *argv[])
{
    vector<string> sources;
    char *date;

    // parsing command line arguments
    if (argc < 4)
    {
        fprintf(stderr, "Too little arguments\n");
        return 1;
    }
    else if (argc > 4)
    {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "-d")
            {
                if (i + 1 < argc)
                {
                    date = argv[++i];
                }
                else
                {
                    fprintf(stderr, "This flag requires one argument as a parameter\n");
                    return 1;
                }
            }
            else
            {
                sources.push_back(argv[i]);
            }
        }
        // read inputfile
        ifstream in(sources[0]);

        deque<string> input_processed;

        // process inputfile without comments
        for (string line; getline(in, line);)
        {
            if (line.empty())
                continue;
            input_processed.push_back(line);
        }

        in.close();

        char *cookie_name, *cookie_timestamp;
        map<char *, int> cookie_map;

        char *time, *temp;
        int max_count = 0;
        for (int i = 0; i < input_processed.size(); ++i)
        {
            cookie_name = strtok((char *)input_processed[i].c_str(), ",");
            cookie_timestamp = strtok(NULL, ",");
            temp = strtok(cookie_timestamp, "T");
            time = strtok(NULL, "T");
            if (strcmp(date, cookie_timestamp)==0)
            {
                cookie_map[cookie_name]++;
                max_count = max(max_count, cookie_map[cookie_name]);
            }
            // printf("%s : %s T %s\n", cookie_name, cookie_timestamp, time);
        }
        
        map<char *, int>::iterator it = cookie_map.begin();

        while (it != cookie_map.end())
        {
            if(it->second==max_count){
                printf("%s\n", it->first);
            }
            it++;
        }
        return 0;
    }
}