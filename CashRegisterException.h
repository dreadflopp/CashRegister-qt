#ifndef CASHREGISTEREXCEPTION_H
#define CASHREGISTEREXCEPTION_H

#include<exception>
#include<string>
#include <utility>

class CashRegisterException: public std::exception {
private:
    std::string msg;
public:
    explicit CashRegisterException(std::string message): msg(std::move(message)) {}
    const char* what() { return msg.c_str(); }
};

class CRException_BadIdx: public CashRegisterException
{
public:
    explicit CRException_BadIdx(std::size_t badIndex): CashRegisterException("CRException_BadIdx: bad index " + std::to_string(badIndex)) {}
};

class CRException_NotANumber: public CashRegisterException
{
public:
    explicit CRException_NotANumber(const std::string& noNumber): CashRegisterException("CRException_NotANumber: " + noNumber + " is not a number.") {}
};

class CRException_elementNotFound: public CashRegisterException
{
public:
    explicit CRException_elementNotFound(std::size_t wrongId): CashRegisterException("CRException_elementNotFound: no item exists with the m_id " + std::to_string(wrongId)) {}
};

class CRException_badKey: public CashRegisterException
{
public:
    explicit CRException_badKey(std::size_t badKey): CashRegisterException("CRException_badKey: the following key is not unique: " + std::to_string(badKey) + ". The operation failed.") {}
};

#endif // CASHREGISTEREXCEPTION_H
