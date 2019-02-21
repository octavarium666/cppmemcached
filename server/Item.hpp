#pragma once

#include "noncopyable.hpp"
#include <memory>

class Item;
typedef std::shared_ptr<Item> ItemPtr;
typedef std::shared_ptr<const Item> ConstItemPtr;

class Item : noncopyable
{
public:

    static ItemPtr makeItem(std::string keyArg,
                            uint32_t flagsArg,
                            int exptimeArg,
                            int valueLen,
                            uint64_t casArg) {
        return std::make_shared<Item>(keyArg, flagsArg, exptimeArg, valueLen, casArg);
    }

    Item(std::string keyArg,
        uint32_t flagsArg,
        int exptimeArg,
        int valueLen,
        uint64_t casArg);


    ~Item() {
        ::free(data);
    };

    std::string getKey() const {
        return std::string(data);
    }

    uint32_t getFlags() const {
        return flags;
    }

    int getRelExptime() const {
        return relExptime;
    }

    int getValueLen() const {
        return valueLen;
    }

    uint64_t getCas() const {
        return cas;
    }


private:
    uint8_t             keylen;
    const uint32_t      flags;
    const int           relExptime;
    const int           valueLen;
    int                 receivedBytes;
    uint64_t            cas;
    size_t              hash;
    char*               data;
};
