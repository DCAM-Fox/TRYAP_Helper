#ifndef MTT_MESSAGING
#define MTT_MESSAGING

#include <cinttypes>
#include <queue>
#include <shared_mutex>
#include <condition_variable>

// Multi-thread messaging.
namespace mtt
{
    // Типы данных.
    typedef uint64_t mid_t; // ID сообщения.

    // Структура-шаблон для сообщений.
    struct Message
    {
        mid_t id;
    };

    // Интерфейс для межпоточного общения путём сообщений.
    template<typename T>
    class Messaging
    {
    public:
        Messaging()
        {
        }
        Messaging(const Messaging& messaging)
        {
            messages = messaging.messages;
        }

        // Отправить сообщение.
        void send(T message)
        {
            std::unique_lock<std::shared_mutex> write_lock(messages_mutex);
            {
                std::unique_lock<std::shared_mutex> write_lock2(id_counter_mutex);
                message.id = id_counter++;
            }
            messages.push(message);
            messages_condition.notify_one();
        }

        // Ожидать сообщение.
        void wait()
        {
            std::shared_lock<std::shared_mutex> read_lock(messages_mutex);
            while (messages.empty())
            { messages_condition.wait(read_lock); }
        }

        // Принять сообщение.
        T receive()
        {
            T message;
            std::unique_lock<std::shared_mutex> write_lock(messages_mutex);
            while (messages.empty())
            { messages_condition.wait(write_lock); }

            // Получение верхнего сообщения.
            message = messages.front();
            messages.pop();
            return message;
        }

        // Попытка принять сообщение.
        bool try_receive(T& message)
        {
            std::unique_lock<std::shared_mutex> write_lock(messages_mutex);
            if (!messages.empty())
            {
                // Получение верхнего сообщения.
                message = messages.front();
                messages.pop();
                return true;
            }
            else { return false; }
        }

        // Обновление счётчика до максимального из текущего и предоставленного значения.
        void update_id_counter(mid_t value)
        {
            std::unique_lock<std::shared_mutex> write_lock(id_counter_mutex);
            if (value > id_counter) { id_counter = value; }
        }

        Messaging<T>& operator=(const Messaging<T>& messaging)
        {
            messages = messaging.messages;
            return *this;
        }

    protected:
        // Сообщения.
        std::queue<T> messages;
        std::shared_mutex messages_mutex;
        std::condition_variable_any messages_condition;

        // Счётчик ID.
        mid_t id_counter = 0;
        std::shared_mutex id_counter_mutex;

    private:

    };
}

#endif

