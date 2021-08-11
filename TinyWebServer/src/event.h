﻿/**
 * @author Ho 229
 * @date 2021/7/28
 */

#ifndef EVENT_H
#define EVENT_H

#include <string>

/**
 * @brief Abstract Event
 */
class Event
{
public:
    enum Type
    {
        AcceptEvent,
        ExceptionEvent
    };

    virtual ~Event() = default;

    virtual Type type() const = 0;

protected:
    explicit Event() {}
};

/**
 * @brief Exception Event
 */
class ExceptionEvent : public Event
{
public:
    enum Error
    {
        UnknownError,
        SocketLoadFailed,
        ListenFailed
    };

    explicit ExceptionEvent(const Error err, const std::string& message = {})
        : m_error(err), m_message(message) {}

    virtual Type type() const override { return Event::ExceptionEvent; }

    Error error() const { return m_error; }

    std::string message() const { return m_message; }

private:
    const Error m_error;
    const std::string m_message;
};


/**
 * @brief Accept Event
 */
class AcceptEvent : public Event
{
public:
    enum Protocol
    {
        HTTP,
        HTTPS
    };

    explicit AcceptEvent(const Protocol& protocol,
                         const std::string& hostName,
                         const std::string& port)
        : m_protocol(protocol), m_hostName(hostName), m_port(port) {}

    virtual Type type() const override { return Event::AcceptEvent; }

    Protocol protocol() const { return m_protocol; }

    std::string hostName() const { return m_hostName; }
    std::string port() const { return m_port; }

private:
    const Protocol m_protocol;
    const std::string m_hostName;
    const std::string m_port;
};

#endif // EVENT_H
