#ifndef QUEUEEXCEPTION_H
#define QUEUEEXCEPTION_H

// DO NOT CHANGE THIS FILE.

class QueueException {
public:
    QueueException(std::string err) {
        error = err;
    }
    
    std::string error;
};

#endif //QUEUEEXCEPTION_H
