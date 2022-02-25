// EPOS Component Declarations

#ifndef __stubs_h
#define __stubs_h

#include <architecture.h>
#include <syscall/message.h>

namespace EPOS::stubs {

using namespace S::U;

class Stubs_Common {
public:
    typedef _SYS::Message Message;

    Stubs_Common(int entity): _id(0), _entity(entity) {}

    template<typename ... Tn>
    long invoke(int _method, Tn ... an) {
        Message msg(_id, _entity, _method);
        msg.set_params(an ...);
        msg.act();
        return msg.result();
    }

private:
    long _id;
    int _entity;
};


class Display: public Stubs_Common {
public:
    Display(): Stubs_Common(Message::ENTITY::DISPLAY) {}
    void print(const char * string) { invoke(Message::PRINT, string); } 
};


} // Stubs 

#endif