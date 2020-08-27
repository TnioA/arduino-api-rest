#ifndef _FACTORYJSON_H
#define _FACTORYJSON_H

#include <assert.h>
#include <string.h>
#include <ctype.h>

class FactoryJson {
    private:
        String content;

    public: 
        FactoryJson();
        String SingleResponse(String key, String value);
        String MultipleResponse(String key, char params[20][100], bool isObject);
};

#endif