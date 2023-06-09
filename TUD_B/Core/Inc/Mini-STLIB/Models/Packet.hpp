#pragma once

#include <functional>
#include <stdint.h>
#include <string>
#include <vector>
#include <cstring>
#include <map>

extern uint32_t debugging_uint;

using namespace std;

template <class ContainerType>
concept Container = requires(ContainerType a, const ContainerType b)
{
    requires std::regular<ContainerType>;
    requires std::swappable<ContainerType>;
    requires std::destructible<typename ContainerType::value_type>;
    requires std::same_as<typename ContainerType::reference, typename ContainerType::value_type &>;
    requires std::same_as<typename ContainerType::const_reference, const typename ContainerType::value_type &>;
    requires std::forward_iterator<typename ContainerType::iterator>;
    requires std::forward_iterator<typename ContainerType::const_iterator>;
    requires std::signed_integral<typename ContainerType::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
ContainerType::iterator>::difference_type>;
    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
ContainerType::const_iterator>::difference_type>;
    { a.begin() };
    { a.end() };
    { b.begin() };
    { b.end() };
    { a.cbegin() };
    { a.cend() };
    { a.size() };
    { a.max_size() };
    { a.empty() };
};

template <class NotContainerType>
concept NotContainer = !Container<NotContainerType>;

template<typename... T>
class Field;

template<>
class Field<> {
    public:
    virtual void parse(uint8_t* ptr) = 0;
    virtual void unparse(uint8_t* ptr) = 0;
    virtual size_t get_size() = 0;
};

template<typename T> requires NotContainer<T>
class Field<T> : public Field<>{
    public:
    T* ptr;
    Field(T* ptr) : ptr(ptr) { }
    void parse(uint8_t* d)   { *this->ptr   = *((T*) d); }
    void unparse(uint8_t* d) { *((T*) d) = *this->ptr; }
    size_t get_size() { return sizeof(T); }
};


template<typename T> requires Container<T>
class Field<T> : public Field<>{
    public:
    T* ptr;
    Field(T* ptr) : ptr(ptr) { }
    void parse(uint8_t* d)   { memcpy(this->ptr->data(),d,this->ptr->size()); }
    void unparse(uint8_t* d) { memcpy(d,this->ptr->data(),this->ptr->size()); }
    size_t get_size() {
    	return this->ptr->size()*sizeof(typename T::value_type);
    }
};

class Packet {
    private:

    static map<uint16_t, Packet*> all_packets;

    public:
    size_t size = 0;
    uint16_t id;
    vector<Field<>*> fields;
    void (*callback)() = nullptr;

    template<typename Arg1, typename... Rest>
    Packet(uint16_t id, Arg1* arg1, Rest*... fields) : id(id) {
        build(arg1, fields...);
        Packet::all_packets[id] = this;
    }

    template<typename... T>
    Packet(uint16_t id, void (*callback)(), T*... fields) : id(id), callback(callback) {
        build(fields...);
        Packet::all_packets[id] = this;
    }

    template<typename Arg1, typename... Rest>
    void build(Arg1* arg1, Rest*... rest) {
    	size += sizeof(Arg1);
        Field<Arg1>* field = new Field<Arg1>(arg1);
        fields.push_back(((Field<>*) field));
        if constexpr(sizeof...(rest) == 0)
            return;
        else
            build(rest...);
    }

    void parse(uint8_t* ptr){
        uint8_t* ptr_temp = ptr;
        for(auto field : fields){
            field -> parse(ptr_temp);
            ptr_temp += field->get_size();
        }
    }

    void unparse(uint8_t* ptr){
        uint8_t* ptr_temp = ptr;
        for(auto field : fields){
            field -> unparse(ptr_temp);
            ptr_temp += field->get_size();
        }
    }

    static void process_packet(uint16_t id, uint8_t* data) {
        for(auto& entry : all_packets){
        	if(entry.second -> id == id){
                entry.second->parse(data);
                if(entry.second->callback != nullptr)
					entry.second->callback();
        	}
        }
    }
};
