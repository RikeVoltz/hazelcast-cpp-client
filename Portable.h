//
//  Portable.h
//  Server
//
//  Created by sancar koyunlu on 1/10/13.
//  Copyright (c) 2013 sancar koyunlu. All rights reserved.
//

#ifndef Server_Portable_h
#define Server_Portable_h

#include <iostream>
class PortableWriter;
class PortableReader;

class Portable{
public:
    virtual int getClassId() = 0; //TODO
    
    virtual void writePortable(PortableWriter* writer) throw(std::ios_base::failure) = 0; //TODO
    
    virtual void readPortable(PortableReader* reader) throw(std::ios_base::failure) = 0; //TODO
    
    virtual int getType() = 0; //TODO
};

#endif